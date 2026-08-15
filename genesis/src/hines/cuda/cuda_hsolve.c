/*
 * cuda_hsolve.c -- GENESIS-side glue for the CUDA channel backend.
 *
 * Compiled by the ordinary C compiler (it includes GENESIS's C headers). It
 * builds the per-compartment index (identical to the OpenCL path), owns the
 * multiloop control flow, and delegates all device work to the extern "C"
 * array-based functions in cuda_backend.cu (compiled by nvcc). Control flow
 * is a 1:1 mirror of opencl/ocl_hsolve.c's ocl_chip_update().
 */
#ifdef USE_CUDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hines_ext.h"
#include "../hines_defs.h"
#include "cuda_hsolve.h"

/* implemented in cuda_backend.cu */
extern void *cuda_backend_init(int ncompts, int nchips, int nops, int ncols, int xdivs,
                              double xmin, double invdx,
                              const int *ops,
                              const double *tablist, int ntab,
                              const double *xvals, int nx,
                              const int *opstart, const int *chipstart,
                      const int *spike_refrac0, int nspike,
                      const double *stablist, int sntab);
extern int  cuda_backend_perstep(void *sth, const double *vm, double *results_out);
extern int  cuda_backend_upload_chip(void *sth, const double *chip);
extern int  cuda_backend_multiloop(void *sth, double *vm_io, double *chip_io,
                                   double *results_out, int nsteps);
extern void cuda_backend_sync_chip(void *sth, double *chip_out);
extern int  cuda_backend_chip_on_gpu(void *sth);
extern double cuda_backend_last_batch_time(void *sth);
extern void cuda_backend_set_last_batch_time(void *sth, double t);
extern int  cuda_backend_spikes_this_step(void *sth);
extern int  cuda_backend_has_spikes(void *sth);
extern int  cuda_backend_multiloop_total(void *sth);
extern void cuda_backend_set_multiloop_total(void *sth, int k);
extern int  cuda_backend_multiloop_called(void *sth);
extern void cuda_backend_bump_multiloop_called(void *sth);
extern int  cuda_backend_initialized(void *sth);
extern void cuda_backend_cleanup(void *sth);

/* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): real multicompartment
** tree elimination -- see GPU_HINES_SOLVE_DESIGN.md and the matching
** functions in opencl/ocl_hsolve.c, which this mirrors exactly. */
extern int  cuda_backend_tree_init(void *sth, int n_trees, int nfuncs, int nravals,
                                   const int *funcs, const double *ravals,
                                   const int *fwd_seg_start, const int *bwd_seg_start,
                                   const int *fwd_root_row, const int *fwd_raval_start,
                                   const int *bwd_raval_start);
extern int  cuda_backend_tree_ready(void *sth);
extern int  cuda_backend_multiloop_tree(void *sth, double *vm_io, double *chip_io,
                                        double *results_out, int nsteps);

/* GENESIS CPU fallback (in hines_4chip.c) */
extern int do_chip_hh4_update(Hsolve *hsolve);
extern void h_dospike_event(Hsolve *hsolve);
extern void h_dosynchan(Hsolve *hsolve, int stabindex, int cindex);
extern int  cuda_backend_needs_chip_every_step(void *sth);
static void cuda_synaptic_pass(Hsolve *hsolve);


/* Registry of live per-hsolve accelerator states.
**
** cuda_cleanup() is registered with atexit() and therefore receives no Hsolve,
** but the device state is now owned per solver -- the one-solver-per-cell idiom
** (`call solver DUPLICATE`) creates thousands of them. Keeping the handles in a
** list here is what lets the exit path release them all. Registration is O(1)
** and the list is walked exactly once, at process exit. */
typedef struct cuda_state_node {
    void   *handle;
    Hsolve *hsolve;              /* owner, so the barrier can dispatch for it */
    struct cuda_state_node *next;
} CudaStateNode;

static CudaStateNode *cuda_states = NULL;
static int cuda_atexit_registered = 0;

static void cuda_state_register(Hsolve *hsolve, void *handle)
{
    CudaStateNode *n = (CudaStateNode *)malloc(sizeof(CudaStateNode));
    if (!n) return;              /* losing a handle leaks; it must not crash */
    n->handle = handle;
    n->hsolve = hsolve;
    n->next   = cuda_states;
    cuda_states = n;
}

/* One dispatch per simulation step covering every registered solver, rather
** than one per solver. The scheduler calls the accelerator once per hsolve per
** step, so the first call of a step does the work for all of them; later calls
** in the same step find their stamp already set and return.
**
** This reorders channel computation relative to h_in_msgs(), which the
** scheduler runs per solver immediately before each update, so solver B's
** channels are computed before B's own h_in_msgs() has run this step. Sound
** only when no solver's input depends on another solver's output within the
** step -- i.e. no spike-mediated coupling. hsolve->spikegen is the marker.
** ininfo is NOT the right test: INJECT creates an ininfo entry too
** (hines_msgs.c), so keying on it would disable batching for inject-driven
** models, which are exactly the ones this is meant to speed up. */
static int cuda_batch_checked = 0;
static int cuda_batch_ok      = 0;

static int cuda_batch_allowed(void)
{
    CudaStateNode *n;
    if (cuda_batch_checked) return cuda_batch_ok;
    cuda_batch_checked = 1;
    cuda_batch_ok = 1;
    for (n = cuda_states; n; n = n->next) {
        if (n->hsolve && n->hsolve->spikegen) {
            fprintf(stderr, "CUDA: spikegen present; cross-hsolve batching "
                            "disabled (message ordering would change).\n");
            cuda_batch_ok = 0;
            break;
        }
    }
    return cuda_batch_ok;
}

/* The work for one solver, factored out so the barrier can run it on behalf of
** solvers whose own turn has not come yet this step. */
static int cuda_perstep_one(Hsolve *hsolve)
{
    if (cuda_backend_needs_chip_every_step(hsolve->accel_state)) {
        cuda_synaptic_pass(hsolve);
        cuda_backend_upload_chip(hsolve->accel_state, hsolve->chip);
    } else if (!cuda_backend_chip_on_gpu(hsolve->accel_state)) {
        cuda_backend_upload_chip(hsolve->accel_state, hsolve->chip);
    }
    if (cuda_backend_perstep(hsolve->accel_state, hsolve->vm, hsolve->results) != 0)
        return -1;
    /* The kernel records threshold crossings; emission happens here because
       h_dospike_event() dispatches to synapses on other cells, which is
       host-side GENESIS messaging the device cannot do. One call per crossing,
       matching what the CPU interpreter does. */
    if (cuda_backend_has_spikes(hsolve->accel_state)) {
        int k = cuda_backend_spikes_this_step(hsolve->accel_state);
        while (k-- > 0) h_dospike_event(hsolve);
    }
    return 0;
}

/* Process-wide: records that the platform cannot drive the GPU at all. The
** multiloop counters and the chip-upload flag used to live here too, which
** silently broke every model with more than one hsolve -- see the CudaState
** fields they moved to. */
static int cuda_disabled         = 0;

/* Where each SYN2_OP's operands start in hsolve->ops[], collected at SETUP.
   Bounded rather than grown: a solver with more synaptic channels than this
   simply is not accelerated, which is safer than a partial list. */
#define MAX_SYN_SITES 4096
static int syn_sites[MAX_SYN_SITES];
static int syn_nsites = 0;

/* The half of SYN2_OP that cannot leave the host: the event countdown lives in
   ops[], and h_dosynchan() calls into the synchan child element to fetch its
   activation. Order matters and follows hines_chip.c exactly -- decay the X
   state first, then let an arriving event add to it -- so both are done here,
   before chip[] is uploaded, and the kernel is left with the dual-exponential
   update alone. */
static void cuda_synaptic_pass(Hsolve *hsolve)
{
    int i;
    for (i = 0; i < syn_nsites; i++) {
        int *op = &hsolve->ops[syn_sites[i]];
        int  k  = op[0];
        int  nchip;
        /* chip slot for this site: the X state, i.e. the first of its two */
        nchip = hsolve->childchips[op[2]];
        hsolve->chip[nchip] *= hsolve->stablist[k];
        if (op[1] == 0) h_dosynchan(hsolve, k, op[2]);
        op[1] -= 1;
    }
}

/* Same sentinel-aware walk as opencl/ocl_hsolve.c build_comp_index(), and the
   same cpu_only[] marking: compartments using opcodes the kernel does not
   implement (SPIKE_OP, synchan, GHK, concentrations) must not be dispatched to
   the GPU. The kernel silently ignores unknown opcodes WITHOUT skipping their
   operands, so the ops[] stream desynchronises from the first such opcode and
   every later chip read lands on a wrong index -- silently wrong results. */
static void build_comp_index(Hsolve *hsolve, int **out_opstart,
                             int **out_chipstart, int **out_cpu_only,
                             int **out_spike_refrac, int *out_nspike,
                             int *out_unsup, int *out_nunsup,
                             int *out_syn, int *out_nsyn)
{
    int n = hsolve->ncompts;
    int *opstart   = (int *)malloc(n * sizeof(int));
    int *chipstart = (int *)malloc(n * sizeof(int));
    int *cpu_only  = (int *)calloc(n, sizeof(int));
    /* Initial refractory counter per compartment, lifted out of ops[] because
       the kernel cannot mutate the opcode stream (uploaded read-only). Zero
       where the compartment has no SPIKE_OP. */
    int *refrac0   = (int *)calloc(n, sizeof(int));
    int nspike = 0;
    int op_i = 1, chip_i = 0, c;

    for (c = 0; c < n; c++) {
        opstart[c]   = op_i;
        chipstart[c] = chip_i;
        chip_i += 2;
        while (hsolve->ops[op_i] > LCOMPT_OP) {
            int op = hsolve->ops[op_i++];
            switch (op) {
                case NEWVOLT_OP:                       break;
                case CHAN_EK_OP: chip_i++;             /* fall through */
                case CHAN_OP:    chip_i++;             break;
                case ADD_CURR_OP:                      break;
                case IPOL1V_OP:  op_i += 2; chip_i++;  break;
                case SYN2_OP:
                    /* Three operands (table index, event countdown, child
                       index) and two chip slots (X and Y state), matching the
                       interpreter in hines_chip.c. Getting this wrong
                       desynchronises everything after it. */
                    if (out_syn && *out_nsyn < MAX_SYN_SITES) {
                        out_syn[*out_nsyn] = op_i;
                        (*out_nsyn)++;
                    }
                    op_i += 3; chip_i += 2;                break;
                case SPIKE_OP:
                    /* Handled on the device now: the counter is seeded here and
                       kept in a writable buffer, the reload value is read from
                       ops[] by the kernel, and the event itself is emitted by
                       the host after the dispatch returns. */
                    refrac0[c] = hsolve->ops[op_i];
                    nspike++;
                    op_i += 2; chip_i++;               break;
                default:
                    /* Record the first few distinct unsupported opcodes so the
                       refusal message can say what is actually missing, rather
                       than leaving the user to bisect a model. */
                    {
                        int k, seen = 0;
                        for (k = 0; k < *out_nunsup && k < 8; k++)
                            if (out_unsup[k] == op) { seen = 1; break; }
                        if (!seen && *out_nunsup < 8)
                            out_unsup[(*out_nunsup)++] = op;
                    }
                    cpu_only[c] = 1;                   break;
            }
        }
        chip_i += 2;
        op_i++;
    }
    *out_opstart   = opstart;
    *out_chipstart = chipstart;
    *out_cpu_only  = cpu_only;
    *out_spike_refrac = refrac0;
    *out_nspike = nspike;
}


/* A compartment that is simultaneously a leaf and has siblings -- i.e. a branch
   exactly one compartment long hanging off a branch point -- is not handled by
   the tree-elimination kernel. GPU_HINES_SOLVE_DESIGN.md isolates the fault to
   the leading-FORWARD_ELIM bootstrap's seed-row assumption, which does not hold
   when row 0/1 is itself a leaf-with-siblings; the failure was only ever
   observed in the first tree, and trees beyond it pass with the identical
   shape.
   
   We refuse it in every tree regardless. Deciding which rows belong to the
   first tree is one more thing the guard could get subtly wrong, and the shape
   does not occur in real dendrite models -- a branch that extends no further is
   an odd way of modelling the soma -- so declining it everywhere costs nothing
   in practice and cannot be got wrong.
   
   Until this commit the case was documented but not enforced: the kernels
   carried a comment about it and do_pertree_validate detected it, but only
   under the opt-in GENESIS_VALIDATE_PERTREE comparison. An ordinary run
   dispatched such a model and produced silently wrong voltages. */
static int cuda_has_degenerate_branch(Hsolve *hsolve)
{
    int i, p;
    if (!hsolve->parents || !hsolve->nkids) return 0;
    for (i = 0; i < hsolve->ncompts; i++) {
        p = hsolve->parents[i];
        if (hsolve->nkids[i] == 0 && p >= 0 && hsolve->nkids[p] > 1)
            return 1;
    }
    return 0;
}

int cuda_init(Hsolve *hsolve)
{
    int n   = hsolve->ncompts;
    int nc  = hsolve->nchips;
    int no  = hsolve->nops;
    int nt  = (hsolve->xdivs > 0 && hsolve->ncols > 0)
              ? (hsolve->xdivs + 2) * hsolve->ncols : 1;
    int nx  = (hsolve->xdivs > 0) ? hsolve->xdivs + 2 : 1;
    int *opstart = NULL, *chipstart = NULL, *cpu_only = NULL, *refrac0 = NULL;
    int nspike = 0;
    int unsup[8], nunsup = 0;
    int nsyn = 0;
    int unsup_count, ci;
    const char *env;

    if (n <= 0 || nc <= 0 || no <= 0) {
        fprintf(stderr, "CUDA: hsolve not initialised (n=%d nc=%d no=%d)\n", n, nc, no);
        return -1;
    }

    if (cuda_has_degenerate_branch(hsolve)) {
        fprintf(stderr,
            "CUDA: this hsolve contains a single-compartment branch off a "
            "branch point, which the tree-elimination kernel does not handle; "
            "acceleration disabled for this hsolve, computing on CPU.\n");
        
        return -1;
    }

    build_comp_index(hsolve, &opstart, &chipstart, &cpu_only, &refrac0, &nspike,
                     unsup, &nunsup, syn_sites, &nsyn);

    /* Refuse the GPU path when any compartment needs an opcode the kernel does
       not implement; the caller sets cuda_disabled and falls back to the CPU
       solver for the rest of the run. Checked before cuda_backend_init() so no
       device resources are allocated on the refusal path. */
    unsup_count = 0;
    for (ci = 0; ci < n; ci++)
        if (cpu_only[ci]) unsup_count++;
    if (unsup_count > 0) {
        fprintf(stderr,
            "CUDA: %d of %d compartments use opcodes the kernel does not "
            "implement; acceleration disabled for this hsolve, computing on "
            "CPU.\n", unsup_count, n);
        {
            int k;
            fprintf(stderr, "CUDA: unsupported opcodes seen:");
            for (k = 0; k < nunsup; k++) fprintf(stderr, " %d", unsup[k]);
            fprintf(stderr, "%s\n", nunsup >= 8 ? " (list truncated)" : "");
        }
        free(opstart); free(chipstart); free(cpu_only); free(refrac0);
        return -1;
    }
    free(cpu_only);

    hsolve->accel_state = cuda_backend_init(n, nc, no, hsolve->ncols, hsolve->xdivs,
                          hsolve->xmin, hsolve->invdx,
                          hsolve->ops,
                          hsolve->tablist, nt,
                          hsolve->xvals, nx,
                                            opstart, chipstart, refrac0, nspike,
                                            hsolve->stablist, hsolve->sntab);
    if (!hsolve->accel_state) {
        free(opstart); free(chipstart); free(refrac0);
        return -1;
    }
    syn_nsites = nsyn;
    cuda_state_register(hsolve, hsolve->accel_state);
    cuda_batch_checked = 0;   /* a solver joined; re-evaluate */
    free(opstart); free(chipstart);

    /* Same env var as the OpenCL path so benchmarks/scripts are unchanged;
       GENESIS_CUDA_MULTILOOP overrides if present. */
    env = getenv("GENESIS_CUDA_MULTILOOP");
    if (!env) env = getenv("GENESIS_OCL_MULTILOOP");
    if (env) {
        int k = atoi(env);
        cuda_backend_set_multiloop_total(hsolve->accel_state, k);
        if (k > 0)
            printf("CUDA: multiloop mode -- %d steps per dispatch\n", k);
    }

    /* cuda_init now runs once per hsolve, and the one-solver-per-cell idiom
    ** creates thousands of them; atexit() only guarantees 32 registrations, so
    ** register the exit hook exactly once. */
    if (!cuda_atexit_registered) {
        atexit(cuda_cleanup);
        cuda_atexit_registered = 1;
    }
    return 0;
}

int cuda_chip_update(Hsolve *hsolve)
{
    if (!cuda_backend_initialized(hsolve->accel_state)) {
        if (cuda_disabled)
            return do_chip_hh4_update(hsolve);
        if (cuda_init(hsolve) != 0) {
            cuda_disabled = 1;
            return do_chip_hh4_update(hsolve);
        }
    }

    if (cuda_backend_multiloop_total(hsolve->accel_state) > 0 &&
        cuda_backend_has_spikes(hsolve->accel_state)) {
        /* A K-step batch runs entirely on the device, so a spike raised inside
           it cannot reach other cells' synapses before the batch ends. That is
           a property of the batching, not of the opcode, so multiloop is
           refused rather than the model. */
        static int warned = 0;
        if (!warned) {
            fprintf(stderr, "CUDA: multiloop disabled for this hsolve -- it "
                            "contains spike generators and events cannot be "
                            "delivered inside a batch.\n");
            warned = 1;
        }
        cuda_backend_set_multiloop_total(hsolve->accel_state, 0);
    }
    if (cuda_backend_multiloop_total(hsolve->accel_state) > 0) {
        if (cuda_backend_multiloop_called(hsolve->accel_state) > 0) {
            cuda_backend_bump_multiloop_called(hsolve->accel_state);
            return 1;   /* vm[] already final; hines.c skips the Hines solve */
        }
        /* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): real
        ** multicompartment tree structure (at least one tree has >1
        ** compartment) -- cuda_backend_multiloop's kernel only implements
        ** the isopotential single-compartment formula and silently drops
        ** axial coupling (see GPU_HINES_SOLVE_DESIGN.md). Dispatch the
        ** validated two-kernel-per-step tree solver instead. Pure
        ** single-compartment networks (n_trees == ncompts) keep using the
        ** faster single-kernel path below, unchanged -- mirrors
        ** opencl/ocl_hsolve.c's ocl_multiloop_dispatch exactly, including
        ** the same overridable safety cap (shared env var, so a script
        ** tuned for one backend works for both). */
        if (hsolve->n_trees > 0 && hsolve->n_trees < hsolve->ncompts) {
            static int cap_checked = 0;
            static long max_ncompts = 20000;
            if (!cap_checked) {
                const char *cap_env = getenv("GENESIS_OCL_TREE_MAX_NCOMPTS");
                if (cap_env) max_ncompts = atol(cap_env);
                cap_checked = 1;
            }
            if (max_ncompts > 0 && hsolve->ncompts > max_ncompts) {
                fprintf(stderr,
                    "CUDA multiloop (tree): ncompts=%d exceeds the safe cap (%ld, "
                    "override with GENESIS_OCL_TREE_MAX_NCOMPTS) -- see "
                    "ocl_hsolve.c/cuda_hsolve.c comments. Falling back to CPU "
                    "for this hsolve; multiloop disabled for the rest of this run.\n",
                    hsolve->ncompts, max_ncompts);
                cuda_backend_set_multiloop_total(hsolve->accel_state, 0);
                return do_chip_hh4_update(hsolve);
            }
            if (!cuda_backend_tree_ready(hsolve->accel_state)) {
                if (cuda_backend_tree_init(hsolve->accel_state, hsolve->n_trees, hsolve->nfuncs, hsolve->nravals,
                                           hsolve->funcs, hsolve->ravals,
                                           hsolve->fwd_seg_start, hsolve->bwd_seg_start,
                                           hsolve->fwd_root_row, hsolve->fwd_raval_start,
                                           hsolve->bwd_raval_start) != 0) {
                    fprintf(stderr, "CUDA multiloop (tree): buffer init failed, fallback CPU\n");
                    return do_chip_hh4_update(hsolve);
                }
            }
            if (cuda_backend_multiloop_tree(hsolve->accel_state, hsolve->vm, hsolve->chip,
                                            hsolve->results, cuda_backend_multiloop_total(hsolve->accel_state)) == 0) {
                cuda_backend_bump_multiloop_called(hsolve->accel_state);
                return 1;
            }
            return 0;
        }
        if (cuda_backend_multiloop(hsolve->accel_state, hsolve->vm, hsolve->chip,
                                   hsolve->results, cuda_backend_multiloop_total(hsolve->accel_state)) == 0) {
            cuda_backend_bump_multiloop_called(hsolve->accel_state);
            return 1;
        }
        return 0;       /* dispatch failed -> CPU Hines solve still needed */
    }

    /* per-step mode, one dispatch per step across all solvers */
    {
    double t = SimulationTime();
    CudaStateNode *n;

    if (cuda_batch_allowed()) {
        for (n = cuda_states; n; n = n->next) {
            if (!n->hsolve || !n->hsolve->accel_state) continue;
            if (cuda_backend_last_batch_time(n->handle) == t) continue;
            if (cuda_perstep_one(n->hsolve) != 0) {
                cuda_disabled = 1;
                return do_chip_hh4_update(hsolve);
            }
            cuda_backend_set_last_batch_time(n->handle, t);
        }
    }

    /* Covers this solver whether or not the batch ran: if it registered after
    ** the batch for this step, its stamp is still unset and it is computed here
    ** rather than returning without having been updated. */
    if (cuda_backend_last_batch_time(hsolve->accel_state) != t) {
        if (cuda_perstep_one(hsolve) != 0) {
            cuda_disabled = 1;
            return do_chip_hh4_update(hsolve);
        }
        cuda_backend_set_last_batch_time(hsolve->accel_state, t);
    }
    }
    return 0;
}

void cuda_sync_chip(Hsolve *hsolve)
{
    if (cuda_backend_chip_on_gpu(hsolve->accel_state))
        cuda_backend_sync_chip(hsolve->accel_state, hsolve->chip);
}

void cuda_cleanup(void)
{
    /* The multiloop summary used to be printed here from file-static counters.
    ** Those are per-hsolve now, so a single process-wide line would be wrong as
    ** soon as more than one solver runs; cuda_backend_cleanup already reports
    ** per-state profiling. */
    while (cuda_states) {
        CudaStateNode *n = cuda_states;
        cuda_states = n->next;
        cuda_backend_cleanup(n->handle);
        free(n);
    }
}

#endif /* USE_CUDA */
