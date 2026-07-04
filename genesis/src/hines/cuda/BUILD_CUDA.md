# GENESIS 2.5 CUDA backend — build & validation guide

**Status: implemented, not yet validated on NVIDIA hardware.** The laptop used
for the OpenCL results has no NVIDIA GPU and no `nvcc`. This backend is a
faithful fp32 port of the validated OpenCL backend (`../opencl/`) and is meant
to be compiled and validated first on a rented NVIDIA GPU (RunPod), then on the
UMCS `inf02`/`inf03` cluster (access window Aug 15–31 2026; cluster admin Karol
Karpowicz). Do not put CUDA hardware/speedup numbers in the paper until this has
run and passed the parity check below.

## Files
- `cuda_channel.cuh` — device kernels (`cuda_chip_channel_update`,
  `cuda_chip_channel_multiloop`), a line-for-line port of `../opencl/ocl_channel.cl`.
- `cuda_backend.cu` — device management + dispatch, **array-based `extern "C"`
  API only** (never includes a GENESIS header, so `nvcc` never parses K&R C).
- `cuda_hsolve.c` — GENESIS-side glue (built by the C compiler); builds the
  per-compartment index and owns the multiloop control flow. Mirrors
  `../opencl/ocl_hsolve.c`.
- `cuda_hsolve.h` — C-callable prototypes.

`hines.c` selects the backend at build time: `-DUSE_CUDA` → `cuda_chip_update`,
`-DUSE_OPENCL` → `ocl_chip_update`, neither → pure CPU. The two accelerator
paths are mutually exclusive; if both are defined CUDA wins.

## Build (RunPod / any CUDA host)

1. Install the CUDA toolkit (nvcc). Confirm: `nvcc --version`, `nvidia-smi`.
2. In `genesis/src`, build the headless binary with CUDA:
   ```sh
   make USE_CUDA=1 CUDA_HOME=/usr/local/cuda nxgenesis
   ```
   The hines library Makefile compiles `cuda/cuda_hsolve.o` (C compiler) and
   `cuda/cuda_backend.o` (`nvcc`) and adds them to `hineslib.o`.
3. **Linker:** the final `nxgenesis` link must include `-lcudart` (and
   `-L$(CUDA_HOME)/lib64`). The OpenCL build injects `-lOpenCL` via the
   top-level `genesis/src/Makefile` `TERMCAP` line (`-lncurses -ltinfo
   -lOpenCL`). For the CUDA build, add `-lcudart` there (or set
   `EXTRALIBS="-L$(CUDA_HOME)/lib64 -lcudart"` on the make command line) —
   `$(CUDA_LIBS)` from the hines Makefile is defined for this purpose.

## Validate (must pass before any paper claim)

Same scripts as the OpenCL path. The CUDA glue accepts the OpenCL env var so
the benchmarks are unchanged (`GENESIS_CUDA_MULTILOOP` overrides if set):

1. **Numerical parity** — the fp32 CUDA path must agree with the fp64 CPU path
   to the same tolerance the OpenCL path does (~2e-7 V for a single AP):
   ```sh
   ./nxgenesis_nocl -nosimrc -notty -batch \
       Scripts/benchmark/hh1952_ap_verify.g 8 200          # CPU RESULT_VM
   GENESIS_CUDA_MULTILOOP=210 ./nxgenesis -nosimrc -notty -batch \
       Scripts/benchmark/hh1952_ap_verify.g 8 200          # CUDA RESULT_VM
   ```
   Expect `NEURONS_AGREE: YES` and |CPU − CUDA| ≈ 1e-7…1e-6 V. A larger gap
   means a port bug — diff the two kernels.
2. **Speedup** — reuse the campaign driver, pointing the GPU arm at the CUDA
   binary (it parses both `OCL MULTILOOP:` and `CUDA MULTILOOP:` lines):
   ```sh
   python3 paper/run_overnight_campaign.py
   ```

## Notes / likely first-run issues
- `nvcc` default host compiler must match the GENESIS C toolchain ABI; if the
  glue and device objects disagree, pass `-ccbin $(CC)` in `NVCCFLAGS`.
- Set `-arch=sm_XX` in `NVCCFLAGS` for the target GPU (e.g. `sm_80` for A100,
  `sm_86` for RTX 30xx/A40, `sm_90` for H100) to avoid JIT on first launch.
- `block = 64` in `cuda_backend.cu` matches the OpenCL local size; 128/256 may
  be better on NVIDIA — sweep it once the parity check passes.
