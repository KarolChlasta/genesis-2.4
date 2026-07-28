#!/bin/sh
# Overnight PGENESIS LSM (Wojcik) MPI scaling sweep: pdim in {2,4,8} -> NP in
# {5,17,65}. This is the first attempt at a real multi-rank PGENESIS run on
# proper cluster hardware (prior laptop attempts hit "Parlib error 23:
# postmaster doesn't exist" with too few ranks). Serves the paper's recorded
# next step: "end-to-end validation on established PGENESIS network models --
# such as liquid-state-machine reservoirs -- to confirm the unmodified-model
# claim and characterize combined MPI + GPU scaling on cluster hardware."
#
# Safety: each pdim attempt is individually timed-out so one hang doesn't
# blow the whole sweep; results/log written incrementally.
# Prepared by Karol Chlasta (karol@chlasta.pl).
set -u
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
LIQUID="$ROOT/liquid"
NODE=$(hostname)
LOG="$HERE/lsm_mpi_sweep_${NODE}_$(date +%F).log"
CSV="$HERE/lsm_mpi_sweep_${NODE}_$(date +%F).csv"
PER_RUN_TIMEOUT=${PER_RUN_TIMEOUT:-1800}   # 30 min ceiling per pdim attempt

echo "node,pdim,np,exit_code,wall_s" > "$CSV"
{
echo "=== LSM MPI sweep start: $(date '+%F %T %Z') on $NODE ==="
command -v mpirun >/dev/null 2>&1 || { echo "module load mpi/mpich-x86_64"; }
if ! command -v mpirun >/dev/null 2>&1; then
    . /etc/profile 2>/dev/null || true
    module load mpi/mpich-x86_64 2>&1 || echo "WARN: module load failed, hoping mpirun is already on PATH"
fi
command -v mpirun && mpirun --version 2>&1 | head -1

cd "$LIQUID"
for PDIM in 2 4 8; do
    cp -f pparameters.g pparameters.g.bak
    sed -i "s/^\([[:space:]]*int[[:space:]]\{1,\}pdim[[:space:]]*=[[:space:]]*\)[0-9]\{1,\}/\1${PDIM}/" pparameters.g
    NP=$((PDIM * PDIM + 1))
    echo "-- pdim=$PDIM  NP=$NP --  $(date '+%T')"
    t0=$(date +%s%N)
    timeout "$PER_RUN_TIMEOUT" sh start.sh </dev/null > "$HERE/lsm_run_${NODE}_pdim${PDIM}_$(date +%F).out" 2>&1
    rc=$?
    t1=$(date +%s%N)
    w=$(awk "BEGIN{printf \"%.2f\",($t1-$t0)/1e9}")
    echo "   exit_code=$rc  wall=${w}s"
    echo "$NODE,$PDIM,$NP,$rc,$w" >> "$CSV"
    mv -f pparameters.g.bak pparameters.g
done
echo "=== LSM MPI sweep end: $(date '+%F %T %Z') ==="
echo "SWEEP_DONE"
} >> "$LOG" 2>&1
echo "csv -> $CSV"
echo "log -> $LOG"
