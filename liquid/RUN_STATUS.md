# liquid/ LSM — run status on GENESIS 2.5 (2026-07-04, laptop)

Single-node bring-up attempt of Wójcik's PGENESIS Liquid State Machine on the
GENESIS 2.5 tree.

## Result: model is GENESIS-2.5-compatible (loads); full parallel run blocked by PGENESIS launch setup

**What works (compatibility — the important part):**
- `nxpgenesis` starts GENESIS 2.4/2.5 and runs the model script.
- **All includes resolve** via the default `.simrc` SIMPATH: `hhchan`,
  `pparameters.g`, `pfunctions.g`, `pimpulse.g`, `neuron.g`.
- The SLI parses and executes the model's own code (reaches
  `GRZEGORZ M. WOJCIK presents...` and beyond). No model edits were needed for
  GENESIS 2.5 compatibility.

**What blocks a full parallel run (PGENESIS runtime/build, NOT the model):**
- The model places cells with `@{npos}` for `npos=1..NodesNumber` where
  `NodesNumber = pdim^2 = 64` (current `pparameters.g`), so it needs ~65 MPI
  ranks (node 0 + workers 1..64). `start.sh` says `-np 17`, which matches an
  older `pdim=4` (16 workers + node 0) — the repo state is internally
  inconsistent (start.sh vs pparameters).
- `pgenesis/bin/pgenesis` (the wrapper that turns `-nodes N` into
  `mpirun -np N ...` and initialises the parallel node set) is **empty (0 bytes)**
  — the PGENESIS install did not generate it.
- Run directly under MPICH: `-np 1` → `0 nodes requested`, `nnodes = 0`,
  `Parlib error 23: postmaster doesn't exist` (Aborted); `-np 4` → barrier
  deadlock / hang. The bare binary does not accept `-nodes` (treats it as a
  script filename).

## Interpretation
The LSM is compatible with GENESIS 2.5 at the script/SLI level (loads and runs
its construction code). Executing the full 64-node parallel simulation needs the
PGENESIS MPI launch fixed: regenerate the `pgenesis` wrapper, confirm the binary
links the active MPICH and initialises `paron`/node count, and reconcile
`pdim`/`start.sh`. This is environment/build work, best done where PGENESIS MPI
is properly configured — i.e. the UMCS `inf02`/`inf03` cluster window (Aug 2026),
which is also where the MPI+GPU scaling numbers for the paper belong.

## Reproduce (laptop)
```bash
cd liquid
mpirun -np 1 ../pgenesis/bin/Linux/nxpgenesis pgmwojcik.g   # loads, then Parlib error
```
