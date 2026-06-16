# PLAN: Proper GPU Parallelization of GENESIS

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

### Paper framing (current honest position)
The current results should be reported as:
> "The GENESIS 2.4 OpenCL execution path was validated on AMD Radeon 890M via
> rusticl/Mesa. Observed CPU/GPU wall-clock speedup was ~1.0x (range 0.91–1.02)
> across all tested configurations, indicating that the current serial dispatch
> model does not leverage GPU data parallelism. GPU utilization remained at a
> few percent. Achieving meaningful GPU acceleration requires restructuring the
> simulation kernel for batched data-parallel execution."

### Next steps
- [ ] Profile OpenCL kernel calls with `rocprof` or `clpeak` to measure actual
      kernel occupancy and transfer overhead
- [ ] Prototype a batched neuron-update kernel: single NDRange kernel over N neurons
      per step, persistent GPU buffers
- [ ] Benchmark prototype at N=10k, 30k, 100k vs current serial dispatch
- [ ] If prototype shows >2x speedup, design full rewrite of the GENESIS step loop
- [ ] Update paper GPU section with honest framing and rewrite roadmap
