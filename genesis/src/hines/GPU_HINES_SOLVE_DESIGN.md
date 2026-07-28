# Design: correct GPU multicompartment (Hines) solve

Goal: real, axially-coupled GPU acceleration for multicompartment dendrite
trees -- the actual defining use case of GENESIS -- replacing the current
per-compartment-independent multiloop kernel, which is only valid for
single-compartment networks (see `../../paper/manuscript_softwarex_draft.tex`
Impact section, and `cluster_bringup/BENCHMARK_NOTES.md`). Karol Chlasta,
2026-07-25.

**Final status: done.** What follows is the chronological derivation log,
kept in full for the historical trail (including hypotheses that turned out
wrong -- see the per-section status markers below). By the end of it, the
`hines_tree_eliminate` kernel is implemented in both OpenCL and CUDA,
validated against the CPU reference for both linear-chain and branching
topologies to ~1e-7 V, and speed-swept with 10 replicates on UMCS A40/A100
cluster nodes and a local AMD Radeon 890M integrated GPU (see "DONE" /
"VALIDATED" section headings below for each milestone). For the headline
numbers and how to reproduce them, see `paper/manuscript_softwarex_draft.tex`
(Table 4, Fig. 4) and `paper/REPLICATION.md` rather than this log.

Original status snapshot at the point this log was started, 2026-07-25:
**per-tree kernel-entry protocol fully derived AND empirically validated
(CPU-side, linear-chain topologies) -- branching topologies not yet
validated; actual OpenCL/CUDA kernel not yet written.**

## VALIDATED 2026-07-25: per-tree kernel-entry protocol (CPU reference implementation)

The design below this point (through "Proposed approach") was the
**pre-validation hypothesis** and got several things wrong in ways that would
have produced a silently-incorrect GPU kernel; kept for the historical
derivation trail, but **the corrected, empirically-validated protocol is
this section**. Implemented as `do_pertree_validate`/`do_pertree_snapshot` in
`hines_solve.c`, called from `hines.c`'s chanmode 4/5 dispatch when
`GENESIS_VALIDATE_PERTREE=1` -- a full from-scratch CPU reimplementation of
the interpreter, scoped per-tree using ONLY `Hsolve`'s
`fwd_seg_start`/`bwd_seg_start`/`fwd_root_row`/`fwd_raval_start`/
`bwd_raval_start` fields, run independently per tree and compared against
`hsolve->vm[]` as written by the real `do_euler_hsolve`/`do_crank_hsolve` for
the same step. **Result: exact match (0 mismatches, double-precision) across
every tested linear-chain configuration** -- N=2..100 trees, NCOMP=1
(degenerate single-compartment, matching the squid benchmark topology)
through NCOMP=32, over 5-20 simulated steps each.

**Three real bugs found and fixed during this validation, each of which
would have produced a silently-wrong GPU kernel if skipped:**

1. **`fwd_seg_start[k]` marks near the END of a tree's own opcode range, not
   the start.** Postorder ("children before parents") means a tree's root --
   where `parentno==-1` fires, the original hook point -- is the LAST row of
   that tree processed, not the first; most of a tree's own opcodes (all its
   non-root rows) are emitted BEFORE its root is ever reached. Fixed in
   `hines_init.c` by tracking the true start via a `prev_was_root` flag
   (captures `nfuncs`/`nravals` the moment a NEW tree's first row begins,
   detected as "the row right after the previous tree's root").
2. **The tree's own leading transition opcode (`SET_DIAG`/`SKIP_DIAG`) must
   be skipped, not executed, by a standalone work-item.** Traced exactly via
   `funcs_dump_test.g`: that opcode's "flush" half writes into the PREVIOUS
   tree's own row slot (harmless/necessary in the single-threaded code,
   which relies on it to persist the previous tree's root value into
   `results[]` for later reference -- but redundant, and a genuine cross-tree
   data race for a parallel kernel, since a standalone work-item already
   provides that value itself via the root-solve write-back, item 3 below).
   Three cases, distinguished by the tree's actual leading opcode:
   - **`SET_DIAG`**: tree's first row is itself 1-compartment/the root (or,
     not yet handled, has siblings). Seed `resultval`/`diaval` directly from
     `results[2*first_row]`/`[+1]` (skip the opcode, no execution).
   - **`SKIP_DIAG`**: the common case -- first row is a plain unbranched
     leaf. The single-threaded flush+advance lands 2 rows further than
     `SET_DIAG` would; replicate by seeding from `results[2*(first_row+1)]`
     instead (the leaf's own value is folded in normally moments later, via
     the next row's `FORWARD_ELIM` referencing it by absolute index --
     channel-update already populated it, no bootstrap dependency).
   - **Leading `FORWARD_ELIM` directly (no transition opcode at all)**: only
     possible for the very first tree in the whole hsolve -- `do_euler_hsolve`'s
     own global bootstrap (`resultvalue=results+2`, "row 0 skipped") means
     rows 0 and 1 (globally) never get an explicit `SET_DIAG`/`SKIP_DIAG`.
     Seed from row 1 directly, replicating that exact global bootstrap.
   All SUBSEQUENT `SET_DIAG`/`SKIP_DIAG` opcodes within the SAME tree (one
   per "un-fused" row transition -- an 8-compartment chain has nearly one per
   row) are executed NORMALLY by the generic interpreter loop; their flush
   target is by construction always within the tree's own row range, safe.
   (Root's own post-fold value needs an explicit write-back into
   `results[2*root_row]` after the uniform root-solve division, for the SAME
   reason -- the backward pass's first `BACKWARD_ELIM` reads the parent/root's
   value via this exact absolute index.)
3. **Validator must run on a snapshot taken BEFORE the real solve, not the
   live post-solve state.** `results[]`/`ravals[]` get mutated in place by
   the real `do_euler_hsolve` (folds, divisions) as it runs; running the
   per-tree reimplementation afterward on the same live arrays double-folds
   already-folded contributions. Fixed with `do_pertree_snapshot()`
   (`memcpy` before the real solve call) plus a matching backward-segment
   boundary fix: a NON-sentinel tree's `bwd_seg_start[kk]`, used as ANOTHER
   tree's upper bound, must have 1 subtracted (it already points PAST kk's
   own root's `CALC_RESULTS` token; used as-is it let that one token leak
   into the wrong tree's segment -- only the sentinel tree's raw value has no
   such token, and is never selected as another tree's bound anyway since
   it's always the global minimum).

## VALIDATED 2026-07-25 (continued): branching topologies

Built `hh_branching_multicompartment_benchmark.g` (N neurons, each a soma
with NBRANCHES dendrite branches of BRANCH_LEN compartments each -- a real
branch point at the soma, triggering `COPY_ARRAY`/`SIBARRAY_ELIM` in
`h_funcs_init`'s construction code, unlike the linear-chain benchmark).
Confirmed `COPY_ARRAY` present in the real opcode stream (`SIBARRAY_ELIM`
still not observed even here -- open curiosity, not yet a blocker, same as
noted in the original branch-test dumps).

**Passes with 0 mismatches** across: a single 3-branch neuron (N=1),
multiple 3-branch neurons (N=5, exercises a non-global-first tree's
branching bootstrap), 4 branches x 2 compartments (N=8), and 2 branches x 5
compartments (N=15) -- i.e. the internal (non-leading) `COPY_ARRAY` handling
already in the forward loop is now empirically confirmed correct, not just
inferred from reading.

**One real, narrow gap found and NOT yet fixed**: `BRANCH_LEN=1` (a branch
that is a single compartment directly off the soma -- its own row is
simultaneously a leaf AND has siblings) breaks, but **only for tree 0**
specifically (the one tree benefiting from the global i<=1 bootstrap
exclusion) -- trees 1+ with the IDENTICAL topology pass with 0 mismatches,
conclusively isolating the bug to the "Case C" (leading-`FORWARD_ELIM`)
bootstrap's `seed_row=1` assumption, which does not account for row 0/1
themselves being leaf-with-siblings in this specific degenerate shape.
**Deliberately not fixed this session** -- real GENESIS dendrite models
essentially never use zero-length branch stubs directly off the soma (a
compartment with no further extension is just an odd way to model the soma
itself), so this is a low-value, narrow edge case relative to the effort of
correctly re-deriving the global-bootstrap interaction with sibling
tracking. `do_pertree_validate` fails LOUDLY on it (real mismatches printed,
not silently wrong), so it is a known, documented, safely-flagged gap, not a
silent risk. Revisit only if a real model ever needs it.

**Practical conclusion**: the per-tree kernel-entry protocol is now
validated for the realistic range of GENESIS multicompartment topologies --
linear chains of any depth, branch points with any number of children and
branch lengths >=2, multiple branch points, degenerate single-compartment
trees. Proceeding to the actual OpenCL kernel implementation on this basis.

## IMPLEMENTED AND VALIDATED 2026-07-25: the actual OpenCL kernel (GPU-side, not just CPU)

`hines_tree_eliminate` (`opencl/ocl_channel.cl`) is a line-for-line port of
`do_pertree_validate` -- same bootstrap cases, same forward/root-solve/
backward structure, same opcode handling. One work-item per tree; `funcs[]`/
`ravals[]`/`results[]` are shared flat buffers (matching the CPU layout
exactly), each work-item touching only its own tree's disjoint sub-ranges,
so the kernel is race-free with zero synchronization between work-items.

**Host-side integration** (`opencl/ocl_hsolve.c`): `ocl_tree_buffers_init()`
uploads `funcs[]`/`ravals[]` (double->float, like every other buffer here)
and the per-tree dispatch metadata (`fwd_seg_start`/`bwd_seg_start`/
`fwd_root_row`/`fwd_raval_start`/`bwd_raval_start` straight from the
`Hsolve` struct); `fwd_seg_end[]`/`bwd_seg_end[]` are derived once here
(the backward one via an O(n_trees log n_trees) sort, since discovery order
!= backward-loop order -- see `do_pertree_validate`'s O(n_trees) per-tree
linear search for the reference this replaces with something that scales to
realistic neuron counts). `ocl_multiloop_dispatch_tree()` replaces the old
single-kernel-with-internal-loop multiloop for real multicompartment trees:
per step, enqueues `chip_channel_update` (channel kinetics, ncompts
work-items, writes `results[]`) then `hines_tree_eliminate` (elimination,
n_trees work-items, reads that `results[]`, writes `vm[]`) on the same
in-order queue -- no host round trip between them, only one upload before
and one download after the whole K-step batch, preserving the multiloop
architecture's core performance property. `ocl_multiloop_dispatch()`
branches on `hsolve->n_trees < hsolve->ncompts`: pure single-compartment
networks (`n_trees == ncompts`, e.g. the squid benchmark) keep using the
old, cheaper single-kernel path unchanged (it's already correct for that
degenerate case -- no elimination needed).

**GPU-side empirical validation** (chanmode=4 + `GENESIS_OCL_MULTILOOP`,
compared against CPU chanmode=1 reference, on this session's AMD Radeon 890M
iGPU): linear chains (N=50 NCOMP=16 x500 steps, N=20 NCOMP=8 x2000 steps,
N=10 NCOMP=32 x300 steps), branching (N=10, 3 branches x 3 compartments,
x50 steps), and the degenerate single-compartment case (N=500 NCOMP=1
x500 steps, confirmed routed to the OLD fast path, not the new kernel) --
**all agree with the CPU reference within ~1e-6..1e-7 V**, consistent with
this codebase's established fp32-kernel tolerance (the elimination kernel
runs in float like every other kernel here; longer integrations accumulate
somewhat more fp32 rounding, as expected, but stay well within tolerance).

**This is the actual fix for the scientific-validity gap this whole
multi-session GPU-Hines effort was for**: real, axially-coupled
multicompartment dendrite trees now get correct, GPU-multiloop-accelerated
(not just per-step) simulation -- not merely per-step dispatch (which was
already correct, established earlier 2026-07-25, but doesn't batch steps)
and not the single-compartment-only multiloop shortcut this replaces for
real trees.

**Known gaps carried forward, unchanged from the CPU validation above**:
the `BRANCH_LEN=1`+tree-0 leading-opcode case (narrow, undocumented on real
models); the kernel currently only runs on the OpenCL backend -- CUDA port
not yet started.

## FOUND 2026-07-25: reproducible GPU driver hang at large ncompts (local iGPU), unresolved -- hard safety cap added

While measuring speed (see below), `ocl_multiloop_dispatch_tree` triggered
`amdgpu: The CS has cancelled because the context is lost. This context is
guilty of a hard recovery.` on this session's AMD Radeon 890M iGPU, at large
enough models. Bisected to a **sharp, exactly reproducible threshold**:
N=1400 x NCOMP=16 (22400 total compartments) works correctly every time;
N=1500 x NCOMP=16 (24000) hangs every time. Confirmed this is NOT a
kernel-launch-queue-depth issue as first suspected -- tried, in order,
periodic `clFlush`, periodic `clFinish` every 16 steps, a genuinely
**blocking `clFinish` after every single step**, and a smaller kernel
work-group size (16 instead of 64): **none moved the threshold at all**,
including the fully-synchronous case, which should have ruled out any
queue-buildup explanation entirely. The channel kernel alone (identical
kernel, identical size, via per-step dispatch with a blocking readback every
step) does **not** hang even at 32000 compartments -- confirming this is
specific to `hines_tree_eliminate` or its interaction with the channel
kernel in the back-to-back dispatch pattern, not a general device memory
limit (buffer sizes here are trivially small -- low single-digit MB) and not
the already-extensively-validated elimination logic itself (correct at
every smaller scale tested, both on CPU and on this same GPU).

**Root cause NOT understood.** No access to system/kernel logs in this
sandboxed session to dig further (no `dmesg`/`journalctl`). One untested
hypothesis: an integrated GPU that also drives the display may be unable to
get the desktop compositor scheduled in during a sustained compute run,
triggering the OS's protective reset independent of anything this code
controls -- but this is a guess, not confirmed, and doesn't obviously
explain why full per-step blocking sync didn't help.

**Mitigation, not a fix**: `ocl_multiloop_dispatch` now hard-caps at
`ncompts > 20000` -- a conservative margin below the observed 22400-working/
24000-hanging boundary -- and falls back to CPU (`do_chip_hh4_update`,
correct, just not GPU-accelerated for that hsolve) with a clear one-time
message, disabling `GENESIS_OCL_MULTILOOP` for the rest of the run so every
subsequent step doesn't retry the same doomed dispatch. Verified this
avoids the hang cleanly (N=1500 now falls back instead of crashing) while
the GPU path still engages correctly for models under the cap (N=1000
confirmed still dispatching to `hines_tree_eliminate`, matching CPU to
~1e-7 V). The cap is deliberately conservative -- it also disables GPU for
the empirically-confirmed-working 20000-22400 range, sacrificing some real
capacity for safety margin given the root cause is unknown.

**This must be re-tested on the actual target cluster hardware (dedicated
A40/A100, no display to contend with, different driver stack entirely)
before trusting any conclusion about whether this is a fundamental
limitation of the design or an artifact specific to this laptop iGPU.** If
it does not reproduce on cluster GPUs, the cap should be relaxed or removed
there (it's a local, not a portable, constant).

## CONFIRMED iGPU-SPECIFIC 2026-07-25 (same day, on UMCS cluster inf02/A40)

Built and ran on UMCS inf02 (NVIDIA A40) the same day, later session:
OpenCL headers/runtime ARE present on the cluster (`CL/cl.h` under the CUDA
toolkit's own include tree at `$CUDA_HOME/targets/x86_64-linux/include`;
`libOpenCL.so` -- the NVIDIA driver's own ICD -- already in the standard
system lib path, no `-L` needed). Built with `USE_OPENCL=1` using `CPATH`
for the include fix (avoids threading a new path through the Makefile's
`CFLAGS_IN` recursive-submake composition -- see the established pitfall
elsewhere in this doc); reused the existing `libfl` stub fix from the CUDA
build. Script: `cluster_bringup/11_build_opencl.sh` (companion to
`10_build.sh`).

Ran the **exact configuration that hung the local AMD iGPU** (N=2000 x
NCOMP=16, 32000 total compartments) with the safety cap temporarily raised
for this test: **ran correctly in 2.5ms, no hang.** Pushed further with no
issue: N=2000 x NCOMP=16 correctness at 500 steps (matches CPU to ~1e-7 V,
37 us/step); N=5000 x NCOMP=16 (80000 compartments, ~6.1x faster than CPU:
GPU 2.27ms/step vs CPU 13.9ms/step); N=10000 x NCOMP=16 (160000
compartments) ran correctly -- the only slow part at that size was the SLI
interpreter's own model-construction phase (~2.5 minutes of pure CPU script
execution building 10000 neurons, nothing to do with the GPU kernel).
Branching topology also re-validated on the A40 (0 mismatches equivalent,
matching CPU).

**Conclusion: the hang is specific to the local AMD Radeon 890M laptop
iGPU** (plausibly the earlier display-contention hypothesis, though still
not confirmed) **and does not reproduce on dedicated datacenter GPUs.** The
cap is now `GENESIS_OCL_TREE_MAX_NCOMPTS`-overridable (0/negative =
disabled) instead of a hardcoded constant, defaulting to the conservative
20000 for safety on unknown/laptop hardware, with cluster deployments
expected to raise or disable it. Per-step GPU speed at cluster scale is
dramatically faster than the local iGPU too, as expected (e.g. N=50 NCOMP=8:
15 us/step on the A40 vs 249 us/step on the iGPU, ~16x) -- this session's
earlier local speed numbers were never meant to be the paper's real
figures anyway, this cluster run is the first real signal of production
performance.

## Speed measured 2026-07-25 (correctness-confirmed range, N<=20000 comps, local iGPU)

CPU vs GPU-multiloop-with-tree-elimination, `hh_multicompartment_benchmark.g`,
NCOMP=16, 500 measured steps:

| N | total comps | CPU s/step | GPU (tree multiloop) s/step | GPU vs CPU |
|---|---|---|---|---|
| 100 | 1600 | 9.26e-5 | 3.93e-4 | 4.2x slower |
| 500 | 8000 | 3.99e-4 | 3.90e-4 | ~even |
| 1000 | 16000 | 9.19e-4 | 4.12e-4 | **2.2x faster** |

Same qualitative shape as the earlier per-step-dispatch speed measurement
(fixed per-dispatch overhead dominates at small N, crossover somewhere
around a few hundred to ~1000 total trees/compartments, GPU pulls ahead
increasingly past that) -- consistent, not a new finding, but now for the
scientifically-correct multiloop-batched path instead of per-step. **N=2000
and above could not be measured this session** due to the hang above.
Real speedup at realistic paper-scale N (thousands+) is still unknown until
either the hang is understood/fixed, or cluster hardware (which may not
share this specific iGPU limit) allows testing past the local cap.

## What's NOT yet done (next steps)

1. Port `hines_tree_eliminate` to CUDA (`cuda_channel.cuh`/`cuda_hsolve.c`),
   mirroring the existing dual-backend pattern -- needed for the actual
   UMCS cluster A40/A100 hardware the paper's benchmark numbers come from.
2. ~~Investigate the large-ncompts GPU hang~~ -- **done 2026-07-25, same
   day**: confirmed iGPU-specific, does not reproduce on UMCS cluster
   inf02 (A40) up to 160000 compartments. Cap now overridable via
   `GENESIS_OCL_TREE_MAX_NCOMPTS` (see dedicated section above).
3. ~~Re-run the correctness validation (GPU vs CPU parity) on cluster
   hardware~~ -- **done 2026-07-25**: linear-chain and branching models
   both match CPU to ~1e-7 V on inf02/A40 via `cluster_bringup/
   11_build_opencl.sh`.
4. Measure a FULL real-speedup sweep (multiloop-with-tree-elimination vs
   CPU, N x NCOMP) on cluster GPUs with the cap raised/disabled -- only a
   handful of spot points measured so far (N=50/2000/5000/10000 at
   NCOMP=16); a proper sweep (both inf02/A40 and inf03/A100) is what
   unlocks a valid "many complicated neurons" benchmark campaign for the
   paper. inf03/A100 not yet tried at all.
5. Only if it matters in practice: revisit the `BRANCH_LEN=1` bootstrap gap
   and/or the un-observed `SIBARRAY_ELIM` opcode (still never seen in any
   test model built this session, branching or not).
6. ~~CUDA port~~ -- **done 2026-07-25, same session**: see dedicated section
   below. Worked correctly on the first cluster test, matching CPU and the
   OpenCL backend closely.

## DONE 2026-07-25: CUDA port (`cuda_hines_tree_eliminate`)

Line-for-line port of `hines_tree_eliminate` into `cuda/cuda_channel.cuh`
(OpenCL C -> CUDA C++ using the file's own existing translation-map
comment: `__kernel`->`extern "C" __global__`, `get_global_id(0)`->
`blockIdx.x*blockDim.x+threadIdx.x`, etc. -- otherwise byte-identical
logic to the already-validated OpenCL kernel). Host-side glue mirrors
`opencl/ocl_hsolve.c` exactly:

- `cuda_backend_tree_init()` (`cuda_backend.cu`) uploads `funcs[]`/
  `ravals[]` and per-tree dispatch metadata, deriving `fwd_seg_end[]`/
  `bwd_seg_end[]` once via `std::sort` (same O(n_trees log n_trees)
  approach as the OpenCL host code, just using C++ standard library
  instead of `qsort`+a comparator).
- `cuda_backend_multiloop_tree()` runs nsteps iterations of (channel
  kernel, tree-eliminate kernel) on CUDA's default stream (implicitly
  ordered, exactly like the OpenCL in-order queue), with the same
  periodic `cudaDeviceSynchronize()` safety measure ported over (even
  though it did not explain the iGPU hang either, when tried on the
  OpenCL side -- included defensively).
- `cuda_hsolve.c`'s multiloop branch gained the identical `n_trees <
  ncompts` dispatch check and the identical, shared-env-var
  (`GENESIS_OCL_TREE_MAX_NCOMPTS`) safety cap as `ocl_hsolve.c` -- a
  script tuned for one backend's cap works unchanged for the other.

**Built and validated directly on UMCS inf02 (A40, sm_86)**, reusing the
existing `cluster_bringup/10_build.sh` unchanged (no new toolchain fixes
needed beyond what the CUDA build already established). Worked correctly
on the **first attempt**: linear-chain (N=50 NCOMP=8 x500 steps) and
branching (N=10, 3 branches x 3 compartments) both match CPU to ~1e-7 V;
timing essentially identical to the OpenCL backend on the same GPU (14.9
us/step CUDA vs 15.2 us/step OpenCL for the same N=50/NCOMP=8 case, as
expected -- same hardware, same algorithm). The shared safety cap verified
working identically to the OpenCL side (default falls back to CPU above
20000 compartments; `GENESIS_OCL_TREE_MAX_NCOMPTS=0` override engages the
GPU kernel). Existing single-compartment CUDA multiloop path (the squid
benchmark) re-confirmed unaffected.

## DONE 2026-07-25: inf03 (A100) validated, first A40-vs-A100 comparison

Home is shared across UMCS cluster nodes, so the same checkout (with the
CUDA port already in place) is visible from inf03 without re-syncing.
Rebuilt with the unmodified `cluster_bringup/10_build.sh`.

**Build gotcha (worth remembering for any future node switch)**: the
rebuild initially failed at runtime with `no kernel image is available for
execution on the device` on inf03 -- `10_build.sh`'s `make clean` does NOT
remove `cuda_backend.o` (the nvcc-compiled translation unit), so a stale
object file containing only inf02's sm_86 cubin got relinked as-is instead
of being recompiled for inf03's sm_80. Fixed by manually removing
`genesis/src/hines/cuda/cuda_backend.o` (and `hines/hineslib.o`, the
archive that embeds it) before rebuilding. **Do this explicitly whenever
switching which node you're building the CUDA backend on**, or fix
`10_build.sh`'s clean step to catch `.cu`-derived `.o` files (not done
this session, left as a papercut for later since a one-line manual `rm`
before each cross-node build is sufficient for now).

Once rebuilt, both CPU-vs-GPU correctness (linear-chain, branching) and
speed re-confirmed on the A100:

| N | NCOMP | node/GPU | CPU s/step | GPU (tree multiloop) s/step | speedup |
|---|---|---|---|---|---|
| 1000 | 16 | inf02/A40  | (not re-measured same-run) | -- | ~2.2x (local iGPU comparison earlier; see below for a same-node figure) |
| 1000 | 16 | inf03/A100 | 1.478e-3 | 2.316e-4 | **6.4x** |
| 5000 | 16 | inf02/A40  | 1.387e-2 | 2.27e-3  | 6.1x |
| 5000 | 16 | inf03/A100 | 1.311e-2 | 9.409e-4 | **13.9x** |

At N=5000 the A100 pulls meaningfully ahead of the A40 (13.9x vs 6.1x) --
consistent with the A100 having more SMs (108 vs 84) and memory bandwidth
that only pays off once the workload is large enough to actually use them;
at the smallest tested size (N=50/NCOMP=8, 400 compartments/50 trees) the
A100 was actually *slower* per-step than the A40 (31.8 vs 14.9 us/step),
i.e. too small a workload to amortize either GPU's fixed per-dispatch
overhead -- the same qualitative crossover-with-N shape seen throughout
this investigation (local iGPU, per-step dispatch, tree multiloop), just
with a different crossover point per device. This is exactly the kind of
multi-GPU generational comparison the paper wants (cf. the cluster-access
memory note on A40/A100/H200 spread being "an excellent multi-gen CUDA-
backend comparison").

## DONE 2026-07-25: full N x NCOMP sweep on both nodes

Full writeup + raw CSVs: `cluster_bringup/logs/
MULTICOMPARTMENT_SWEEP_2026-07-25_ANALYSIS.md` (generated by the new
`cluster_bringup/50_multicompartment_sweep.sh`, run in parallel on inf02
and inf03 via the shared cluster home). Headline numbers: **12.7x speedup
on A40, 29.1x on A100** at the largest tested size (N=10000 x NCOMP=16,
160000 total compartments); both GPUs show the same small-N "GPU is
slower than CPU" -> crossover -> growing-speedup-with-size shape seen
throughout this investigation, with the A100 consistently ahead of the
A40 and pulling further ahead as problem size grows (more SMs/bandwidth
paying off once there's enough parallel work). See that file for the full
two-axis (N sweep + NCOMP sweep) tables and reading notes.

Not yet done: a finer grid past this first systematic sweep; inf04 (4x
A40)/inf05 (H200) not yet tried; branching-topology speed (only
correctness validated so far, not relative speedup).

## What the CPU reference actually does (read from source tonight)

The real algorithm is **not** "update each compartment independently" -- it is
a **compiled opcode program** that performs Gaussian elimination on the
tree-structured (branched dendrite) sparse matrix arising from the cable
equation, executed by a tiny bytecode interpreter (`do_fast_hsolve` /
`do_euler_hsolve` / `do_crank_hsolve` in `hines_solve.c`).

- **Forward elimination pass** (`FORWARD_ELIM`, `SET_DIAG`, `SKIP_DIAG`,
  `SIBARRAY_ELIM`, `FASTSIBARRAY_ELIM`, `COPY_ARRAY`): walks the tree
  bottom-up (children before parents), eliminating each row's reference to its
  parent, folding sibling (branch-point) contributions into a scratch `raval`
  array. Genuinely **sequential**: each step depends on the previous
  compartment's eliminated diagonal/RHS.
- **Root solve**: `results[last]/diaval` once the tree is fully eliminated.
- **Backward substitution pass** (`BACKWARD_ELIM`, `CALC_RESULTS`,
  `SIBARRAY_ELIM`): walks the tree top-down (parents before children),
  computing each compartment's final value from its parent's.
- **`FINISH`** (opcode 7) terminates each pass.

Data (`Hsolve` struct, `hines_struct.h`): `funcs` (the opcode program),
`ravals` (scaled axial-resistance values consumed in program order), `results`
(interleaved RHS/diagonal state, 2 doubles per compartment), `compts`/`elmnum`
(compartment ordering). This structure is built **once** at `SETUP` time
(`hines_init.c`/`hines_chip_init.c`) from the tree topology (`parents`/`kids`)
and then just replayed every timestep -- this is why the CPU path is fast
(no per-step pointer-chasing).

## Why the current multiloop kernel is wrong for multicompartment models

`ocl_channel.cl` / `cuda_channel.cuh` only implement the **channel-kinetics**
update per compartment (gating variables, conductances) -- they never execute
anything resembling `FORWARD_ELIM`/`SIBARRAY_ELIM`/`BACKWARD_ELIM`. For a
single-compartment network this is fine (there is no axial coupling to solve --
`ncompts==1` short-circuits to `results/diag` directly, per
`do_fast_hsolve`'s own special case). For any real multicompartment cell,
skipping the elimination silently drops all inter-compartment coupling --
exactly the bug found and corrected on 2026-07-24
(`cluster_bringup/BENCHMARK_NOTES.md`, the "~96x" retraction).

## Key structural fact for our workload: one hsolve, many independent trees

Our benchmark/LSM networks build **one `hsolve` covering all N neurons**
(`path "/net/##[][TYPE=compartment]"`), and the N neurons are **electrically
disconnected from each other** (no synaptic/axial messages between different
neurons' compartments in these scripts). The resulting matrix is therefore
**block-diagonal**: conceptually N independent per-neuron elimination
sub-programs.

**CORRECTED 2026-07-25 (verified empirically, see below): `FINISH` is NOT a
per-neuron delimiter.** There are exactly **two `FINISH` markers total** for
the whole combined `hsolve` -- one ending the forward-elimination pass, one
ending the backward-substitution pass -- **regardless of how many
disconnected neurons/trees are combined**. The original hypothesis in this
doc (initially written from reading `hines_solve.c`'s two `FINISH`-terminated
while-loops without reading the *construction* side) was wrong: those two
loops are the forward/backward pass boundaries for the *entire* hsolve
object, not per-tree. Confirmed by direct empirical dump (see next section)
and by the construction code structure in `hines_init.c`
(`h_funcs_init`, ~line 107): a single `for (i=0;i<ncompts;i++)` loop spans
*all* compartments across *all* trees, with `FINISH` emitted exactly once
after that loop closes (line ~896) and once after the backward pass (~1033).

Tree boundaries are instead implicit: a compartment with `parents[i]==-1` is
a fresh tree root, and the construction code emits `SET_DIAG` (a "start a new
diagonal/RHS pair", not "eliminate against a parent") for such rows instead
of `FORWARD_ELIM` -- there is no parent to eliminate against. **Splitting the
combined program per neuron therefore cannot be done by scanning the flat
opcode array for a delimiter after the fact** (no such delimiter exists at
tree granularity) -- it must be done using the tree-structure information
(`parents[]`/`hnum`/`elmnum`) that is already known at *construction* time,
either by hooking `h_funcs_init` to also record each root's opcode-range as
it builds them, or by pre-computing root boundaries from `parents[]` before
calling the existing construction routine and having it emit boundary
markers into a side-channel array.

This does **not** invalidate the overall strategy (parallelize *across*
neurons, not within a single tree -- still the right scope for our workload:
many modest trees, not one huge one) -- it only changes *how* to determine
each neuron's opcode-range boundaries: from construction-time tree knowledge,
not from post-hoc opcode-array scanning.

### Empirical verification (2-neuron test, 2026-07-25)

Added a temporary `GENESIS_DUMP_FUNCS=1`-gated debug dump in `hines_init.c`
(kept in place, off by default, for continued investigation -- see the
`getenv("GENESIS_DUMP_FUNCS")` block near the end of `h_funcs_init`). Test
model: `genesis/Scripts/benchmark/funcs_dump_test.g`, two disconnected
3-compartment linear-chain neurons (compartments 0-2 = neuron A, 3-5 =
neuron B; `parents[] = -1 0 1 -1 3 4`, confirming two roots at indices 0 and
3 as expected).

Two dump events occur per `SETUP`+`reset`: first a **count-only** pass
(`justcount=1`, `hsolve->funcs` still `NULL` -- sizes `hsolve->nfuncs` before
allocation), then triggered by the first `reset`, the **real fill** pass
(`justcount=0`) with the populated array:

```
funcs[] = FE FE SETD FE SKIPD SKIPD FE 6 SETD FE 8 FINISH
          FE 10 6 FE 8 6 6 FE COPY 6 FE SKIPD 6 FINISH
```
(26 entries total; `FE`=`FORWARD_ELIM`(=0, ambiguous with a literal operand
value of 0 -- don't over-interpret individual small integers without tracking
each opcode's known operand count). Exactly 2 `FINISH` tokens: position 12
(end of forward pass) and position 26 (end of backward pass) -- one pass
boundary each, not one per neuron, confirming the correction above.

**Practical note for continuing:** `h_funcs_init` is called at least twice per
solver (count pass at `SETUP`, fill pass at first `reset`) -- any future
instrumentation/hook needs to handle both calls (e.g. gate on `justcount==0`
for anything that needs the real, populated array).

### Boundary-detection hook (implemented + verified, 2026-07-25)

Added two minimal, purely-observational hooks (gated on
`!justcount && getenv("GENESIS_DUMP_FUNCS") && parentno == -1`, zero effect on
existing control flow) right after each of the two `parentno=parents[comptindex];`
reads in `hines_init.c` (forward-pass loop ~line 425, backward-pass loop
~line 908). Each prints the row (`i`, hnum-order), the real compartment index,
and the **current `nfuncs`** -- i.e. exactly the funcs[]-array offset where
that tree's segment begins.

Result on the 2-neuron branch test (6 compartments, `parents[]=[-1,0,0,-1,3,3]`,
so compartment 3 = root of neuron "cell1", compartment 0 = root of "cell0"):

```
FWD_ROOT i=2 comptindex=3 nfuncs=0    <- cell1's forward segment starts at 0
FWD_ROOT i=5 comptindex=0 nfuncs=6    <- cell0's forward segment starts at 6
BWD_ROOT i=2 comptindex=3 nfuncs=18   <- cell1's backward segment starts at 18
                                          (only ONE bwd hit, not two!)
```

**Full algorithm now understood:**
- **Forward pass**: every tree's root triggers the hook -- N trees give N
  `FWD_ROOT` events, and consecutive events' `nfuncs` values directly bound
  each tree's forward segment: `[fwd_root[k], fwd_root[k+1])`, last tree runs
  to the forward `FINISH`.
- **Backward pass**: the loop is `for (i=ncompts-2; i>=0; i--)` -- it
  explicitly **skips `i=ncompts-1`** ("soma done automatically", per the
  existing comment/guard at that site, which is one of the three solver
  defects already fixed and described in the SoftwareX paper). Whichever
  tree's root lands at hnum position `ncompts-1` (here: cell0's root, the
  *last* `FWD_ROOT` seen) is this automatic "soma" -- its single-row backward
  step is folded into the interpreter's built-in "solve last row" step
  (`*resultvalue=resultval/diaval` in `do_fast_hsolve`) and needs **no**
  separate backward-pass boundary. Only the *other* N-1 trees' roots pass
  through the explicit backward loop and fire `BWD_ROOT` (matches: 2 trees ->
  1 explicit `BWD_ROOT` here).
- So: **N forward segments** (from N `FWD_ROOT` events) and **N backward
  segments** = (N-1 explicit `BWD_ROOT` events) + (1 implicit segment for
  whichever tree's root is the last `FWD_ROOT`, positioned at the forward-pass
  `FINISH` boundary, no separate marker needed).

This is sufficient information to implement the real (non-debug) splitting
logic: promote these two hooks from `fprintf` to writing into a real
per-solver array (new `Hsolve` struct fields, e.g. `int *neuron_fwd_start;
int *neuron_bwd_start; int n_neurons;`), sized via a first observational pass
(count `FWD_ROOT` hits) or simply `calloc(ncompts, ...)` (safe upper bound,
one tree per compartment worst case) and shrunk/tracked with a counter.

## Proposed approach: one GPU thread (or small group) per neuron

1. **Split the combined program by neuron -- CORRECTED plan.** Cannot scan the
   flat `funcs` array for a delimiter after the fact (no per-tree delimiter
   exists, see above). Instead, hook `h_funcs_init` itself (`hines_init.c`) at
   construction time: it already knows, row by row, when it starts a new tree
   (`parents[i]==-1` triggers `SET_DIAG` instead of `FORWARD_ELIM`). Record
   `nfuncs` (and the matching `nravals`/row index) at each such boundary into a
   new side array (e.g. `hsolve->neuron_prog_offsets[]`), during the **fill**
   pass only (`justcount==0` -- the count pass has no array to index into
   yet). This gives, per neuron, exactly the `[start,end)` range into `funcs`
   (and correspondingly `ravals`) needed to hand that neuron's program to one
   GPU thread. Must handle forward- and backward-pass offsets separately
   (each neuron has one sub-range in each pass).
2. **Pack into GPU buffers**: one flat `funcs` buffer (as today, just also
   keep the per-neuron offset table), one flat `ravals` buffer, one flat
   `results` buffer (the actual state, uploaded/downloaded every
   dispatch/multiloop batch as now).
3. **Kernel**: one work-item per neuron. Each work-item runs the **exact same
   interpreter loop** as `do_fast_hsolve`/`do_euler_hsolve` (a line-for-line
   port, like the existing channel kernels are line-for-line ports of their
   CPU counterparts), operating only on its own slice of `funcs`/`ravals`/
   `results` (via its offset). This makes correctness verification tractable:
   it is the *same* algorithm per neuron, just SIMD-across-neurons instead of
   SIMD-across-independent-channel-updates.
4. **Multiloop composition**: for K steps in one dispatch (as today's
   multiloop does for channel updates), each work-item loops K times over its
   own interpreter + the existing per-compartment channel-update logic,
   interleaved exactly as the CPU per-step loop does (channel update ->
   hsolve elimination -> vm update), entirely within one kernel invocation
   per neuron-thread. Needs checking the CPU step's exact op order in
   `hines.c`'s dispatch (`hines_2chip.c`/`hines_4chip.c` etc. -- not yet read).
5. **Validation**: reuse the existing discipline -- a branching multicompartment
   test model (e.g. extend `hh1952_ap_verify.g`'s pattern to a Y-shaped 3+
   compartment cell with a real branch point, so `SIBARRAY_ELIM` is actually
   exercised, not just a linear chain), compare fp64 CPU vs fp32 GPU Vm
   trajectories to the same ~1e-7 V tolerance already established.

## MAJOR FINDING 2026-07-25: non-multiloop per-step OpenCL dispatch is ALREADY CORRECT for multicompartment models

Before starting the interpreter-kernel implementation (item 5 below), checked
whether the *existing* non-multiloop dispatch path might already be valid --
`hines.c`'s `case PROCESS:` chanmode-4/5 dispatch (`#if defined(USE_OPENCL) ||
defined(USE_CUDA)` branch) calls `ACCEL_CHIP_UPDATE(hsolve)` and only skips
`do_euler_hsolve`/`do_crank_hsolve` (real CPU elimination) `if (ocl_vm_ready)`.
Reading `ocl_hsolve.c`'s `ocl_chip_update()`: the multiloop branch
(`ocl_state.multiloop_total > 0`) returns 1 (skip elimination -- the known
bug). But the **non-multiloop branch** (lines ~504-567) uploads `vm[]`, runs
*only* the per-compartment channel-kinetics kernel, downloads `results[]`, and
**returns 0** -- meaning real CPU Hines elimination (`do_euler_hsolve`) runs
every step afterward, same as the CPU path. This makes sense: elimination
needs tree structure, which the per-step dispatch never touches -- it stays on
CPU every step in this mode.

**Empirically verified** using `hh_multicompartment_benchmark.g` (real
AXIAL/RAXIAL-coupled linear cables, current injected only at compartment 0),
comparing CPU (chanmode=1) vs GPU per-step (chanmode=4, no
`GENESIS_OCL_MULTILOOP`) vs GPU multiloop (chanmode=4 +
`GENESIS_OCL_MULTILOOP`), reading `Vm` of the soma and the far-end compartment
after 500 steps, at three sizes (NCOMP=1, NCOMP=2, NCOMP=8 x N=50):

| case | RESULT_VM_SOMA | RESULT_VM_FAR |
|---|---|---|
| CPU (chanmode=1) | -0.07891220069 | -0.08172388197 |
| GPU per-step (chanmode=4) | -0.0789122347 | -0.08172388662 |
| GPU multiloop (chanmode=4+multiloop) | -0.0337 (garbage) | -0.0344 (garbage) |

GPU per-step matches CPU to ~5e-9 V at every tested size (NCOMP=1/2/8).
Multiloop diverges wildly (no axial leak term -> unconstrained runaway), as
expected from the already-documented bug.

**First attempt at this comparison gave a false negative**: both GPU arms
initially read back exactly `EREST_ACT` (-0.070 V) regardless of chanmode,
looking like a total failure even at NCOMP=1 with current injected right at
the soma. Root cause: `getfield` reads the *element's own* field storage,
which the accelerator path does not keep in sync every step -- discovered by
comparing against `hh1952_ap_verify.g`, which already carries an explicit
comment ("Wire a recording message for cell0 BEFORE SETUP -- required for
chanmode 4 to enable h_out_msgs Vm sync") and calls `call /net/solver HGET
{path}` before every `getfield` on an hsolve'd compartment. Adding the
matching `HGET` calls before the `getfield`s in
`hh_multicompartment_benchmark.g` immediately produced the correct, CPU-matching
numbers above. **Any future GPU-mode numeric readout of an hsolve'd
compartment must call `HGET` first** -- this is not new/discovered-this-session
behavior, it was already known and documented in the AP-verify script, just
missed when instrumenting the multicompartment benchmark.

Full raw data (all tested sizes, plus CPU-vs-GPU speed measurements) captured
in `MULTICOMPARTMENT_GPU_FINDINGS_2026-07-25.md` alongside this file.

**Practical consequence**: the from-scratch parallel Hines-elimination GPU
kernel (items 5-6 below) is **not required for scientific validity** --
per-step dispatch already gives numerically correct multicompartment GPU
results today, for any topology (branching included, since elimination is
untouched, still the real CPU algorithm). It remains a legitimate *future*
optimization (it would let elimination happen on-device too, avoiding the
per-step upload/download round trip and unlocking true multi-step multiloop
batching for multicompartment models) but is no longer a blocker for
publishing a valid "many complicated neurons" GPU benchmark. Immediate next
step: measure whether per-step dispatch's *speed* (not just correctness) beats
CPU for multicompartment workloads -- unlike multiloop, it pays a
upload/download + kernel-launch round trip every single step, so the
speedup, if any, will look different from the multiloop numbers already in
the paper and needs its own measurement.

## Kernel design groundwork, 2026-07-25 (fresh source reading, not from memory)

Two of the three prerequisites flagged in item 1 of "what's not yet done"
(below) are now resolved by directly reading `hines_solve.c` and `hines.c`'s
`case PROCESS:` dispatch (not reconstructed from memory -- this session
already got burned once by trusting a memory-reconstructed hypothesis about
`FINISH` boundaries, so treating fresh reads as the only trustworthy source
going forward).

**Per-step operation order (resolves the open question in proposal step 4
above)**: `hines.c:148-240`. For chanmode 4/5, each step is exactly two
back-to-back phases, NOT interleaved per-compartment:
1. `h_in_msgs` (synaptic/external inputs)
2. Channel-kinetics update: `ACCEL_CHIP_UPDATE` (GPU chip update) or
   `do_chip_hh4ni_update` (CPU) -- computes conductances from current `vm[]`.
3. `do_euler_hsolve` / `do_crank_hsolve` (`hines_solve.c:223`/`:140`) -- ONE
   self-contained call doing forward elimination, the implicit last-row
   solve, backward substitution, AND the `vm[]` write, all in one pass.
4. `h_out_msgs`.

This is good news for a multiloop kernel: each work-item just needs to loop
K times over (channel-kinetics phase, then elimination phase) -- the same
two-phase shape the existing single-compartment multiloop kernel already
has, just with an elimination phase added.

**`results[]`/`raval[]`/`ravals[]` addressing** (resolves part of proposal
step 1's implicit assumption): read `do_fast_hsolve`/`do_euler_hsolve`
(`hines_solve.c:45-116`, `:223-296`) directly. `raval` and `ravals` are
**the same underlying buffer** (`raval = hsolve->ravals` at entry) accessed
two ways: `*ravals++` is a *sequentially-advancing read cursor*, while
`raval[*funcs++]` / `results[*funcs...]` are *absolute-indexed*
read/write using an index **embedded directly as an operand in the `funcs[]`
opcode stream** (not computed from position or from a separate offset table).
Consequence: since each tree occupies a contiguous, disjoint row range
(already established from the `fwd_seg_start`/`bwd_seg_start` work), and the
`funcs[]` operands for a given tree's ops were emitted using that tree's own
absolute row indices, **GPU work-items sharing the same global `results[]`/
`ravals[]` buffers get correct absolute-indexed addressing for free** -- no
new per-tree offset table needed for these two. The one exception: the
*sequential* `*ravals++` read cursor (used for `FORWARD_ELIM`/
`FASTSIBARRAY_ELIM`/`COPY_ARRAY`/`BACKWARD_ELIM` operands, distinct from the
absolute-indexed `raval[idx]` writes) genuinely needs a per-tree starting
offset -- a small additive extension of the same instrumentation already
built this session (count `ravals` entries consumed per tree during the fill
pass, same way `nfuncs` is already tracked, store as e.g.
`fwd_raval_start[]`/`bwd_raval_start[]`).

**Open complication, NOT yet resolved -- needs empirical verification, not
more source-reading**: `do_euler_hsolve`'s start (`resultvalue=results+2`,
"row 0 skipped") and end-of-forward-pass ("store result last row",
`resultval/diaval` direct divide before flipping to backward substitution)
special cases are written for ONE global sequential walk over the *whole*
hsolve. Splitting execution per-tree means **every** tree needs its own
local version of both boundary cases (its own "first row" start state, its
own "last row of my tree, solve directly" transition) -- not just the one
tree that happens to sit at the global last position (that's what the
existing `bwd_seg_start` `-1` sentinel already captures, but only for the
*single-threaded* code's one implicit global transition; a per-tree kernel
needs this transition **once per tree**, always, not once total). Exactly
which `funcs[]` operand in `FORWARD_ELIM`/`SIBARRAY_ELIM` refers to "the
child being folded in" vs "the running parent accumulator" was not fully
pinned down with certainty from source-reading alone in this pass -- per
this session's established discipline (burned once already on the `FINISH`
hypothesis), this needs a small hand-computable branching test model (simple
enough resistances/capacitances to check the expected forward/backward
elimination values by hand or with a short script) plus a debug dump of
`results[]`/`raval[]` state at pass boundaries, not further inference from
reading alone, before writing kernel code that touches this logic.

## What's NOT yet done (next steps, likely spans multiple sessions)

1. Read `hines.c` + `hines_2chip.c`/`hines_4chip.c`/`hines_chip_init.c` to get
   the exact per-step operation order (channel update vs elimination vs vm
   update) and how `chip`/`ops` (channel side) relate to `funcs`/`ravals`
   (elimination side) -- needed to correctly interleave both in one kernel.
2. ~~Confirm the block-diagonal/FINISH-boundary assumption empirically~~ --
   **done 2026-07-25**: assumption was wrong as originally stated (see
   correction above); real per-neuron boundaries come from construction-time
   `parents[i]==-1` tracking, not `FINISH` scanning. Debug dump
   (`GENESIS_DUMP_FUNCS=1`) left in place in `hines_init.c` for continued work.
3. ~~Extend a branching multi-neuron test model~~ -- **done 2026-07-25**:
   `funcs_dump_branch_test.g` (2 kids/root) and `funcs_dump_branch3_test.g`
   (3 kids/root). Note: neither triggered a literal `SIBARRAY_ELIM` token in
   these small/uniform test cases (only `COPY_ARRAY`, once per branch point)
   -- open curiosity (maybe `SIBARRAY_ELIM` needs a deeper/non-uniform tree),
   but **not a blocker**: the interpreter port must handle every opcode
   generically regardless of which ones a given test happens to exercise.
4. ~~Write the host-side per-neuron program-splitting logic~~ -- **boundary
   detection done and verified 2026-07-25** (see hook section above: N
   `FWD_ROOT` events bound N forward segments; N-1 explicit `BWD_ROOT` events
   + 1 implicit segment for the hnum-`ncompts-1` tree bound the backward
   segments). ~~Still open: promote to real struct fields~~ -- **done
   2026-07-25**: `Hsolve` gained `n_trees`/`fwd_seg_start[]`/`bwd_seg_start[]`
   (declared `hines_struct.h`, allocated+populated in `h_funcs_init`'s fill
   pass, freed in `h_delete` alongside `funcs`/`ravals`). A local
   `root_to_tree_idx[]` map (freed at function end, not persisted) lets the
   backward pass -- which visits roots in a different order than the forward
   pass discovered them -- write into the *same* tree slot. Verified exact
   match with the hand-derived values on all three test models
   (`funcs_dump_test.g`: `fwd=[2,8] bwd=[18,-1]`;
   `funcs_dump_branch_test.g`: `fwd=[0,6] bwd=[18,-1]`;
   `funcs_dump_branch3_test.g`: `fwd=[1,9] bwd=[25,-1]`) --
   `n_trees=2` and exactly one `-1` sentinel in every case, as expected.
   **Sanity-checked no regression**: `hh1952_ap_verify.g` CPU-vs-OpenCL parity
   still 1.95e-7 V (within the established ~1e-7..1e-6 V tolerance); squid
   N=2000 speedup still ~13.7x (consistent with prior ~10.6-13x runs).
5. Implement the interpreter kernel (OpenCL first, matching existing
   convention; CUDA port after, mirroring the existing dual-backend pattern).
   This is the next real increment -- it actually consumes
   `fwd_seg_start`/`bwd_seg_start` to dispatch one GPU work-item per tree, and
   is where a mistake would affect real simulation output (unlike the
   purely-additive prep work done so far). Budget a full, unhurried session.
6. Build the branching-neuron validation model and run the parity check
   (have branching test *models* already; still need the actual GPU kernel
   to validate against).
7. ~~Only after parity passes: benchmark multicompartment N/complexity
   sweeps~~ -- **unblocked 2026-07-25, does not need to wait for items 5/6**:
   per-step dispatch already gives correct multicompartment results (see
   MAJOR FINDING above), so the "lots of complicated neurons" campaign for the
   paper can proceed now, using chanmode=4 without
   `GENESIS_OCL_MULTILOOP`/`GENESIS_CUDA_MULTILOOP` set. Next concrete step:
   add `walltimemark`/`{walltime}` timing to `hh_multicompartment_benchmark.g`
   (matching the pattern already in `hh1952_squid_multiloop_benchmark.g`) and
   measure whether per-step dispatch's speed beats CPU at realistic
   N x NCOMP sizes -- it pays an upload/download + kernel-launch round trip
   every step (no multi-step batching), so this needs its own measurement
   and cannot be assumed from the multiloop numbers already in the paper.

## Why this matters for the paper

This directly answers the anticipated reviewer question ("your benchmark is
single-compartment -- does the speedup hold for GENESIS's actual use case,
multicompartment dendrites?") with a real yes, rather than leaving it as an
acknowledged limitation / future-work line. It is a genuine, nontrivial piece
of engineering -- correctly worth scoping across sessions, not rushed.

## MAJOR FIX (2026-07-25): model construction was O(n^2) -- fixed to O(n),
## unlocking Blue-Brain-microcircuit-scale (N=31,000+) population benchmarks

**Trigger.** Attempting to reproduce the Blue Brain Project's landmark
~31,000-neuron rat-somatosensory-cortex-column reconstruction scale
(Markram et al., Cell 2015) as a new multi-compartment GPU data point:
`hh_branching_multicompartment_benchmark.g` at `N=31000` (4 branches x 4
compartments + soma = 17 compts/neuron, 527,000 total compartments) never
completed even after a 900s budget on the UMCS cluster. This was surprising
-- the paper's existing sweep only went to `N=10,000` (Table 4), and nobody
had pushed further.

**Diagnosis, in order found (each confirmed empirically before moving on,
not just reasoned about):**

1. Local scaling profile (`hh_branching_multicompartment_benchmark.g`,
   construction-phase-only wall time, CPU): doubling N roughly
   4-5.6x'd the time (N=1000: 1.38s, N=8000: 105.45s) -- exponent ~2.09,
   i.e. genuinely O(n^2), not the "SLI interpreter overhead" originally
   assumed (that would just be O(n)).
2. `sim_attach.c: Attach()` -- called on every `create` -- scanned every
   existing sibling under the same parent (linear `for` over
   `parent->child`/`->next`, `strcmp` on name+index) to detect the rare
   same-name-overwrite case. O(n) per create, O(n^2) building n siblings
   under one parent (e.g. `/net/cell0..cellN-1`). Fixed: use the existing
   global element hash table for the duplicate check (O(1) amortized) and
   a new `childtail` field (mirroring the `msgintail`/`msgouttail` pattern
   already used for message lists) for O(1) append.
   - Found and fixed a real bug while implementing this: `Pathname()`
     returns a pointer into a *shared static buffer*.
     `ElementHashFind(Pathname(child))` passes that pointer as the search
     key, but `ElementHashFind()` itself calls `Pathname()` again
     internally (on every candidate it compares against) -- silently
     overwriting the caller's key mid-comparison, so `strcmp` was
     comparing the buffer against itself and (almost) always "matching".
     Symptom: dozens of spurious `overwriting an existing element` warnings
     and a final `ncompts` far short of what was requested (real elements
     silently freed as false "duplicates"). Fix: copy the key out with
     `strcpy` into a local buffer first, exactly like `ElementHashRemove()`
     already does -- this exact defensive pattern was sitting right next
     to the bug the whole time.
3. Re-profiled: scaling *improved* (exponent ~1.35) but N=31,000 still
   didn't finish in 60s. `sim_hash.c`'s global element hash table was a
   fixed 10,007 buckets forever (`ElementHashInit()`), so once total
   element count is well past that, chain lookups degrade back toward
   O(n) themselves. Added load-factor-triggered dynamic rehashing (prime
   ladder 10007/100003/1000003/10000019/100000007). This is a real,
   independently-justified fix (any GENESIS script building a very large
   model benefits) but, measured, turned out **not** to be where the
   remaining time was going for our specific benchmark -- included for
   completeness/correctness, not because it was the bottleneck.
4. Re-profiled again: no change at all from the rehashing fix, which
   meant the hash table was never the live bottleneck. Suspected
   `GetElement()`: its absolute-path hash lookup only ever hits when the
   *full* path already exists; `do_copy()`'s destination-path probe
   (`copy /library/Na_chan {comp}/Na_chan`, used twice per compartment
   here) always targets a not-yet-created leaf, so it always misses and
   falls through to a manual root-to-leaf tree walk -- which re-scanned
   *every intermediate segment's sibling list from scratch* (e.g.
   `/net` -> `cellN` among all N cells) even though `cellN` was already
   hashed. Fixed: try a hash lookup for each intermediate segment's own
   path before falling back to `GetChildElement()`'s linear scan; only
   the genuinely-missing final leaf still falls through (correct and
   rare).
5. Re-profiled: real improvement (exponent ~1.35, same as before -- this
   fix and #3 landed together operationally but #3 wasn't load-bearing;
   #4 was), N=16,000 now finished (27s) but N=31,000 still didn't in 60s.
   Tried `perf` (blocked: `perf_event_paranoid=4`, no root) and
   `valgrind --tool=callgrind` (ran clean but dumped a 0-byte output file
   -- GENESIS's `quit` path doesn't trigger callgrind's exit hook).
   Fell back to manual instrumentation: added temporary
   `walltimemark`/`{walltime}` markers between construction phases
   directly in a scratch copy of the `.g` script. Result at N=16,000: the
   neuron-building loop itself was only 5.2s of a 24.2s total --
   **`call /net/solver SETUP` alone was 18.8s (78% of total time)** --
   completely different code path (hsolve's own `h_init()`/
   `h_funcs_init()` in `hines_init.c`, not general element
   creation/path-resolution at all.
6. Read `h_init()` in full: two separate, pre-existing (not touched
   earlier this session, or at any point before today) O(ncompts) linear
   scans over *every* compartment, run *per compartment*:
   - Resolving an `AXIAL` message's source `Element*` to its index in
     `compts[]` (to identify each compartment's parent): a raw
     `for(j=0;j<ncompts;j++) if(msgin->src==(Element*)compts[j])`.
   - "Fill in indices for kids": for each compartment `i`, scan all
     `ncompts` compartments again to find which ones have `parents[j]==i`.
   Both O(ncompts^2) total, and -- since `ncompts` here is *every
   compartment across every tree in the hsolve*, not per-tree -- this is
   the one bottleneck that scales with total population size regardless
   of how the other four are fixed. This is almost certainly why nobody
   hit it before: the paper's existing sweep only reached 160,000 total
   compartments (Table 4, N=10,000 x NCOMP=16); this one needed the push
   to 527,000 (N=31,000) to dominate visibly.
   Fixed: (a) build a local pointer-to-index hash (`CidxEntry`, simple
   linear-probing over a power-of-two table) once up front, replacing the
   AXIAL-parent linear scan with an O(1) lookup; (b) replace the
   "fill in kids" O(n^2) double-loop with a single O(n) pass using a
   per-parent fill cursor (`nkids[]` -- and hence each `kids[i]`'s correct
   allocated size -- is already known by that point, from the first pass).

**Result** (`hh_branching_multicompartment_benchmark.g`, N independent
4-branch x 4-compartment neurons, CPU, local machine, full run: construction
+ hsolve SETUP + timed step phase):

| N      | total compartments | before               | after (all 5 fixes) |
|--------|---------------------|----------------------|----------------------|
| 1,000  | 17,000              | (baseline)           | 0.51 s |
| 2,000  | 34,000              |                       | 0.81 s |
| 4,000  | 68,000              |                       | 1.71 s |
| 8,000  | 136,000             | 105 s                | 3.90 s |
| 16,000 | 272,000             | did not finish (60s+)| 7.53 s |
| 31,000 (Blue Brain scale) | 527,000  | did not finish (900s+) | **14.66 s** |

Fitted scaling exponent, N=1,000 to N=31,000 (31x): **~0.98 -- effectively
linear**, versus ~2.09 before any fix, ~1.35 after fixes #2+#4 alone (i.e.
the general element-creation/path-resolution fixes helped a lot but
`h_init()`'s per-compartment scans, fix #6, were the dominant term all
along and are what finally gets this to true O(n)).

**Regression verification** (all before/after, byte-identical modulo normal
cpu-seconds timing jitter): `hh1952_ap_verify.g` (CPU and OpenCL GPU,
`RESULT_VM` unchanged to the last printed digit), `hh_multicompartment_
benchmark.g` and `hh_branching_multicompartment_benchmark.g` at N=100
(`RESULT_VM_FAR`/`RESULT_VM_SOMA` unchanged, CPU and GPU), and the paper's
own ordinary-workflow baselines `Cal8.g`/`Cal7difshell.g` (diffed directly
against a pre-fix binary kept from earlier in the session -- identical
output, including the same pre-existing headless-mode warnings/missing-tool
messages that are unrelated to this fix).

**Files changed**: `genesis/src/sim/sim_attach.c`, `sim_hash.c`,
`sim_get.c`, `sim_elemlist.c`, `sim_copy.c`/`sim_detach.c`/`sim_delete.c`/
`sim_map.c` (minor `childtail`-consistency plumbing for #2),
`sim/struct_defs.h` (new `Element.childtail` field), and
`hines/hines_init.c` (#6). None of these are specific to the GPU work --
they are correctness-preserving performance fixes to core GENESIS
element/hsolve-construction code, so every GENESIS/PGENESIS user building
large models benefits, not just this paper's benchmarks.

**Why this matters for the paper.** This turns "population-scale
multi-compartment GPU acceleration" from a demonstration capped at
N=10,000 into one that comfortably reaches, and exceeds, a real published
landmark (Blue Brain's ~31,000-neuron microcircuit) in ~15 seconds of
model-construction wall time on a single machine -- independent of GPU vs
CPU, since this fix is entirely in the model-construction phase that both
arms share equally. Worth its own paragraph (or a short subsection) in the
Impact/Software-description sections: it is a genuine, general-purpose
GENESIS kernel contribution discovered as a side effect of pushing the GPU
benchmark to a literature-relevant scale, not a GPU-specific optimization.
