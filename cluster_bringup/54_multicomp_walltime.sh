#!/bin/sh
# Multi-compartment tree-elimination campaign, end-to-end wall clock.
#
# 51_weekend_campaign.sh reports RESULT_T_PER_STEP for both arms, so unlike the
# single-compartment campaign it is at least internally consistent -- but it is
# a step-phase number, which excludes model construction. For a population of
# 50,000 x 16 compartments construction is tens of seconds, so the step-phase
# ratio is not what a user experiences.
#
# This runs the same sweep with wall clock around the whole process, matching
# 53_singlecomp_walltime.sh so both tables in the paper rest on one definition.
# Linear-chain only: the branching topology gives statistically indistinguishable
# speedups and is already omitted from the figure.
#
# Overridable: REPS (default 10), STEPS (default 200), NLIST.
set -u

HERE=$(cd "$(dirname "$0")" && pwd)
R=$(cd "$HERE/.." && pwd)
NODE=$(hostname)
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
[ -n "$GPU" ] || GPU="no-gpu"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"

mkdir -p "$HERE/logs"
OUT="$HERE/logs/multicomp_walltime_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
REPS=${REPS:-10}
STEPS=${STEPS:-200}
NLIST=${NLIST:-"100 500 1000 2000 3000 5000 7000 10000 15000 20000 30000 40000 50000"}

BIN_CPU="$R/genesis/src/nxgenesis_nocl"
BIN_GPU="$R/genesis/src/nxgenesis"
SCRIPT="genesis/Scripts/benchmark/hh_multicompartment_benchmark.g"
for b in "$BIN_CPU" "$BIN_GPU"; do
    [ -x "$b" ] || { echo "ERROR: missing $b -- build first" >&2; exit 1; }
done

echo "node,gpu,ncomp_per_neuron,n_neurons,total_comps,n_steps,mode,rep,wall_s" > "$OUT"
echo "== end-to-end wall clock, REPS=$REPS STEPS=$STEPS on $NODE ($GPU) =="
cd "$R"

for N in $NLIST; do
    for MODE in cpu gpu; do
        if [ "$MODE" = cpu ]; then
            BIN="$BIN_CPU"; CM=1; EXTRA=""
        else
            BIN="$BIN_GPU"; CM=4; EXTRA="GENESIS_CUDA_MULTILOOP=$((STEPS + 10))"
        fi
        r=1
        while [ "$r" -le "$REPS" ]; do
            S=$(date +%s%N)
            env GENESIS_BENCH_CHANMODE=$CM GENESIS_BENCH_NCOMP=16 $EXTRA \
                timeout 1800 "$BIN" -nosimrc -notty -batch "$SCRIPT" "$N" "$STEPS" \
                >/dev/null 2>&1
            E=$(date +%s%N)
            echo "$NODE,$GPU,16,$N,$((N * 16)),$STEPS,$MODE,$r,$(awk "BEGIN{printf \"%.6f\", ($E-$S)/1e9}")" >> "$OUT"
            r=$((r + 1))
        done
        echo "  N=$N $MODE done $(date +%T)"
    done
done

echo "== $OUT =="
