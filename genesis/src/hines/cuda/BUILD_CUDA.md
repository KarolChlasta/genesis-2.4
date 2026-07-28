# GENESIS 2.5 CUDA backend — build & validation guide

**Status: implemented and validated.** This backend is a faithful fp32 port
of the OpenCL backend (`../opencl/`). It has been built and validated on an
NVIDIA RTX 4090 (RunPod, `sm_89`) and, independently, on the UMCS "Lunar"
cluster's A100 (`sm_80`) and A40 (`sm_86`) nodes: numerical parity with the
fp64 CPU path to ~1e-7 V, and a 10-replicate step-phase speedup sweep for
both the single-compartment multiloop kernel and the multi-compartment
`hines_tree_eliminate` tridiagonal-elimination kernel (the latter is not yet
covered by this doc — see
[`../GPU_HINES_SOLVE_DESIGN.md`](../GPU_HINES_SOLVE_DESIGN.md)). Full numbers
are in `paper/manuscript_softwarex_draft.tex` (Tables 3–4) and
`paper/REPLICATION.md`; raw campaign data is in `cluster_bringup/logs/`.

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
   `-L$(CUDA_HOME)/lib64`). The top-level `genesis/src/Makefile`'s
   `EXTRALIBS` defaults to `$(SPRNGLIB) $(TERMCAP)` (which already carries
   `-lOpenCL` via `TERMCAP`); passing `EXTRALIBS=-lcudart` on the command
   line *replaces*, not appends to, that default and silently drops sprng
   and termcap. Pass the **full** set instead, plus `-lstdc++` (the CUDA
   glue's C++ object needs it):
   ```sh
   make USE_CUDA=1 CUDA_HOME=/usr/local/cuda \
        EXTRALIBS="sprng/lib/liblfg.a -lncurses -ltinfo -lOpenCL -L/usr/local/cuda/lib64 -lcudart -lstdc++" \
        nxgenesis
   ```
   This exact incantation (plus a `-arch` auto-detected from the GPU and a
   `libfl` stub some clusters lack) is scripted and tested end to end in
   [`cluster_bringup/10_build.sh`](../../../../cluster_bringup/10_build.sh) —
   prefer that over reconstructing the command by hand.

## Validate

Same scripts as the OpenCL path (`GENESIS_CUDA_MULTILOOP` is the CUDA
equivalent of `GENESIS_OCL_MULTILOOP`):

1. **Numerical parity** — the fp32 CUDA path must agree with the fp64 CPU path
   to the same tolerance the OpenCL path does (~1e-7 V for a single AP):
   ```sh
   ./nxgenesis_nocl -nosimrc -notty -batch \
       Scripts/benchmark/hh1952_ap_verify.g 8 200          # CPU RESULT_VM
   GENESIS_CUDA_MULTILOOP=210 ./nxgenesis -nosimrc -notty -batch \
       Scripts/benchmark/hh1952_ap_verify.g 8 200          # CUDA RESULT_VM
   ```
   Expect `NEURONS_AGREE: YES` and |CPU − CUDA| ≈ 1e-7…1e-6 V. A larger gap
   means a port bug — diff the two kernels. `cluster_bringup/20_validate.sh`
   automates exactly this.
2. **Speedup** — for the single-compartment kernel, `experiments/run_overnight_campaign.py`
   drives both the OpenCL and CUDA binaries (it parses both `OCL MULTILOOP:`
   and `CUDA MULTILOOP:` dispatch lines); for a multi-replicate cluster sweep
   of either kernel, see `cluster_bringup/30_benchmark_gpu.sh`,
   `cluster_bringup/51_weekend_campaign.sh` (multi-compartment), and
   `cluster_bringup/52_cuda_singlecomp_campaign.sh` (single-compartment).

## Notes / likely first-run issues
- `nvcc` default host compiler must match the GENESIS C toolchain ABI; if the
  glue and device objects disagree, pass `-ccbin $(CC)` in `NVCCFLAGS`.
- Set `-arch=sm_XX` in `NVCCFLAGS` for the target GPU (e.g. `sm_80` for A100,
  `sm_86` for RTX 30xx/A40, `sm_90` for H100) to avoid JIT on first launch.
- `block = 64` in `cuda_backend.cu` matches the OpenCL local size; 128/256 may
  be better on NVIDIA — sweep it once the parity check passes.
