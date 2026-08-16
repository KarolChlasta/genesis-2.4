#!/bin/sh
# End-to-end speedup vs simulation length, multi-compartment.
#
# Table 3 reports 3.6-3.9x end-to-end at N=50000, against 37-81x step-phase.
# That gap is not a property of the kernel: those runs are 200 steps, so the
# unaccelerated construction phase dominates the wall clock. The existing
# K-sweep figure makes this point only for single-compartment networks.
#
# This sweeps K at fixed N so the multi-compartment end-to-end figure can be
# shown climbing toward its step-phase ceiling as runs lengthen -- which is the
# regime real modelling studies work in. N=10000 (160000 compartments) is large
# enough to be past the crossover and small enough that K=5000 finishes.
set -u

HERE=$(cd "$(dirname "$0")" && pwd)
R=$(cd "$HERE/.." && pwd)
NODE=$(hostname)
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
[ -n "$GPU" ] || GPU="no-gpu"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
# Without this the tree multiloop declines any hsolve over 20000 compartments
# and falls back to per-step dispatch -- a different measurement entirely.
export GENESIS_OCL_TREE_MAX_NCOMPTS=0

USED=$(nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits 2>/dev/null | head -1)
if [ "${ALLOW_BUSY_GPU:-0}" != "1" ] && [ -n "$USED" ] && [ "$USED" -gt 500 ]; then
    echo "ERROR: $USED MiB already allocated on $GPU -- timings would be inflated." >&2
    exit 1
fi

BENCH_SCRIPT=${BENCH_SCRIPT:-hh_multicompartment_createmap}
SCRIPT="genesis/Scripts/benchmark/$BENCH_SCRIPT.g"
mkdir -p "$HERE/logs"
OUT="$HERE/logs/multicomp_ksweep_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
REPS=${REPS:-5}
N=${N:-10000}
KLIST=${KLIST:-"200 500 1000 2000 5000"}

BIN_CPU="$R/genesis/src/nxgenesis_nocl"
BIN_GPU="$R/genesis/src/nxgenesis"
for b in "$BIN_CPU" "$BIN_GPU"; do
    [ -x "$b" ] || { echo "ERROR: missing $b -- build first" >&2; exit 1; }
done

echo "node,gpu,ncomp_per_neuron,n_neurons,total_comps,n_steps,mode,rep,wall_s" > "$OUT"
echo "== end-to-end vs K, N=$N REPS=$REPS on $NODE ($GPU) =="
cd "$R"

for K in $KLIST; do
    for MODE in cpu gpu; do
        if [ "$MODE" = cpu ]; then
            BIN="$BIN_CPU"; CM=1; EXTRA=""
        else
            BIN="$BIN_GPU"; CM=4; EXTRA="GENESIS_CUDA_MULTILOOP=$((K + 10))"
        fi
        r=1
        while [ "$r" -le "$REPS" ]; do
            S=$(date +%s%N)
            env GENESIS_BENCH_CHANMODE=$CM GENESIS_BENCH_NCOMP=16 $EXTRA \
                timeout 3600 "$BIN" -nosimrc -notty -batch "$SCRIPT" "$N" "$K" \
                >/dev/null 2>&1
            E=$(date +%s%N)
            echo "$NODE,$GPU,16,$N,$((N * 16)),$K,$MODE,$r,$(awk "BEGIN{printf \"%.6f\", ($E-$S)/1e9}")" >> "$OUT"
            r=$((r + 1))
        done
        echo "  K=$K $MODE done $(date +%T)"
    done
done

echo "== $OUT =="
