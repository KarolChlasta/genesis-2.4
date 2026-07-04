# CUDA backend validation — NVIDIA RTX 4090 (RunPod)

Date: 2026-07-04. First validation of the GENESIS 2.5 CUDA backend on real
NVIDIA hardware (previously code-only / unvalidated).

## Environment
- GPU: NVIDIA GeForce RTX 4090 (Ada, `sm_89`, 128 SMs, 24 GB), driver 570.195.03
- Toolkit: CUDA 12.8 (nvcc 12.8.93), gcc 13.3.0, Ubuntu 24.04.3
- Host: AMD Ryzen 9 9950X (16C/32T), 123 GB RAM (RunPod pod, $0.69/hr)
- Image: `runpod/pytorch` CUDA 12.8 devel; OpenCL loader added via `ocl-icd-opencl-dev`
- Build: `USE_CUDA=1`, `nvcc -O2 -std=c++14 -arch=sm_89 -ccbin gcc`, linked `-lcudart`

## Build result
- `cuda_backend.cu` compiles on nvcc 12.8 with one cosmetic warning (unused var).
- `nxgenesis` links against `libcudart.so.12`; `cuda_chip_update` symbol present.
- Runtime device banner confirms genuine GPU dispatch:
  `CUDA: device: NVIDIA GeForce RTX 4090 (sm_89, 128 SMs)`

## Correctness (hh1952_ap_verify.g, 8 HH neurons, 2 nA step, 200 steps)
| Path | RESULT_VM (V) | NEURONS_AGREE |
|---|---|---|
| CPU (fp64) | -0.02143485882 | YES |
| CUDA multiloop (fp32) | -0.02143492922 | YES |

Agreement: **7.0×10⁻⁸ V** (fp32 rounding). The CUDA backend is numerically
correct. (Cross-check: laptop OpenCL fp32 gave -0.02143505402 on the same test —
both accelerators agree with fp64 CPU to ~1×10⁻⁷ V.)

## Speedup (hh_spiking_benchmark.g, K=50000 steps, clocks locked)
"CPU step" = GENESIS `{cpu}` step-loop time (fp64). "CUDA dispatch" = kernel
`clock_gettime` wall time for all 50000 steps in one multiloop dispatch (fp32).

| N | CPU step (s) | CUDA dispatch (ms) | kernel µs/step | step-phase speedup |
|---:|---:|---:|---:|---:|
| 500 | 0.248 | 48.2 | 0.96 | 5.1× |
| 5,000 | 2.467 | 48.2 | 0.96 | 51× |
| 50,000 | 25.70 | 195.1 | 3.90 | 132× |

**Key finding:** the RTX 4090 kernel time is flat (~48 ms) from N=500 to N=5000 —
the GPU is far from saturated (128 SMs / 16384 cores) — so unlike the integrated
Radeon 890M (which peaks near N=5000 then falls), CUDA step-phase speedup keeps
**rising with N** (5×→51×→132×). Datacenter/desktop NVIDIA GPUs pay off most at
large network sizes.

## Reproduce
On an `sm_89` CUDA pod (CUDA 12.x devel image):
```
git clone https://github.com/KarolChlasta/genesis-2.4 && cd genesis-2.4
CUDA_ARCH=sm_89 bash genesis/src/hines/cuda/runpod_validate.sh
```
Raw sweep data: `cuda_sweep_rtx4090.csv` in this folder.
