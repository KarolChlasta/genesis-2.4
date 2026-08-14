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
                              const int *opstart, const int *chipstart);
extern int  cuda_backend_perstep(void *sth, const double *vm, double *results_out);
extern int  cuda_backend_upload_chip(void *sth, const double *chip);
extern int  cuda_backend_multiloop(void *sth, double *vm_io, double *chip_io,
                                   double *results_out, int nsteps);
extern void cuda_backend_sync_chip(void *sth, double *chip_out);
extern int  cuda_backend_chip_on_gpu(void *sth);
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


/* Registry of live per-hsolve accelerator states.
**
** cuda_cleanup() is registered with atexit() and therefore receives no Hsolve,
** but the device state is now owned per solver -- the one-solver-per-cell idiom
** (`call solver DUPLICATE`) creates thousands of them. Keeping the handles in a
** list here is what lets the exit path release them all. Registration is O(1)
** and the list is walked exactly once, at process exit. */
typedef struct cuda_state_node {
    void *handle;
    struct cuda_state_node *next;
} CudaStateNode;

static CudaStateNode *cuda_states = NULL;
static int cuda_atexit_registered = 0;

static void cuda_state_register(void *handle)
{
    CudaStateNode *n = (CudaStateNode *)malloc(sizeof(CudaStateNode));
    if (!n) return;              /* losing a handle leaks; it must not crash */
    n->handle = handle;
    n->next   = cuda_states;
    cuda_states = n;
}

static int cuda_multiloop_total  = 0;
static int cuda_multiloop_called = 0;
static int cuda_disabled         = 0;
static int cuda_chip_uploaded    = 0;

/* Same sentinel-aware walk as opencl/ocl_hsolve.c build_comp_index(), and the
   same cpu_only[] marking: compartments using opcodes the kernel does not
   implement (SPIKE_OP, synchan, GHK, concentrations) must not be dispatched to
   the GPU. The kernel silently ignores unknown opcodes WITHOUT skipping their
   operands, so the ops[] stream desynchronises from the first such opcode and
   every later chip read lands on a wrong index -- silently wrong results. */
static void build_comp_index(Hsolve *hsolve, int **out_opstart,
                             int **out_chipstart, int **out_cpu_only)
{
    int n = hsolve->ncompts;
    int *opstart   = (int *)malloc(n * sizeof(int));
    int *chipstart = (int *)malloc(n * sizeof(int));
    int *cpu_only  = (int *)calloc(n, sizeof(int));
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
                case SPIKE_OP:   op_i += 2; chip_i++;
                    cpu_only[c] = 1;                   break;
                default:
                    cpu_only[c] = 1;                   break;
            }
        }
        chip_i += 2;
        op_i++;
    }
    *out_opstart   = opstart;
    *out_chipstart = chipstart;
    *out_cpu_only  = cpu_only;
}

int cuda_init(Hsolve *hsolve)
{
    int n   = hsolve->ncompts;
    int nc  = hsolve->nchips;
    int no  = hsolve->nops;
    int nt  = (hsolve->xdivs > 0 && hsolve->ncols > 0)
              ? (hsolve->xdivs + 2) * hsolve->ncols : 1;
    int nx  = (hsolve->xdivs > 0) ? hsolve->xdivs + 2 : 1;
    int *opstart = NULL, *chipstart = NULL, *cpu_only = NULL;
    int unsup, ci;
    const char *env;

    if (n <= 0 || nc <= 0 || no <= 0) {
        fprintf(stderr, "CUDA: hsolve not initialised (n=%d nc=%d no=%d)\n", n, nc, no);
        return -1;
    }

    build_comp_index(hsolve, &opstart, &chipstart, &cpu_only);

    /* Refuse the GPU path when any compartment needs an opcode the kernel does
       not implement; the caller sets cuda_disabled and falls back to the CPU
       solver for the rest of the run. Checked before cuda_backend_init() so no
       device resources are allocated on the refusal path. */
    unsup = 0;
    for (ci = 0; ci < n; ci++)
        if (cpu_only[ci]) unsup++;
    if (unsup > 0) {
        fprintf(stderr,
            "CUDA: %d of %d compartments use opcodes not implemented by the "
            "kernel (SPIKE_OP/synchan/GHK/concentrations); acceleration "
            "disabled for this hsolve, computing on CPU.\n", unsup, n);
        free(opstart); free(chipstart); free(cpu_only);
        return -1;
    }
    free(cpu_only);

    hsolve->accel_state = cuda_backend_init(n, nc, no, hsolve->ncols, hsolve->xdivs,
                          hsolve->xmin, hsolve->invdx,
                          hsolve->ops,
                          hsolve->tablist, nt,
                          hsolve->xvals, nx,
                                            opstart, chipstart);
    if (!hsolve->accel_state) {
        free(opstart); free(chipstart);
        return -1;
    }
    cuda_state_register(hsolve->accel_state);
    free(opstart); free(chipstart);

    /* Same env var as the OpenCL path so benchmarks/scripts are unchanged;
       GENESIS_CUDA_MULTILOOP overrides if present. */
    env = getenv("GENESIS_CUDA_MULTILOOP");
    if (!env) env = getenv("GENESIS_OCL_MULTILOOP");
    if (env) {
        cuda_multiloop_total = atoi(env);
        if (cuda_multiloop_total > 0)
            printf("CUDA: multiloop mode -- %d steps per dispatch\n", cuda_multiloop_total);
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

    if (cuda_multiloop_total > 0) {
        if (cuda_multiloop_called > 0) {
            cuda_multiloop_called++;
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
                cuda_multiloop_total = 0;
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
                                            hsolve->results, cuda_multiloop_total) == 0) {
                cuda_multiloop_called = 1;
                return 1;
            }
            return 0;
        }
        if (cuda_backend_multiloop(hsolve->accel_state, hsolve->vm, hsolve->chip,
                                   hsolve->results, cuda_multiloop_total) == 0) {
            cuda_multiloop_called = 1;
            return 1;
        }
        return 0;       /* dispatch failed -> CPU Hines solve still needed */
    }

    /* per-step mode: upload chip once, then vm every step */
    if (!cuda_chip_uploaded) {
        cuda_backend_upload_chip(hsolve->accel_state, hsolve->chip);
        cuda_chip_uploaded = 1;
    }
    if (cuda_backend_perstep(hsolve->accel_state, hsolve->vm, hsolve->results) != 0) {
        cuda_disabled = 1;
        return do_chip_hh4_update(hsolve);
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
    if (cuda_multiloop_called > 0) {
        printf("CUDA MULTILOOP SUMMARY\n");
        printf("  batch dispatched : 1 kernel call covering %d steps\n",
               cuda_multiloop_total);
        printf("  no-op steps      : %d (CPU Hines identity pass-through)\n",
               cuda_multiloop_called - 1);
    }
    while (cuda_states) {
        CudaStateNode *n = cuda_states;
        cuda_states = n->next;
        cuda_backend_cleanup(n->handle);
        free(n);
    }
}

#endif /* USE_CUDA */
