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
 */

/* op-codes — musza byc zgodne z hines_defs.h */
#define LCOMPT_OP    102
#define NEWVOLT_OP   5100
#define CHAN_OP      3000
#define CHAN_EK_OP   3001
#define ADD_CURR_OP  3200
#define IPOL1V_OP    4001
#define FINISH_OP    7

__kernel void chip_channel_update(
    __global const double *vm,          /* [ncompts] napięcia */
    __global       double *chip,        /* [nchips]  stan bramek + stale */
    __global       double *results,     /* [ncompts*2] prawy bok + diag */
    __global const double *tablist,     /* [xdivs+1][ncols] tabele bramek */
    __global const double *xvals,       /* [xdivs+2] wartosci V dla tabeli */
    __global const int    *ops,         /* tablica operacji */
    __global const int    *comp_opstart,/* [ncompts] indeks startowy w ops[] */
    __global const int    *comp_chipstart,/* [ncompts] indeks startowy w chip[] */
    const int   ncols,
    const int   xdivs,
    const double xmin,
    const double invdx
)
{
    int gid = get_global_id(0);

    double Vm       = vm[gid];
    int    op_i     = comp_opstart[gid];
    int    chip_i   = comp_chipstart[gid];

    double sumgchan = 0.0;
    double ichan    = chip[chip_i] + chip[chip_i + 1]; /* Em/Rm + inject */
    chip_i += 2;

    double Gk = 0.0, Ek = 0.0;

    /* indeks w tabeli napiecia */
    int    filo = 0;
    double vipol = 0.0;
    double xlo = -1e20, xhi = 1e20;

    int op;
    while ((op = ops[op_i++]) != LCOMPT_OP) {

        if (op == NEWVOLT_OP) {
            vipol = (Vm - xmin) * invdx;
            if (vipol < 0.0)       vipol = 0.0;
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
            /* fall through do CHAN_OP */
            Gk = chip[chip_i++];
        } else if (op == CHAN_OP) {
            Gk = chip[chip_i++];
        } else if (op == ADD_CURR_OP) {
            sumgchan += Gk;
            ichan    += Ek * Gk;
            continue;
        } else if (op == IPOL1V_OP) {
            /* interpolacja liniowa bramki z 1D tabeli */
            int col = ops[op_i++];
            int base = filo * ncols + col;
            double B = tablist[base];
            double Bn= tablist[base + ncols];
            double B_interp = B + vipol * (Bn - B);

            double A = tablist[base + 1];
            double An= tablist[base + 1 + ncols];
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

            /* Gk *= X^power */
            if      (power == 1) Gk *= X;
            else if (power == 2) Gk *= X * X;
            else if (power == 3) Gk *= X * X * X;
            else if (power == 4) { X *= X; Gk *= X * X; }
            continue;
        } else {
            /* nieobslugiwany op — sygnalizuj przez wyzerowanie Gk */
            Gk = 0.0;
        }
    }

    /* zapisz wyniki dla tego kompartmentu */
    /* chip[chip_i] = tbyc, chip[chip_i+1] = diagterm */
    double tbyc     = chip[chip_i];
    double diagterm = chip[chip_i + 1];
    results[gid * 2]     = Vm + ichan * tbyc;
    results[gid * 2 + 1] = sumgchan * tbyc + diagterm;
}
