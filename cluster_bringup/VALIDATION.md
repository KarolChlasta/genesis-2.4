# GENESIS 2.5 CUDA backend — validation on UMCS (A100)

**Result: PASS.** The fp32 CUDA hines backend agrees with the fp64 CPU reference
to **|CPU − CUDA| = 7.04 × 10⁻⁸ V** on the HH1952 action-potential test — within
the fp32 tolerance (1e-7…1e-6 V). First numerical validation of the GENESIS 2.5
CUDA backend on the UMCS cluster.

- Node: **inf03**, GPU **NVIDIA A100-PCIE-40GB** (sm_80, 108 SMs), driver 595.71.05
- Toolchain: **CUDA 12.8** (`/storage/opt/cuda/cuda-12.8`), **gcc 8.5.0**, `-arch=sm_80`
- Repo commit built: `c6f4d02` (see `~/genesis-2.5/TRANSFER_PROVENANCE.txt`)
- Date: 2026-07-23. Prepared by Karol Chlasta.

| binary | precision | RESULT_VM (V) |
|--------|-----------|---------------|
| `nxgenesis_nocl` (CPU) | fp64 | −0.02143485882 |
| `nxgenesis` (CUDA, A100) | fp32 | −0.02143492922 |
| | **\|Δ\|** | **7.040 × 10⁻⁸** |

CUDA runtime confirmed active: `CUDA: device: NVIDIA A100-PCIE-40GB (sm_80, 108
SMs)`, multiloop dispatch `210 steps | kernel 0.8 ms | 3.97 µs/step`.

## Three build/run fixes required on this cluster (record for reviewers)

The stock `BUILD_CUDA.md` recipe did not work as-is; three cluster-specific issues
were diagnosed and fixed (baked into `10_build.sh` / `20_validate.sh`):

1. **Missing `libfl`.** The cluster ships the `flex` binary but not the flex
   library, so linking `code_g` (`LEXLIB=-lfl`) failed with `cannot find -lfl`,
   which cascaded (`code_g` never built → no generated `*_g@.c` → `No rule to make
   sim/simlib.o`). Fix: build a local `libfl.a` with a `yywrap` stub and override
   `LEXLIB`.
2. **`EXTRALIBS` clobbering.** `genesis/src/Makefile` sets
   `EXTRALIBS = $(SPRNGLIB) $(TERMCAP)`. Passing `EXTRALIBS="-lcudart"` (as the
   stock note suggests) *replaces* it, dropping SPRNG + termcap → undefined
   `get_rn_dbl_simple`, `tgetstr`, etc. Also the C++ `cuda_backend.o` needs
   `-lstdc++` (`__gxx_personality_v0`). Fix: pass the FULL set —
   `sprng/lib/liblfg.a -lncurses -ltinfo -lOpenCL -L$CUDA_HOME/lib64 -lcudart -lstdc++`.
3. **Run from the repo root.** `hh1952_ap_verify.g` does
   `include genesis/src/startup/schedule.g` (path relative to the repo root).
   Run from `genesis/src`, that include fails, the solver no-ops, and Vm stays at
   rest (−0.07 V) — a **false** `NEURONS_AGREE: YES`. Run from the repo root so the
   schedule loads and the AP actually integrates.

## Exact commands (reproduce)
```sh
# on inf03 (A100), repo at ~/genesis-2.5, home shared
cd ~/genesis-2.5/cluster_bringup
./10_build.sh        # builds nxgenesis_nocl (CPU) + nxgenesis (CUDA, sm_80)
./20_validate.sh     # -> PARITY: PASS, |CPU-CUDA| = 7.0e-8 V
```

## Logs
- `logs/validate_parity_inf03_2026-07-23.log` — full parity output + verdict
- `logs/build_cpu_inf03_2026-07-23_tail.log`, `logs/build_cuda_inf03_2026-07-23_tail.log`
- Full build logs remain on the cluster at `~/genesis-2.5/cluster_bringup/build_*.log`

## Next
- Benchmark A100 (inf03) and A40 (inf02) with `30_benchmark_gpu.sh` (A40 uses sm_86).
- PGENESIS LSM smoke-test with `40_smoke_lsm.sh` (needs `module load mpi/mpich-x86_64`).
