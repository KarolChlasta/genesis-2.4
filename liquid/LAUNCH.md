# Launching the PGENESIS LSM (turnkey)

_Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-15._


This directory is prepared so the Wójcik Liquid State Machine can be launched on
the UMCS cluster (inf02/inf03) with a single command, once an MPI runtime is
available. The launch was reconciled and validated up to the parallel-init step
on a laptop (see `RUN_STATUS.md`); the remaining step is a real multi-rank run
where PGENESIS/MPI is properly configured.

## Two launch paths

**1. Direct (recommended, csh-free): `start.sh`**
```sh
cd liquid
./start.sh                      # NP auto-derived from pdim in pparameters.g
```
`start.sh` reads `pdim` from `pparameters.g`, computes `NP = pdim^2 + 1`
(pdim^2 worker nodes + node 0 coordinator), and runs headless with the
self-contained `.psimrc`. No csh/tcsh needed.

Useful overrides:
```sh
DRYRUN=1 ./start.sh             # print the mpirun command, run nothing
NP=17 ./start.sh                # force rank count (must match the model's pdim)
HOSTFILE=mpich.cfg ./start.sh   # bare-ssh MPICH run with an explicit machinefile
BATCH=0 ./start.sh              # interactive genesis prompt instead of -batch
```

**2. csh wrapper: `../pgenesis/bin/pgenesis`**
```sh
cd liquid
../pgenesis/bin/pgenesis -nox -nodes 65 pgmwojcik.g
```
This is the `-nodes N` interface referenced by the benchmark protocol. It was
regenerated from the template (it shipped 0 bytes) via
`pgenesis/regen_pgenesis_wrapper.sh` and self-locates its paths, but it is
`#!/bin/csh` so the host needs **csh/tcsh** and `mpirun` on PATH.

## On SLURM (UMCS inf02/inf03)

```sh
cd liquid
# edit the MPI module line and --ntasks in run_lsm.slurm first
sbatch run_lsm.slurm
```
`--ntasks` **must** equal `pdim^2 + 1`. Rank count is dictated by the model
(cells are placed on nodes `1..pdim^2`), not by the allocation.

## Rank count vs pdim (single source of truth: `pparameters.g`)

| pdim | workers (pdim^2) | NP (--ntasks) |
|-----:|-----------------:|--------------:|
|    4 |               16 |            17 |
|    6 |               36 |            37 |
|    8 |               64 |            65 |
|   10 |              100 |           101 |
|   12 |              144 |           145 |

For an MPI scaling sweep, change `pdim` in `pparameters.g` and re-run;
`start.sh` picks up the new `NP` automatically (keep `--ntasks` in sync under
SLURM).

## Pre-flight on the cluster

1. `module load` the cluster MPI; confirm `mpirun --version`.
2. `DRYRUN=1 ./start.sh` — confirm the printed command and `NP`.
3. Small run first: set `pdim = 4` in `pparameters.g`, `sbatch` (or
   `./start.sh` in an interactive allocation) with 17 ranks. Expect the model
   to reach `GRZEGORZ M. WOJCIK presents...`, cross its barriers, print
   `****************** THE END ******************`, and exit on `quit`.
4. Scale up pdim once the small run completes cleanly.

## Known-good partial state (laptop, np=1)

`NP=1 ./start.sh` loads the model, prints the banner, then stops at
`Parlib error 23: postmaster doesn't exist`. That error is expected with a
single rank (no worker node set) and is the documented pre-cluster checkpoint —
it confirms model + SIMPATH + launch flags are correct and only the multi-rank
MPI node set is missing.
