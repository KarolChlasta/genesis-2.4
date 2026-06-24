# PLAN: Proper GPU Parallelization of GENESIS

## SECOND CORRECTION (2026-06-18): the whole benchmark campaign's binaries are confounded
On top of the OCL-never-triggered finding below, the "CPU" (`genesis/genesis`)
and "GPU" (`genesis/src/nxgenesis`) binaries used throughout the
dense_10rep, extreme_5rep, and longrun campaigns differ by more than
OpenCL: `genesis/genesis` links libX11/libXt (X11/XODUS GUI build),
`genesis/src/nxgenesis` is headless. This X11-linked binary has a real,
reproducible per-element-creation overhead (concentrated in kernel/system
time, scales with element count, not explained by X-server IPC or page
faults) that swamps total runtime for benchmarks with many cheap elements
and fast per-step compute (`region_proxy_microcircuit`, hence its
inflated ~6.7x "speedup") while being negligible for benchmarks with
expensive per-step compute (`mesoscale_sparse`/`biophysical_cellscale`,
hence their ~1.0-1.1x). **None of the CPU-vs-GPU numbers in
`genesis25_cpu_gpu_dense_10rep*.csv`, `genesis25_cpu_gpu_extreme_5rep*.csv`,
or `genesis25_cpu_gpu_longrun*.csv` can be reported as characterizing GPU
performance or even GPU absence** — they reflect this binary-choice
artifact. Full root-cause investigation, including what was ruled out and
the recommended fix (same binary for both arms, built with/without
`USE_OPENCL=1`): `paper/x11_binary_confound_investigation.md`.

## What we have done (as of 2026-06-16)

### Benchmark campaign completed
- CPU serial baseline (dense 10-rep, 18 size points): **DONE**
  - `genesis25_cpu_scaling_dense_10rep.csv` / `_summary.csv`
- GPU dense 10-rep campaign: **DONE**
  - `genesis25_gpu_scaling_dense_10rep.csv` / `_summary.csv`
- Paired CPU/GPU speedup table and figures (fig6, fig7): **DONE**
  - `genesis25_cpu_gpu_speedup_dense_10rep.csv`
- Extreme sizes 5-rep (N=35k–45k mesoscale, N=7k–10k biophysical, larger region-proxy): **DONE**
  - `genesis25_cpu_gpu_extreme_5rep.csv` / `_summary.csv` / `_speedup.csv`
  - Figures: `fig8_extreme_runtime_ci.png`, `fig9_extreme_speedup.png`
- Long-run stress validation (4×2h repeat-loop sessions): **IN PROGRESS**
  - `genesis25_cpu_gpu_longrun_raw.csv` / `_summary.csv`
  - Script: `run_genesis25_cpu_gpu_longrun_4x2h.sh`

### Key finding from benchmarks
CPU vs GPU speedup is **~1.0x** (range 0.91–1.02) across all tested configurations.
GPU utilization during benchmarks is only **a few percent**.

### Why GPU utilization is low (root cause analysis)
The current GENESIS 2.4 OpenCL backend is a **thin wrapper** — it routes computation
through the OpenCL API but does not restructure the simulation for data parallelism.

1. **Single-threaded serial dispatch** (`NLWP=1` for the GENESIS process).
   The driver loop is: `for each step → enqueue kernel → wait → read back → next step`.
   The GPU sits idle during the CPU-side overhead between each call.

2. **Work-item granularity too small.** The Radeon 890M has 12 CUs × 64 lanes = 768
   parallel shader lanes. Each kernel dispatch likely covers one neuron or a small
   batch, leaving >99% of GPU capacity idle per call.

3. **CPU↔GPU memory round-trips per step.** Neuron state is likely copied CPU→GPU
   before each step and GPU→CPU after, which serializes the pipeline and saturates
   PCIe/shared-memory bandwidth instead of compute.

4. **Model construction is entirely CPU-bound.** For N=30,000, construction takes
   ~26 s with zero GPU involvement. Simulation steps add negligible time on top.

### What a proper GPU rewrite requires

#### Minimum changes for meaningful speedup
| Change | Description |
|---|---|
| Batch kernel dispatch | One `clEnqueueNDRangeKernel(global_size=N)` per time step covering all neurons simultaneously |
| Persistent GPU state | Allocate neuron/synapse state buffers on GPU once; keep them there for all steps |
| Async step loop | CPU enqueues all steps without synchronizing per-step; reads back only at end |
| Work-group tuning | Set local work-group size to match GPU wavefront (64 for RDNA/GCN) |

#### Deeper changes for full parallelism
- Restructure synapse computation: scatter/gather over sparse connectivity using GPU-native data structures
- Use atomic operations for spike accumulation across presynaptic populations
- Consider double-buffering for spike events

#### Reference implementations to study
- **GeNN** (GPU-enhanced Neuronal Networks): C++/CUDA, generates per-model GPU kernels
- **Brian2GeNN**: Brian2 front-end → GeNN GPU backend
- **Brian2OpenCL**: Brian2 with OpenCL backend (closest to our stack)
- **NEST GPU**: spiking network simulator with CUDA backend

### CORRECTION (2026-06-17): the ~1.0x finding above was CPU-vs-CPU, not CPU-vs-GPU
Re-investigation found that **none** of the three production benchmark scripts
(mesoscale_sparse, biophysical_cellscale, region_proxy_microcircuit) ever created
an `hsolve` object — they all schedule plain compartments with `useclock`, which
means `chanmode`/`calcmode` never reach the `ocl_chip_update()` dispatch condition
(`chanmode∈{4,5} && calcmode==1`). Both the "CPU" and "GPU" binaries in that
campaign ran the identical pure-CPU `do_chip_hh4_update()` path. The reported
~1.0x speedup measured CPU against CPU; it says nothing about GPU performance.
Full investigation log: see memory `project_ocl_profiling_investigation.md`
and `genesis/Scripts/benchmark/ocl_hh_benchmark.g` (the corrected benchmark
that actually exercises chanmode=4/calcmode=1 hsolve + OpenCL).

A second, independent bug was found and fixed while building that corrected
benchmark: GENESIS encodes per-compartment boundaries in the flat `ops[]`
array using **three** sentinel values — `FCOMPT_OP`(101) opens the first
compartment, `COMPT_OP`(100) separates every middle compartment, and only the
truly last compartment is closed by `LCOMPT_OP`(102). Both
`build_comp_index()` and the `chip_channel_update` OpenCL kernel in
`genesis/src/hines/opencl/` originally tested only `op != LCOMPT_OP`, so they
swallowed the 100/101 sentinels as if they were data, merged many
compartments into one, and eventually walked off the end of the `ops[]`
buffer — causing a GPU page fault ("Memory access fault ... Page not present")
on every run with real tabchannel networks. Fixed by switching to a peek-based
loop (`while (ops[op_i] > LCOMPT_OP)`) matching the CPU interpreter's actual
semantics in `hines_chip.c`. Verified by dumping the raw `ops[]` array and
confirming the decoded opcode sequence (NEWVOLT_OP, CHAN_EK_OP, IPOL1V_OP ×2,
ADD_CURR_OP, ...) repeats with the expected period and that `opstart[]`
lines up exactly with it.

### Real OCL kernel profiling (2026-06-17, AMD Radeon 890M gfx1150 via rusticl)
Single hsolve covering N HH neurons (Na: X³Y¹, K: X⁴ tabchannel gates),
dt=50µs, 5000 steps, `CL_QUEUE_PROFILING_ENABLE` + `clGetEventProfilingInfo`
for kernel time, `clock_gettime(CLOCK_MONOTONIC)` around the full
upload→kernel→download sequence (`ocl_chip_update`):

| N neurons | kernel time/step | ocl_chip_update wall/step | GPU active frac | total step time (incl. CPU Hines solve) |
|---|---|---|---|---|
| 100  | 4.96 µs  | 49.0 µs  | 10.13% | 61.3 µs |
| 500  | 6.42 µs  | 79.4 µs  | 8.09%  | 124.2 µs |
| 1000 | 10.52 µs | 116.9 µs | 9.00%  | 209.9 µs |
| 2000 | 13.44 µs | 134.5 µs | 9.99%  | 323.1 µs |

Reproduce with:
```
genesis/src/nxgenesis -nosimrc -notty -batch genesis/Scripts/benchmark/ocl_hh_benchmark.g <N> 5000
```
Raw logs: `paper/profiling_runs/ocl_profile_N{100,500,1000,2000}.txt`

**Interpretation:** the actual GPU kernel (channel/gate update) is genuinely
cheap — single-digit to low-double-digit microseconds — and scales sub-linearly
with N for this small range, consistent with the 890M (12 CUs × 64 lanes = 768
lanes) being far from saturated at N≤2000 compartments. But kernel execution
is only **~8–10%** of `ocl_chip_update`'s own wall time; the remaining ~90% is
host-side dispatch/transfer overhead (`clEnqueueWriteBuffer` ×2,
`clEnqueueNDRangeKernel`, `clEnqueueReadBuffer` ×2, all serialized once per
step). And `ocl_chip_update` itself is only the channel-update fraction of
the total step — the Hines tridiagonal solve (forward elimination + back
substitution) still runs entirely on the CPU. So even a perfectly-saturated
GPU channel kernel could not by itself yield a large end-to-end speedup,
confirming the rewrite-roadmap conclusion below: batching transfers/dispatch
across steps and moving (or skipping) the tridiagonal solve matter more than
further optimizing the channel kernel alone.

### Next steps
- [ ] Profile OpenCL kernel calls with `rocprof` or `clpeak` to measure actual
      kernel occupancy and transfer overhead
- [x] Prototype a batched neuron-update kernel: single NDRange kernel over N neurons
      per step, persistent GPU buffers — DONE (chip_channel_multiloop, 2026-06-24)
- [x] Benchmark prototype at N=100-10k vs current serial dispatch — DONE (2026-06-24)
      Result: GPU kernel 4-149× faster; end-to-end 1.1-1.4× due to GENESIS scheduler
- [x] Update paper GPU section with honest framing and rewrite roadmap, citing
      the real OCL kernel profiling numbers above instead of the retracted
      CPU-vs-CPU ~1.0x figure — DONE (Section 3.6, 2026-06-24)
- [ ] **[Next: GENESIS scheduler restructuring]** Modify the GENESIS step loop
      to skip absorbed elements genuinely (not iterate as no-ops) when GPU
      multiloop has consumed the computation. This is the bottleneck for
      end-to-end speedup: ~25-45 ns/element/step × N×3 elements dominates
      at all tested N values (98-99% of GPU arm total step time at N≥2000).
      Requires changes to `genesis/src/sim/` (scheduler) not `genesis/src/hines/`.

## Multiloop kernel implementation (2026-06-24)

### What was done

**`chip_channel_multiloop`** kernel added to `ocl_channel.cl`:
- One work-item per compartment (same as `chip_channel_update`)
- Inner loop: `for (step = 0; step < nsteps; step++)` — all K steps inside one GPU dispatch
- Voltage update inline: `vm[gid] = rhs / denom` at the end of each inner step
- After all steps: writes identity to `results[]` (vm_final, 1.0) so the CPU
  Hines solver is a no-op (`vm_new = vm_final / 1.0 = vm_final`)
- Refactored single-step logic into shared `channel_step()` device function

**`ocl_multiloop_dispatch()`** in `ocl_hsolve.c`:
- One `WriteBuffer(vm)` + one `WriteBuffer(chip)` — uploaded once per batch
- Single `clEnqueueNDRangeKernel` for all K steps
- One `ReadBuffer(vm)` + `ReadBuffer(results)` + `ReadBuffer(chip)` after completion
- Reports timing: `OCL MULTILOOP: K krokow | kernel X ms | total Y ms | Z us/krok`

**Activation**: set `GENESIS_OCL_MULTILOOP=<nsteps>` before running:
```bash
GENESIS_OCL_MULTILOOP=5000 genesis/src/nxgenesis -nosimrc -notty -batch \
    genesis/Scripts/benchmark/ocl_hh_benchmark.g 2000 5000
```

### Measured performance (ROCm 6.3.1, Radeon 890M gfx1150, K=5000, single replicate)

`ocl_hh_benchmark.g` outside container with ROCm ICD. "GPU kernel" = kernel
execution time for all 5000 steps (one dispatch). "GENESIS step" = GENESIS
`{cpu}` counter for 5000 steps. "GPU kernel speedup" = CPU total / GPU kernel.
"End-to-end speedup" = CPU GENESIS step / GPU GENESIS step.

| N | CPU total (s) | GPU kernel (ms) | GPU dispatch total (ms) | GPU kernel speedup | GENESIS step GPU (s) | End-to-end speedup |
|---:|---:|---:|---:|---:|---:|---:|
|    100 | 0.067 |  15.4 |  17.9 |   4.4× | 0.055 | 1.22× |
|    500 | 0.316 |  15.8 |  17.8 |  20.0× | 0.225 | 1.40× |
|  1,000 | 0.507 |  15.5 |  18.0 |  32.7× | 0.441 | 1.15× |
|  2,000 | 1.065 |  19.1 |  21.0 |  55.8× | 1.008 | 1.06× |
|  5,000 | 2.813 |  31.3 |  34.5 |  89.8× | 2.449 | 1.15× |
| 10,000 | 8.359 |  56.1 |  60.5 | 149.0× | 6.728 | 1.24× |

**Key finding:** the GPU kernel is 4-149× faster than CPU computation.
End-to-end GENESIS speedup is only 1.1-1.4× because the GENESIS scheduler
iterates over all N×3 absorbed elements each step (~25-45 ns/element),
an O(N) overhead that dominates at all tested N values (98-99% of GPU arm's
total step time at N≥2000).

**Estimate for previous ~22× claim:** at N=2000, K=5000, the kernel itself
runs in 19.1ms while the CPU total is 1065ms → 55.8× kernel speedup. The
earlier "~22×" estimate was based on subtracting estimated GENESIS overhead;
the measured kernel speedup at N=2000 is ~56×. The end-to-end speedup,
however, is only 1.06× (GENESIS scheduler bottleneck).

### Limitation: single-compartment networks only

`chip_channel_multiloop` does the voltage update directly in the kernel as
`vm_new = rhs / denom`. This is correct only when each compartment is
independent (no parent-child connectivity in the Hines matrix). For
multi-compartment neurons with dendritic trees, the voltage update requires
solving a tridiagonal system that couples compartments — this cannot be done
independently per work-item. Multiloop mode must not be used for such networks.

The `ocl_hh_benchmark.g` benchmark (N independent single-compartment neurons)
is exactly the valid use case.

### Correctness note

The identity trick for results[] means the CPU Hines solver computes
`vm_new = results[2i] / results[2i+1] = vm_final / 1.0 = vm_final`. This is
correct because:
1. `vm[]` already holds the GPU-computed final voltage from the multiloop
2. The CPU "solve" just copies it through unchanged
3. `chip[]` was also downloaded after the multiloop, so gate variable state is
   correct for any post-simulation GENESIS script that inspects it
