#!/bin/sh
# PGENESIS Liquid State Machine smoke-test: small pdim (default 4 -> 17 ranks).
# Confirms the parallel model loads, crosses its barriers, and quits cleanly.
# Requires an MPI runtime on PATH (module load <mpi>). Prepared by Karol Chlasta.
#
# Overridable: PDIM (must divide 16: 2/4/8/16), DRYRUN=1 (print, don't run).
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
cd "$HERE/../liquid"

command -v mpirun >/dev/null 2>&1 || { echo "ERROR: mpirun not on PATH — module load <mpi> first"; exit 1; }

PDIM=${PDIM:-4}
cp -f pparameters.g pparameters.g.bak
# temporarily set pdim for the smoke test; start.sh derives NP = pdim^2 + 1
sed -i "s/^\([[:space:]]*int[[:space:]]\{1,\}pdim[[:space:]]*=[[:space:]]*\)[0-9]\{1,\}/\1${PDIM}/" pparameters.g
trap 'mv -f pparameters.g.bak pparameters.g 2>/dev/null || true' EXIT

echo "== LSM smoke-test: pdim=${PDIM} (NP=$((PDIM*PDIM+1))) =="
DRYRUN=${DRYRUN:-0} sh start.sh

echo "== restoring pparameters.g =="
