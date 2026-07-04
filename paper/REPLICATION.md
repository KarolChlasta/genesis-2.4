# Replication Guide: GENESIS 2.5 CPU vs GPU Benchmarks

## Overview

This document records every build and run step needed to reproduce the CPU vs GPU
benchmark results. The authoritative results for the SoftwareX submission
(`paper/manuscript_softwarex_draft.tex`, Table 2 / Figs. of the campaign) are
produced by the single driver `paper/run_overnight_campaign.py` — see
**"Authoritative reproduction"** below. The earlier sections document the build
and the historical per-dispatch measurements that led to it.

A clean CPU vs GPU comparison requires **two headless binaries built from the same
source** — one with the OpenCL channel-update kernel compiled in (`USE_OPENCL=1`)
and one without. Using the X11-linked `genesis` binary as the CPU arm is invalid:
it has per-element construction overhead from the GUI toolkit that scales with
network size and is unrelated to GPU acceleration. Full investigation:
`paper/x11_binary_confound_investigation.md`.

---

## Authoritative reproduction (SoftwareX draft, 2026-07)

After building `nxgenesis` (USE_OPENCL=1) and `nxgenesis_nocl` (Steps 1–3 below),
one driver produces every number and figure in the manuscript's illustrative
examples:

```bash
python3 paper/run_overnight_campaign.py      # writes paper/campaign_*.csv
python3 paper/plot_campaign.py               # writes paper/figures/fig_campaign_*.png
```

What it measures and why it supersedes the older method:

- **Wall-clock, both arms identical.** Whole-process time via `time.monotonic()`
  around each `nxgenesis(_nocl)` run — not GENESIS's `{cpu}` timer for CPU and the
  kernel's dispatch report for GPU (that asymmetry overstated the GPU arm by
  omitting its residual per-step overhead). The internal timers are still recorded
  and agree with the wall-clock step phase, which is what licenses the comparison.
- **Construction separated from stepping.** Each config is timed at `K` steps and
  at `K=0`; the per-step simulation phase is their difference, so one-time,
  CPU-bound model construction does not dilute (or, for tiny fast steps, dominate)
  the accelerator comparison. Both the step-phase and the end-to-end speedup are
  reported.
- **Biophysically meaningful workload.** `hh_spiking_benchmark.g` drives every
  neuron with a suprathreshold current so it fires action potentials, exercising
  the repaired `inject` path (not a flat rest state).
- **Correctness quantified.** `hh1952_ap_verify.g` across CPU / GPU per-step /
  GPU multiloop; fp32 vs fp64 agree to ~2e-7 V over a single AP
  (`campaign_divergence.csv`).

Studies produced: `campaign_wallclock_summary.csv` (speedup/throughput/real-time
factor vs N), `campaign_ksweep.csv` (speedup vs simulation length), and
`campaign_divergence.csv` (fp32/fp64 fidelity), plus a long-run reproducibility
loop (`campaign_reproducibility.csv`). A hard deadline bounds the run and every
row is written incrementally, so it is interrupt-safe.

**CUDA:** the same driver drives the CUDA build (parses `CUDA MULTILOOP:` lines).
Build with `make USE_CUDA=1 CUDA_HOME=/usr/local/cuda` and see
`genesis/src/hines/cuda/BUILD_CUDA.md`. Not yet validated on NVIDIA hardware.

---

## Platform

| Item | Value |
|------|-------|
| Host | AMD Ryzen AI 9 HX 370, 12 cores / 24 threads |
| GPU  | Radeon 890M (gfx1150 / RDNA 3.5 integrated) |
| OS   | Linux 6.17 (Tuxedo) |
| Compiler | GCC 15.2.0 |
| Date | 2026-06-24 |

### OpenCL environment note

Two OpenCL runtimes are present on the host:

| Runtime | Library | fp64 | Device name reported |
|---------|---------|------|----------------------|
| ROCm 6.3.1 (host) | `/opt/rocm-6.3.1/lib/libamdocl64.so` | YES | `gfx1150` |
| Mesa rusticl (container) | `libRusticlOpenCL.so.1` | NO | `AMD Radeon 890M Graphics (radeonsi, ...)` |

As of commit `567395d` the `ocl_channel.cl` kernel runs in **fp32** (single
precision). Host code in `ocl_hsolve.c` converts double↔float at upload/download
time. Both ROCm and Mesa rusticl are therefore able to dispatch the kernel; the
earlier requirement for `cl_khr_fp64` no longer applies. The startup diagnostic
`"OCL: urzadzenie nie wspiera fp64, wylaczam GPU"` is no longer emitted.

**To run the OCL profiling benchmark** (Table 2 data in the manuscript),
run `nxgenesis` outside the container with the ROCm ICD active:

```bash
LD_LIBRARY_PATH=/opt/rocm-6.3.1/lib \
OCL_ICD_VENDORS=/run/host/etc/OpenCL/vendors \
genesis/src/nxgenesis -nosimrc -notty -batch \
    genesis/Scripts/benchmark/ocl_hh_benchmark.g 1000 5000 2>&1
```

Look for `OCL: urzadzenie: gfx1150` (ROCm device name) in the output to confirm
genuine GPU dispatch. The `OCL PROFILING SUMMARY` printed at exit is the Table 2
source.

**To run the multiloop GPU benchmark** (GPU dozens-of-times-faster-than-CPU):

```bash
LD_LIBRARY_PATH=/opt/rocm-6.3.1/lib \
OCL_ICD_VENDORS=/run/host/etc/OpenCL/vendors \
./paper/run_genesis25_multiloop_benchmark.sh 2000 5000 3
```

This compares `nxgenesis_nocl` (CPU) against `nxgenesis` with
`GENESIS_OCL_MULTILOOP=5000`. In multiloop mode the entire 5000-step simulation
is dispatched in a single GPU kernel call (all steps run inside the kernel,
eliminating the per-step PCIe transfer overhead). Measured results on ROCm
(outside container, K=5000 steps, single replicate):

| N neurons | CPU GENESIS step (s) | GPU kernel only (ms) | GPU kernel speedup | GENESIS step GPU (s) | End-to-end speedup |
|---:|---:|---:|---:|---:|---:|
|    100 | 0.067 |  15.4 |   4.4× | 0.055 | 1.22× |
|    500 | 0.316 |  15.8 |  20.0× | 0.225 | 1.40× |
|  1,000 | 0.507 |  15.5 |  32.7× | 0.441 | 1.15× |
|  2,000 | 1.065 |  19.1 |  55.8× | 1.008 | 1.06× |
|  5,000 | 2.813 |  31.3 |  89.8× | 2.449 | 1.15× |
| 10,000 | 8.359 |  56.1 | 149.0× | 6.728 | 1.24× |

The GPU kernel achieves 4-149× speedup over CPU computation. End-to-end
GENESIS speedup is only 1.1-1.4× because the GENESIS scheduler iterates over
all N×3 absorbed elements per step (~25-45 ns/element), scaling O(N) and
dominating at all tested N. Restructuring the GENESIS scheduler to skip
absorbed elements is required to realize the kernel-level speedup end-to-end.

In the container with Mesa rusticl: after the fp32 port (`567395d`) the GPU kernel
dispatches correctly and multiloop speedup matches the ROCm numbers above.

**Historical note — extreme_5rep campaign:** `run_genesis25_cpu_gpu_extreme_5rep.sh`
was run before the fp32 port, inside the container with Mesa rusticl. At that time
rusticl could not compile the fp64 kernel, so both arms silently ran on CPU. The
resulting speedup ratio of ~1.0 is a CPU-vs-CPU comparison and does not reflect
GPU performance.

---

## Step 1: Restore the netcdf library (one-time, after clean)

The GENESIS diskio subsystem bundles netcdf-3.4. Its `configure` script false-
detects "cross-compiling" on modern hosts (the `ftruncate` run-test) and aborts
before emitting `macros.make`, so **`configure` is not run at all**. Both files it
would otherwise generate are committed to the repo:

```
genesis/src/diskio/interface/netcdf/netcdf-3.4/src/libsrc/ncconfig.h
genesis/src/diskio/interface/netcdf/netcdf-3.4/src/macros.make
```

`make nxgenesis` builds most diskio objects itself, but **not** the three the final
link needs: `libnetcdf.a`, `netcdflib.o`, and `FMT1lib.o`. Build them once after a
clean checkout (verified on a fresh clone, 2026-07):

```bash
CF="-O2 -D__NO_MATH_INLINES -DLONGWORDS -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X \
    -std=gnu89 -Wno-implicit-function-declaration -Wno-int-conversion \
    -Wno-incompatible-pointer-types -Wno-strict-prototypes"

# 1. libnetcdf.a  (NO ./configure — macros.make + ncconfig.h are committed)
cd genesis/src/diskio/interface/netcdf/netcdf-3.4/src
make libsrc/all         # only libsrc is needed; ncdump will fail, ignore it
cd ../../../../../..

# 2. netcdflib.o  (GENESIS wrapper around libnetcdf.a)
( cd genesis/src/diskio/interface/netcdf \
    && make CC=gcc CFLAGS_IN="$CF" LD=ld LDFLAGS="" AR=ar RANLIB=ranlib )

# 3. FMT1lib.o    (second diskio format; make nxgenesis does not build it)
( cd genesis/src/diskio/interface/FMT1 \
    && make CC=gcc CFLAGS_IN="$CF" LD=ld LDFLAGS="" AR=ar RANLIB=ranlib )
```

(`fflib.o` and `diskiolib.o` are built automatically by `make nxgenesis` in Step 2.)
An automated, phase-guarded version of this whole sequence — including the CUDA
build — is in `genesis/src/hines/cuda/runpod_validate.sh`.

---

## Step 2: Build `nxgenesis_nocl` (CPU arm)

```bash
cd genesis/src

# After make clean in hines, the generated hines_d@.c contains
# `sizeof(#)` and `var.NNN` patterns (numeric member names) for anonymous
# struct fields that modern GCC rejects.  These lines are patched in-tree
# (see hines/hines_d@.c, lines 65/67/73 — replaced with comments).
# No functional change: the fields are opaque OCL-internal padding not
# accessible via GENESIS scripting.

make nxgenesis           # builds WITHOUT USE_OPENCL (flag not set)
cp nxgenesis nxgenesis_nocl
```

Verify:
```bash
nm nxgenesis_nocl | grep ocl_chip_update   # must return empty
```

---

## Step 3: Build `nxgenesis` (GPU arm, USE_OPENCL=1)

The top-level Makefile does NOT forward `USE_OPENCL` to subdirectory makes.
It must be set as a make variable when calling the hines submake directly:

```bash
cd genesis/src/hines
# Delete OCL-affected objects to force recompile:
rm -f hines.o hines_4chip.o opencl/ocl_hsolve.o hineslib.o

make USE_OPENCL=1 \
     CC="gcc" AR="ar" RANLIB="ranlib" OS="BSD" MACHINE="Linux" \
     CFLAGS_IN="-O2 -D__NO_MATH_INLINES -DLONGWORDS -std=gnu89 \
                -Wno-implicit-function-declaration -Wno-int-conversion \
                -Wno-incompatible-pointer-types -Wno-strict-prototypes \
                -I/usr/lib/x86_64-linux-gnu/include \
                -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X"
cd ..

# Relink nxgenesis (picks up the new OCL hineslib.o):
make nxgenesis
```

Verify:
```bash
nm nxgenesis | grep ocl_chip_update   # must show two symbols
```

---

## Step 4: Run the benchmarks

Scripts are in `paper/`. Both use `nxgenesis_nocl` for the CPU arm and
`nxgenesis` for the GPU arm.

### Extreme 5-rep (6 configs × 5 reps, ~20 min)

```bash
./paper/run_genesis25_cpu_gpu_extreme_5rep.sh
```

Output: `paper/genesis25_cpu_gpu_extreme_5rep.csv`,
        `paper/genesis25_cpu_gpu_extreme_5rep_summary.csv`,
        `paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv`

### Long-run 4 × 2h (reviewer stress test)

```bash
./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
```

Rerun a single session (e.g. session 2 only):
```bash
START_SESSION=2 END_SESSION=2 ./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
```

Output: `paper/genesis25_cpu_gpu_longrun_raw.csv`,
        `paper/genesis25_cpu_gpu_longrun_summary.csv`

---

## Binary checksums

Recorded 2026-06-26 (v5: scheduler fix + fp32 port + hsolve inject fix):

```
9c3cf331b192339c03ea642a7d8a825d0c33a981fe48d2b92a3e1e25af487825  genesis/src/nxgenesis
2ea8c5f9b9943b76b0a11a3a657aaf293d65971d8c4640ab6c2ee63a383145ef  genesis/src/nxgenesis_nocl
```

---

## Known issues and workarounds

| Issue | Cause | Fix |
|-------|-------|-----|
| `No rule to make netcdflib.o` | `fflibs` sentinel stale after clean | Delete `fflibs`, rebuild (Step 1) |
| `ncconfig.h: No such file` | configure cross-compile false positive | Use committed `ncconfig.h` (Step 1) |
| `sizeof(#)` in `hines_d@.c` | Code generator emits invalid C for anonymous struct fields | Three lines commented out in-tree (Step 2) |
| `USE_OPENCL` not propagated | Top-level Makefile doesn't forward it to subdirs | Build hines directly with `USE_OPENCL=1` (Step 3) |
| `ncdump` link failure | `yylex` undefined from `libfl` | Irrelevant — only `libsrc/libnetcdf.a` is needed, not ncdump |
| ~~"GPU" arm not slower despite OCL enabled~~ | ~~Radeon 890M iGPU has no fp64 OpenCL support~~ | Fixed in commit `567395d`: kernel ported to fp32; rusticl now dispatches GPU correctly |
