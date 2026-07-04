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
  apt-get update -qq && apt-get install -y -qq build-essential bison flex \
      libncurses-dev git ca-certificates python3 python3-matplotlib >/dev/null || true
  command -v nvcc >/dev/null || { echo "FATAL: nvcc not found; use a CUDA pod image"; exit 1; }
  nvcc --version | tail -1
  nvidia-smi --query-gpu=name,memory.total,clocks.max.sm --format=csv,noheader || true
fi

# 2 ------------------------------------------------------------------ get source
if phase 2; then
  say 2 "clone/update source"
  if [ -d "$DIR/.git" ]; then git -C "$DIR" pull --ff-only || true; else git clone "$REPO" "$DIR"; fi
fi
cd "$DIR/genesis/src" || { echo "FATAL: source tree missing"; exit 1; }

# 3 ------------------------------------------------------------ netcdf (diskio)
# The bundled netcdf-3.4 configure false-positives as cross-compile; ncconfig.h
# is pre-filled in-tree. Only libsrc is needed (ncdump link failure is harmless).
if phase 3; then
  say 3 "build bundled netcdf libsrc"
  ( cd diskio/interface/netcdf/netcdf-3.4/src && \
    CC=gcc CPICOPT="" CXX="" FC="" AR=ar YACC=bison ./configure >/dev/null 2>&1 || true; \
    make libsrc/all >/dev/null 2>&1 || true )
  touch diskio/interface/netcdf/netcdflib || true
fi

# 4 ------------------------------------------------------- CPU arm (no accel)
if phase 4; then
  say 4 "build nxgenesis_nocl (fp64 CPU baseline)"
  make -s nxgenesis CFLAGS="$CFLAGS_COMMON -DNO_X -Dnetcdf -DFMT1 -DINCSPRNG" 2>&1 | tail -5
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
if phase 6; then
  say 6 "link nxgenesis with USE_CUDA + -lcudart"
  make -s nxgenesis USE_CUDA=1 CUDA_HOME="$CUDA_HOME" \
      CFLAGS="$CFLAGS_COMMON -DUSE_CUDA -DNO_X -Dnetcdf -DFMT1 -DINCSPRNG" \
      EXTRALIBS="-L$CUDA_HOME/lib64 -lcudart" 2>&1 | tail -10
  nm nxgenesis | grep -q cuda_chip_update && echo "  CUDA symbols present ✓" \
    || echo "WARN: cuda_chip_update not linked — check EXTRALIBS/TERMCAP (-lcudart)"
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
