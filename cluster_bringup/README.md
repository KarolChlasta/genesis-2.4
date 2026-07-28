# Cluster bring-up — GENESIS 2.5 on UMCS (miranda → inf02/inf03)

Turnkey scripts to go from a fresh login to CUDA-validated + benchmarked, in
order. Run **on the compute node** (inf02 = A40, inf03 = A100), not on miranda.
These are shell (cluster ops); only the optional plotting is Python.

Prepared by Karol Chlasta (karol@chlasta.pl). Grounded in
`genesis/src/hines/cuda/BUILD_CUDA.md`. The exact cluster hardware/software
(pinned toolchain, CUDA/MPI versions) is recorded in
[`env/ENVIRONMENT.md`](env/ENVIRONMENT.md) — the reproducibility record.

## Access path
```sh
ssh miranda                 # lunar.umcs.pl:55500 (see ~/.ssh/config)
ssh inf03                   # from miranda: A100 node (or inf02 = A40)
cd <repo>/cluster_bringup   # shared home, so clone once
```

## Order
| # | Script | What | Safe? |
|---|--------|------|-------|
| 0 | `00_recon.sh` | read-only: GPU, compute_cap, nvcc, modules, /storage/opt, build deps | yes |
| 1 | `10_build.sh` | build `nxgenesis` with CUDA (auto `-arch` from GPU) + CPU ref | builds |
| 2 | `20_validate.sh` | numerical parity CPU vs CUDA (must print `NEURONS_AGREE: YES`) | runs |
| 3 | `30_benchmark_gpu.sh` | wall-clock timing, tagged by node/GPU → CSV | runs |
| 4 | `40_smoke_lsm.sh` | PGENESIS LSM smoke-test (pdim=4 → 17 ranks) | runs MPI |

## Per-node GPU arch (auto-detected, for reference)
| node | GPU | compute_cap | -arch |
|------|-----|-------------|-------|
| inf02 | A40 | 8.6 | sm_86 |
| inf03 | A100 | 8.0 | sm_80 |

## Typical session
```sh
ssh inf03                           # A100
cd <repo>/cluster_bringup
./00_recon.sh                       # provenance snapshot of the node
./10_build.sh                       # CUDA_HOME defaults to /storage/opt/cuda/cuda-12.8
./20_validate.sh                    # expect NEURONS_AGREE: YES
./30_benchmark_gpu.sh               # A100 timing -> results CSV
module load mpi/mpich-x86_64        # provides mpirun for the LSM
./40_smoke_lsm.sh                   # LSM 17-rank smoke test
```
Repeat on inf02 (A40) for the A40-vs-A100 comparison (shared home = one clone).
`10_build.sh` auto-picks `-arch` from the GPU (sm_80 A100 / sm_86 A40); no CUDA
module exists on this cluster — CUDA is pinned via `CUDA_HOME` (see ENVIRONMENT.md).
