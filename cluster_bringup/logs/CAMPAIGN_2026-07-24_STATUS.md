# Overnight CUDA campaign (2026-07-24) — status

Launched 00:51-00:52, killed by `timeout 16h` ~16:51-16:52 (still on N=200000).
Raw CSV/log for both nodes are in this directory.

## Bug found: all CPU-arm rows are invalid
`run_one()` in `50_overnight_campaign.sh` called `env "$3" GENESIS_BENCH_CHANMODE=...`
where `$3` (extra env string) is an **empty literal `""` for the CPU arm**. POSIX
`env` treats a bare `""` positional as the command to exec (not a no-op), so it
failed immediately: `env: '': No such file or directory` (exit 127), confirmed
by direct reproduction on inf03. Every "CPU" row in both CSVs (`wall_s` ≈ 0.001–
0.002 s for every N from 500 to 200,000) measures this instant failure, not
GENESIS execution. **Fixed** in the script (only pass `$3` to `env` when
non-empty); fix verified live on inf03 (CPU K=0/K=5000 at N=2000 now shows real,
differing wall-clock: 0.844 s / 0.875 s).

## What's still valid: CUDA-arm timing (both nodes, N=500..100,000)
The CUDA rows were unaffected (their extra-env string `GENESIS_CUDA_MULTILOOP=$K`
is never empty). For N=500 through 100,000 there are full 10-rep CUDA
measurements on both A100 (inf03) and A40 (inf02) — real construction+step
wall-clock, useful on its own, but **not** yet a CPU-vs-GPU speedup number
(needs a corrected CPU-arm rerun for the same N grid).

## Real finding: N=200,000 construction cost
CUDA K=0 (construction only) at N=200,000 took **2634–3419 s (44–57 min)** per
single run (both GPUs, since construction is host-CPU work) — the campaign got
stuck there for the remaining ~11 of its 16 allotted hours and never reached
N=500,000 or 1,000,000. This is much worse than a naive linear extrapolation
from smaller N and is a genuine, reportable limitation (GENESIS SLI network
construction is O(N) serial), not a bug.

## Operator mistake (also recorded)
While smoke-testing the fix, a copy of the script (still using the same
`$OUT` filename pattern) was accidentally run on inf03 and **overwrote** the
original `campaign_inf03_NVIDIA_A100-PCIE-40GB_2026-07-24.csv` on the cluster
(truncated to the 4-row smoke test). No data was lost: the full original
(352 rows / 344 rows for A40) had already been pulled to this `logs/` directory
and is what's committed here. Cluster-side file is now just smoke-test debris.

## Recommendation for next run
1. Use the fixed `50_overnight_campaign.sh` (env bug resolved).
2. Rerun the CPU arm (or the full campaign) for **N=500..100,000 only** — that
   grid is known to complete in well under an hour per node; this yields a
   clean, valid multi-replicate CPU-vs-CUDA speedup table.
3. Treat N≥200,000 as a **separate, deliberate** experiment (not part of a
   blind large sweep) given the construction-cost finding above — e.g. profile
   construction time alone first, or address it as future work in the paper
   text rather than trying to brute-force through it again.
