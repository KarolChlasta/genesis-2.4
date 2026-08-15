#!/bin/sh
# Single-compartment multiloop campaign with BOTH arms timed the same way.
#
# Why this exists: 52_cuda_singlecomp_campaign.sh takes the CPU number from
# GENESIS's own {cpu} step-loop timer and the GPU number from the device-side
# "CUDA MULTILOOP: ... total X ms" kernel report. Those are different
# quantities -- the GPU side excludes host work, transfers and construction --
# so their ratio is not a speedup of anything a user experiences, and it is
# inflated. Reviewer 2 of SOFTX-D-26-00952 raised exactly this.
#
# Here both arms are wall-clock around the whole process, so the ratio is an
# end-to-end speedup including construction, transfers and per-step host work.
# The step-phase figure remains available from each arm's own internal report;
# this script deliberately does not mix the two definitions.
#
# Overridable: REPS (default 10), STEPS (default 50000).
set -u

HERE=$(cd "$(dirname "$0")" && pwd)
R=$(cd "$HERE/.." && pwd)
NODE=$(hostname)
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1)
[ -n "$GPU" ] || GPU="no-gpu"

export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"

mkdir -p "$HERE/logs"
OUT="$HERE/logs/singlecomp_walltime_${NODE}_$(date +%Y%m%d_%H%M%S).csv"
REPS=${REPS:-10}
STEPS=${STEPS:-50000}

BIN_CPU="$R/genesis/src/nxgenesis_nocl"
BIN_GPU="$R/genesis/src/nxgenesis"
for b in "$BIN_CPU" "$BIN_GPU"; do
    [ -x "$b" ] || { echo "ERROR: missing $b -- build first" >&2; exit 1; }
done

echo "node,gpu,n_neurons,n_steps,mode,rep,wall_s" > "$OUT"
echo "== both arms wall-clock, REPS=$REPS STEPS=$STEPS on $NODE ($GPU) =="
cd "$R"

for N in 500 5000 50000; do
    for MODE in cpu gpu; do
        if [ "$MODE" = cpu ]; then
            BIN="$BIN_CPU"
        else
            BIN="$BIN_GPU"
        fi
        r=1
        while [ "$r" -le "$REPS" ]; do
            S=$(date +%s%N)
            if [ "$MODE" = cpu ]; then
                timeout 1800 "$BIN" -nosimrc -notty -batch \
                    genesis/Scripts/benchmark/hh_spiking_benchmark.g "$N" "$STEPS" \
                    >/dev/null 2>&1
            else
                GENESIS_CUDA_MULTILOOP="$STEPS" timeout 1800 "$BIN" -nosimrc -notty -batch \
                    genesis/Scripts/benchmark/hh_spiking_benchmark.g "$N" "$STEPS" \
                    >/dev/null 2>&1
            fi
            E=$(date +%s%N)
            echo "$NODE,$GPU,$N,$STEPS,$MODE,$r,$(awk "BEGIN{printf \"%.6f\", ($E-$S)/1e9}")" >> "$OUT"
            r=$((r + 1))
        done
        echo "  N=$N $MODE done $(date +%T)"
    done
done

echo "== $OUT =="
