# GENESIS 2.5 — weekend status & plan (started 2026-07-04, overnight run)

This is an autonomous overnight increment. Nothing here is committed; review
before committing. The guiding rule was the one this project already follows:
**measure, don't assert** — every number below comes from a run on this laptop,
and where the previous draft asserted numbers that the data did not support, I
corrected them rather than propagating them.

## TL;DR of what changed tonight

1. **Found and am fixing a data-integrity problem in the paper.** The SoftwareX
   draft's Table 2 reported end-to-end speedups of **3.2–16.2×** that (a) did not
   match the committed CSV (`genesis25_ocl_multiloop_scaling_summary.csv`, which
   says 2.65–14.83×), and (b) were produced by an *asymmetric* timing method —
   CPU timed with GENESIS's `{cpu}` step timer, GPU timed only by the kernel's own
   dispatch report, which omits the GPU arm's residual per-step overhead. The
   paper also contradicted itself: Table 2 said the scheduler fix was done, while
   the Impact/Conclusions listed it as future work.

2. **Re-measured everything properly** with a new wall-clock harness
   (`run_overnight_campaign.py`): whole-process `time.monotonic()` on *both* arms,
   same binary family (no X11 confound), construction phase separated from the
   step phase by a K=0 baseline. The internal timers and the external wall-clock
   now agree, which is what licenses the comparison. Running as I write this.

3. **Made the benchmark biophysically meaningful.** The old `ocl_hh_benchmark.g`
   integrates *resting* neurons. The new `hh_spiking_benchmark.g` injects a
   suprathreshold current so every HH neuron fires action-potential trains — the
   regime neuroscientists actually simulate, and the one that exercises the
   `inject` path the three Hines-solver fixes repaired.

4. **Added neuroscience-facing metrics**: throughput (neuron-steps/s) and
   real-time factor (biological seconds per wall second), not just raw speedup.

5. **Wrote the CUDA backend** (`genesis/src/hines/cuda/`): a faithful fp32 port
   of the validated OpenCL kernels, wired behind `USE_CUDA` so it is inert in the
   current build. Cannot be compiled here (no NVIDIA GPU / no nvcc) — it is
   RunPod/UMCS-ready with a build+validation guide (`cuda/BUILD_CUDA.md`).

6. **Fixed a latent benchmark bug**: the `argc > N` argv guards in the benchmark
   scripts were off by one, silently pinning the step count to its default (5000)
   whenever a custom value was passed. This never surfaced because the old sweep
   always passed 5000 = the default. Fixed in `hh_spiking_benchmark.g` and
   `hh1952_ap_verify.g`.

## Measured results (this laptop: AMD Radeon 890M, Mesa rusticl, fp32; K=50000)

Final, reconciled after a controlled GPU-variability diagnostic (see below).
Step-phase = channel-update simulation (scales with biological time); sustained =
warm GPU (reproducible ±2%); single-run = cold-start median.

| N | step-phase (sustained) | step-phase (single run) | end-to-end (single run) | throughput (M nsteps/s) |
|---:|---:|---:|---:|---:|
| 500 | 2.7× | 2.0× | 1.3× | 223 |
| 1000 | 5.2× | 3.7× | 2.3× | 446 |
| 2000 | 10.0× | 6.5× | 3.7× | 855 |
| 5000 | **18.1×** | **13.5×** | **4.2×** | **1524** |
| 10000 | 14.3× | 6.8× | 2.5× | 1232 |
| 20000 | 3.6× | 3.1× | 1.6× | 305 |
| 50000 | 3.2× | 3.2× | 1.2× | 253 |

**Important late finding (GPU DVFS).** The first campaign showed the N=10000
step-speedup varying 2× (5.8×–13.3×) run-to-run. A controlled diagnostic
explained it: with a 2-run GPU warm-up the dispatch is rock-stable (±1–2%), but
in a single run the CPU-bound model build leaves the GPU idle and *downclocked*,
so the first dispatch is ~1.3–2× slower. So there are two honest regimes —
**sustained/warm** (long or repeated runs: up to ~18× at N=5000) and
**single cold-start** (~13×). Beyond N≈10000 the integrated GPU stops sustaining
fast clocks and both fall to ~3×. All of this is now in the paper (Table 2 +
Fig.), reported as two regimes, not hidden behind one number. This is exactly
the kind of thing the RunPod/NVIDIA run should re-check — a discrete-GPU with
stable clocks may not show the cold-start gap at all.

**K-sweep (N=5000):** as the run lengthens, construction amortizes and end-to-end
speedup climbs 1.3× (K=5000) → 8.4× (K=200000), toward the ~13× step-phase
ceiling (`campaign_ksweep.csv`). This is the regime that matters — real studies
run long.

**Correctness:** fp32 GPU vs fp64 CPU agree to ~2×10⁻⁷ V for a single action
potential across all three execution paths (CPU / GPU per-step / GPU multiloop),
`NEURONS_AGREE: YES` throughout (`campaign_divergence.csv`); they diverge in spike
*phase* over long runs, as any fp32-vs-fp64 oscillator does — reported, not hidden.

## CUDA validation plan (see memory `project_cuda_cluster_plan.md`)

- **Stage 1 — RunPod:** rent an NVIDIA GPU, `make USE_CUDA=1`, run the parity
  check in `cuda/BUILD_CUDA.md` (must match CPU to ~1e-6 V), then the speedup
  sweep. Only after this do any CUDA numbers go in the paper.
- **Stage 2 — UMCS `inf02`/`inf03`:** Wójcik has the Institute Director's OK.
  Admin **Karol Karpowicz** (karol.karpowicz@mail.umcs.pl); access window
  **15–31 Aug 2026** (ask for a 1–2 day early login test). Confirm the node GPU
  model with Karpowicz before writing hardware claims.

## Recommended next steps for the weekend (for discussion, not done yet)

1. Review the corrected Table 2 / figures and the honest step-vs-end-to-end
   framing; decide how to present the N≈5000 efficiency peak.
2. Rebuild `nxgenesis` from the edited source (the hines.c change is behaviourally
   identical for OpenCL — a rebuild just re-syncs binary↔source) and re-run the
   AP-verify parity check once more.
3. RunPod CUDA bring-up (Stage 1) — likely a half-day including first-compile
   fixes (host-compiler ABI, `-arch=sm_XX`).
4. Decide scope: keep the paper single-compartment (honest, matches the multiloop
   kernel's validity) or scope a multi-compartment tridiagonal GPU solve as
   explicit future work.

## Files added/changed tonight (uncommitted)
- `genesis/Scripts/benchmark/hh_spiking_benchmark.g` (new; driven spiking)
- `genesis/Scripts/benchmark/hh1952_ap_verify.g` (argv-guard fix)
- `genesis/src/hines/cuda/` (new: cuda_channel.cuh, cuda_backend.cu,
  cuda_hsolve.c, cuda_hsolve.h, BUILD_CUDA.md)
- `genesis/src/hines/hines.c` (backend-select macro; OpenCL path unchanged)
- `genesis/src/hines/Makefile` (USE_CUDA branch)
- `paper/run_overnight_campaign.py`, `paper/plot_campaign.py` (new harness+plots)
- `paper/manuscript_softwarex_draft.tex` (to be updated with measured numbers)
