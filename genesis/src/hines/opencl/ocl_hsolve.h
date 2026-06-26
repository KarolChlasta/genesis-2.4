#ifndef OCL_HSOLVE_H
#define OCL_HSOLVE_H

#ifdef USE_OPENCL

#include <CL/cl.h>
/* hines_struct.h included via hines_ext.h — do not include directly */
typedef struct hsolve_type Hsolve;

typedef struct {
    cl_context       context;
    cl_command_queue queue;
    cl_program       program;
    cl_kernel        kernel;       /* chip_channel_update   — single step */
    cl_kernel        kernel_multi; /* chip_channel_multiloop — K steps    */
    cl_device_id     device;

    /* GPU buffers — float mirrors of hsolve's double arrays. Kernel runs in
       fp32 (device may lack cl_khr_fp64, e.g. AMD RDNA3); host converts
       double<->float at upload/download time using the scratch buffers
       below. */
    cl_mem buf_vm;       /* float[ncompts] */
    cl_mem buf_chip;     /* float[nchips]  */
    cl_mem buf_results;  /* float[ncompts*2] */
    cl_mem buf_tablist;  /* float[xdivs+1 * ncols] */
    cl_mem buf_xvals;    /* float[xdivs+2] */
    cl_mem buf_ops;      /* int[nops] */
    cl_mem buf_stablist; /* float[sntab*6] */

    /* host-side float scratch buffers reused every step for double<->float
       conversion (avoids malloc/free per step) */
    float *f_vm;         /* [ncompts] */
    float *f_chip;       /* [nchips]  */
    float *f_results;    /* [ncompts*2] */

    int    ncompts;
    int    nchips;
    int    nops;
    int    initialized;
    /* Set on any init failure so subsequent steps skip OCL without retrying. */
    int    disabled;
    /* After the first successful kernel run chip[] lives on the GPU.
       CPU copy (hsolve->chip) is stale until ocl_sync_chip() is called. */
    int    chip_on_gpu;

    /* Multiloop mode: set via GENESIS_OCL_MULTILOOP env var before running.
       If multiloop_total > 0, the first call to ocl_chip_update runs all
       multiloop_total steps on GPU in one shot; subsequent calls are no-ops.
       Only valid for single-compartment networks (no tridiagonal coupling). */
    int    multiloop_total;   /* 0 = off; >0 = steps per batch */
    int    multiloop_called;  /* counts ocl_chip_update calls when multiloop active */

    /* profiling accumulators */
    unsigned long long prof_kernel_ns;  /* total GPU kernel execution time */
    unsigned long long prof_total_ns;   /* total wall time inside ocl_chip_update */
    unsigned long long prof_transfer_ns;/* wall time of buffer transfers only */
    unsigned long       prof_calls;     /* number of steps profiled */
} OclHsolveState;

/* one global state — one GPU context per GENESIS process */
extern OclHsolveState ocl_state;

int  ocl_init(Hsolve *hsolve);
int  ocl_chip_update(Hsolve *hsolve);
void ocl_sync_chip(Hsolve *hsolve); /* download chip[] to CPU on demand */
void ocl_cleanup(void);

#endif /* USE_OPENCL */
#endif /* OCL_HSOLVE_H */
