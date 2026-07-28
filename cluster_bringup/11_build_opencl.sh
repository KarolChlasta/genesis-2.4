#!/bin/sh
# Build nxgenesis with the OpenCL backend on the current node (inf02=A40).
# Companion to 10_build.sh (CUDA) -- validates whether the hines_tree_eliminate
# kernel (GENESIS 2.5, 2026-07-25) works on this cluster's NVIDIA OpenCL ICD,
# not just the local AMD iGPU it was developed against.
#
# Toolchain notes for this cluster (RHEL 8.5.0 gcc, no CL/cl.h in /usr/include):
#   - libOpenCL.so IS in the standard system lib path (ldconfig -p shows
#     /lib64/libOpenCL.so, NVIDIA driver's ICD) -- no -L needed for linking.
#   - CL/cl.h is NOT in /usr/include, only under the CUDA toolkit's own
#     include tree. Using CPATH (a GCC env var, not threaded through the
#     Makefile's CFLAGS_IN composition at all) avoids the documented
#     CFLAGS-propagation-through-recursive-submake pitfall from the CUDA
#     build fixes.
#   - Fix 1 (libfl) reused as-is from 10_build.sh.
#
# Prepared by Karol Chlasta (karol@chlasta.pl).
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
SRC="$ROOT/genesis/src"

: "${CUDA_HOME:=/storage/opt/cuda/cuda-13.0}"
export CPATH="$CUDA_HOME/targets/x86_64-linux/include${CPATH:+:$CPATH}"
CC=${CC:-$(command -v gcc)}

STUB="$ROOT/locallib/libfl.a"
if [ ! -f "$STUB" ]; then
  mkdir -p "$ROOT/locallib"
  printf 'int yywrap(void){return 1;}\n' > "$ROOT/locallib/yywrap.c"
  gcc -c "$ROOT/locallib/yywrap.c" -o "$ROOT/locallib/yywrap.o"
  ar rcs "$STUB" "$ROOT/locallib/yywrap.o"
fi
EXTRALIBS="sprng/lib/liblfg.a -lncurses -ltinfo -lOpenCL"

echo "CPATH=$CPATH"
echo "CC=$CC"
echo "EXTRALIBS=$EXTRALIBS"

cd "$SRC"

echo "== [1/2] CPU reference build =="
make clean >/dev/null 2>&1
make LEXLIB="$STUB" nxgenesis
cp -f nxgenesis nxgenesis_nocl
cp -f nxgenesis "$HERE/nxgenesis_nocl_ocl.bak"

echo "== [2/2] OpenCL build =="
make clean >/dev/null 2>&1
make USE_OPENCL=1 EXTRALIBS="$EXTRALIBS" LEXLIB="$STUB" nxgenesis
[ -x nxgenesis_nocl ] || cp -f "$HERE/nxgenesis_nocl_ocl.bak" nxgenesis_nocl

echo "== done =="
ls -la nxgenesis nxgenesis_nocl
ldd ./nxgenesis | grep -i opencl || echo "WARN: libOpenCL not linked"
