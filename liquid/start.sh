#!/bin/sh
# Launch G. M. Wojcik's PGENESIS Liquid State Machine under MPI.
#
# Single source of truth for parallelism is `pdim` in pparameters.g:
#   workers      = pdim * pdim         (cells placed on nodes 1..pdim^2)
#   total ranks  = pdim * pdim + 1     (node 0 coordinator + the workers)
# So NP is DERIVED, never hand-set here -- this is what keeps start.sh and
# pparameters.g from drifting apart (the old -np 17 vs pdim=8 bug).
#
# This is the csh-free launch path (direct mpirun). It bypasses the csh
# bin/pgenesis wrapper, so it needs no csh/tcsh. Run it from any host that has
# an MPI runtime on PATH (module load the cluster's MPI first).
#
# Overridable via environment:
#   NP=<n>            force total rank count (default: pdim^2 + 1)
#   MODEL=<file.g>    model script            (default: pgmwojcik.g)
#   PGENESIS_BIN=...  path to nxpgenesis      (default: ../pgenesis/bin/Linux/nxpgenesis)
#   HOSTFILE=<file>   pass -machinefile <file> to mpirun (e.g. non-SLURM cluster)
#   BATCH=0          run interactive (default 1: headless -notty -batch)
#   DRYRUN=1          print the mpirun command and exit without running
#
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-15.
set -eu

HERE=$(cd "$(dirname "$0")" && pwd)
cd "$HERE"

BIN=${PGENESIS_BIN:-"$HERE/../pgenesis/bin/Linux/nxpgenesis"}
MODEL=${MODEL:-pgmwojcik.g}

# Derive pdim from pparameters.g (first `int pdim = <N>` line).
PDIM=$(sed -n 's/^[[:space:]]*int[[:space:]]\{1,\}pdim[[:space:]]*=[[:space:]]*\([0-9]\{1,\}\).*/\1/p' pparameters.g | head -n1)
[ -n "$PDIM" ] || { echo "ERROR: could not read pdim from pparameters.g" >&2; exit 1; }
WORKERS=$(( PDIM * PDIM ))
NP=${NP:-$(( WORKERS + 1 ))}

# Sanity checks.
[ -x "$BIN" ] || { echo "ERROR: nxpgenesis not found/executable: $BIN" >&2; exit 1; }
[ -r "$MODEL" ] || { echo "ERROR: model script not readable: $HERE/$MODEL" >&2; exit 1; }
command -v mpirun >/dev/null 2>&1 || { echo "ERROR: mpirun not on PATH (module load your MPI?)" >&2; exit 1; }

# Host placement: explicit HOSTFILE wins; otherwise let the launcher/scheduler
# decide (SLURM+PMI, or mpirun defaults). The stale local mpich.cfg is NOT used
# automatically -- pass HOSTFILE=mpich.cfg to opt in.
HOSTARG=""
[ -n "${HOSTFILE:-}" ] && HOSTARG="-machinefile $HOSTFILE"

# nxpgenesis flags: pin SIMPATH to the local .psimrc (host-independent) and run
# headless so the run terminates on the model's own `quit` instead of dropping
# to an interactive `genesis #0 >` prompt. See paper/benchmark_run_protocol.md.
GENFLAGS=""
[ -r "$HERE/.psimrc" ] && GENFLAGS="-altsimrc .psimrc"
[ "${BATCH:-1}" = "1" ] && GENFLAGS="$GENFLAGS -notty -batch"

# Warn if running under a SLURM allocation whose task count won't fit the model.
if [ -n "${SLURM_NTASKS:-}" ] && [ "${SLURM_NTASKS}" != "$NP" ]; then
  echo "WARNING: SLURM_NTASKS=$SLURM_NTASKS but this model needs NP=$NP (pdim=$PDIM)." >&2
  echo "         Request --ntasks=$NP, or change pdim in pparameters.g." >&2
fi

echo "== PGENESIS LSM launch =="
echo "  binary : $BIN"
echo "  model  : $MODEL"
echo "  pdim   : $PDIM  (workers=$WORKERS)"
echo "  ranks  : NP=$NP  (workers + node 0)"
echo "  mpirun : $(command -v mpirun)"
echo "  flags  : $GENFLAGS"
[ -n "$HOSTARG" ] && echo "  hosts  : $HOSTARG"
echo "========================="

# shellcheck disable=SC2086  # HOSTARG/GENFLAGS are intentional word-split args
if [ "${DRYRUN:-0}" = "1" ]; then
  echo mpirun -np "$NP" $HOSTARG "$BIN" $GENFLAGS "$MODEL"
  exit 0
fi
set -x
exec mpirun -np "$NP" $HOSTARG "$BIN" $GENFLAGS "$MODEL"
