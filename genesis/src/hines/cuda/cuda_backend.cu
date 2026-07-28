/*
 * cuda_backend.cu -- CUDA device management + dispatch, array-based API.
 *
 * This translation unit is compiled by nvcc (C++). It deliberately does NOT
 * include any GENESIS header: it talks to the rest of hsolve only through the
 * plain-array extern "C" API declared at the bottom, so nvcc never has to
 * parse GENESIS's K&R C. The GENESIS-struct-aware glue lives in the C file
 * cuda_hsolve.c, which is compiled by the ordinary C compiler and calls these
 * functions. This mirrors the split the OpenCL backend gets for free (its
 * kernel is a runtime-compiled string), and is the standard robust way to add
 * CUDA to a C codebase.
 *
 * Semantics are a 1:1 port of opencl/ocl_hsolve.c: fp32 kernels, host-side
 * double<->float conversion at the buffer boundary, persistent chip[] on the
 * device between per-step calls, and a multiloop path that batches K steps in
 * one launch. Timing lines are printed in the same shape as the OpenCL path
 * ("CUDA MULTILOOP: ... total X ms") so the benchmark harness parses either.
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cuda_runtime.h>
#include "cuda_channel.cuh"

#define CUDA_CHECK(call, what)                                                  \
    do {                                                                        \
        cudaError_t _e = (call);                                                \
        if (_e != cudaSuccess) {                                                \
            fprintf(stderr, "CUDA: %s failed: %s\n", (what),                    \
                    cudaGetErrorString(_e));                                    \
            return -1;                                                          \
        }                                                                       \
    } while (0)

namespace {

struct CudaState {
    int initialized = 0;
    int disabled    = 0;
    int chip_on_gpu = 0;

    int ncompts = 0, nchips = 0, nops = 0, ncols = 0, xdivs = 0;
    float xmin = 0.0f, invdx = 0.0f;

    /* device buffers (fp32 mirrors of hsolve's double arrays) */
    float *d_vm = nullptr, *d_chip = nullptr, *d_results = nullptr;
    float *d_tablist = nullptr, *d_xvals = nullptr;
    int   *d_ops = nullptr, *d_opstart = nullptr, *d_chipstart = nullptr;

    /* host fp32 scratch reused every step */
    float *f_vm = nullptr, *f_chip = nullptr, *f_results = nullptr;

    /* per-step profiling */
    cudaEvent_t ev_start = nullptr, ev_stop = nullptr;
    double prof_kernel_ms = 0.0;
    unsigned long prof_calls = 0;

    /* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): device buffers for
    ** cuda_hines_tree_eliminate, the real per-tree multicompartment solver
    ** -- mirrors opencl/ocl_hsolve.h's matching fields. See
    ** GPU_HINES_SOLVE_DESIGN.md for the validated kernel-entry protocol. */
    int tree_ready = 0;
    int n_trees = 0;
    int *d_funcs = nullptr;
    float *d_ravals = nullptr;
    int *d_fwd_seg_start = nullptr, *d_fwd_seg_end = nullptr;
    int *d_bwd_seg_start = nullptr, *d_bwd_seg_end = nullptr;
    int *d_fwd_root_row = nullptr, *d_fwd_raval_start = nullptr, *d_bwd_raval_start = nullptr;
};

CudaState S;

inline void d2f(const double *src, float *dst, int n) {
    for (int i = 0; i < n; i++) dst[i] = (float)src[i];
}
inline void f2d(const float *src, double *dst, int n) {
    for (int i = 0; i < n; i++) dst[i] = (double)src[i];
}

inline int grid_for(int n, int block) { return (n + block - 1) / block; }

} /* anonymous namespace */

extern "C" {

/* Configure device + upload static data. opstart/chipstart are built by the
   C glue (build_comp_index) exactly as for OpenCL. tablist/xvals are the
   double source arrays (may be null when there are no tabchannels). */
int cuda_backend_init(int ncompts, int nchips, int nops, int ncols, int xdivs,
                      double xmin, double invdx,
                      const int *ops,
                      const double *tablist, int ntab,
                      const double *xvals, int nx,
                      const int *opstart, const int *chipstart)
{
    int dev_count = 0;
    CUDA_CHECK(cudaGetDeviceCount(&dev_count), "cudaGetDeviceCount");
    if (dev_count < 1) {
        fprintf(stderr, "CUDA: no device found\n");
        return -1;
    }
    cudaDeviceProp prop;
    CUDA_CHECK(cudaGetDeviceProperties(&prop, 0), "cudaGetDeviceProperties");
    printf("CUDA: device: %s (sm_%d%d, %d SMs)\n",
           prop.name, prop.major, prop.minor, prop.multiProcessorCount);

    S.ncompts = ncompts; S.nchips = nchips; S.nops = nops;
    S.ncols = ncols; S.xdivs = xdivs;
    S.xmin = (float)xmin; S.invdx = (float)invdx;

    if (ntab < 1) ntab = 1;
    if (nx  < 1) nx  = 1;

    CUDA_CHECK(cudaMalloc(&S.d_vm,        ncompts * sizeof(float)),   "malloc vm");
    CUDA_CHECK(cudaMalloc(&S.d_chip,      nchips  * sizeof(float)),   "malloc chip");
    CUDA_CHECK(cudaMalloc(&S.d_results,   ncompts * 2 * sizeof(float)),"malloc results");
    CUDA_CHECK(cudaMalloc(&S.d_tablist,   ntab    * sizeof(float)),   "malloc tablist");
    CUDA_CHECK(cudaMalloc(&S.d_xvals,     nx      * sizeof(float)),   "malloc xvals");
    CUDA_CHECK(cudaMalloc(&S.d_ops,       nops    * sizeof(int)),     "malloc ops");
    CUDA_CHECK(cudaMalloc(&S.d_opstart,   ncompts * sizeof(int)),     "malloc opstart");
    CUDA_CHECK(cudaMalloc(&S.d_chipstart, ncompts * sizeof(int)),     "malloc chipstart");

    S.f_vm      = (float *)malloc(ncompts * sizeof(float));
    S.f_chip    = (float *)malloc(nchips  * sizeof(float));
    S.f_results = (float *)malloc(ncompts * 2 * sizeof(float));

    /* upload static data (once): ops, opstart, chipstart, and fp32 tables */
    CUDA_CHECK(cudaMemcpy(S.d_ops, ops, nops * sizeof(int),
                          cudaMemcpyHostToDevice), "copy ops");
    CUDA_CHECK(cudaMemcpy(S.d_opstart, opstart, ncompts * sizeof(int),
                          cudaMemcpyHostToDevice), "copy opstart");
    CUDA_CHECK(cudaMemcpy(S.d_chipstart, chipstart, ncompts * sizeof(int),
                          cudaMemcpyHostToDevice), "copy chipstart");

    {
        float dummy = 0.0f;
        float *fconv = (float *)malloc((ntab > nx ? ntab : nx) * sizeof(float));
        if (tablist && xdivs > 0) {
            d2f(tablist, fconv, ntab);
            CUDA_CHECK(cudaMemcpy(S.d_tablist, fconv, ntab * sizeof(float),
                                  cudaMemcpyHostToDevice), "copy tablist");
        } else {
            CUDA_CHECK(cudaMemcpy(S.d_tablist, &dummy, sizeof(float),
                                  cudaMemcpyHostToDevice), "copy tablist(dummy)");
        }
        if (xvals && xdivs > 0) {
            d2f(xvals, fconv, nx);
            CUDA_CHECK(cudaMemcpy(S.d_xvals, fconv, nx * sizeof(float),
                                  cudaMemcpyHostToDevice), "copy xvals");
        } else {
            CUDA_CHECK(cudaMemcpy(S.d_xvals, &dummy, sizeof(float),
                                  cudaMemcpyHostToDevice), "copy xvals(dummy)");
        }
        free(fconv);
    }

    cudaEventCreate(&S.ev_start);
    cudaEventCreate(&S.ev_stop);

    S.initialized = 1;
    S.chip_on_gpu = 0;
    printf("CUDA: ready (%d compartments, %d chips)\n", ncompts, nchips);
    return 0;
}

/* One-step dispatch: upload vm (always) + chip (first call only), launch the
   single-step kernel, download results[]. Mirrors ocl_chip_update per-step. */
int cuda_backend_perstep(const double *vm, double *results_out)
{
    int n = S.ncompts, nc = S.nchips;
    d2f(vm, S.f_vm, n);
    CUDA_CHECK(cudaMemcpy(S.d_vm, S.f_vm, n * sizeof(float),
                          cudaMemcpyHostToDevice), "upload vm");
    /* chip[] uploaded by cuda_backend_upload_chip() on the first step */

    int block = 64, grid = grid_for(n, block);
    cudaEventRecord(S.ev_start);
    cuda_chip_channel_update<<<grid, block>>>(
        S.d_vm, S.d_chip, S.d_results, S.d_tablist, S.d_xvals,
        S.d_ops, S.d_opstart, S.d_chipstart,
        n, S.ncols, S.xdivs, S.xmin, S.invdx);
    cudaEventRecord(S.ev_stop);

    cudaError_t kerr = cudaGetLastError();
    if (kerr != cudaSuccess) {
        fprintf(stderr, "CUDA: kernel launch failed: %s\n",
                cudaGetErrorString(kerr));
        return -1;
    }
    S.chip_on_gpu = 1;

    CUDA_CHECK(cudaMemcpy(S.f_results, S.d_results, n * 2 * sizeof(float),
                          cudaMemcpyDeviceToHost), "download results");
    f2d(S.f_results, results_out, n * 2);

    cudaEventSynchronize(S.ev_stop);
    float ms = 0.0f;
    cudaEventElapsedTime(&ms, S.ev_start, S.ev_stop);
    S.prof_kernel_ms += ms;
    S.prof_calls++;
    return 0;
}

/* Upload chip[] to device (called once, before the first per-step kernel). */
int cuda_backend_upload_chip(const double *chip)
{
    d2f(chip, S.f_chip, S.nchips);
    CUDA_CHECK(cudaMemcpy(S.d_chip, S.f_chip, S.nchips * sizeof(float),
                          cudaMemcpyHostToDevice), "upload chip");
    S.chip_on_gpu = 1;
    return 0;
}

/* Multiloop dispatch: one upload of vm+chip, one K-step kernel launch, one
   download of vm+chip+results. Mirrors ocl_multiloop_dispatch. */
int cuda_backend_multiloop(double *vm_io, double *chip_io,
                           double *results_out, int nsteps)
{
    int n = S.ncompts, nc = S.nchips;

    d2f(vm_io, S.f_vm, n);
    d2f(chip_io, S.f_chip, nc);
    CUDA_CHECK(cudaMemcpy(S.d_vm, S.f_vm, n * sizeof(float),
                          cudaMemcpyHostToDevice), "ml upload vm");
    CUDA_CHECK(cudaMemcpy(S.d_chip, S.f_chip, nc * sizeof(float),
                          cudaMemcpyHostToDevice), "ml upload chip");

    int block = 64, grid = grid_for(n, block);
    cudaEventRecord(S.ev_start);
    cuda_chip_channel_multiloop<<<grid, block>>>(
        S.d_vm, S.d_chip, S.d_results, S.d_tablist, S.d_xvals,
        S.d_ops, S.d_opstart, S.d_chipstart,
        n, S.ncols, S.xdivs, S.xmin, S.invdx, nsteps);
    cudaEventRecord(S.ev_stop);

    cudaError_t kerr = cudaGetLastError();
    if (kerr != cudaSuccess) {
        fprintf(stderr, "CUDA multiloop: launch failed: %s\n",
                cudaGetErrorString(kerr));
        return -1;
    }

    CUDA_CHECK(cudaMemcpy(S.f_vm, S.d_vm, n * sizeof(float),
                          cudaMemcpyDeviceToHost), "ml download vm");
    CUDA_CHECK(cudaMemcpy(S.f_results, S.d_results, n * 2 * sizeof(float),
                          cudaMemcpyDeviceToHost), "ml download results");
    CUDA_CHECK(cudaMemcpy(S.f_chip, S.d_chip, nc * sizeof(float),
                          cudaMemcpyDeviceToHost), "ml download chip");
    f2d(S.f_vm, vm_io, n);
    f2d(S.f_results, results_out, n * 2);
    f2d(S.f_chip, chip_io, nc);
    S.chip_on_gpu = 0;

    cudaEventSynchronize(S.ev_stop);
    float ms = 0.0f;
    cudaEventElapsedTime(&ms, S.ev_start, S.ev_stop);
    printf("CUDA MULTILOOP: %d steps | kernel %.1f ms | total %.1f ms | %.3f us/step\n",
           nsteps, ms, ms, ms * 1e3 / nsteps);
    return 0;
}

/* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): uploads funcs[]/
** ravals[] and per-tree dispatch metadata for cuda_hines_tree_eliminate,
** and derives fwd_seg_end[]/bwd_seg_end[] once here (O(n_trees log
** n_trees) sort for the backward one, since discovery order != backward-
** loop order -- see the CPU reference do_pertree_validate's O(n_trees)
** per-tree search that this replaces with something that scales, and
** opencl/ocl_hsolve.c's ocl_tree_buffers_init, which this mirrors
** exactly). Called once, lazily, the first time a multiloop batch
** actually needs it (real tree structure, not all-single-compartment). */
int cuda_backend_tree_init(int n_trees, int nfuncs, int nravals,
                           const int *funcs, const double *ravals,
                           const int *fwd_seg_start, const int *bwd_seg_start,
                           const int *fwd_root_row, const int *fwd_raval_start,
                           const int *bwd_raval_start)
{
    std::vector<int> fwd_seg_end(n_trees), bwd_seg_end(n_trees);
    std::vector<float> fravals(nravals);
    std::vector<std::pair<int,int> > sorted(n_trees); /* (bwd_seg_start, idx) */
    int i;

    for (i = 0; i < n_trees; i++) {
        fwd_seg_end[i] = (i+1 < n_trees) ? fwd_seg_start[i+1] : bwd_seg_start[n_trees-1] - 1;
        sorted[i] = std::make_pair(bwd_seg_start[i], i);
    }
    std::sort(sorted.begin(), sorted.end());
    for (i = 0; i < n_trees; i++) {
        int this_idx = sorted[i].second;
        bwd_seg_end[this_idx] = (i+1 < n_trees) ? sorted[i+1].first - 1 : nfuncs - 1;
    }
    d2f(ravals, fravals.data(), nravals);

    CUDA_CHECK(cudaMalloc(&S.d_funcs, nfuncs * sizeof(int)), "malloc funcs");
    CUDA_CHECK(cudaMalloc(&S.d_ravals, nravals * sizeof(float)), "malloc ravals(tree)");
    CUDA_CHECK(cudaMalloc(&S.d_fwd_seg_start, n_trees * sizeof(int)), "malloc fwd_seg_start");
    CUDA_CHECK(cudaMalloc(&S.d_fwd_seg_end, n_trees * sizeof(int)), "malloc fwd_seg_end");
    CUDA_CHECK(cudaMalloc(&S.d_bwd_seg_start, n_trees * sizeof(int)), "malloc bwd_seg_start");
    CUDA_CHECK(cudaMalloc(&S.d_bwd_seg_end, n_trees * sizeof(int)), "malloc bwd_seg_end");
    CUDA_CHECK(cudaMalloc(&S.d_fwd_root_row, n_trees * sizeof(int)), "malloc fwd_root_row");
    CUDA_CHECK(cudaMalloc(&S.d_fwd_raval_start, n_trees * sizeof(int)), "malloc fwd_raval_start");
    CUDA_CHECK(cudaMalloc(&S.d_bwd_raval_start, n_trees * sizeof(int)), "malloc bwd_raval_start");

    CUDA_CHECK(cudaMemcpy(S.d_funcs, funcs, nfuncs * sizeof(int), cudaMemcpyHostToDevice), "copy funcs");
    CUDA_CHECK(cudaMemcpy(S.d_ravals, fravals.data(), nravals * sizeof(float), cudaMemcpyHostToDevice), "copy ravals(tree)");
    CUDA_CHECK(cudaMemcpy(S.d_fwd_seg_start, fwd_seg_start, n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy fwd_seg_start");
    CUDA_CHECK(cudaMemcpy(S.d_fwd_seg_end, fwd_seg_end.data(), n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy fwd_seg_end");
    CUDA_CHECK(cudaMemcpy(S.d_bwd_seg_start, bwd_seg_start, n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy bwd_seg_start");
    CUDA_CHECK(cudaMemcpy(S.d_bwd_seg_end, bwd_seg_end.data(), n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy bwd_seg_end");
    CUDA_CHECK(cudaMemcpy(S.d_fwd_root_row, fwd_root_row, n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy fwd_root_row");
    CUDA_CHECK(cudaMemcpy(S.d_fwd_raval_start, fwd_raval_start, n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy fwd_raval_start");
    CUDA_CHECK(cudaMemcpy(S.d_bwd_raval_start, bwd_raval_start, n_trees * sizeof(int), cudaMemcpyHostToDevice), "copy bwd_raval_start");

    S.n_trees = n_trees;
    S.tree_ready = 1;
    printf("CUDA: tree-elimination kernel ready (%d trees)\n", n_trees);
    return 0;
}

int cuda_backend_tree_ready(void) { return S.tree_ready; }

/* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): multiloop dispatch for
** real multicompartment trees -- nsteps iterations of (channel kernel over
** ncompts threads -> writes results[]; tree-eliminate kernel over n_trees
** threads -> reads that results[], writes vm[]) on the SAME CUDA stream
** (default stream here, implicitly ordered exactly like the OpenCL
** in-order queue), so each iteration's elimination kernel is guaranteed to
** see that iteration's own channel kernel's output with no explicit sync
** needed -- then one download of vm[]/chip[]. Mirrors
** opencl/ocl_hsolve.c's ocl_multiloop_dispatch_tree exactly, including the
** periodic cudaDeviceSynchronize() as cheap insurance against an unbounded
** host-side command queue (see that function's comment for why this
** alone did NOT explain the large-ncompts hang found on a local AMD iGPU
** and not reproduced on cluster A40 -- ported here defensively anyway). */
int cuda_backend_multiloop_tree(double *vm_io, double *chip_io, double *results_out, int nsteps)
{
    int n = S.ncompts, nc = S.nchips;
    int step;

    d2f(vm_io, S.f_vm, n);
    d2f(chip_io, S.f_chip, nc);
    CUDA_CHECK(cudaMemcpy(S.d_vm, S.f_vm, n * sizeof(float), cudaMemcpyHostToDevice), "mlt upload vm");
    CUDA_CHECK(cudaMemcpy(S.d_chip, S.f_chip, nc * sizeof(float), cudaMemcpyHostToDevice), "mlt upload chip");

    {
    int chan_block = 64, chan_grid = grid_for(n, chan_block);
    int tree_block = 64, tree_grid = grid_for(S.n_trees, tree_block);

    cudaEventRecord(S.ev_start);
    for (step = 0; step < nsteps; step++) {
        cuda_chip_channel_update<<<chan_grid, chan_block>>>(
            S.d_vm, S.d_chip, S.d_results, S.d_tablist, S.d_xvals,
            S.d_ops, S.d_opstart, S.d_chipstart,
            n, S.ncols, S.xdivs, S.xmin, S.invdx);
        cuda_hines_tree_eliminate<<<tree_grid, tree_block>>>(
            S.d_funcs, S.d_ravals, S.d_results, S.d_vm,
            S.d_fwd_seg_start, S.d_fwd_seg_end,
            S.d_bwd_seg_start, S.d_bwd_seg_end,
            S.d_fwd_root_row, S.d_fwd_raval_start, S.d_bwd_raval_start,
            S.n_trees);
        if ((step & 15) == 15) cudaDeviceSynchronize();
    }
    cudaEventRecord(S.ev_stop);

    cudaError_t kerr = cudaGetLastError();
    if (kerr != cudaSuccess) {
        fprintf(stderr, "CUDA multiloop (tree): kernel error: %s\n", cudaGetErrorString(kerr));
        return -1;
    }

    CUDA_CHECK(cudaMemcpy(S.f_vm, S.d_vm, n * sizeof(float), cudaMemcpyDeviceToHost), "mlt download vm");
    CUDA_CHECK(cudaMemcpy(S.f_results, S.d_results, n * 2 * sizeof(float), cudaMemcpyDeviceToHost), "mlt download results");
    CUDA_CHECK(cudaMemcpy(S.f_chip, S.d_chip, nc * sizeof(float), cudaMemcpyDeviceToHost), "mlt download chip");
    f2d(S.f_vm, vm_io, n);
    f2d(S.f_results, results_out, n * 2);
    f2d(S.f_chip, chip_io, nc);
    S.chip_on_gpu = 0;

    cudaEventSynchronize(S.ev_stop);
    float ms = 0.0f;
    cudaEventElapsedTime(&ms, S.ev_start, S.ev_stop);
    printf("CUDA MULTILOOP (tree): %d steps x 2 kernels | total %.1f ms | %.3f us/step\n",
           nsteps, ms, ms * 1e3 / nsteps);
    }
    return 0;
}

void cuda_backend_sync_chip(double *chip_out)
{
    if (!S.initialized || !S.chip_on_gpu) return;
    cudaMemcpy(S.f_chip, S.d_chip, S.nchips * sizeof(float),
               cudaMemcpyDeviceToHost);
    f2d(S.f_chip, chip_out, S.nchips);
    S.chip_on_gpu = 0;
}

int cuda_backend_chip_on_gpu(void) { return S.chip_on_gpu; }
int cuda_backend_initialized(void) { return S.initialized; }

void cuda_backend_cleanup(void)
{
    if (!S.initialized) return;
    cudaFree(S.d_vm); cudaFree(S.d_chip); cudaFree(S.d_results);
    cudaFree(S.d_tablist); cudaFree(S.d_xvals);
    cudaFree(S.d_ops); cudaFree(S.d_opstart); cudaFree(S.d_chipstart);
    if (S.tree_ready) {
        cudaFree(S.d_funcs); cudaFree(S.d_ravals);
        cudaFree(S.d_fwd_seg_start); cudaFree(S.d_fwd_seg_end);
        cudaFree(S.d_bwd_seg_start); cudaFree(S.d_bwd_seg_end);
        cudaFree(S.d_fwd_root_row); cudaFree(S.d_fwd_raval_start); cudaFree(S.d_bwd_raval_start);
    }
    free(S.f_vm); free(S.f_chip); free(S.f_results);
    if (S.ev_start) cudaEventDestroy(S.ev_start);
    if (S.ev_stop)  cudaEventDestroy(S.ev_stop);
    if (S.prof_calls > 0) {
        printf("CUDA PROFILING SUMMARY\n");
        printf("  steps profiled : %lu\n", S.prof_calls);
        printf("  kernel total   : %.3f ms  (%.2f us/step)\n",
               S.prof_kernel_ms, S.prof_kernel_ms * 1e3 / S.prof_calls);
        printf("  NOTE: kernel is only the channel-update fraction of a step;\n");
        printf("        the Hines solve runs on the CPU (per-step mode).\n");
    }
    S.initialized = 0;
}

} /* extern "C" */
