# liquid/ — PGENESIS Liquid State Machine (G. M. Wójcik)

Archived parallel (PGENESIS/MPI) neural-simulation code by **Grzegorz Marcin
Wójcik** (© 2002–2005), a Maass-style **Liquid State Machine**: an 8×8×16
multicompartmental Hodgkin–Huxley reservoir with a retina input layer and 10×10
readout layers, probabilistically connected, partitioned across MPI nodes
(`pdim`² nodes; see `pparameters.g`).

Provenance: supplied by G. M. Wójcik from his archives (ran on his setup). Kept
here as a real published-class PGENESIS network model, intended as a
backward-compatibility / real-model benchmark vehicle for the GENESIS 2.5
accelerator work (unmodified-model claim, and combined MPI + GPU scaling on
cluster hardware). Not modified as part of GENESIS 2.5; recorded as-is.

Entry point: `start.sh` → `mpirun ... nxmpgenesis pgmwojcik.g`.

Files: `pgmwojcik.g` (main), `pparameters.g` (config), `pfunctions.g`,
`pimpulse.g` (stimulus), `neuron.g` (cell), `mpich.cfg` (machinefile).
