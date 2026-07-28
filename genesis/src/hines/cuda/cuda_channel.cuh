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

/* ------------------------------------------------------------------ */
/* cuda_hines_tree_eliminate -- real Hines tridiagonal elimination,    */
/* one thread per disconnected tree (neuron). CUDA port of             */
/* opencl/ocl_channel.cl's hines_tree_eliminate -- itself a line-for-  */
/* line port of the CPU reference do_pertree_validate() (hines_solve.c,*/
/* GENESIS 2.5, Karol Chlasta 2026-07-25), validated (0 mismatches)    */
/* against the CPU solver across linear-chain and branching topologies,*/
/* and separately re-validated on GPU (this OpenCL kernel, on UMCS     */
/* cluster inf02/A40) the same day -- see GPU_HINES_SOLVE_DESIGN.md    */
/* for the full derivation, the three bugs found and fixed getting     */
/* here, and the one known narrow gap (BRANCH_LEN=1 direct siblings    */
/* off the soma, tree 0 only). Do NOT "simplify" this without re-      */
/* running that CPU-side validator against any change.                 */
/*                                                                      */
/* Opcodes (must match hines_defs.h): FORWARD_ELIM=BACKWARD_ELIM=0,     */
/* SET_DIAG=1, SKIP_DIAG=2, FASTSIBARRAY_ELIM=3, COPY_ARRAY=4,          */
/* SIBARRAY_ELIM=5, CALC_RESULTS=6, FINISH=7.                           */
/*                                                                      */
/* funcs[]/ravals[]/results[] are SHARED, flat buffers covering the     */
/* whole hsolve (all trees) -- each thread touches only its own tree's  */
/* disjoint sub-ranges (funcs[]/ravals[] via the fwd_/bwd_ *_start/_end */
/* bounds; results[]/vm[] via absolute row indices that, by             */
/* construction, never cross into another tree's rows), so this is      */
/* race-free without any synchronization between threads.               */
/* ------------------------------------------------------------------ */
extern "C" __global__ void
cuda_hines_tree_eliminate(
    const int   *funcs,          /* [nfuncs] shared opcode program */
    float       *ravals,         /* [nravals] shared; COPY_ARRAY/FASTSIBARRAY_ELIM mutate it in place */
    float       *results,        /* [ncompts*2] shared RHS/diag, read+written */
    float       *vm,             /* [ncompts] output */
    const int   *fwd_seg_start,  /* [n_trees] */
    const int   *fwd_seg_end,    /* [n_trees] */
    const int   *bwd_seg_start,  /* [n_trees] */
    const int   *bwd_seg_end,    /* [n_trees] */
    const int   *fwd_root_row,   /* [n_trees] */
    const int   *fwd_raval_start,/* [n_trees] */
    const int   *bwd_raval_start,/* [n_trees] */
    const int   n_trees
)
{
    int k = blockIdx.x * blockDim.x + threadIdx.x;
    if (k >= n_trees) return;

    int   funcs_i   = fwd_seg_start[k];
    int   ravals_i  = fwd_raval_start[k];
    int   root_row  = fwd_root_row[k];
    int   first_row = (k == 0) ? 0 : fwd_root_row[k-1] + 1;
    int   fwd_end   = fwd_seg_end[k];
    int   seed_row, resultvalue_i, op;
    float resultval, diaval, temp = 0.0f;

    /* Bootstrap: skip the leading transition opcode (its flush target
       belongs to the PREVIOUS tree -- a cross-tree data race for a
       parallel kernel; the root-solve write-back below already
       supplies what that flush would have persisted). */
    op = funcs[funcs_i];
    if (op == 1 /* SET_DIAG */) {
        seed_row = first_row;
        funcs_i++;
    } else if (op == 2 /* SKIP_DIAG */) {
        seed_row = first_row + 1;
        funcs_i++;
    } else if (k == 0 && op == 0 /* FORWARD_ELIM */) {
        seed_row = 1;
    } else {
        /* Unhandled leading opcode -- known narrow gap (see comment
           above). Leave this tree untouched rather than compute
           something silently wrong. */
        return;
    }
    resultvalue_i = 2 * seed_row;
    resultval = results[resultvalue_i];
    diaval    = results[resultvalue_i + 1];

    /* Forward pass: process every opcode belonging to this tree.
       SET_DIAG/SKIP_DIAG recur once per "un-fused" row transition
       WITHIN the tree (not just at the start) and are executed
       normally here -- their flush target is always within this
       tree's own row range, safe. */
    while (funcs_i < fwd_end) {
        op = funcs[funcs_i++];
        if (op == 0 /* FORWARD_ELIM */) {
            int operand = funcs[funcs_i++];
            temp = ravals[ravals_i++] / results[operand + 1];
            diaval -= ravals[ravals_i++] * temp;
            resultval -= results[operand] * temp;
        } else if (op == 1 /* SET_DIAG */) {
            results[resultvalue_i]     = resultval;
            results[resultvalue_i + 1] = diaval;
            resultvalue_i += 2;
            resultval = results[resultvalue_i];
            diaval    = results[resultvalue_i + 1];
        } else if (op == 2 /* SKIP_DIAG */) {
            results[resultvalue_i]     = resultval;
            results[resultvalue_i + 1] = diaval;
            resultvalue_i += 4;
            resultval = results[resultvalue_i];
            diaval    = results[resultvalue_i + 1];
        } else if (op == 3 /* FASTSIBARRAY_ELIM */) {
            int operand = funcs[funcs_i++];
            ravals[operand] -= ravals[ravals_i++] * temp;
        } else if (op == 4 /* COPY_ARRAY */) {
            int operand = funcs[funcs_i++];
            ravals[operand] = ravals[ravals_i++];
        } else if (op == 5 /* SIBARRAY_ELIM */) {
            int op1 = funcs[funcs_i];
            int op2 = funcs[funcs_i + 1];
            ravals[op2] -= ravals[op1] * temp;
            funcs_i += 2;
        }
        /* any other token would mean fwd_seg_end was computed wrong
           upstream -- nothing safe to do per-thread, just stop */
        else {
            break;
        }
    }

    /* Root solve: uniform for every tree, regardless of whether the
       single-threaded CPU code happened to handle this particular
       tree via the forward pass's "last row" special case or the
       backward pass's CALC_RESULTS. */
    resultval = resultval / diaval;
    results[2 * root_row] = resultval;
    vm[root_row] = resultval;

    /* Backward pass: this tree's own rows strictly below its root, if
       any (may be empty, e.g. any single-compartment tree). */
    if (bwd_seg_end[k] > bwd_seg_start[k]) {
        int   bfuncs_i        = bwd_seg_start[k];
        int   bravals_i       = bwd_raval_start[k];
        int   bend            = bwd_seg_end[k];
        int   bresultvalue_i  = 2 * (root_row - 1);
        float bresultval      = results[bresultvalue_i];
        int   brow, bop;

        while (bfuncs_i < bend) {
            bop = funcs[bfuncs_i++];
            if (bop == 0 /* BACKWARD_ELIM, aliased to FORWARD_ELIM=0 */) {
                int operand = funcs[bfuncs_i++];
                bresultval -= ravals[bravals_i++] * results[operand];
            } else if (bop == 6 /* CALC_RESULTS */) {
                brow = bresultvalue_i / 2;
                bresultval = bresultval / results[bresultvalue_i + 1];
                results[bresultvalue_i] = bresultval;
                vm[brow] = bresultval;
                bresultvalue_i -= 2;
                bresultval = results[bresultvalue_i];
            } else if (bop == 5 /* SIBARRAY_ELIM */) {
                int op1 = funcs[bfuncs_i];
                int op2 = funcs[bfuncs_i + 1];
                bresultval -= ravals[op1] * results[op2];
                bfuncs_i += 2;
            } else {
                break;
            }
        }
    }
}
