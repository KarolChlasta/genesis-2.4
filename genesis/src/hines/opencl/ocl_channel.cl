#pragma OPENCL EXTENSION cl_khr_fp64 : enable

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
static double
channel_step(int gid,
             double Vm,
             __global       double *chip,
             __global const double *tablist,
             __global const double *xvals,
             __global const int    *ops,
             __global const int    *comp_opstart,
             __global const int    *comp_chipstart,
             const int   ncols,
             const int   xdivs,
             const double xmin,
             const double invdx)
{
    int op_i   = comp_opstart[gid];
    int chip_i = comp_chipstart[gid];

    double sumgchan = 0.0;
    double ichan    = chip[chip_i] + chip[chip_i + 1]; /* Em/Rm + inject */
    chip_i += 2;

    double Gk = 0.0, Ek = 0.0;

    int    filo = 0;
    double vipol = 0.0;

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
            if (vipol < 0.0)        vipol = 0.0;
            else if (vipol > xdivs) vipol = (double)xdivs;
            filo  = (int)vipol;
            vipol = vipol - (double)filo;
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
            double B      = tablist[base];
            double Bn     = tablist[base + ncols];
            double B_interp = B + vipol * (Bn - B);

            double A      = tablist[base + 1];
            double An     = tablist[base + 1 + ncols];
            double A_interp = A + vipol * (An - A);

            int power = ops[op_i++];
            double X;
            if (power > 0) {
                X = chip[chip_i] = (chip[chip_i] * (2.0 - B_interp) + A_interp) / B_interp;
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
            Gk = 0.0;
        }
    }

    /* chip[chip_i] = tbyc (dt/Cm), chip[chip_i+1] = diagterm (Hines diagonal) */
    double tbyc     = chip[chip_i];
    double diagterm = chip[chip_i + 1];

    /* Single-compartment voltage update: vm_new = rhs / denom */
    return (Vm + ichan * tbyc) / (sumgchan * tbyc + diagterm);
}

/* ------------------------------------------------------------------ */
/* chip_channel_update — jeden krok, wyniki do results[] dla CPU Hines */
/* ------------------------------------------------------------------ */
__kernel void chip_channel_update(
    __global const double *vm,          /* [ncompts] napięcia */
    __global       double *chip,        /* [nchips]  stan bramek + stale */
    __global       double *results,     /* [ncompts*2] prawy bok + diag */
    __global const double *tablist,     /* [xdivs+1][ncols] tabele bramek */
    __global const double *xvals,       /* [xdivs+2] wartosci V dla tabeli */
    __global const int    *ops,
    __global const int    *comp_opstart,
    __global const int    *comp_chipstart,
    const int   ncompts,
    const int   ncols,
    const int   xdivs,
    const double xmin,
    const double invdx
)
{
    int gid = get_global_id(0);
    if (gid >= ncompts) return;

    double Vm = vm[gid];
    int op_i   = comp_opstart[gid];
    int chip_i = comp_chipstart[gid];

    double sumgchan = 0.0;
    double ichan    = chip[chip_i] + chip[chip_i + 1];
    chip_i += 2;

    double Gk = 0.0, Ek = 0.0;
    int    filo  = 0;
    double vipol = 0.0;
    double xlo = -1e20, xhi = 1e20;

    int op;
    while (ops[op_i] > LCOMPT_OP) {
        op = ops[op_i++];

        if (op == NEWVOLT_OP) {
            vipol = (Vm - xmin) * invdx;
            if (vipol < 0.0)        vipol = 0.0;
            else if (vipol > xdivs) vipol = (double)xdivs;
            filo  = (int)vipol;
            vipol = vipol - (double)filo;
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
            double B      = tablist[base];
            double Bn     = tablist[base + ncols];
            double B_interp = B + vipol * (Bn - B);

            double A      = tablist[base + 1];
            double An     = tablist[base + 1 + ncols];
            double A_interp = A + vipol * (An - A);

            int power = ops[op_i++];
            double X;
            if (power > 0) {
                X = chip[chip_i] = (chip[chip_i] * (2.0 - B_interp) + A_interp) / B_interp;
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
            Gk = 0.0;
        }
    }

    double tbyc     = chip[chip_i];
    double diagterm = chip[chip_i + 1];
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
    __global       double *vm,          /* [ncompts] napięcia — read+write */
    __global       double *chip,        /* [nchips]  stan bramek + stale */
    __global       double *results,     /* [ncompts*2] tożsame po wykonaniu */
    __global const double *tablist,
    __global const double *xvals,
    __global const int    *ops,
    __global const int    *comp_opstart,
    __global const int    *comp_chipstart,
    const int   ncompts,
    const int   ncols,
    const int   xdivs,
    const double xmin,
    const double invdx,
    const int    nsteps
)
{
    int gid = get_global_id(0);
    if (gid >= ncompts) return;

    int step;
    for (step = 0; step < nsteps; step++) {
        double Vm_new = channel_step(gid, vm[gid], chip,
                                     tablist, xvals, ops,
                                     comp_opstart, comp_chipstart,
                                     ncols, xdivs, xmin, invdx);
        vm[gid] = Vm_new;
    }

    /* Wynik identycznosciowy dla CPU Hinesa: vm_nowe = vm_final / 1.0 */
    results[gid * 2]     = vm[gid];
    results[gid * 2 + 1] = 1.0;
}
