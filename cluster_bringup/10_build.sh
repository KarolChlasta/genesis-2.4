#!/bin/sh
# Build nxgenesis with the CUDA backend + a CPU-reference binary on the current
# node (inf02=A40/sm_86, inf03=A100/sm_80). VALIDATED on UMCS inf03 (A100),
# 2026-07-23, CUDA 12.8 + gcc 8.5.0. Grounded in
# genesis/src/hines/cuda/BUILD_CUDA.md, with two fixes needed on this cluster:
#
#   Fix 1 (libfl): the cluster has the `flex` binary but not libfl. GENESIS links
#     code_g with -lfl (LEXLIB=-lfl). We build a local yywrap stub libfl.a and
#     override LEXLIB.
#   Fix 2 (EXTRALIBS): genesis/src/Makefile defines EXTRALIBS = $(SPRNGLIB)
#     $(TERMCAP). Passing EXTRALIBS=-lcudart *replaces* it and drops sprng +
#     termcap. We must pass the FULL set: sprng + termcap + cudart + stdc++
#     (the last for the C++ cuda_backend.o -> __gxx_personality_v0).
#
# Prepared by Karol Chlasta (karol@chlasta.pl).
# Overridable: CUDA_HOME, CC, ARCH.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
SRC="$ROOT/genesis/src"

# CUDA (no module on this cluster; pinned 12.8). nvcc is not on PATH by default.
: "${CUDA_HOME:=/storage/opt/cuda/cuda-12.8}"
[ -x "$CUDA_HOME/bin/nvcc" ] && export PATH="$CUDA_HOME/bin:$PATH"
command -v nvcc >/dev/null 2>&1 || { echo "ERROR: nvcc not found (CUDA_HOME=$CUDA_HOME)"; exit 1; }
CC=${CC:-$(command -v gcc)}
if [ -z "${ARCH:-}" ]; then
  cc=$(nvidia-smi --query-gpu=compute_cap --format=csv,noheader 2>/dev/null | head -1 | tr -d '. ')
  ARCH="sm_${cc:-80}"
fi

# Fix 1: local libfl stub.
STUB="$ROOT/locallib/libfl.a"
if [ ! -f "$STUB" ]; then
  mkdir -p "$ROOT/locallib"
  printf 'int yywrap(void){return 1;}\n' > "$ROOT/locallib/yywrap.c"
  gcc -c "$ROOT/locallib/yywrap.c" -o "$ROOT/locallib/yywrap.o"
  ar rcs "$STUB" "$ROOT/locallib/yywrap.o"
fi
# Fix 2: full EXTRALIBS (default sprng+termcap, then cudart+stdc++).
EXTRALIBS="sprng/lib/liblfg.a -lncurses -ltinfo -lOpenCL -L$CUDA_HOME/lib64 -lcudart -lstdc++"
echo "CUDA_HOME=$CUDA_HOME  ARCH=$ARCH  CC=$CC"
echo "LEXLIB=$STUB"
echo "EXTRALIBS=$EXTRALIBS"

cd "$SRC"

# 1) CPU reference (fp64), saved as nxgenesis_nocl.
echo "== [1/2] CPU reference build =="
make clean >/dev/null 2>&1
make LEXLIB="$STUB" nxgenesis
cp -f nxgenesis nxgenesis_nocl
cp -f nxgenesis "$HERE/nxgenesis_nocl.bak"     # survive the next clean

# 2) CUDA build (nxgenesis = CUDA binary).
echo "== [2/2] CUDA build (arch=$ARCH) =="
make clean >/dev/null 2>&1
# Fix 3 (found 2026-07-25, switching inf02->inf03 mid-session; widened
# 2026-07-25 evening after a struct_defs.h ABI change silently corrupted a
# run): `make clean` does not remove ANYTHING under hines/cuda/, plain .c
# files included, not just cuda_backend.o -- that whole subdirectory
# appears to be outside the plain-C Makefile's clean rule's awareness
# (added via the USE_CUDA=1 conditional, which apparently isn't wired into
# `clean` at all). Two symptoms seen from this, both silent (no build
# error) because the stale .o still links successfully:
#   (a) a stale cuda_backend.o built for a DIFFERENT GPU's arch (e.g.
#       inf02's sm_86 reused on inf03) fails at RUNTIME with "no kernel
#       image is available for execution on the device";
#   (b) a stale cuda_hsolve.o compiled against an OLDER struct_defs.h
#       (e.g. before the Element.childtail field was added) silently
#       reads Hsolve fields (ncompts/nchips/nops) at the WRONG byte
#       offset once every OTHER .o has the new layout -- prints
#       "CUDA: hsolve not initialised (n=0 nc=0 no=<garbage>)", disables
#       the CUDA backend for the rest of the run, and silently degrades
#       to a slow CPU/GPU hybrid fallback that still produces numerically
#       plausible (but misleadingly slow, and mislabeled "GPU") results --
#       no crash, no error a casual run would notice.
# Always force the WHOLE directory to rebuild, not just the two files
# previously known to need it.
rm -f hines/cuda/*.o hines/hineslib.o
make USE_CUDA=1 CUDA_HOME="$CUDA_HOME" NVCCFLAGS="-arch=$ARCH -ccbin $CC" \
     EXTRALIBS="$EXTRALIBS" LEXLIB="$STUB" nxgenesis
[ -x nxgenesis_nocl ] || cp -f "$HERE/nxgenesis_nocl.bak" nxgenesis_nocl

echo "== done =="
ls -la nxgenesis nxgenesis_nocl
ldd ./nxgenesis | grep -i cudart || echo "WARN: libcudart not linked"
echo "Next: ./20_validate.sh   (must print NEURONS_AGREE: YES and |CPU-CUDA| ~ 1e-7 V)"
