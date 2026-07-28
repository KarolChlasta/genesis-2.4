# experiments/ — manifest (complete reproducibility package)

Everything used to produce the GENESIS 2.5 accelerator benchmark results, in one
folder. Nothing here is required at a specific path to *run* GENESIS — these are
copies/records for reproduction and archival. Canonical source lives in the
GENESIS tree (paths noted below); the `scripts/` copies are snapshots of exactly
what was run for these results.

## Environment (full setup)
- `EXPERIMENTAL_SETUP.md` — hardware, software versions, build recipe, all gotchas.
- `cuda_validation/pod_environment.txt` — raw RTX 4090 pod dump (OS, CPU Ryzen 9
  9950X, GPU/driver/CUDA 12.8, nvcc/gcc/make/ld versions, package list, commit).
- `cuda_validation/build_log_rtx4090.txt` — the actual pod build log.

## Scripts run (snapshots; canonical path in parentheses)
| Snapshot | Canonical | What it does |
|---|---|---|
| `scripts/run_overnight_campaign.py` *(here)* | `experiments/` | OpenCL campaign driver (Studies 1–4) |
| `scripts/plot_campaign.py` *(here)* | `experiments/` | builds `paper/figures/fig_campaign_*.png` |
| `scripts/hh_spiking_benchmark.g` | `genesis/Scripts/benchmark/` | driven spiking HH timing benchmark |
| `scripts/hh1952_ap_verify.g` | `genesis/Scripts/benchmark/` | CPU-vs-GPU correctness (single AP) |
| `scripts/ocl_hh_benchmark.g` | `genesis/Scripts/benchmark/` | OpenCL dispatch benchmark |
| `scripts/runpod_validate.sh` | `genesis/src/hines/cuda/` | CUDA pod bring-up + validation |

CUDA backend source (not copied — product code): `genesis/src/hines/cuda/`
(`cuda_backend.cu`, `cuda_channel.cuh`, `cuda_hsolve.c/.h`, `BUILD_CUDA.md`).

## Data
| File | Contents |
|---|---|
| `data/campaign_wallclock_summary.csv` | OpenCL speedup / throughput / real-time factor vs N |
| `data/campaign_ksweep.csv` | speedup vs simulation length K |
| `data/campaign_divergence.csv` | fp32-vs-fp64 agreement vs steps |
| `data/campaign_reproducibility.csv` | long-run stability |
| `data/campaign_wallclock_raw.csv` | per-rep raw wall times |
| `data/campaign_final_table.csv`, `campaign_warm_dispatch.csv` | derived speedup tables |
| `cuda_validation/cuda_sweep_rtx4090.csv` | CUDA speedup sweep (RTX 4090) |
| `cuda_validation/parity_rtx4090.txt` | CUDA fp32 vs CPU fp64 correctness |

## Results summaries
- `cuda_validation/RESULTS.md` — RTX 4090 CUDA validation (correctness + speedup).
- Headline numbers: `EXPERIMENTAL_SETUP.md` §6.

## Reproduce
```bash
# OpenCL campaign (laptop):
python3 experiments/run_overnight_campaign.py && python3 experiments/plot_campaign.py
# CUDA validation (sm_89 CUDA pod):
bash genesis/src/hines/cuda/runpod_validate.sh
```
Repo commit used for the RTX 4090 run: `4ef3938` (+ the build fixes now committed).
