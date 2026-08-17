#!/bin/bash
# Measure the OpenCL backend on both cluster cards.
#
# The paper's only OpenCL performance figures come from a laptop integrated GPU.
# CUDA is reported on the A40 and the A100, and OpenCL should be too: same
# hardware, same protocol, no private machine in the results.
#
# Two hazards this script exists to handle.
#
# 11_build_opencl.sh runs `make clean` and overwrites nxgenesis -- the CUDA
# binary every other measurement in this paper used. Both binaries are copied
# with checksums before anything is built, and an EXIT/INT/TERM trap restores
# them however the script ends, including a dropped connection.
#
# $HOME is shared between the nodes, so the build must happen exactly once.
# Building on inf02 and inf03 together would have them overwriting each other's
# objects in the same tree. This builds here, then benchmarks over ssh on each
# node in turn with BENCH_ONLY=1.
set -u
R="$HOME/genesis-2.5"
SELF="$HOME/$(basename "$0")"
cd "$R" || exit 1

bench_here() {
    export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
    export GENESIS_OCL_TREE_MAX_NCOMPTS=0
    cd "$R" || exit 1
    S=genesis/Scripts/benchmark/hh_spiking_benchmark.g
    K=50000
    echo "  card: $(nvidia-smi --query-gpu=name --format=csv,noheader | head -1)"
    ldd genesis/src/nxgenesis 2>/dev/null | grep -qi opencl \
        || echo "  WARN: libOpenCL not linked into this binary"
    for N in 500 5000 50000; do
        ctot=0; gtot=0
        for r in 1 2 3; do
            t0=$(date +%s%N)
            ./genesis/src/nxgenesis_nocl -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
            t1=$(date +%s%N)
            GENESIS_OCL_MULTILOOP=$K ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
            t2=$(date +%s%N)
            ctot=$(awk "BEGIN{print $ctot+($t1-$t0)/1e9}")
            gtot=$(awk "BEGIN{print $gtot+($t2-$t1)/1e9}")
        done
        awk -v c="$ctot" -v g="$gtot" -v N="$N" \
            'BEGIN{printf "  N=%-6s CPU %7.2fs  OpenCL %7.2fs  speedup %5.1fx\n", N, c/3, g/3, c/g}'
    done
}

# A benchmark-only invocation must not touch the backup or the trap.
if [ "${BENCH_ONLY:-0}" = 1 ]; then bench_here; exit 0; fi

echo "== backing up the CUDA build =="
BK="$HOME/backup_cuda_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$BK"
for f in genesis/src/nxgenesis genesis/src/nxgenesis_nocl; do
    [ -f "$f" ] || { echo "missing $f -- nothing to protect, aborting" >&2; exit 1; }
    cp -p "$f" "$BK/$(basename "$f")"
done
( cd "$BK" && md5sum ./* > checksums.txt && cat checksums.txt )
echo "backup: $BK"

restore() {
    echo
    echo "== restoring the CUDA build =="
    cp -p "$BK/nxgenesis" "$R/genesis/src/nxgenesis"
    cp -p "$BK/nxgenesis_nocl" "$R/genesis/src/nxgenesis_nocl"
    ( cd "$BK" && md5sum -c checksums.txt --quiet 2>/dev/null ) && echo "backup verified intact"
    ( cd "$R/genesis/src" && md5sum nxgenesis nxgenesis_nocl )
    echo "restored from $BK"
}
trap restore EXIT INT TERM

echo
echo "== building the OpenCL backend (once; \$HOME is shared) =="
if ! sh cluster_bringup/11_build_opencl.sh > /tmp/ocl_build.log 2>&1 || [ ! -x genesis/src/nxgenesis ]; then
    echo "OpenCL build FAILED"; grep -iE "error" /tmp/ocl_build.log | head -8; exit 1
fi
ldd genesis/src/nxgenesis | grep -i opencl || echo "WARN: libOpenCL not linked"

echo
echo "== OpenCL correctness against the fp64 CPU solver =="
cpu=$(./genesis/src/nxgenesis_nocl -nosimrc -notty -batch \
        genesis/Scripts/benchmark/hh1952_ap_verify.g 8 200 2>&1 | sed -n 's/^RESULT_VM= *//p')
ocl=$(GENESIS_OCL_MULTILOOP=210 ./genesis/src/nxgenesis -nosimrc -notty -batch \
        genesis/Scripts/benchmark/hh1952_ap_verify.g 8 200 2>&1 | sed -n 's/^RESULT_VM= *//p')
awk -v a="$cpu" -v b="$ocl" 'BEGIN{d=a-b; printf "CPU %s  OpenCL %s  |diff| %.2e V\n", a, b, (d<0?-d:d)}'

echo
echo "== OpenCL vs CPU, single-compartment multiloop, K=50000 =="
for node in inf02 inf03; do
    echo "[$node]"
    ssh -o BatchMode=yes -n "$node" "BENCH_ONLY=1 bash $SELF" 2>&1 | grep -vE "^==|^backup"
done
