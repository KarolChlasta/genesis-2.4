#!/bin/sh
# CPU vs CUDA multiloop benchmark on the current GPU node (inf03=A100/inf02=A40).
# Workload: a single hsolve over N HH1952 neurons, N_STEPS, chanmode 4.
#   CPU arm : nxgenesis_nocl               (pure CPU Hines)
#   GPU arm : nxgenesis + GENESIS_CUDA_MULTILOOP=N_STEPS  (one GPU kernel dispatch)
# Wall-clock timed (date +%s%N), 1 warm-up + N_REPS measured. Run from repo root
# (the benchmark includes genesis/src/startup/schedule.g). CSV tagged by node/GPU.
# Prepared by Karol Chlasta (karol@chlasta.pl).
# Env: N_NEURONS (2000), N_STEPS (5000), N_REPS (5 measured, +1 warm-up).
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"
: "${CUDA_HOME:=/storage/opt/cuda/cuda-12.8}"
export LD_LIBRARY_PATH="$CUDA_HOME/lib64:${LD_LIBRARY_PATH:-}"

N_NEURONS=${N_NEURONS:-2000}
N_STEPS=${N_STEPS:-5000}
N_REPS=${N_REPS:-5}
BENCH=genesis/Scripts/benchmark/hh1952_squid_multiloop_benchmark.g
CPU=./genesis/src/nxgenesis_nocl
GPU=./genesis/src/nxgenesis
for b in "$CPU" "$GPU"; do [ -x "$b" ] || { echo "ERROR: missing $b (run 10_build.sh)"; exit 1; }; done

GPUNAME=$(nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1 | tr ' ' '_')
NODE=$(hostname)
CSV="$HERE/bench_${NODE}_${GPUNAME:-noGPU}_$(date +%F).csv"
echo "mode,node,gpu,neurons,steps,rep,wall_s" > "$CSV"

run() {   # $1=mode $2=bin ; rest=env assignments (e.g. VAR=val)
  mode=$1; bin=$2; shift 2
  r=0
  while [ "$r" -le "$N_REPS" ]; do   # r=0 is the warm-up (discarded)
    t0=$(date +%s%N)
    env "$@" "$bin" -nosimrc -notty -batch "$BENCH" "$N_NEURONS" "$N_STEPS" </dev/null >/dev/null 2>&1 || true
    t1=$(date +%s%N)
    w=$(awk "BEGIN{printf \"%.3f\",($t1-$t0)/1e9}")
    [ "$r" -ge 1 ] && echo "$mode,$NODE,$GPUNAME,$N_NEURONS,$N_STEPS,$r,$w" >> "$CSV"
    r=$((r+1))
  done
}

echo "== CPU vs CUDA  N=$N_NEURONS steps=$N_STEPS reps=$N_REPS(+warmup)  $NODE / $GPUNAME =="
echo "-- CPU  (nxgenesis_nocl) --"; run CPU  "$CPU"
echo "-- CUDA (GENESIS_CUDA_MULTILOOP=$N_STEPS) --"; run CUDA "$GPU" "GENESIS_CUDA_MULTILOOP=$N_STEPS"

echo "== means (wall_s) =="
awk -F, 'NR>1{s[$1]+=$7;n[$1]++} END{
  for(m in s){mean[m]=s[m]/n[m]; printf "  %-4s mean %.3f s (%d reps)\n",m,mean[m],n[m]}
  if(mean["CPU"]>0 && mean["CUDA"]>0) printf "  SPEEDUP (CPU/CUDA) = %.2fx\n", mean["CPU"]/mean["CUDA"]
}' "$CSV"
echo "csv -> $CSV"
