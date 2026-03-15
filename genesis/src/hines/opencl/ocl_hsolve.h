#ifndef OCL_HSOLVE_H
#define OCL_HSOLVE_H

#ifdef USE_OPENCL

#include <CL/cl.h>
#include "../hines_struct.h"

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
} OclHsolveState;

/* one global state — one GPU context per GENESIS process */
extern OclHsolveState ocl_state;

int  ocl_init(Hsolve *hsolve);
int  ocl_chip_update(Hsolve *hsolve);
void ocl_cleanup(void);

#endif /* USE_OPENCL */
#endif /* OCL_HSOLVE_H */
