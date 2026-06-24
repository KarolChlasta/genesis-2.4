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
    cl_kernel        kernel;
    cl_device_id     device;

    /* GPU buffers — mirrors of hsolve arrays */
    cl_mem buf_vm;       /* double[ncompts] */
    cl_mem buf_chip;     /* double[nchips]  */
    cl_mem buf_results;  /* double[ncompts*2] */
    cl_mem buf_tablist;  /* double[xdivs+1 * ncols] */
    cl_mem buf_xvals;    /* double[xdivs+2] */
    cl_mem buf_ops;      /* int[nops] */
    cl_mem buf_stablist; /* double[sntab*6] */

    int    ncompts;
    int    nchips;
    int    nops;
    int    initialized;
    /* Set on any init failure so subsequent steps skip OCL without retrying. */
    int    disabled;
    /* After the first successful kernel run chip[] lives on the GPU.
       CPU copy (hsolve->chip) is stale until ocl_sync_chip() is called. */
    int    chip_on_gpu;

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
