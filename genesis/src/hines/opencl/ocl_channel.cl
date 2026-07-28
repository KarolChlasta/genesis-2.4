/*
 * ocl_channel.cl
 *
 * OpenCL kernel dla obliczen kanalow jonowych hsolve chanmode 2/4.
 * Jeden work-item odpowiada jednemu kompartmentowi.
 *
 * Uproszczony model: obsluguje CHAN_OP/CHAN_EK_OP + IPOL1V_OP (bramki
 * napiecie-zalezne z interpolacja liniowa) — pokrywa >90% typowych modeli
 * (tabchannel z bramkami m,h,n).
 *
 * Operacje wymagajace globalnej synchronizacji (SPIKE_OP, synchan) sa
 * pomijane i obslugiwane przez CPU fallback w ocl_hsolve.c.
 *
 * Dwa kernele:
 *   chip_channel_update   — jeden krok, wyniki do results[] dla CPU Hines
 *   chip_channel_multiloop — K krokow w jednym dispatchu, aktualizuje vm[]
 *                            bezposrednio (eliminuje roundtrip CPU/GPU na krok)
 *
 * fp32: urzadzenie moze nie wspierac cl_khr_fp64 (np. AMD RDNA3 890M) —
 * kernel uzywa float zamiast double. Host konwertuje double<->float na
 * upload/download (patrz ocl_hsolve.c).
 */

/* op-codes — musza byc zgodne z hines_defs.h */
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
/* Wspolna funkcja obliczajaca jeden krok kanalow dla kompartmentu gid */
/* Zwraca nowe napięcie. chip[] jest modyfikowany w miejscu (bramki).  */
/* ------------------------------------------------------------------ */
static float
channel_step(int gid,
             float Vm,
             __global       float *chip,
             __global const float *tablist,
             __global const float *xvals,
             __global const int    *ops,
             __global const int    *comp_opstart,
             __global const int    *comp_chipstart,
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

    /* comp_opstart[gid] points at this compartment's first real opcode,
       skipping the entry sentinel (FCOMPT_OP/COMPT_OP) that precedes it.
       Compartment data ends at the next sentinel (COMPT_OP for any but
       the last compartment, LCOMPT_OP for the last) -- all real opcodes
       are > LCOMPT_OP, all sentinels are <= LCOMPT_OP. */
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

    /* chip[chip_i] = tbyc (dt/Cm), chip[chip_i+1] = diagterm (Hines diagonal) */
    float tbyc     = chip[chip_i];
    float diagterm = chip[chip_i + 1];

    /* Single-compartment voltage update: vm_new = rhs / denom */
    return (Vm + ichan * tbyc) / (sumgchan * tbyc + diagterm);
}

/* ------------------------------------------------------------------ */
/* chip_channel_update — jeden krok, wyniki do results[] dla CPU Hines */
/* ------------------------------------------------------------------ */
__kernel void chip_channel_update(
    __global const float *vm,          /* [ncompts] napięcia */
    __global       float *chip,        /* [nchips]  stan bramek + stale */
    __global       float *results,     /* [ncompts*2] prawy bok + diag */
    __global const float *tablist,     /* [xdivs+1][ncols] tabele bramek */
    __global const float *xvals,       /* [xdivs+2] wartosci V dla tabeli */
    __global const int    *ops,
    __global const int    *comp_opstart,
    __global const int    *comp_chipstart,
    const int   ncompts,
    const int   ncols,
    const int   xdivs,
    const float xmin,
    const float invdx
)
{
    int gid = get_global_id(0);
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
    float xlo = -1e20f, xhi = 1e20f;

    int op;
    while (ops[op_i] > LCOMPT_OP) {
        op = ops[op_i++];

        if (op == NEWVOLT_OP) {
            vipol = (Vm - xmin) * invdx;
            if (vipol < 0.0f)       vipol = 0.0f;
            else if (vipol > xdivs) vipol = (float)xdivs;
            filo  = (int)vipol;
            vipol = vipol - (float)filo;
            xlo   = xvals[filo];
            xhi   = xvals[filo + 1];
            (void)xlo; (void)xhi;
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
/* chip_channel_multiloop — K krokow w jednym dispatchu               */
/*                                                                      */
/* Jeden work-item = jeden kompartment, petla wewnetrzna = nsteps.    */
/* Eliminuje roundtrip CPU/GPU na kazdy krok: upload vm+chip raz,     */
/* kernel liczy K krokow, download vm raz.                            */
/*                                                                      */
/* UWAGA: aktualizacja napiecia vm[gid] odbywa sie bezposrednio        */
/* (rownanie dla kompartmentu jednookienkowego). Dla sieci neuronow    */
/* wielookninkowych (drzewa dendrytyczne) nie stosowac — wymagany jest */
/* solver trojdiagonalny sprzegajacy sasiednie kompartmenty.           */
/*                                                                      */
/* Po zakonczeniu wszystkich krokow zapisuje do results[] wartosci     */
/* identycznosciowe (vm_final, 1.0) tak, ze CPU solver Hinesa          */
/* liczy: vm_nowe = vm_final / 1.0 = vm_final (brak zmiany).          */
/* ------------------------------------------------------------------ */
__kernel void chip_channel_multiloop(
    __global       float *vm,          /* [ncompts] napięcia — read+write */
    __global       float *chip,        /* [nchips]  stan bramek + stale */
    __global       float *results,     /* [ncompts*2] tożsame po wykonaniu */
    __global const float *tablist,
    __global const float *xvals,
    __global const int    *ops,
    __global const int    *comp_opstart,
    __global const int    *comp_chipstart,
    const int   ncompts,
    const int   ncols,
    const int   xdivs,
    const float xmin,
    const float invdx,
    const int    nsteps
)
{
    int gid = get_global_id(0);
    if (gid >= ncompts) return;

    int step;
    for (step = 0; step < nsteps; step++) {
        float Vm_new = channel_step(gid, vm[gid], chip,
                                     tablist, xvals, ops,
                                     comp_opstart, comp_chipstart,
                                     ncols, xdivs, xmin, invdx);
        vm[gid] = Vm_new;
    }

    /* Wynik identycznosciowy dla CPU Hinesa: vm_nowe = vm_final / 1.0 */
    results[gid * 2]     = vm[gid];
    results[gid * 2 + 1] = 1.0f;
}

/* ------------------------------------------------------------------ */
/* hines_tree_eliminate — real Hines tridiagonal elimination on GPU,   */
/* one work-item per disconnected tree (neuron), replacing the         */
/* single-compartment-only shortcut in chip_channel_multiloop above.   */
/*                                                                      */
/* Line-for-line port of the CPU reference do_pertree_validate()       */
/* (hines_solve.c, GENESIS 2.5, Karol Chlasta 2026-07-25), which was    */
/* validated to exact match against do_euler_hsolve across many        */
/* linear-chain and branching topologies -- see                        */
/* GPU_HINES_SOLVE_DESIGN.md for the full derivation, the three real    */
/* bugs found and fixed getting here, and the one known narrow gap      */
/* (BRANCH_LEN=1 direct siblings off the soma, tree 0 only). Do NOT     */
/* "simplify" this without re-running that CPU-side validator against   */
/* any change -- several individually-plausible-looking shortcuts       */
/* here were tried and found wrong during that validation.              */
/*                                                                      */
/* Opcodes (must match hines_defs.h): FORWARD_ELIM=BACKWARD_ELIM=0,     */
/* SET_DIAG=1, SKIP_DIAG=2, FASTSIBARRAY_ELIM=3, COPY_ARRAY=4,          */
/* SIBARRAY_ELIM=5, CALC_RESULTS=6, FINISH=7.                           */
/*                                                                      */
/* funcs[]/ravals[]/results[] are SHARED, flat buffers covering the     */
/* whole hsolve (all trees) -- each work-item touches only its own      */
/* tree's disjoint sub-ranges (funcs[]/ravals[] via the fwd_/bwd_       */
/* *_start/_end bounds; results[]/vm[] via absolute row indices that,   */
/* by construction, never cross into another tree's rows), so this is   */
/* race-free without any synchronization between work-items.            */
/* ------------------------------------------------------------------ */
__kernel void hines_tree_eliminate(
    __global const int   *funcs,          /* [nfuncs] shared opcode program */
    __global       float *ravals,         /* [nravals] shared; COPY_ARRAY/FASTSIBARRAY_ELIM mutate it in place */
    __global       float *results,        /* [ncompts*2] shared RHS/diag, read+written */
    __global       float *vm,             /* [ncompts] output */
    __global const int   *fwd_seg_start,  /* [n_trees] */
    __global const int   *fwd_seg_end,    /* [n_trees] */
    __global const int   *bwd_seg_start,  /* [n_trees] */
    __global const int   *bwd_seg_end,    /* [n_trees] */
    __global const int   *fwd_root_row,   /* [n_trees] */
    __global const int   *fwd_raval_start,/* [n_trees] */
    __global const int   *bwd_raval_start,/* [n_trees] */
    const int   n_trees
)
{
    int k = get_global_id(0);
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
           upstream -- nothing safe to do per-work-item, just stop */
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
