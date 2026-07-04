/*
 * cuda_channel.cuh
 *
 * CUDA port of opencl/ocl_channel.cl. One thread == one compartment.
 * Line-for-line faithful to the OpenCL kernels so the two backends compute
 * bit-comparable results (both fp32); see opencl/ocl_channel.cl for the
 * annotated reference version and the sentinel/opcode explanation.
 *
 * Translation map OpenCL C -> CUDA C++:
 *   __kernel void          -> extern "C" __global__ void
 *   __global float *       -> float *          (device global memory)
 *   __global const float * -> const float *
 *   get_global_id(0)       -> blockIdx.x * blockDim.x + threadIdx.x
 *   static float f(...)     -> __device__ float f(...)
 *
 * Kernels run in float (fp32): the host converts double<->float at the
 * buffer boundary (see cuda_hsolve.cu), exactly as the OpenCL path does, so
 * a device without fp64 (or where fp64 is slow) is not penalised.
 */
#ifndef CUDA_CHANNEL_CUH
#define CUDA_CHANNEL_CUH

/* op-codes -- must match hines_defs.h and ocl_channel.cl */
#define COMPT_OP     100
#define FCOMPT_OP    101
#define LCOMPT_OP    102
#define NEWVOLT_OP   5100
#define CHAN_OP      3000
#define CHAN_EK_OP   3001
#define ADD_CURR_OP  3200
#define IPOL1V_OP    4001
#define FINISH_OP    7

/* ------------------------------------------------------------------ */
/* One channel-update step for compartment gid. Returns the new voltage;
   chip[] gate variables are updated in place. Identical maths to
   ocl_channel.cl channel_step(). */
/* ------------------------------------------------------------------ */
__device__ static float
cuda_channel_step(int gid,
                  float Vm,
                  float       *chip,
                  const float *tablist,
                  const float *xvals,
                  const int   *ops,
                  const int   *comp_opstart,
                  const int   *comp_chipstart,
                  const int   ncols,
                  const int   xdivs,
                  const float xmin,
                  const float invdx)
{
    int op_i   = comp_opstart[gid];
    int chip_i = comp_chipstart[gid];

    float sumgchan = 0.0f;
    float ichan    = chip[chip_i] + chip[chip_i + 1]; /* Em/Rm + inject */
    chip_i += 2;

    float Gk = 0.0f, Ek = 0.0f;
    int   filo  = 0;
    float vipol = 0.0f;

    int op;
    while (ops[op_i] > LCOMPT_OP) {
        op = ops[op_i++];

        if (op == NEWVOLT_OP) {
            vipol = (Vm - xmin) * invdx;
            if (vipol < 0.0f)       vipol = 0.0f;
            else if (vipol > xdivs) vipol = (float)xdivs;
            filo  = (int)vipol;
            vipol = vipol - (float)filo;
            continue;
        }

        if (op == CHAN_EK_OP) {
            Ek = chip[chip_i++];
            Gk = chip[chip_i++];
        } else if (op == CHAN_OP) {
            Gk = chip[chip_i++];
        } else if (op == ADD_CURR_OP) {
            sumgchan += Gk;
            ichan    += Ek * Gk;
            continue;
        } else if (op == IPOL1V_OP) {
            int col  = ops[op_i++];
            int base = filo * ncols + col;
            float B      = tablist[base];
            float Bn     = tablist[base + ncols];
            float B_interp = B + vipol * (Bn - B);

            float A      = tablist[base + 1];
            float An     = tablist[base + 1 + ncols];
            float A_interp = A + vipol * (An - A);

            int power = ops[op_i++];
            float X;
            if (power > 0) {
                X = chip[chip_i] = (chip[chip_i] * (2.0f - B_interp) + A_interp) / B_interp;
            } else {
                X = chip[chip_i] = A_interp / B_interp;
                power = -power;
            }
            chip_i++;

            if      (power == 1) Gk *= X;
            else if (power == 2) Gk *= X * X;
            else if (power == 3) Gk *= X * X * X;
            else if (power == 4) { X *= X; Gk *= X * X; }
            continue;
        } else {
            Gk = 0.0f;
        }
    }

    float tbyc     = chip[chip_i];
    float diagterm = chip[chip_i + 1];
    return (Vm + ichan * tbyc) / (sumgchan * tbyc + diagterm);
}

/* ------------------------------------------------------------------ */
/* chip_channel_update -- one step, writes results[] for the CPU Hines solve */
/* ------------------------------------------------------------------ */
extern "C" __global__ void
cuda_chip_channel_update(const float *vm,
                         float       *chip,
                         float       *results,
                         const float *tablist,
                         const float *xvals,
                         const int   *ops,
                         const int   *comp_opstart,
                         const int   *comp_chipstart,
                         const int   ncompts,
                         const int   ncols,
                         const int   xdivs,
                         const float xmin,
                         const float invdx)
{
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gid >= ncompts) return;

    float Vm = vm[gid];
    int op_i   = comp_opstart[gid];
    int chip_i = comp_chipstart[gid];

    float sumgchan = 0.0f;
    float ichan    = chip[chip_i] + chip[chip_i + 1];
    chip_i += 2;

    float Gk = 0.0f, Ek = 0.0f;
    int   filo  = 0;
    float vipol = 0.0f;

    int op;
    while (ops[op_i] > LCOMPT_OP) {
        op = ops[op_i++];

        if (op == NEWVOLT_OP) {
            vipol = (Vm - xmin) * invdx;
            if (vipol < 0.0f)       vipol = 0.0f;
            else if (vipol > xdivs) vipol = (float)xdivs;
            filo  = (int)vipol;
            vipol = vipol - (float)filo;
            continue;
        }

        if (op == CHAN_EK_OP) {
            Ek = chip[chip_i++];
            Gk = chip[chip_i++];
        } else if (op == CHAN_OP) {
            Gk = chip[chip_i++];
        } else if (op == ADD_CURR_OP) {
            sumgchan += Gk;
            ichan    += Ek * Gk;
            continue;
        } else if (op == IPOL1V_OP) {
            int col  = ops[op_i++];
            int base = filo * ncols + col;
            float B      = tablist[base];
            float Bn     = tablist[base + ncols];
            float B_interp = B + vipol * (Bn - B);

            float A      = tablist[base + 1];
            float An     = tablist[base + 1 + ncols];
            float A_interp = A + vipol * (An - A);

            int power = ops[op_i++];
            float X;
            if (power > 0) {
                X = chip[chip_i] = (chip[chip_i] * (2.0f - B_interp) + A_interp) / B_interp;
            } else {
                X = chip[chip_i] = A_interp / B_interp;
                power = -power;
            }
            chip_i++;

            if      (power == 1) Gk *= X;
            else if (power == 2) Gk *= X * X;
            else if (power == 3) Gk *= X * X * X;
            else if (power == 4) { X *= X; Gk *= X * X; }
            continue;
        } else {
            Gk = 0.0f;
        }
    }

    float tbyc     = chip[chip_i];
    float diagterm = chip[chip_i + 1];
    results[gid * 2]     = Vm + ichan * tbyc;
    results[gid * 2 + 1] = sumgchan * tbyc + diagterm;
}

/* ------------------------------------------------------------------ */
/* chip_channel_multiloop -- K steps in one launch (single-compartment only) */
/* Mirrors ocl_channel.cl chip_channel_multiloop: one thread per compartment,
   inner loop over nsteps, voltage updated inline, then an identity result[]
   so the CPU Hines pass is a no-op. NOT valid for multi-compartment trees. */
/* ------------------------------------------------------------------ */
extern "C" __global__ void
cuda_chip_channel_multiloop(float       *vm,
                            float       *chip,
                            float       *results,
                            const float *tablist,
                            const float *xvals,
                            const int   *ops,
                            const int   *comp_opstart,
                            const int   *comp_chipstart,
                            const int   ncompts,
                            const int   ncols,
                            const int   xdivs,
                            const float xmin,
                            const float invdx,
                            const int   nsteps)
{
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gid >= ncompts) return;

    for (int step = 0; step < nsteps; step++) {
        float Vm_new = cuda_channel_step(gid, vm[gid], chip,
                                         tablist, xvals, ops,
                                         comp_opstart, comp_chipstart,
                                         ncols, xdivs, xmin, invdx);
        vm[gid] = Vm_new;
    }

    results[gid * 2]     = vm[gid];
    results[gid * 2 + 1] = 1.0f;
}

#endif /* CUDA_CHANNEL_CUH */
