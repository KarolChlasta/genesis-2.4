#!/bin/bash
# PGENESIS strong-scaling benchmark (Table 3 in manuscript)
# Measures wall-clock time for N_TOTAL=2400 HH1952 neurons over N_STEPS=5000 steps
# at P = 1, 2, 4, 6, 8, 12, 16, 20, 24 MPI ranks.
#
# The GENESIS script consumes 3 user args (N_TOTAL, N_NODES, N_STEPS); PGENESIS
# internally strips the last command-line argument, so a dummy "0" is appended.
#
# Usage: bash paper/run_pgenesis_mpi_scaling.sh
# Output: paper/genesis25_pgenesis_mpi_scaling.csv

set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
PGEN="$REPO/pgenesis/bin/Linux/nxpgenesis"
BENCH="$REPO/genesis/Scripts/benchmark/hh1952_mpi_scaling.g"
MPIRUN="/home/griffi/.local/bin/mpirun"
CSV="$REPO/paper/genesis25_pgenesis_mpi_scaling.csv"

N_TOTAL=2400
N_STEPS=5000
REPS=11              # 11 total; first excluded as warmup
PROC_LIST="1 2 4 6 8 12 16 20 24"

echo "=== PGENESIS strong-scaling benchmark ==="
echo "N_TOTAL=$N_TOTAL  N_STEPS=$N_STEPS  REPS=$REPS (first=warmup)"
echo "Binary: $PGEN"
echo ""

if [[ ! -x "$PGEN" ]]; then
    echo "ERROR: nxpgenesis not found at $PGEN" >&2
    exit 1
fi

printf "P,rep,wall_s\n" > "$CSV"

declare -A t1_mean

for NP in $PROC_LIST; do
    echo "--- P=$NP ---"
    rep_times=""
    for rep in $(seq 1 $REPS); do
        t_start=$(date +%s%N)
        "$MPIRUN" -np "$NP" "$PGEN" -nosimrc -notty \
            -batch "$BENCH" "$N_TOTAL" "$NP" "$N_STEPS" 0 \
            2>/dev/null | grep -q "PGENESIS_DONE" || true
        t_end=$(date +%s%N)
        wall=$(awk "BEGIN{printf \"%.6f\", ($t_end - $t_start) / 1e9}")
        printf "%d,%d,%s\n" "$NP" "$rep" "$wall" >> "$CSV"
        echo "  rep=$rep wall=${wall}s"
        if [[ $rep -gt 1 ]]; then
            rep_times="$rep_times $wall"
        fi
    done

    # Compute mean, SD, CV over valid replicates (reps 2..REPS)
    read mean sd <<< $(echo "$rep_times" | awk '{
        n=NF; sum=0; sumsq=0
        for(i=1;i<=n;i++){sum+=$i; sumsq+=$i*$i}
        mean=sum/n; sd=sqrt(sumsq/n - mean*mean)
        printf "%.4f %.4f", mean, sd
    }')
    cv=$(awk "BEGIN{printf \"%.2f\", $sd / $mean * 100}")
    t1_mean[$NP]=$mean
    echo "  P=$NP mean=${mean}s sd=${sd}s CV=${cv}%"
    echo ""
done

echo "=== Summary ==="
printf "%-4s  %8s  %6s  %5s  %6s  %6s\n" "P" "T_P(s)" "SD(s)" "CV(%)" "S_P" "E_P"
t1=${t1_mean[1]}
for NP in $PROC_LIST; do
    t_p=${t1_mean[$NP]}
    s_p=$(awk "BEGIN{printf \"%.3f\", $t1 / $t_p}")
    e_p=$(awk "BEGIN{printf \"%.3f\", $t1 / $t_p / $NP}")
    sd=$(awk -v csv="$CSV" -v np="$NP" 'BEGIN{FS=","} $1==np && $2>1{sum+=$3; sumsq+=$3*$3; n++} END{mean=sum/n; sd=sqrt(sumsq/n-mean*mean); printf "%.4f", sd}' "$CSV")
    cv=$(awk "BEGIN{printf \"%.2f\", $sd / $t_p * 100}")
    printf "%-4s  %8s  %6s  %5s  %6s  %6s\n" "$NP" "$t_p" "$sd" "$cv" "$s_p" "$e_p"
done

echo ""
echo "CSV written to $CSV"
