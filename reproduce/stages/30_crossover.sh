#!/bin/sh
# Wall clock against run length, which is what makes the Arbor comparison
# meaningful: the two simulators cross, so a single run length answers only
# which side of the crossing was chosen.
set -u
RESULTS=$1
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT" || exit 1
S=genesis/Scripts/benchmark/hh_multicompartment_createmap.g
N=10000
OUT="$RESULTS/crossover.csv"
echo "simulator,n_steps,rep,wall_s" > "$OUT"

for K in 5000 50000; do
    r=1; tot=0
    while [ "$r" -le 3 ]; do
        t0=$(date +%s%N)
        env GENESIS_BENCH_CHANMODE=4 GENESIS_BENCH_NCOMP=16 GENESIS_CUDA_MULTILOOP=$((K+10)) \
            ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" >/dev/null 2>&1
        t1=$(date +%s%N)
        w=$(awk "BEGIN{printf \"%.4f\", ($t1-$t0)/1e9}")
        echo "GENESIS 2.5,$K,$r,$w" >> "$OUT"
        tot=$(awk "BEGIN{print $tot + $w}")
        r=$((r+1))
    done
    awk -v t="$tot" -v K="$K" 'BEGIN{printf "K=%s  GENESIS GPU %.2fs\n", K, t/3}'
    awk -v t="$tot" -v K="$K" 'BEGIN{printf "crossover_genesis_k%s,%.2f,s\n", K, t/3}' >> "$RESULTS/summary.csv"
done
echo "Arbor arm: see reproduce/README.md (needs an Arbor built with CUDA)"
