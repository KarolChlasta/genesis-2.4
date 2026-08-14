#ifndef OCL_HSOLVE_H
#define OCL_HSOLVE_H

#ifdef USE_OPENCL

#include <CL/cl.h>
/* hines_struct.h included via hines_ext.h — do not include directly */
typedef struct hsolve_type Hsolve;

/* Device-level resources: one OpenCL context, program and kernel set per
   GENESIS process, shared by every hsolve element. These are split out from
   the per-hsolve buffers below because the common GENESIS idiom -- one solver
   per cell, built with `call solver DUPLICATE` -- creates thousands of hsolve
   elements, and they must be able to share one context while each keeps its
   own buffers. */
typedef struct {
    cl_context       context;
    cl_command_queue queue;
    cl_program       program;
    cl_kernel        kernel;       /* chip_channel_update   — single step */
    cl_kernel        kernel_multi; /* chip_channel_multiloop — K steps, single-compt only */
    cl_kernel        kernel_tree;  /* hines_tree_eliminate — real multicompartment solve */
    cl_device_id     device;
} OclDeviceState;

typedef struct {
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

    /* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): buffers for
    ** hines_tree_eliminate, the real per-tree multicompartment solver --
    ** see GPU_HINES_SOLVE_DESIGN.md for the validated kernel-entry
    ** protocol this ports. funcs[]/ravals[] are the Hsolve opcode
    ** program/coefficient arrays (int/double on CPU -> int/float here,
    ** ravals converted like every other double->float buffer). The
    ** fwd_/bwd_ *_start/_end arrays are per-tree dispatch metadata:
    ** *_start come directly from the matching Hsolve fields (fwd_
    ** seg_start/bwd_seg_start/fwd_root_row/fwd_raval_start/
    ** bwd_raval_start); *_end are derived once at init time (see
    ** ocl_tree_buffers_init) since deriving them per-work-item on GPU
    ** would need an O(n_trees) search per tree. */
    cl_mem buf_funcs;          /* int[nfuncs] */
    cl_mem buf_ravals;         /* float[nravals], READ_WRITE */
    cl_mem buf_fwd_seg_start;  /* int[n_trees] */
    cl_mem buf_fwd_seg_end;    /* int[n_trees] */
    cl_mem buf_bwd_seg_start;  /* int[n_trees] */
    cl_mem buf_bwd_seg_end;    /* int[n_trees] */
    cl_mem buf_fwd_root_row;   /* int[n_trees] */
    cl_mem buf_fwd_raval_start;/* int[n_trees] */
    cl_mem buf_bwd_raval_start;/* int[n_trees] */
    int    n_trees;
    int    tree_kernel_ready;  /* 1 once buf_funcs etc are uploaded */

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

/* Shared device resources, initialised once. */
extern OclDeviceState ocl_dev;


int  ocl_init(Hsolve *hsolve);
int  ocl_chip_update(Hsolve *hsolve);
void ocl_sync_chip(Hsolve *hsolve); /* download chip[] to CPU on demand */
void ocl_cleanup(void);

#endif /* USE_OPENCL */
#endif /* OCL_HSOLVE_H */
