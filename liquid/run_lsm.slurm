#!/bin/bash
#SBATCH --job-name=lsm-pgenesis
#SBATCH --ntasks=65            # MUST equal pdim^2 + 1  (pdim=8 -> 65). Change
#                             # this together with pdim in pparameters.g.
#SBATCH --cpus-per-task=1
#SBATCH --time=02:00:00
#SBATCH --output=lsm-%j.out
#SBATCH --error=lsm-%j.err
#
# SLURM launch of the PGENESIS Liquid State Machine on UMCS inf02/inf03.
#
# Before submitting:
#   1. Edit the MPI module name below to match `module avail` on the cluster.
#   2. Keep --ntasks == pdim^2 + 1. pdim must divide 16, so valid values are
#      pdim = 2/4/8/16 -> --ntasks = 5/17/65/257. For a scaling sweep, change
#      pdim in pparameters.g and --ntasks together. Max for this model: pdim=16.
#   3. Submit from the liquid/ directory:  sbatch run_lsm.slurm
#
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-15.
set -euo pipefail

# --- environment -----------------------------------------------------------
# module purge
# module load mpi            # <-- set to the cluster's MPICH/OpenMPI module
command -v mpirun >/dev/null || { echo "mpirun not on PATH: load an MPI module" >&2; exit 1; }

cd "$SLURM_SUBMIT_DIR"

# start.sh derives NP from pdim and warns if SLURM_NTASKS disagrees; it runs
# headless (-notty -batch) with the local self-contained .psimrc.
exec ./start.sh
