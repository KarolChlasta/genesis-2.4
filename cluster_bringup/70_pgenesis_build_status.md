# PGENESIS build on UMCS cluster — status (2026-07-24 night session)

Goal: build `nxpgenesis` (real multi-rank MPI) to run the Wójcik LSM on
inf02/inf03 — the paper's "characterize combined MPI + GPU scaling" next step.
**Not finished tonight** — paused deliberately to avoid loading inf02/inf03
with extra compile work while the overnight CUDA campaign (job #1, see
`50_overnight_campaign.sh`) is running clean timing measurements on both nodes.

## Fixes found and applied so far (all committed, all real/durable)
1. **libfl missing** — cluster has `flex` binary but not `libfl`. Built a local
   stub (`~/genesis-2.5/locallib/libfl.a`, `yywrap` only) and pass
   `LEXLIB=$HOME/genesis-2.5/locallib/libfl.a` to `make`.
2. **`-Wno-format-security`** — RHEL-hardened gcc treats old non-literal printf
   format strings (e.g. `src/par/rsync.c`) as `-Werror`. Added to `CFLAGS` in
   `pgenesis/Makefile` (source-level edit, not command-line override — a
   command-line `CFLAGS=` override breaks recursive propagation of
   `-DUSE_MPI=01` through `TOPFLAGS`, confirmed empirically).
3. **`MPI_LIB` env leak** — `module load mpi/mpich-x86_64` exports
   `MPI_LIB=/usr/lib64/mpich/lib` (a bare directory); `pgenesis/Makefile`
   inserts `$(MPI_LIB)` raw into the link line, and Make silently inherits it
   from the environment → linker error "file not recognized: Is a directory".
   Fix: `unset MPI_LIB` before `make` (mpicc already adds the right `-L`/`-l`
   flags on its own).
4. **`hineslib_cpu.o` naming mismatch** — `pgenesis/Makefile`'s `BASELIBS`
   hardcodes `hineslib_cpu.$(LIBEXT)`, but `genesis/src`'s `make nxinstall`
   only ever produces `hineslib.o`. Fix: `cp genesis/lib/hineslib.o
   genesis/lib/hineslib_cpu.o` after each `nxinstall` (must be redone whenever
   `hineslib.o` is regenerated).
5. **PIE vs non-PIC objects** — `mpicc` on this cluster unconditionally applies
   RHEL's `redhat-hardened-ld` specs, which **append `-pie` without gating on
   `-no-pie`** (confirmed empirically: a plain `-no-pie` flag is silently
   ineffective here, even reproduced with the exact expanded `mpicc -show`
   command run manually). Fix: compile **-fPIC** instead of fighting `-pie`.
   Added to `pgenesis/Makefile` CFLAGS and to `genesis/src/Makefile` CFLAGS
   (so `genesis/lib/*.o` that PGENESIS links against are PIC too).

   **Confirmed safe**: re-running `genesis/src`'s `make nxinstall` does NOT
   rebuild/overwrite the top-level `genesis/src/nxgenesis` /
   `nxgenesis_nocl` binaries (verified via timestamp + `ldd libcudart` after
   running it tonight) — it only (re)populates `genesis/lib/`. The validated
   CUDA parity result (|CPU−CUDA| = 7.04e-8 V) is intact.

## Remaining problem (where we stopped)
After fix #5, most `genesis/lib/*.o` became PIC (simlib, utillib, ss,
shelllib, toollib, olflib, hineslib_cpu(alias), liblfg, newconnlib, buflib,
seglib, hhlib, devlib) — but the link **still** fails on a second set:
`outlib.o conclib.o userlib.o porelib.o chemlib.o paramlib.o diskiolib.o
FMT1lib.o netcdflib.o libnetcdf.a`.

Root cause identified: these come from subdirectories whose own Makefiles set
`CFLAGS = $(CFLAGS_IN) -D$(MACHINE)` (a **different** variable, `CFLAGS_IN`,
not `CFLAGS`) — e.g. `out/`, `oldconn/{axon,synapse,personal,sim,tools}/`,
`user/`, `pore/`, `chemesis/`, `param/`, `diskio/`,
`diskio/interface/{FMT1,netcdf}/`. My top-level `-fPIC` edit to
`genesis/src/Makefile`'s `CFLAGS` doesn't reach them because the top Makefile
must pass `CFLAGS_IN="$(CFLAGS) ..."` down to them (matches the pattern seen
in the `nxinstall`/`nxlibs` recipe: `CFLAGS_IN="$(CFLAGS) $(DISKIOFLAGS)
$(SPRNG_FLAG) -DNO_X"` at Makefile:1479) — so `-fPIC` in `CFLAGS` *should*
already be flowing through via `CFLAGS_IN`... but empirically it isn't
reaching some of these objects. Not yet root-caused precisely (didn't want to
keep iterating live-on-cluster and adding CPU load while job #1 runs).

**netcdf in particular** (`diskio/interface/netcdf/netcdf-3.4/src/`) is a
bundled third-party autotools-ish source tree with its own `macros.make` —
likely needs its own independent `-fPIC` addition regardless of what
`genesis/src/Makefile` passes down.

## Next steps (resumable, no guessing needed — pick up here)
1. Trace exactly why `-fPIC` in `CFLAGS` isn't reaching `CFLAGS_IN` for
   `out/oldconn/user/pore/chemesis/param/diskio` — check the actual
   `nxinstall`/`nxlibs` recipe args (`CFLAGS_IN="..."` at Makefile:1479) match
   what's really invoked for the *library* build path (as opposed to the
   final `nxgenesis`/`nxgenesis_nocl` binary path) — the object list involved
   here is built via a different target chain than the one we've been running.
2. Separately, add `-fPIC` directly into
   `diskio/interface/netcdf/netcdf-3.4/src/macros.make` (bundled netcdf; not
   part of genesis's own CFLAGS lineage) and `diskio/interface/FMT1/Makefile`.
3. Re-run `genesis/src`'s `make nxinstall` (confirmed safe/no-op on the
   validated nxgenesis/nxgenesis_nocl binaries), refresh the
   `hineslib_cpu.o` alias, then retry `pgenesis`'s `make ... nxinstall`
   (script: adapt `50_overnight_campaign.sh`'s sibling, or just rerun the
   inline build commands from this session's history).
4. Once `bin/Linux/nxpgenesis` exists: smoke-test with `liquid/start.sh`
   (`NP=5`, i.e. `pdim=2`) before trusting `60_overnight_lsm_mpi_sweep.sh`
   unattended (this MPI path has never succeeded end-to-end before).
5. **Do this when inf02/inf03 are not busy with a timed campaign**, to avoid
   contaminating wall-clock data with build-process CPU contention.

Prepared by Karol Chlasta (karol@chlasta.pl).
