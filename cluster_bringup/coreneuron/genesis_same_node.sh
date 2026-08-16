#!/bin/sh
# GENESIS arms on the node that ran NEURON and CoreNEURON.
#
# The multi-compartment GENESIS numbers were taken on inf02 (Xeon Gold 6342,
# 2.80 GHz) and the NEURON ones on inf03 (Xeon Platinum 8358, 2.60 GHz). For
# single-threaded arms that clock difference is about 8%, so the two sets are
# not directly comparable. This repeats the GENESIS arms on inf03 so every
# figure in the comparison comes from one machine.
set -u
R="$HOME/genesis-2.5"
cd "$R" || exit 1
export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
# Above 20000 compartments the tree multiloop declines the model and falls back
# to per-step dispatch; 10000 x 16 is well past that.
export GENESIS_OCL_TREE_MAX_NCOMPTS=0

N=${N:-10000}
K=${K:-5000}
REPS=${REPS:-3}
S="genesis/Scripts/benchmark/hh_multicompartment_createmap.g"

USED=$(nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits 2>/dev/null | head -1)
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
if [ -n "$USED" ] && [ "$USED" -gt 500 ]; then
    echo "ABORT: $USED MiB already on $GPU" >&2; exit 1
fi
echo "== GENESIS N=$N NCOMP=16 K=$K on $(hostname) ($GPU) =="

r=1
while [ "$r" -le "$REPS" ]; do
    S1=$(date +%s%N)
    env GENESIS_BENCH_CHANMODE=1 GENESIS_BENCH_NCOMP=16 \
        timeout 3600 ./genesis/src/nxgenesis_nocl -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
    E1=$(date +%s%N)
    awk "BEGIN{printf \"  genesis-cpu rep $r wall=%.2fs\n\", ($E1-$S1)/1e9}"
    r=$((r + 1))
done

r=1
while [ "$r" -le "$REPS" ]; do
    S1=$(date +%s%N)
    env GENESIS_BENCH_CHANMODE=4 GENESIS_BENCH_NCOMP=16 GENESIS_CUDA_MULTILOOP=$((K + 10)) \
        timeout 3600 ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
    E1=$(date +%s%N)
    awk "BEGIN{printf \"  genesis-gpu rep $r wall=%.2fs\n\", ($E1-$S1)/1e9}"
    r=$((r + 1))
done
