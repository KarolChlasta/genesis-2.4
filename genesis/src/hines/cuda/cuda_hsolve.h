/*
 * cuda_hsolve.h -- C-callable interface to the CUDA channel backend.
 *
 * Mirrors opencl/ocl_hsolve.h. Only the function prototypes are exposed to
 * the C side (hines.c); the device state struct (CUDA event/stream types)
 * lives inside cuda_hsolve.cu so this header stays compilable by a plain C
 * compiler. The functions carry the same names/semantics as the OpenCL ones
 * (cuda_ prefix) so hines.c can select a backend with a single macro.
 */
#ifndef CUDA_HSOLVE_H
#define CUDA_HSOLVE_H

#ifdef USE_CUDA

/* hines_struct.h is included via hines_ext.h before this header. */
typedef struct hsolve_type Hsolve;

#ifdef __cplusplus
extern "C" {
#endif

int  cuda_init(Hsolve *hsolve);
int  cuda_chip_update(Hsolve *hsolve);   /* returns 1 in multiloop mode */
void cuda_sync_chip(Hsolve *hsolve);
void cuda_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* USE_CUDA */
#endif /* CUDA_HSOLVE_H */
