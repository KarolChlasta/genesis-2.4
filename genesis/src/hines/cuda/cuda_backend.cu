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
