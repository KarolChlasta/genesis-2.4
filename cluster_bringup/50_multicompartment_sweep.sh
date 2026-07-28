#!/bin/sh
# GENESIS 2.5 multicompartment GPU-tree-elimination benchmark sweep.
# Runs hh_multicompartment_benchmark.g across an N x NCOMP grid, CPU vs GPU
# (tree multiloop), on the current node. Appends CSV rows to $OUT.
# GPU backend auto-selected by which binary exists (nxgenesis, built with
# either USE_OPENCL or USE_CUDA per whatever cluster_bringup/1x_build*.sh
# ran last on this node).
#
# Usage: ./50_multicompartment_sweep.sh [NODE_LABEL]
#
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-25.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"

NODE=${1:-$(hostname)}
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
OUT="$HERE/logs/multicompartment_sweep_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
mkdir -p "$HERE/logs"

B="genesis/Scripts/benchmark/hh_multicompartment_benchmark.g"
CPU_BIN="./genesis/src/nxgenesis_nocl"
GPU_BIN="./genesis/src/nxgenesis"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
export GENESIS_OCL_TREE_MAX_NCOMPTS=0   # this is real cluster HW, no iGPU cap needed

echo "node,gpu,ncomp,n_neurons,total_comps,mode,t_per_step_s" > "$OUT"
echo "Sweep on $NODE ($GPU) -> $OUT"

run_one() {
    ncomp=$1; n=$2; steps=$3; mode=$4
    total=$((ncomp * n))
    if [ "$mode" = "CPU" ]; then
        bin="$CPU_BIN"; cm=1; extra=""
    else
        bin="$GPU_BIN"; cm=4
        extra="GENESIS_CUDA_MULTILOOP=$((steps+10)) GENESIS_OCL_MULTILOOP=$((steps+10))"
    fi
    line=$(timeout 300 env GENESIS_BENCH_CHANMODE=$cm GENESIS_BENCH_NCOMP=$ncomp $extra \
        "$bin" -nosimrc -notty -batch "$B" "$n" "$steps" </dev/null 2>&1 \
        | grep RESULT_T_PER_STEP | awk -F= '{print $2}' | tr -d ' ')
    if [ -z "$line" ]; then
        echo "  WARN: $mode ncomp=$ncomp n=$n FAILED/empty"
        line="NA"
    fi
    echo "$NODE,$GPU,$ncomp,$n,$total,$mode,$line" >> "$OUT"
    echo "  $mode ncomp=$ncomp n=$n total=$total -> $line s/step"
}

# Fixed NCOMP=16 (realistic dendrite depth), sweep N.
for n in 100 500 1000 2000 5000 10000; do
    steps=200
    [ "$n" -ge 5000 ] && steps=100
    run_one 16 "$n" "$steps" CPU
    run_one 16 "$n" "$steps" GPU
done

# Fixed N=1000, sweep NCOMP (compartment depth).
for ncomp in 4 8 32 64; do
    run_one "$ncomp" 1000 200 CPU
    run_one "$ncomp" 1000 200 GPU
done

echo "Done -> $OUT"
