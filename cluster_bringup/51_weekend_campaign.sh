#!/bin/sh
# GENESIS 2.5 weekend multi-replicate multi-compartment GPU campaign.
# Post O(n^2)->O(n) construction fix (2026-07-25): 10 replicates x 13 N
# values x {linear-chain, branching} x {CPU, GPU} on the current node.
# Runs in an hour or so now, not the weekend it was scoped for, but
# launched via nohup regardless so it survives disconnection either way.
#
# Usage: nohup ./51_weekend_campaign.sh [NODE_LABEL] > campaign.out 2>&1 &
#
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-25.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"

NODE=${1:-$(hostname)}
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
OUT="$HERE/logs/weekend_campaign_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
mkdir -p "$HERE/logs"

CPU_BIN="./genesis/src/nxgenesis_nocl"
GPU_BIN="./genesis/src/nxgenesis"
LC_SCRIPT="genesis/Scripts/benchmark/hh_multicompartment_benchmark.g"
BR_SCRIPT="genesis/Scripts/benchmark/hh_branching_multicompartment_benchmark.g"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
# Without this the tree multiloop refuses any hsolve over 20000 compartments
# and silently falls back to per-step dispatch, which measures a different code
# path entirely -- at N=50000 that alone looks like a 3-7x GPU slowdown.
export GENESIS_OCL_TREE_MAX_NCOMPTS=0   # real cluster HW, no iGPU cap needed

# Refuse to measure on a card someone else is using: a foreign job once inflated
# every GPU time in the companion wall-clock sweep by ~30% while leaving the CPU
# arm untouched, and the contention was steady enough that the curve still looked
# smooth and monotonic. Set ALLOW_BUSY_GPU=1 to override deliberately.
USED=$(nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits 2>/dev/null | head -1)
if [ "${ALLOW_BUSY_GPU:-0}" != "1" ] && [ -n "$USED" ] && [ "$USED" -gt 500 ]; then
    echo "ERROR: $USED MiB already allocated on $GPU -- timings would be inflated." >&2
    echo "       Wait for the card, or set ALLOW_BUSY_GPU=1 if that is intended." >&2
    exit 1
fi

echo "node,gpu,topology,ncomp_per_neuron,n_neurons,total_comps,mode,rep,t_per_step_s" > "$OUT"
echo "Weekend campaign on $NODE ($GPU) -> $OUT"

run_lc() {
    n=$1; steps=$2; mode=$3; rep=$4
    if [ "$mode" = "CPU" ]; then bin="$CPU_BIN"; cm=1; extra=""
    else bin="$GPU_BIN"; cm=4; extra="GENESIS_CUDA_MULTILOOP=$((steps+10)) GENESIS_OCL_MULTILOOP=$((steps+10))"
    fi
    line=$(timeout 300 env GENESIS_BENCH_CHANMODE=$cm GENESIS_BENCH_NCOMP=16 $extra \
        "$bin" -nosimrc -notty -batch "$LC_SCRIPT" "$n" "$steps" </dev/null 2>&1 \
        | grep RESULT_T_PER_STEP | awk -F= '{print $2}' | tr -d ' ')
    [ -z "$line" ] && line="NA"
    echo "$NODE,$GPU,linear-chain,16,$n,$((n*16)),$mode,$rep,$line" >> "$OUT"
    echo "  rep=$rep linear-chain $mode n=$n -> $line s/step"
}

run_branch() {
    n=$1; steps=$2; mode=$3; rep=$4
    if [ "$mode" = "CPU" ]; then bin="$CPU_BIN"; cm=1; extra=""
    else bin="$GPU_BIN"; cm=4; extra="GENESIS_CUDA_MULTILOOP=$((steps+10)) GENESIS_OCL_MULTILOOP=$((steps+10))"
    fi
    line=$(timeout 300 env GENESIS_BENCH_CHANMODE=$cm $extra \
        "$bin" -nosimrc -notty -batch "$BR_SCRIPT" "$n" "$steps" 4 4 </dev/null 2>&1 \
        | grep RESULT_T_PER_STEP | awk -F= '{print $2}' | tr -d ' ')
    [ -z "$line" ] && line="NA"
    echo "$NODE,$GPU,branching-4x4,17,$n,$((n*17)),$mode,$rep,$line" >> "$OUT"
    echo "  rep=$rep branching $mode n=$n -> $line s/step"
}

for rep in 1 2 3 4 5 6 7 8 9 10; do
    for n in 100 500 1000 2000 3000 5000 7000 10000 15000 20000 30000 40000 50000; do
        steps=200
        [ "$n" -ge 5000 ] && steps=100
        run_lc "$n" "$steps" CPU "$rep"
        run_lc "$n" "$steps" GPU "$rep"
        run_branch "$n" "$steps" CPU "$rep"
        run_branch "$n" "$steps" GPU "$rep"
    done
done

echo "Done -> $OUT"
