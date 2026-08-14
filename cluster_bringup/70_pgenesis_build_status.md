# PGENESIS build on UMCS cluster — RESOLVED (2026-08-14)

Goal: build `nxpgenesis` (real multi-rank MPI) to run the Wójcik LSM on
inf02/inf03 — the paper's "characterize combined MPI + GPU scaling" next step.

**Status: done.** `pgenesis/bin/Linux/nxpgenesis` builds and runs on the
cluster: ELF PIE, links `libmpi.so.12` from `/usr/lib64/mpich/lib`, no missing
shared objects, starts and reaches normal GENESIS startup.

## Correction to the previous diagnosis

The 2026-07-24 notes ended on two hypotheses, **both of which were wrong**:

1. *"trace exactly why `-fPIC` in CFLAGS isn't reaching `CFLAGS_IN` for
   out/oldconn/user/pore/chemesis/param/diskio"* — it **was** reaching them.
   Every object under `genesis/src/` was already position-independent
   (0 absolute relocations, checked with `readelf -r`).
2. *"netcdf in particular likely needs its own independent `-fPIC`"* — it did
   not. `libnetcdf.a` was clean.

What actually looked like a `CFLAGS_IN` problem: the link error names
`outlib.o`, `conclib.o` … without paths, and those are the copies in
`genesis/lib/`, not the freshly built objects in `genesis/src/`.

## The four real causes

**1. `genesis/lib/` was stale.** `make nxinstall` copies objects from
`genesis/src/` into `genesis/lib/`; PGENESIS links against `genesis/lib/`. The
`-fPIC` rebuild happened on 2026-07-25, but the last `nxinstall` had run on
2026-07-24, so `genesis/lib/` still held pre-fix, non-PIC objects. Re-running
`make nxinstall` fixed all ten libraries at once. `nxinstall` passes no
compiler flags — it is a pure copy target — so it must be re-run after **any**
rebuild of `genesis/src/`.

**2. `hineslib.o` was non-PIC because of `nvcc`.** All of `hines/*.o` were
position-independent except the partial-link product `hineslib.o`, which
bundles `CUDA_OBJS`. `cuda/cuda_backend.o` is compiled by `nvcc`, which does
not inherit `-fPIC` from `CFLAGS` and does not pass it to the host compiler by
itself. **Fixed in source:** `NVCCFLAGS` in `genesis/src/hines/Makefile` now
carries `-Xcompiler -fPIC`.

**3. `pgenesis/Makefile` had hardcoded laptop paths.** `CC` and
`MPI_CMD`/`MPI_DEBUG_CMD` pointed at `/home/griffi/.local/bin/`, which exists
on no cluster node. **Fixed in source** (commit `build: resolve mpicc/mpirun
from PATH…`): both resolve from `PATH`.

**4. SPRNG's `liblfg.a` was non-PIC.** `genesis/src/sprng/Makefile` set
`CFLAGS = $(RNG_CFLAGS)`, and `RNG_CFLAGS` is defined nowhere in the tree — so
SPRNG was the one subdirectory compiled with empty flags, ignoring the
`CFLAGS_IN` the parent passes everybody else. Compounding it, `SRC/Makefile`'s
`clean` removed only `SRC/*.o` and never descended into the per-generator
subdirectories, so `lfg/lfg.o` survived clean rebuilds and kept re-poisoning
the archive. **Both fixed in source.**

## Build order that works

The ordering matters because PGENESIS needs a CPU-only hines library:
`pgenesis/Makefile`'s `BASELIBS` lists `hineslib_cpu.$(LIBEXT)`, and a
`USE_CUDA` build of `hineslib.o` carries `cuda/*.o` plus undefined
`cudaMalloc`/`cudaLaunchKernel` symbols that the PGENESIS link — which pulls in
no `libcudart` — cannot resolve.

```sh
# 1. CPU build first (this is also what 10_build.sh saves as nxgenesis_nocl)
cd genesis/src
make LEXLIB=$HOME/genesis-2.5/locallib/libfl.a nxgenesis
make LEXLIB=$HOME/genesis-2.5/locallib/libfl.a nxinstall

# 2. hineslib_cpu.o alias — must be refreshed after every nxinstall
cp genesis/lib/hineslib.o genesis/lib/hineslib_cpu.o

# 3. PGENESIS
cd ../../pgenesis
module load mpi/mpich-x86_64
unset MPI_LIB          # the module exports a bare directory the Makefile
                       # splices raw into the link line
make LEXLIB=$HOME/genesis-2.5/locallib/libfl.a nxinstall

# 4. CUDA build last, so it does not leave a CUDA-flavoured hineslib.o
#    in genesis/lib/ for a later PGENESIS link to trip over
cd ../genesis/src
sh ../../cluster_bringup/10_build.sh     # or the USE_CUDA=1 invocation from it
```

Doing step 4 before step 2 is what makes `hineslib_cpu.o` a CUDA object; the
symptom is undefined `cuda*` symbols at the PGENESIS link, which looks
unrelated to anything above.

## Still carried from the earlier session (unchanged, still true)

1. **libfl missing** — cluster has `flex` but not `libfl`. Local stub at
   `locallib/libfl.a` (`yywrap` only), passed as `LEXLIB=`.
2. **`-Wno-format-security`** — RHEL-hardened gcc treats old non-literal printf
   formats as `-Werror`. In `pgenesis/Makefile` CFLAGS.
3. **`MPI_LIB` env leak** — `module load mpi/mpich-x86_64` exports a bare
   directory; `unset MPI_LIB` before `make`.
4. **`-fPIC` everywhere** — `mpicc` here applies RHEL's hardened-ld specs and
   appends `-pie` unconditionally; `-no-pie` is silently ineffective, so
   everything PGENESIS links must be position-independent.

## Known non-blocking noise

`make nxinstall` in `pgenesis/` reports several `Error 126 (ignored)` lines
from install helpers and still exits 0 with a working binary. The csh wrapper
`pgenesis/bin/pgenesis` regenerates as 0 bytes and there is no `csh`/`tcsh` on
the cluster, so the wrapper path is unavailable — use the csh-free
`liquid/start.sh`.

Prepared by Karol Chlasta (karol@chlasta.pl).
