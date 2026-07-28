#!/bin/sh
# GENESIS 2.5 multi-replicate CUDA single-compartment kernel campaign.
# Resolves the "Recorded next steps" item from the manuscript: Table 3 (RTX
# 4090) was single-replicate; this gives the same N grid (500, 5000, 50000)
# mean +/- std over 10 replicates on UMCS cluster-class GPUs (A40, A100).
#
# Timing extraction avoids the CPU-timer/GPU-blocked-wait confound already
# documented in the paper: the CPU arm's time comes from GENESIS's own
# native "completed N steps in X cpu seconds" report (reliable for a
# pure-CPU, non-blocking computation); the GPU arm's time comes from the
# device-side "CUDA MULTILOOP: ... | total X ms" dispatch report, NOT the
# script's {cpu} timer (which reads ~0 for both arms in this multiloop
# script -- the exact confound the paper's validation-discipline
# paragraph warns about).
#
# Usage: ./52_cuda_singlecomp_campaign.sh [NODE_LABEL]
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-25.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"

NODE=${1:-$(hostname)}
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
OUT="$HERE/logs/cuda_singlecomp_campaign_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
mkdir -p "$HERE/logs"

CPU_BIN="./genesis/src/nxgenesis_nocl"
GPU_BIN="./genesis/src/nxgenesis"
BENCH="genesis/Scripts/benchmark/hh_spiking_benchmark.g"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"

echo "node,gpu,n_neurons,n_steps,mode,rep,t_total_s" > "$OUT"
echo "CUDA single-compartment campaign on $NODE ($GPU) -> $OUT"

run_cpu() {
    n=$1; steps=$2; rep=$3
    out=$(timeout 300 "$CPU_BIN" -nosimrc -notty -batch "$BENCH" "$n" "$steps" </dev/null 2>&1)
    t=$(echo "$out" | grep "completed $steps steps" | tail -1 | grep -oP 'in \K[0-9.]+(?= cpu seconds)')
    [ -z "$t" ] && t="NA"
    echo "$NODE,$GPU,$n,$steps,CPU,$rep,$t" >> "$OUT"
    echo "  rep=$rep CPU n=$n -> ${t}s"
}

run_gpu() {
    n=$1; steps=$2; rep=$3
    out=$(timeout 300 env GENESIS_CUDA_MULTILOOP=$steps "$GPU_BIN" -nosimrc -notty -batch "$BENCH" "$n" "$steps" </dev/null 2>&1)
    ms=$(echo "$out" | grep "CUDA MULTILOOP:" | tail -1 | grep -oP 'total \K[0-9.]+(?= ms)')
    if [ -n "$ms" ]; then
        t=$(awk "BEGIN{printf \"%.6f\", $ms/1000}")
    else
        t="NA"
    fi
    echo "$NODE,$GPU,$n,$steps,GPU,$rep,$t" >> "$OUT"
    echo "  rep=$rep GPU n=$n -> ${t}s"
}

for rep in 1 2 3 4 5 6 7 8 9 10; do
    for n in 500 5000 50000; do
        steps=50000
        run_cpu "$n" "$steps" "$rep"
        run_gpu "$n" "$steps" "$rep"
    done
done

echo "Done -> $OUT"
