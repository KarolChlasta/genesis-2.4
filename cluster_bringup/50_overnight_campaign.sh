#!/bin/sh
# Overnight multi-replicate CPU-vs-CUDA campaign, single-compartment-per-neuron
# (hh1952_squid_multiloop_benchmark.g -- the VALIDATED regime for chanmode=4 +
# CUDA multiloop; NOT the multicompartment script, whose GPU result was
# invalidated on 2026-07-24, see BENCHMARK_NOTES.md).
#
# Methodology mirrors the paper's own protocol (Illustrative examples): each
# (N, arm, rep) is measured at K=0 (construction only) and K=TARGET_K
# (construction + step phase); their difference isolates the step phase.
# CPU arm = nxgenesis_nocl, chanmode=1 (real CPU Hines). GPU arm = nxgenesis,
# chanmode=4 + GENESIS_CUDA_MULTILOOP=K.
#
# Safety: wrap the WHOLE campaign in `timeout` at the call site (see launch
# command below) so it terminates by morning regardless; writes incrementally
# to CSV so partial results survive an interruption.
# Prepared by Karol Chlasta (karol@chlasta.pl).
set -u
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"
: "${CUDA_HOME:=/storage/opt/cuda/cuda-12.8}"
export LD_LIBRARY_PATH="$CUDA_HOME/lib64:${LD_LIBRARY_PATH:-}"

B=genesis/Scripts/benchmark/hh1952_squid_multiloop_benchmark.g
# N capped at 100000 by default: SLI network construction is O(N) serial, and
# N=200000 alone took 44-57 min PER RUN (K=0, construction-only) in the
# 2026-07-24 campaign -- with the CPU arm now actually running (bugfix below),
# a full 10-rep sweep at N>=200000 would take many hours per node. Treat
# N>=200000 as a separate, deliberate experiment (override N_LIST via env),
# not part of the default multi-rep grid. See logs/CAMPAIGN_2026-07-24_STATUS.md.
N_LIST="${N_LIST:-500 1000 2000 5000 10000 20000 50000 100000}"
TARGET_K=50000
REPS=${REPS:-10}
NODE=$(hostname)
GPU=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1 | tr ' ' '_')
OUT="$HERE/campaign_${NODE}_${GPU:-noGPU}_$(date +%F).csv"
LOG="$HERE/campaign_${NODE}_${GPU:-noGPU}_$(date +%F).log"

echo "node,gpu,arm,N,K,rep,wall_s" > "$OUT"
{
echo "=== overnight campaign start: $(date '+%F %T %Z') on $NODE ($GPU) ==="
echo "N grid: $N_LIST   K=0,$TARGET_K   reps=$REPS"

run_one() {  # chanmode bin extra_env N K
    # BUG (found 2026-07-24, invalidated the first overnight run): `env "$3" ...`
    # fails immediately (exit 127, "No such file or directory") when $3 is an
    # empty string -- env treats a bare "" as the command to exec, not a VAR=
    # assignment to skip. This silently broke every CPU-arm run (envstr="")
    # for ~16h, producing near-instant "wall_s" values (~0.002s for ALL N) that
    # looked superficially like valid data but measured env's own failure, not
    # GENESIS. Only pass $3 to env when non-empty.
    t0=$(date +%s%N)
    if [ -n "$3" ]; then
        env "$3" GENESIS_BENCH_CHANMODE="$1" "$2" -nosimrc -notty -batch "$B" "$4" "$5" \
            </dev/null >/dev/null 2>&1
    else
        env GENESIS_BENCH_CHANMODE="$1" "$2" -nosimrc -notty -batch "$B" "$4" "$5" \
            </dev/null >/dev/null 2>&1
    fi
    t1=$(date +%s%N)
    awk "BEGIN{printf \"%.4f\",($t1-$t0)/1e9}"
}

for N in $N_LIST; do
    echo "-- N=$N --  $(date '+%T')"
    # warm-up (discarded)
    run_one 1 ./genesis/src/nxgenesis_nocl ""                                "$N" "$TARGET_K" >/dev/null
    run_one 4 ./genesis/src/nxgenesis      "GENESIS_CUDA_MULTILOOP=$TARGET_K" "$N" "$TARGET_K" >/dev/null

    r=1
    while [ "$r" -le "$REPS" ]; do
        for K in 0 "$TARGET_K"; do
            w=$(run_one 1 ./genesis/src/nxgenesis_nocl "" "$N" "$K")
            echo "$NODE,$GPU,CPU,$N,$K,$r,$w" >> "$OUT"
            w=$(run_one 4 ./genesis/src/nxgenesis "GENESIS_CUDA_MULTILOOP=$K" "$N" "$K")
            echo "$NODE,$GPU,CUDA,$N,$K,$r,$w" >> "$OUT"
        done
        r=$((r + 1))
    done
done
echo "=== overnight campaign end: $(date '+%F %T %Z') ==="
echo "CAMPAIGN_DONE"
} >> "$LOG" 2>&1
echo "csv -> $OUT"
echo "log -> $LOG"
