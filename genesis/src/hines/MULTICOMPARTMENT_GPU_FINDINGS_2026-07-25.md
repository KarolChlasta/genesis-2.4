# Multicompartment GPU findings, 2026-07-25 — raw data for publication selection

Karol Chlasta. Captured verbatim from local test runs so nothing has to be
re-derived later; treat as a data log, not a polished narrative. Cross-refs:
`GPU_HINES_SOLVE_DESIGN.md` (design rationale/history for the correctness
finding this data supports).

**Hardware for ALL numbers in this file**: local dev machine, AMD Radeon 890M
integrated GPU (`radeonsi`, `strix1`, ACO, Mesa OpenCL via DRM 3.64, kernel
6.17.0-122035-tuxedo). **NOT** the UMCS cluster's discrete A40 (inf02) / A100
(inf03) used elsewhere in the paper's single-compartment benchmarks. These
numbers establish *correctness* and the *qualitative shape* of the
per-step-dispatch speed tradeoff (fixed per-step overhead vs compartment-count
scaling) — absolute speedup figures for the paper must be re-measured on
cluster discrete GPUs before publication; an iGPU sharing system RAM/launch
latency with the CPU is not representative of A40/A100 performance.

Test model: `genesis/Scripts/benchmark/hh_multicompartment_benchmark.g` — N
independent neurons, each a linear cable of NCOMP Hodgkin-Huxley
compartments (Na+K on every compartment) with real `AXIAL`/`RAXIAL`
inter-compartment coupling, current injected only at compartment 0 (the
"soma"). One `hsolve` covers all N x NCOMP compartments. `DT=10e-6 s`.

## 1. Correctness: per-step OpenCL dispatch vs multiloop vs CPU reference

Three dispatch modes compared: CPU reference (`chanmode=1`, `nxgenesis_nocl`),
GPU per-step (`chanmode=4`, `nxgenesis`, **no** `GENESIS_OCL_MULTILOOP` set),
GPU multiloop (`chanmode=4` + `GENESIS_OCL_MULTILOOP=<steps>`). Readout: `Vm`
of cell0's soma (compartment 0, where current is injected) and cell0's far
compartment (`NCOMP-1`, only reaches a non-trivial value if axial coupling
correctly propagated the signal down the cable), after 500 integration steps
(`DT=10e-6 s`, i.e. 5 ms simulated). **Critical prerequisite**: `getfield` on
an hsolve'd compartment under chanmode 4/5 reads stale/unsynced data unless
preceded by `call /net/solver HGET <path>` — first attempt at this comparison
gave a false "GPU totally broken, stuck at EREST_ACT" result purely from
missing this call (see `GPU_HINES_SOLVE_DESIGN.md`, "MAJOR FINDING" section,
for the full misdiagnosis-and-fix narrative — worth keeping for the paper's
discussion of accelerator-API pitfalls, since it is a genuine, non-obvious
trap other GENESIS-GPU users would hit).

| N | NCOMP | mode | VM_SOMA | VM_FAR |
|---|---|---|---|---|
| 50 | 8 | CPU (chanmode=1) | -0.07891220069 | -0.08172388197 |
| 50 | 8 | GPU per-step (chanmode=4) | -0.0789122347 | -0.08172388662 |
| 50 | 8 | GPU multiloop (chanmode=4+multiloop) | -0.0337 | -0.0344 |
| 1 | 1 | CPU | -0.07428599875 | (same, NCOMP=1) |
| 1 | 1 | GPU per-step | -0.07428595805 | (same) |
| 1 | 2 | CPU | -0.07714324828 | -0.07821949841 |
| 1 | 2 | GPU per-step | -0.07714336227 | -0.07821960856 |
| 1000 | 16 | CPU | -0.07915745334 | -0.08059562488 |
| 1000 | 16 | GPU per-step | -0.07915750153 | -0.08059532978 |

**GPU per-step matches CPU to ~3e-7..5e-9 V at every tested size** (single
compartment through N=1000 x NCOMP=16 = 16000 compartments). **GPU multiloop
diverges wildly** (order 0.03-0.05 V off, physiologically implausible —
unconstrained runaway from the missing axial leak term), consistent with the
already-documented "multiloop skips elimination, invalid for multicompartment"
defect. This is the headline result: **per-step GPU dispatch is a valid,
already-existing correct multicompartment GPU acceleration path** — no new
elimination kernel is required for scientific validity (see design doc for
why a from-scratch parallel-elimination kernel remains a *worthwhile future
optimization* regardless, just not a blocker).

## 2. Speed: CPU vs GPU per-step, by N (NCOMP=16 unless noted)

Timing via the new `walltimemark`/`{walltime}` `CLOCK_MONOTONIC` timer
(`sim/sim_ops.c`), 500 measured steps + 10 warm-up combined into one `step`
call (see script comments for why). `RESULT_T_PER_STEP` in seconds/step.

| N | NCOMP | total comps | CPU s/step | GPU per-step s/step | GPU vs CPU |
|---|---|---|---|---|---|
| 100 | 8 | 800 | 2.183e-5 | 3.402e-4 | 15.6x **slower** |
| 100 | 16 | 1600 | 5.290e-5 | 3.515e-4 | 6.65x **slower** |
| 250 | 16 | 4000 | 1.530e-4 | 4.334e-4 | 2.83x **slower** |
| 500 | 8 | 4000 | 1.442e-4 | 3.970e-4 | 2.75x **slower** |
| 500 | 16 | 8000 | 2.908e-4 | 4.489e-4 | 1.54x **slower** |
| 1000 | 16 | 16000 | 1.026e-3 | 6.466e-4 | **1.59x faster** |
| 2000 | 16 | 32000 | 4.084e-3 | 1.061e-3 | **3.85x faster** |
| 5000 | 16 | 80000 | 1.115e-2 | 2.108e-3 | **5.29x faster** |

**Crossover point (this iGPU, NCOMP=16): between N=500 and N=1000 total
compartments** (~8000-16000 compartments). Below it, per-step dispatch's
fixed per-step overhead (upload `vm[]`, launch channel-kinetics kernel,
download `results[]` — once per step, no multi-step batching in this mode)
dominates; above it, the O(total compartments) CPU elimination + channel
update cost overtakes the fixed GPU overhead and the parallel channel-kinetics
work wins. Speedup grows with N past the crossover (1.59x at N=1000 -> 5.29x
at N=5000), consistent with the fixed overhead becoming proportionally
smaller. **Expectation for cluster A40/A100** (not yet measured): discrete
GPUs have far more compute units than this integrated GPU and dedicated VRAM
bandwidth, so (a) the crossover point should shift to smaller N (more raw
throughput advantage per compartment) and (b) the asymptotic speedup should be
substantially higher than the 5.29x ceiling seen here — but PCIe upload/
download latency per step (a cost this iGPU doesn't pay, sharing memory with
the CPU) could partly offset that; this is exactly why it needs a real
cluster measurement rather than extrapolation.

## 3. Implications / what to measure next on the cluster

1. Re-run this exact script (`hh_multicompartment_benchmark.g`, now with
   `walltimemark` timing and `RESULT_VM_*`/`HGET` parity checks built in) on
   inf02 (A40) and inf03 (A100), sweeping N at fixed NCOMP (16, maybe also 32)
   to find the real crossover point and asymptotic speedup on the actual
   target hardware.
2. This result is strong enough to stand on its own in the paper as "a
   correct, measured multicompartment GPU speedup exists via per-step
   dispatch," independent of whether the from-scratch parallel-elimination
   kernel (`GPU_HINES_SOLVE_DESIGN.md` items 5-6) ever gets built — that
   remains a legitimate "future work" direction (would remove the per-step
   upload/download round trip and enable multi-step multiloop batching for
   multicompartment models, likely pushing the crossover point down further
   and raising the asymptotic speedup), not a prerequisite for a valid
   result today.
3. The HGET-sync trap (section 1) is worth a short methods/discussion note
   regardless of which benchmark numbers make the final cut — it's a
   non-obvious correctness pitfall specific to GENESIS's accelerator API that
   silently produces a "looks broken" (or worse, silently wrong but
   plausible-looking) result, and documenting it has standalone value for
   other GENESIS-GPU users/reviewers.
