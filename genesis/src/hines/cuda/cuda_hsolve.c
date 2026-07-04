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
extern int  cuda_backend_init(int ncompts, int nchips, int nops, int ncols, int xdivs,
                              double xmin, double invdx,
                              const int *ops,
                              const double *tablist, int ntab,
                              const double *xvals, int nx,
                              const int *opstart, const int *chipstart);
extern int  cuda_backend_perstep(const double *vm, double *results_out);
extern int  cuda_backend_upload_chip(const double *chip);
extern int  cuda_backend_multiloop(double *vm_io, double *chip_io,
                                   double *results_out, int nsteps);
extern void cuda_backend_sync_chip(double *chip_out);
extern int  cuda_backend_chip_on_gpu(void);
extern int  cuda_backend_initialized(void);
extern void cuda_backend_cleanup(void);

/* GENESIS CPU fallback (in hines_4chip.c) */
extern int do_chip_hh4_update(Hsolve *hsolve);

static int cuda_multiloop_total  = 0;
static int cuda_multiloop_called = 0;
static int cuda_disabled         = 0;
static int cuda_chip_uploaded    = 0;

/* Same sentinel-aware walk as opencl/ocl_hsolve.c build_comp_index(). */
static void build_comp_index(Hsolve *hsolve, int **out_opstart, int **out_chipstart)
{
    int n = hsolve->ncompts;
    int *opstart   = (int *)malloc(n * sizeof(int));
    int *chipstart = (int *)malloc(n * sizeof(int));
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
                case SPIKE_OP:   op_i += 2; chip_i++;  break;
                default:                               break;
            }
        }
        chip_i += 2;
        op_i++;
    }
    *out_opstart   = opstart;
    *out_chipstart = chipstart;
}

int cuda_init(Hsolve *hsolve)
{
    int n   = hsolve->ncompts;
    int nc  = hsolve->nchips;
    int no  = hsolve->nops;
    int nt  = (hsolve->xdivs > 0 && hsolve->ncols > 0)
              ? (hsolve->xdivs + 2) * hsolve->ncols : 1;
    int nx  = (hsolve->xdivs > 0) ? hsolve->xdivs + 2 : 1;
    int *opstart = NULL, *chipstart = NULL;
    const char *env;

    if (n <= 0 || nc <= 0 || no <= 0) {
        fprintf(stderr, "CUDA: hsolve not initialised (n=%d nc=%d no=%d)\n", n, nc, no);
        return -1;
    }

    build_comp_index(hsolve, &opstart, &chipstart);
    if (cuda_backend_init(n, nc, no, hsolve->ncols, hsolve->xdivs,
                          hsolve->xmin, hsolve->invdx,
                          hsolve->ops,
                          hsolve->tablist, nt,
                          hsolve->xvals, nx,
                          opstart, chipstart) != 0) {
        free(opstart); free(chipstart);
        return -1;
    }
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

    atexit(cuda_cleanup);
    return 0;
}

int cuda_chip_update(Hsolve *hsolve)
{
    if (!cuda_backend_initialized()) {
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
        if (cuda_backend_multiloop(hsolve->vm, hsolve->chip,
                                   hsolve->results, cuda_multiloop_total) == 0) {
            cuda_multiloop_called = 1;
            return 1;
        }
        return 0;       /* dispatch failed -> CPU Hines solve still needed */
    }

    /* per-step mode: upload chip once, then vm every step */
    if (!cuda_chip_uploaded) {
        cuda_backend_upload_chip(hsolve->chip);
        cuda_chip_uploaded = 1;
    }
    if (cuda_backend_perstep(hsolve->vm, hsolve->results) != 0) {
        cuda_disabled = 1;
        return do_chip_hh4_update(hsolve);
    }
    return 0;
}

void cuda_sync_chip(Hsolve *hsolve)
{
    if (cuda_backend_chip_on_gpu())
        cuda_backend_sync_chip(hsolve->chip);
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
    cuda_backend_cleanup();
}

#endif /* USE_CUDA */
