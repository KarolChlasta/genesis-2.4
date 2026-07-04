#!/usr/bin/env bash
# GENESIS 2.5 CUDA bring-up + validation for a fresh RunPod pod.
#
# Goal: spend paid GPU time on building and measuring, not fumbling. Run top to
# bottom on a CUDA pod (e.g. RTX 4090, sm_89). Each phase is guarded and echoes a
# checkpoint; if one fails, fix it and re-run from that phase (set START_PHASE).
#
#   bash runpod_validate.sh            # full run
#   START_PHASE=5 bash runpod_validate.sh   # skip straight to the CUDA build
#
# NOTE: the CUDA backend has NOT been compiled on real hardware yet, so phases
# 5-7 are the ones most likely to need a small fix on first contact (host-compiler
# ABI, -arch, or the -lcudart link). That is exactly why we start on the cheapest
# capable card. See BUILD_CUDA.md.
set -uo pipefail

REPO="${REPO:-https://github.com/KarolChlasta/genesis-2.4}"
DIR="${DIR:-$HOME/genesis-2.4}"
CUDA_HOME="${CUDA_HOME:-/usr/local/cuda}"
CUDA_ARCH="${CUDA_ARCH:-sm_89}"     # RTX 4090=sm_89, A100=sm_80, H100=sm_90, 5090=sm_120
START_PHASE="${START_PHASE:-1}"
CFLAGS_COMMON="-O2 -D__NO_MATH_INLINES -DLONGWORDS -std=gnu89 \
  -Wno-implicit-function-declaration -Wno-int-conversion \
  -Wno-incompatible-pointer-types -Wno-strict-prototypes"

say(){ echo -e "\n==== [phase $1] $2 ===="; }
phase(){ [ "$1" -ge "$START_PHASE" ]; }

# 1 ----------------------------------------------------------- system + toolkit
if phase 1; then
  say 1 "system deps + toolkit check"
  # ocl-icd-opencl-dev provides libOpenCL.so: GENESIS links -lOpenCL into EVERY
  # binary (even the code_g generator), so without the loader the whole build
  # dies at "cannot find -lOpenCL" -> "No rule to make sim/simlib.o". CUDA pod
  # images have CUDA but no OpenCL loader, so install it (loader stub only).
  apt-get update -qq && apt-get install -y -qq build-essential bison flex \
      libncurses-dev git ca-certificates python3 python3-matplotlib \
      ocl-icd-opencl-dev >/dev/null || true
  # nvcc may be installed but not on PATH (e.g. /usr/local/cuda-12.x/bin)
  export PATH="$CUDA_HOME/bin:$PATH"
  command -v nvcc >/dev/null || { echo "FATAL: nvcc not found; use a CUDA *devel* pod image"; exit 1; }
  nvcc --version | tail -1
  nvidia-smi --query-gpu=name,memory.total,clocks.max.sm --format=csv,noheader || true
fi

# 2 ------------------------------------------------------------------ get source
if phase 2; then
  say 2 "clone/update source"
  if [ -d "$DIR/.git" ]; then git -C "$DIR" pull --ff-only || true; else git clone "$REPO" "$DIR"; fi
fi
cd "$DIR/genesis/src" || { echo "FATAL: source tree missing"; exit 1; }

# 3 --------------------------------------------------- diskio libs (VERIFIED recipe)
# Verified on a clean clone. macros.make is now committed (the bundled netcdf-3.4
# configure false-positives as cross-compile and never emits it), so NO configure
# is run. `make nxgenesis` builds most diskio objects itself but NOT these three,
# which the final link needs — build them explicitly first:
#   libnetcdf.a  (netcdf-3.4 libsrc)   netcdflib.o  (wrapper)   FMT1lib.o
if phase 3; then
  say 3 "build diskio libs (netcdf libsrc + netcdflib.o + FMT1lib.o, no configure)"
  DCF="$CFLAGS_COMMON -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X"
  ( cd diskio/interface/netcdf/netcdf-3.4/src && make libsrc/all ) \
    || { echo "FATAL: libnetcdf.a build failed (is macros.make present?)"; exit 1; }
  ( cd diskio/interface/netcdf && make CC=gcc CFLAGS_IN="$DCF" LD=ld LDFLAGS="" AR=ar RANLIB=ranlib ) \
    || { echo "FATAL: netcdflib.o build failed"; exit 1; }
  ( cd diskio/interface/FMT1 && make CC=gcc CFLAGS_IN="$DCF" LD=ld LDFLAGS="" AR=ar RANLIB=ranlib ) \
    || { echo "FATAL: FMT1lib.o build failed"; exit 1; }
  ls diskio/interface/netcdf/netcdflib.o diskio/interface/FMT1/FMT1lib.o \
     diskio/interface/netcdf/netcdf-3.4/src/libsrc/libnetcdf.a >/dev/null 2>&1 \
     && echo "  diskio libs OK ✓" || { echo "FATAL: a diskio lib is missing"; exit 1; }
fi

# 4 ------------------------------------------------------- CPU arm (no accel)
# Plain `make nxgenesis` — the committed Makefile already carries the modern-GCC
# flags (-std=gnu89, -Wno-*); it builds fflib.o/diskiolib.o and links against the
# phase-3 libs. Do NOT override CFLAGS here (it drops those flags and breaks GCC 15).
if phase 4; then
  say 4 "build nxgenesis_nocl (fp64 CPU baseline)"
  make nxgenesis 2>&1 | tail -5
  [ -f nxgenesis ] || { echo "FATAL: nxgenesis (CPU) did not build"; exit 1; }
  cp -f nxgenesis nxgenesis_nocl
  nm nxgenesis_nocl | grep -q ocl_chip_update && echo "WARN: nocl has OCL syms" || echo "  nocl clean ✓"
fi

# 5 --------------------------------------------------------- CUDA objects (nvcc)
if phase 5; then
  say 5 "compile CUDA backend (nvcc + gcc glue)"
  ( cd hines && rm -f hines.o hines_4chip.o hineslib.o cuda/cuda_backend.o cuda/cuda_hsolve.o
    make USE_CUDA=1 CUDA_HOME="$CUDA_HOME" NVCC="$CUDA_HOME/bin/nvcc" \
      NVCCFLAGS="-O2 -std=c++14 -arch=$CUDA_ARCH -ccbin gcc" \
      CC=gcc AR=ar RANLIB=ranlib OS=BSD MACHINE=Linux \
      CFLAGS_IN="$CFLAGS_COMMON -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X" 2>&1 | tail -20 )
  ls -la hines/cuda/cuda_backend.o hines/cuda/cuda_hsolve.o 2>/dev/null || \
    { echo "FATAL: CUDA objects not built — inspect the tail above"; exit 1; }
fi

# 6 ------------------------------------------------- link GPU binary (-lcudart)
# NB: passing EXTRALIBS/CFLAGS to `make nxgenesis` reorders the link and drops
# the termcap libs (undefined `tgetstr`). Instead relink explicitly, reusing the
# object list from the working CPU link and appending `-lcudart` LAST so library
# order is preserved. hines/hineslib.o already contains the CUDA objects (phase 5).
if phase 6; then
  say 6 "link nxgenesis with the CUDA hineslib + -lcudart"
  OBJS="sim/simlib.o sys/utillib.o ss/ss.o shell/shelllib.o par/parlib.o \
    buffer/buflib.o segment/seglib.o hh/hhlib.o device/devlib.o out/outlib.o \
    olf/olflib.o tools/toollib.o concen/conclib.o hines/hineslib.o user/userlib.o \
    param/paramlib.o pore/porelib.o oldconn/axon/axonlib.o oldconn/synapse/synlib.o \
    oldconn/personal/perlib.o oldconn/sim/simconnlib.o oldconn/tools/toolconnlib.o \
    diskio/interface/netcdf/netcdflib.o \
    diskio/interface/netcdf/netcdf-3.4/src/libsrc/libnetcdf.a \
    diskio/interface/FMT1/FMT1lib.o diskio/diskiolib.o kinetics/kinlib.o \
    chemesis/chemlib.o newconn/newconnlib.o nxloadlib.o"
  gcc $CFLAGS_COMMON -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X $OBJS \
      -lfl -lm sprng/lib/liblfg.a -lncurses -ltinfo -lOpenCL \
      -L"$CUDA_HOME/lib64" -lcudart -o nxgenesis 2>&1 | tail -8
  nm nxgenesis 2>/dev/null | grep -q cuda_chip_update \
    && { echo "  CUDA symbols present ✓"; ldd nxgenesis | grep -i cudart; } \
    || { echo "FATAL: cuda_chip_update not linked"; exit 1; }
fi

# 7 ------------------------------------------------------- lock clocks + validate
if phase 7; then
  say 7 "lock clocks + numerical parity (fp32 CUDA vs fp64 CPU)"
  MAXSM=$(nvidia-smi --query-gpu=clocks.max.sm --format=csv,noheader,nounits | head -1)
  nvidia-smi -pm 1 >/dev/null 2>&1 || true
  [ -n "${MAXSM:-}" ] && nvidia-smi -lgc "$MAXSM","$MAXSM" >/dev/null 2>&1 && echo "  locked SM clock @ ${MAXSM}MHz" || echo "  (clock lock unavailable — continuing)"
  V=genesis/Scripts/benchmark/hh1952_ap_verify.g
  cpu=$(./nxgenesis_nocl -nosimrc -notty -batch "$DIR/$V" 8 200 2>/dev/null | grep RESULT_VM)
  gpu=$(GENESIS_CUDA_MULTILOOP=210 ./nxgenesis -nosimrc -notty -batch "$DIR/$V" 8 200 2>/dev/null | grep RESULT_VM)
  echo "  CPU  $cpu"; echo "  CUDA $gpu"
  echo "  -> expect agreement to ~1e-6 V and NEURONS_AGREE: YES on both"
fi

# 8 ----------------------------------------------------------------- speedup
if phase 8; then
  say 8 "CUDA speedup sweep (small + large N to saturate the GPU)"
  # reuse the campaign harness (parses CUDA MULTILOOP lines); extend N upward
  # because a datacenter/consumer GPU won't saturate until far past N=5000.
  cd "$DIR"
  python3 - <<'PY'
import importlib.util, statistics
s=importlib.util.spec_from_file_location("c","paper/run_overnight_campaign.py")
c=importlib.util.module_from_spec(s); s.loader.exec_module(c)
c.GPU_BIN=c.ROOT/"genesis/src/nxgenesis"; c.CPU_BIN=c.ROOT/"genesis/src/nxgenesis_nocl"
print(f"{'N':>8} {'CPUstep_s':>10} {'GPUdisp_ms':>11} {'speedup':>8}")
for N in (500,2000,5000,10000,50000,100000,200000):
    cw,co=c.run_once(c.CPU_BIN,c.TIMING_G,N,50000,None)
    gw,go=c.run_once(c.GPU_BIN,c.TIMING_G,N,50000,50000)
    cs=c.cpu_step_time(co); gd=c.gpu_dispatch_ms(go)
    if cs and gd: print(f"{N:>8} {cs:>10.3f} {gd:>11.1f} {cs/(gd/1000):>7.1f}x")
    else: print(f"{N:>8}  parse-fail (check output)")
PY
fi

say 9 "done — copy paper/campaign_*.csv off the pod before terminating it"
