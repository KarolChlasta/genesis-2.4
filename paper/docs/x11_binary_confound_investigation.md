# Investigation: the CPU-vs-GPU benchmark binaries differ by more than OpenCL

Date: 2026-06-18

## Summary

Every paired CPU/GPU benchmark in this repository (`genesis25_cpu_gpu_dense_10rep*`,
`genesis25_cpu_gpu_extreme_5rep*`, `genesis25_cpu_gpu_longrun*`) defines:

```
CPU = genesis/genesis        # built via the default "genesis" Makefile target
GPU = genesis/src/nxgenesis  # built via the "nxgenesis" target, with USE_OPENCL=1
```

`ldd` shows these binaries differ in more than OpenCL support:

```
$ ldd genesis/genesis | grep -i x11
        libXt.so.6 => ...
        libX11.so.6 => ...

$ ldd genesis/src/nxgenesis | grep -i opencl
        libOpenCL.so.1 => ...
```

`genesis/genesis` is the default build with the X11/XODUS GUI toolkit linked
in. `genesis/src/nxgenesis` is the headless ("non-X") build. Combined with
the finding in `paper/PLAN_gpu_rewrite.md` / the OCL profiling investigation
that **none of the three production benchmark scripts ever create an
`hsolve` object** (so `ocl_chip_update()` is never called by *either*
binary, regardless of how it was built), this means the entire "CPU vs GPU"
comparison reported in this repository's benchmark CSVs to date is actually
a comparison between **two different CPU builds** — not CPU vs GPU.

This document records how that was diagnosed and root-caused.

## Background: how the discrepancy was first noticed

The `extreme_5rep` campaign showed wildly inconsistent "speedup" depending on
which benchmark was run:

| benchmark | reported CPU/GPU speedup |
|---|---|
| `mesoscale_sparse_benchmark` | ~1.08–1.10x |
| `biophysical_cellscale_benchmark` | ~0.85–1.00x |
| `region_proxy_microcircuit_benchmark` | **~6.6–6.7x** |

A genuine GPU effect should not produce a 6.7x speedup on the *cheapest*,
fastest-per-step benchmark while showing ~1.0x on the others — if anything,
GPU parallelism advantages tend to show up more under heavier per-step
compute, not less. This pattern was the trigger for the investigation below.

## Step 1: rule out OpenCL/GPU compute

Already established independently (see the OCL profiling investigation):
none of `mesoscale_sparse_benchmark.g`, `biophysical_cellscale_benchmark.g`,
or `region_proxy_microcircuit_benchmark.g` create an `hsolve` element with
`chanmode=4`/`calcmode=1`. `ocl_chip_update()` is therefore never invoked by
either the "CPU" or the "GPU" binary in this campaign. Whatever produces the
6.7x gap, it isn't the GPU.

## Step 2: rule out pure process-startup overhead

Timed a trivial no-op script (`echo quit`) 20 times per binary using the
exact flags the runner scripts use (`-nosimrc -notty -batch`, no `-nox`):

```
genesis (X11):      mean ≈ 7.3 ms/run
nxgenesis (headless): mean ≈ 4.3 ms/run
```

A ~3ms gap cannot explain the 60+ ms gaps observed in real runs (e.g.
`region_proxy_microcircuit_benchmark` at 2,000 elements: 78ms vs 13ms).

## Step 3: isolate construction time from simulation-step time

`region_proxy_microcircuit_benchmark.g` was truncated to a "construction-only"
variant — everything up to (but not including) `reset`/`step`, ending in
`quit` — and timed with `/usr/bin/time -v` at two network sizes:

| elements (Ex+Inh cells) | `genesis` (X11) elapsed | `nxgenesis` (headless) elapsed | `genesis` sys time | `nxgenesis` sys time |
|---|---|---|---|---|
| 2,000  (40×40 + 20×20) | 0.04 s | 0.01 s | 0.03 s | 0.00 s |
| 8,000  (80×80 + 40×40) | 0.20 s | 0.02 s | 0.16 s | 0.00 s |

Two things stand out:

1. **The gap is almost entirely in construction**, not in the simulation
   step loop. For the full script at 2,000 elements (2,000 steps), total
   elapsed time was 78ms (X11) vs 13ms (headless) — and construction alone
   already accounted for 40ms vs 10ms of that.
2. **The gap scales with element count.** Going from 2,000 to 8,000 elements
   (4x) took the `genesis` (X11) construction time from 0.04s to 0.20s (5x)
   while `nxgenesis` (headless) only grew from 0.01s to 0.02s (2x). The
   overhead is per-`create`/`setfield`/`addmsg` command, not a fixed
   one-time cost.
3. **The overhead is concentrated in *system* time** (kernel-attributed CPU
   time), not user time: 0.16s system time for `genesis` at 8,000 elements,
   versus ~0.00s for `nxgenesis`.

This single mechanism explains the whole campaign's inconsistent pattern:
`region_proxy_microcircuit` builds thousands of small elements but spends
very little time per simulation step (~15–40 µs/step), so the
construction-phase X11-vs-headless gap dominates total runtime and produces
an inflated 6.7x "speedup." `mesoscale_sparse`/`biophysical_cellscale` build
comparable numbers of elements but spend ~1.75 ms/step on the much larger
dense connectivity, so the same fixed/scaling construction-phase gap is
swamped by step-loop cost, producing the ~1.0–1.1x "speedup" that was
previously (and incorrectly) read as "GPU acceleration isn't happening, as
expected for a thin wrapper."

## Step 4: rule out two plausible mechanisms

- **Live X-server IPC.** Re-ran the 8,000-element construction-only test
  with `DISPLAY` unset entirely. Timing was **identical** (0.16s system
  time, 0.20s elapsed) to the `DISPLAY=:0` case. If the overhead came from
  blocking on real X-server socket round-trips, removing a valid display
  should have changed the result — it didn't. The XODUS/X11 toolkit clearly
  initializes (it prints `Starting XODUS 2.0` unconditionally) but does not
  appear to depend on display reachability for this cost.
- **Memory allocation / page faults.** `/usr/bin/time -v` minor page fault
  counts at 8,000 elements were nearly identical between binaries (4,786 for
  `genesis` vs 4,540 for `nxgenesis`) — a ~250-fault difference is far too
  small (each minor fault costs low microseconds) to account for 160ms of
  system time.

## What remains unresolved

The *exact* syscall(s) responsible were not identified. `strace` is not
installed in this environment, and `perf stat`/`perf record` fail with
`perf_event_paranoid=4` (no permission for tracepoints or even basic
hardware/software performance counters without root). Relaxing that setting
was not done in this investigation (would require root and a kernel sysctl
change, out of scope without explicit request).

What is established with high confidence: the overhead is real,
reproducible, scales with the number of element-creation commands, is
concentrated in kernel (system) time, and is tied to linking
`libX11`/`libXt` — independent of whether a live, reachable X display is
present.

## Implication for the paper

Every CPU-vs-GPU number collected so far in this repository
(`genesis25_cpu_gpu_dense_10rep*.csv`, `genesis25_cpu_gpu_extreme_5rep*.csv`,
`genesis25_cpu_gpu_longrun*.csv`) is confounded by binary choice (X11-linked
vs headless build), in addition to OpenCL never being exercised by any of
the underlying scripts. None of these numbers can be honestly reported as
characterizing GPU performance, or even as a clean "no GPU effect" CPU vs
CPU control — they reflect an unrelated, X11-link-specific construction-time
artifact whose magnitude depends on the ratio of element count to per-step
compute cost in each benchmark.

## Recommendation for any future CPU vs GPU comparison

Use the **same binary** for both arms of the comparison. The Makefile's
`USE_OPENCL` flag is purely additive — confirmed in
`genesis/src/hines/Makefile`, it only adds `-DUSE_OPENCL`, the
`opencl/ocl_hsolve.o` object, and `-lOpenCL`; it does not change any other
compile flags or behavior. So:

1. Build headless `nxgenesis` twice: once with `USE_OPENCL=1`, once without.
   Force a clean rebuild each time (`make clean` or remove the relevant
   `.o`/library archive files first) — a `make nxgenesis` run without
   `USE_OPENCL=1` immediately after a `USE_OPENCL=1` build can silently
   relink stale cached objects and still pull in `-lOpenCL` without
   recompiling anything OpenCL-specific. Verify with `ldd` after rebuilding
   that the no-OpenCL binary really has no `libOpenCL` dependency.
2. Use a benchmark script that actually creates an `hsolve` with
   `chanmode=4`/`calcmode=1` (e.g. `genesis/Scripts/benchmark/ocl_hh_benchmark.g`),
   and confirm the `OCL PROFILING SUMMARY` printout shows `steps profiled`
   matching the expected step count before trusting any timing number.
3. Report kernel time, host dispatch/transfer overhead, and total step time
   separately (as `ocl_hh_benchmark.g` / `ocl_cleanup()` now do) rather than
   a single end-to-end wall-clock ratio, since the GPU channel kernel is
   only a small fraction of total step time (see `PLAN_gpu_rewrite.md`).

## Related

- `paper/PLAN_gpu_rewrite.md` — corrected root-cause analysis and real OCL
  kernel profiling numbers (this document complements it by explaining the
  *historical* CPU-vs-GPU numbers' confound, while that document focuses on
  the real GPU kernel profiling after the page-fault fix).
- `genesis/Scripts/benchmark/ocl_hh_benchmark.g` — corrected benchmark that
  actually exercises the OpenCL path and can be safely compared
  binary-for-binary if a no-OpenCL headless build is added.
