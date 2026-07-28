# GENESIS 2.5 GPU benchmark — notes & methodology

## CORRECTION 2026-07-24: the "~96×" result below is INVALID — do not cite it

**Root cause:** `cuda_chip_channel_multiloop` (`genesis/src/hines/cuda/cuda_channel.cuh`)
has **no axial (Hines) coupling between compartments** — its own header comment
says so explicitly: *"K steps in one launch (single-compartment only) ... NOT
valid for multi-compartment trees."* Each `vm[gid]` is updated as an isolated
point RC circuit for the whole K-step batch.

The CPU arm (chanmode 1) used the real Hines solver on my `AXIAL`/`RAXIAL`-wired
16-compartment cable (correct, coupled dynamics). The CUDA arm (chanmode 4 +
multiloop) computed 3200 **uncoupled** point neurons — a different computation,
not the same model. **The "~96×" number below compares two different
calculations, not CPU-vs-GPU on the same task, and must not be used or cited.**

This was caught while editing the SoftwareX manuscript (2026-07-24) — the
manuscript's own pre-existing text already stated this multiloop limitation
correctly; a new paragraph almost contradicted it before this was caught. The
manuscript was NOT updated with this number and cites only the validated
single-compartment parity result (|CPU−CUDA| = 7.04e-8 V, A100).

**What remains valid:** the single-compartment numerical parity checks
(`VALIDATION.md`) and the per-kernel dispatch-throughput sweep
(`logs/gpu_sweep_a100_vs_a40_2026-07-23.txt`) as a measure of raw kernel
dispatch cost — NOT as a multi-compartment simulation result.

**Follow-on:** a genuine multi-compartment GPU speedup needs a GPU-side
tridiagonal (Hines) solve (see `paper/PLAN_gpu_rewrite.md`; cf. Arbor's
GPU-resident cable solver). Until that exists, GPU acceleration in this codebase
is validated only for single-compartment (point-neuron-per-compartment) networks.

---

## UPDATE 2026-07-23 (evening): first "result" — ~96× on A100 (SEE CORRECTION ABOVE — INVALID, kept for the record)

On the **compute-bound multicompartment** workload (the class GENESIS is built
for), the A100 gives a **~96× compute speedup** over a single CPU core:

| | compute/step (N=200, NCOMP=16 → 3200 compartments) |
|---|---|
| CPU (chanmode 1, fp64) | 297.4 µs/step |
| CUDA (chanmode 4, A100) | 3.1 µs/step (kernel self-report: 2.38 µs/step) |
| **speedup** | **~96×** |

Method: two-step-count subtraction (construction cancels; CPU Δwall = 5.95 s vs
CUDA Δwall = 0.06 s for +20000 steps — clean signal). Consistent with the
literature for detailed multicompartment simulators (Arbor ~200×/GPU;
see `RELATED_WORK_AND_BENCHMARK_DESIGN.md`).

**Two corrections vs the "preliminary" notes below:**
1. **argv bug:** the squid/multicompartment scripts guarded `argv 2` with
   `argc > 2` (off by one), so **N_STEPS was never read** — the CPU always ran the
   default 5000 steps while the GPU step count came from `GENESIS_CUDA_MULTILOOP`.
   The earlier "CPU doesn't scale with steps" was largely this artifact. Fixed to
   `argc > 1` (and `argc > 0` for `argv 1`).
2. **Workload:** single-compartment (squid) is not compute-bound (nothing to
   accelerate). Multicompartment HH is — and shows the expected large speedup.

Still preliminary (single measurement, one size, A100 only). Full campaign
(reps + 95% CI, NCOMP/N sweep, A40 vs A100) is the next step.

---

## Original preliminary notes (single-compartment; superseded — kept for the record)

**Status: preliminary.** The CUDA backend is built and *numerically validated* on
the A100 (see `VALIDATION.md`, |CPU−CUDA| = 7e-8 V). inf03 (A100), 2026-07-23,
Karol Chlasta.

## What we measured
- Workload: `hh1952_squid_multiloop_benchmark.g` — single hsolve over N HH1952
  neurons, chanmode 4; GPU arm dispatches all steps in one CUDA multiloop kernel.
- End-to-end wall-clock (`date +%s%N`), CPU (`nxgenesis_nocl`) vs CUDA
  (`GENESIS_CUDA_MULTILOOP`). Data: `logs/bench_inf03_*.csv`.
- CUDA kernel self-report (accurate): **A100 ≈ 2.6–3.2 µs/step** for one hsolve
  (e.g. N=10000, 120000 steps → kernel 315 ms).

## Findings (why the naive speedup is misleading)
1. **Construction dominates end-to-end.** Building N neurons in the SLI script is
   O(N) and serial (~6–7 s at N=10000). It is identical for CPU and CUDA, so it
   dilutes any compute difference: end-to-end wall-clock speedup was only
   1.1–1.4× and *does not* reflect the compute backends.
2. **The CPU arm with chanmode 4 does not compute per step.** CPU wall-clock is
   flat in the step count (7.114 s at 20k steps vs 7.116 s at 120k steps). chanmode
   4 is the *accelerator* mode; on the CPU binary it is an identity pass-through
   ("CPU Hines identity pass-through"), so it is **not a valid CPU reference** for
   a compute comparison.
3. **The script's internal timer is unusable.** `Total wall time` prints `0 s`
   (GENESIS `{cpu}` resolution is too coarse) — cannot isolate the step loop from
   construction with it.

## Required before any speedup claim (campaign design)
1. **Real CPU reference:** run the CPU arm with a standard CPU Hines solver
   (chanmode 1), not chanmode 4, so it actually integrates per step.
2. **Isolate compute from construction:** time only the step loop — either add a
   fine-grained wall-clock around `step` in the benchmark script, or use the
   two-step-count subtraction method (construction cancels). The GPU side already
   reports an accurate kernel time to cross-check.
3. **Sweep and replicate:** vary N (and steps) to show scaling; ≥10 reps with 95%
   CI; discard warm-up.
4. **Cross-GPU:** repeat on inf02 (A40, sm_86) vs inf03 (A100, sm_80).
5. Report both **compute-only** speedup (headline) and **end-to-end** wall-clock
   (honest, construction-inclusive) separately.

## Preliminary numbers (illustrative only, NOT for the paper)
- End-to-end wall (N=10000, 100000 steps, 3 reps): CPU ≈ 7.1 s, CUDA ≈ 6.4 s.
- CUDA compute (kernel, accurate): A100 ≈ 2.6–3.2 µs/step (one hsolve).
