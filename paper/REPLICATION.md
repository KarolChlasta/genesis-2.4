# Replication Guide: GENESIS 2.5 CPU vs GPU Benchmarks

## Overview

This document records every build and run step needed to reproduce the CPU vs GPU
benchmark results reported in `paper/manuscript_genesis_2_5_proposal.md`.

A clean CPU vs GPU comparison requires **two headless binaries built from the same
source** — one with the OpenCL channel-update kernel compiled in (`USE_OPENCL=1`)
and one without. Using the X11-linked `genesis` binary as the CPU arm is invalid:
it has per-element construction overhead from the GUI toolkit that scales with
network size and is unrelated to GPU acceleration. Full investigation:
`paper/x11_binary_confound_investigation.md`.

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

The `ocl_channel.cl` kernel uses `double` throughout and requires `cl_khr_fp64`.
Mesa rusticl on this GPU reports `CL_DEVICE_DOUBLE_FP_CONFIG=0` and does not
expose `cl_khr_fp64`, so the kernel fails to compile under rusticl and
`ocl_chip_update` falls back to CPU for the entire run. The one-time startup
diagnostic `"OCL: urzadzenie nie wspiera fp64, wylaczam GPU"` confirms this.

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
eliminating the per-step PCIe transfer overhead). Expected results on ROCm:

| Configuration | step 5000 time | vs CPU |
|---|---|---|
| CPU (nxgenesis_nocl, N=2000) | ~1.6 s | 1× |
| GPU single-step (nxgenesis, N=2000) | ~0.67 s | 2.4× |
| GPU multiloop (nxgenesis, N=2000) | ~0.08 s | ~20× |

At larger N (GPU more saturated): speedup scales toward 50-100×.
In the container with Mesa rusticl (no fp64): both arms run on CPU, speedup = 1×,
warning `"nie wspiera fp64"` is printed.

**The end-to-end CPU vs GPU benchmark campaign** (`run_genesis25_cpu_gpu_extreme_5rep.sh`)
ran inside the container and used Mesa rusticl (no fp64), so both arms ran CPU
code. The speedup ratio of ~1.0 reflects a CPU-vs-CPU comparison with matched
headless binaries.

---

## Step 1: Restore the netcdf library (one-time, after clean)

The GENESIS diskio subsystem bundles netcdf-3.4. Its `configure` script fails on
this platform (cross-compile false positive). A pre-filled `ncconfig.h` for Linux
x86_64 is committed at:

```
genesis/src/diskio/interface/netcdf/netcdf-3.4/src/libsrc/ncconfig.h
```

If the build fails with `No rule to make target 'diskio/interface/netcdf/netcdflib.o'`,
the stale `fflibs` sentinel exists but the objects were deleted. Fix:

```bash
rm genesis/src/diskio/interface/netcdf/netcdflib.o 2>/dev/null || true
rm genesis/src/diskio/interface/fflibs 2>/dev/null || true

# Build libnetcdf.a (configure step skipped — ncconfig.h is pre-filled):
cd genesis/src/diskio/interface/netcdf/netcdf-3.4/src
CC=gcc CPICOPT="" CXX="" FC="" AR=ar YACC=bison ./configure || true
make libsrc/all         # only libsrc is needed; ncdump will fail, ignore it
cd ../../../../../..

# Touch the netcdflib sentinel and build the GENESIS wrapper object:
touch genesis/src/diskio/interface/netcdf/netcdflib
cd genesis/src/diskio/interface/netcdf
make CC="gcc" \
     CFLAGS_IN="-O2 -D__NO_MATH_INLINES -DLONGWORDS -Dnetcdf -DFMT1 -DINCSPRNG \
                -DNO_X -std=gnu89 -Wno-implicit-function-declaration \
                -Wno-int-conversion -Wno-incompatible-pointer-types \
                -Wno-strict-prototypes" \
     LD="ld" LDFLAGS="" AR="ar" RANLIB="ranlib"
cd ../../../..
```

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

Recorded 2026-06-24 (v3: multiloop kernel + kernel_multi release):

```
4438cdc1c78e7793202616890a5dadbb1f52de165e01b5c3ddc18959aedac5e0  genesis/src/nxgenesis
7bc0bf0d2276c18a3d5366e460d2170c453d0e94c17ef0ee0d8f11401653e5fb  genesis/src/nxgenesis_nocl
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
| "GPU" arm not slower despite OCL enabled | Radeon 890M iGPU has no fp64 OpenCL support (`CL_DEVICE_DOUBLE_FP_CONFIG=0`, `cl_khr_fp64` absent) — kernel compile fails, silent CPU fallback every step | By design — code now detects this once at startup, prints diagnostic, and disables OCL for the run |
