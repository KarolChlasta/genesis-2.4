#!/bin/sh
# End-to-end accelerator speedup, both arms wall-clocked identically.
#
# Both arms are timed the same way, around the whole process, so construction
# and transfers are inside every figure. Quoting a step-phase number for one arm
# and a wall-clock number for the other inflates the ratio roughly tenfold; the
# paper reports one definition throughout and so does this.
set -u
RESULTS=$1
MODE=${2:-quick}
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT" || exit 1
S=genesis/Scripts/benchmark/hh_multicompartment_createmap.g

if [ "$MODE" = quick ]; then NLIST="10000"; K=5000; REPS=2
else                          NLIST="10000 50000"; K=5000; REPS=3; fi

for N in $NLIST; do
    ctot=0; gtot=0
    r=1
    while [ "$r" -le "$REPS" ]; do
        t0=$(date +%s%N)
        env GENESIS_BENCH_CHANMODE=1 GENESIS_BENCH_NCOMP=16 \
            ./genesis/src/nxgenesis_nocl -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
        t1=$(date +%s%N)
        env GENESIS_BENCH_CHANMODE=4 GENESIS_BENCH_NCOMP=16 GENESIS_CUDA_MULTILOOP=$((K+10)) \
            ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
        t2=$(date +%s%N)
        ctot=$(awk "BEGIN{print $ctot + ($t1-$t0)/1e9}")
        gtot=$(awk "BEGIN{print $gtot + ($t2-$t1)/1e9}")
        r=$((r+1))
    done
    awk -v c="$ctot" -v g="$gtot" -v n="$REPS" -v N="$N" -v K="$K" \
        'BEGIN{printf "N=%s K=%s  CPU %.2fs  GPU %.2fs  speedup %.1fx\n", N, K, c/n, g/n, c/g}'
    [ "$N" = 10000 ] && [ "$K" = 5000 ] && \
        awk -v c="$ctot" -v g="$gtot" 'BEGIN{printf "ksweep_k5000,%.2f,x\n", c/g}' >> "$RESULTS/summary.csv"
done
