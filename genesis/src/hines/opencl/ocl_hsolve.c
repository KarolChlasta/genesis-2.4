/*
 * ocl_hsolve.c — integracja OpenCL z hsolve GENESIS 2.4
 *
 * Zastepuje do_chip_hh4_update() dla chanmode 2-4.
 * Przy pierwszym wywolaniu inicjalizuje GPU, kompiluje kernel,
 * alokuje bufory. Kazdy krok: upload vm+chip -> kernel -> download results.
 */

#ifdef USE_OPENCL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CL/cl.h>
#include "../hines_ext.h"
#include "../hines_defs.h"
#include "ocl_hsolve.h"

/* Device-level resources, created once per process and shared by every hsolve.
   Kept separate from the per-hsolve buffers below so that the one-solver-per-cell
   idiom (`call solver DUPLICATE`) can share a single context. */
OclDeviceState ocl_dev = {0};



/* Registry of live per-hsolve states: ocl_cleanup() is an atexit hook and
   receives no Hsolve, but the buffers are now owned per solver. */
typedef struct ocl_state_node {
    OclHsolveState *st;
    struct ocl_state_node *next;
} OclStateNode;

static OclStateNode *ocl_states = NULL;
static int ocl_atexit_registered = 0;
/* Process-wide "do not retry" flag. Mirrors cuda_disabled: it records that
   the platform cannot drive the GPU, and before ocl_init has run there is
   no per-hsolve state to hang it on. */
static int ocl_disabled = 0;

static void ocl_state_register(OclHsolveState *st)
{
    OclStateNode *n = (OclStateNode *)malloc(sizeof(OclStateNode));
    if (!n) return;
    n->st = st; n->next = ocl_states; ocl_states = n;
}

/* Wczytuje plik .cl jako string */
static char *load_kernel_source(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    char *src = (char *)malloc(sz + 1);
    fread(src, 1, sz, f);
    src[sz] = '\0';
    fclose(f);
    return src;
}

/* Konwersja double<->float na granicy host/GPU (kernel pracuje w fp32). */
static void d2f(const double *src, float *dst, int n)
{
    int i;
    for (i = 0; i < n; i++) dst[i] = (float)src[i];
}
static void f2d(const float *src, double *dst, int n)
{
    int i;
    for (i = 0; i < n; i++) dst[i] = (double)src[i];
}

/*
 * build_comp_index — buduje tablice indeksow per-kompartment
 *
 * ops[] i chip[] sa plaskimi tablicami bez separatorow — kazdy kompartment
 * ma inny offset. Ta funkcja przechodzi przez ops[] i liczy gdzie zaczyna
 * sie kazdy kompartment, zapisujac wynik w comp_opstart[] i comp_chipstart[].
 *
 * Przy okazji wykrywa operacje nieobslugiwane przez GPU (SPIKE_OP, synchan,
 * GHK, koncentracje) i oznacza takie kompartmenty w cpu_only[].
 */
static void build_comp_index(Hsolve *hsolve,
                              int **out_opstart,
                              int **out_chipstart,
                              int **out_cpu_only)
{
    int n = hsolve->ncompts;
    int *opstart   = (int *)malloc(n * sizeof(int));
    int *chipstart = (int *)malloc(n * sizeof(int));
    int *cpu_only  = (int *)calloc(n, sizeof(int));
    int c;
    /* ops[0] holds FCOMPT_OP (101), a sentinel marking the start of
       compartment 0. Every compartment's real ops are followed by another
       sentinel -- COMPT_OP (100) for all but the last compartment,
       LCOMPT_OP (102) for the last -- which simultaneously marks the start
       of the next compartment. Sentinels carry no operands and satisfy
       value <= LCOMPT_OP, while every real opcode is > LCOMPT_OP; this is
       exactly how the CPU interpreter in hines_chip.c tells them apart
       (peek, not equality-with-102). Checking only `!= LCOMPT_OP` here
       swallowed the 100/101 sentinels as ordinary ops and merged many
       compartments' data together -- the root cause of the GPU page fault. */
    int op_i = 1, chip_i = 0;

    for (c = 0; c < n; c++) {
        opstart[c]   = op_i;
        chipstart[c] = chip_i;
        chip_i += 2; /* Em/Rm + inject */

        while (hsolve->ops[op_i] > LCOMPT_OP) {
            int op = hsolve->ops[op_i++];
            switch (op) {
                case NEWVOLT_OP:                          break;
                case CHAN_EK_OP: chip_i++;                /* fall through */
                case CHAN_OP:    chip_i++;                break;
                case ADD_CURR_OP:                         break;
                case IPOL1V_OP:  op_i += 2; chip_i++;    break;
                case SPIKE_OP:   op_i += 2; chip_i++;
                    cpu_only[c] = 1;                      break;
                default:
                    cpu_only[c] = 1;                      break;
            }
        }
        chip_i += 2; /* tbyc + diagterm */
        op_i++; /* consume the sentinel separating this compartment from the next */
    }

    *out_opstart   = opstart;
    *out_chipstart = chipstart;
    *out_cpu_only  = cpu_only;
}


/* A compartment that is simultaneously a leaf and has siblings -- i.e. a branch
   exactly one compartment long hanging off a branch point -- is not handled by
   the tree-elimination kernel. GPU_HINES_SOLVE_DESIGN.md isolates the fault to
   the leading-FORWARD_ELIM bootstrap's seed-row assumption, which does not hold
   when row 0/1 is itself a leaf-with-siblings; the failure was only ever
   observed in the first tree, and trees beyond it pass with the identical
   shape.
   
   We refuse it in every tree regardless. Deciding which rows belong to the
   first tree is one more thing the guard could get subtly wrong, and the shape
   does not occur in real dendrite models -- a branch that extends no further is
   an odd way of modelling the soma -- so declining it everywhere costs nothing
   in practice and cannot be got wrong.
   
   Until this commit the case was documented but not enforced: the kernels
   carried a comment about it and do_pertree_validate detected it, but only
   under the opt-in GENESIS_VALIDATE_PERTREE comparison. An ordinary run
   dispatched such a model and produced silently wrong voltages. */
static int ocl_has_degenerate_branch(Hsolve *hsolve)
{
    int i, p;
    if (!hsolve->parents || !hsolve->nkids) return 0;
    for (i = 0; i < hsolve->ncompts; i++) {
        p = hsolve->parents[i];
        if (hsolve->nkids[i] == 0 && p >= 0 && hsolve->nkids[p] > 1)
            return 1;
    }
    return 0;
}

/*
 * ocl_init — inicjalizacja OpenCL, wywolywana raz przy pierwszym kroku
 *
 * 1. Wykrywa platforme i urzadzenie (GPU AMD, fallback CPU)
 * 2. Kompiluje ocl_channel.cl
 * 3. Alokuje bufory GPU
 * 4. Buduje indeksy per-kompartment i uploaduje dane statyczne
 * 5. Ustawia argumenty kernela
 */
int ocl_init(Hsolve *hsolve)
{
    OclHsolveState *st;
    cl_int err;
    cl_platform_id platform;

    /* Allocated here and published on the solver only after a fully successful
       init, so every failure path below simply frees it and leaves
       hsolve->accel_state NULL. */
    st = (OclHsolveState *)calloc(1, sizeof(OclHsolveState));
    if (!st) return -1;

    /* ocl_init runs once per hsolve now, and the one-solver-per-cell idiom
       creates thousands of them; atexit() only guarantees 32 registrations. */
    if (!ocl_atexit_registered) {
        atexit(ocl_cleanup);
        ocl_atexit_registered = 1;
    }

    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: brak platformy OpenCL (%d)\n", err);
        free(st); return -1;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1,
                         &ocl_dev.device, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: brak GPU, probuje CPU\n");
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1,
                             &ocl_dev.device, NULL);
        if (err != CL_SUCCESS) {
            fprintf(stderr, "OCL: brak urzadzenia (%d)\n", err);
            free(st); return -1;
        }
    }

    char devname[128];
    clGetDeviceInfo(ocl_dev.device, CL_DEVICE_NAME,
                    sizeof(devname), devname, NULL);
    printf("OCL: urzadzenie: %s\n", devname);

    /* Kernel runs in fp32 (see ocl_channel.cl) — no cl_khr_fp64 requirement,
       so devices without double-precision support (e.g. AMD RDNA3 890M)
       are no longer excluded here. */

    ocl_dev.context = clCreateContext(NULL, 1, &ocl_dev.device,
                                        NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateContext (%d)\n", err);
        free(st); return -1;
    }

    cl_queue_properties qprops[] = {
        CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0
    };
    ocl_dev.queue = clCreateCommandQueueWithProperties(
                          ocl_dev.context, ocl_dev.device, qprops, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateCommandQueue (%d)\n", err);
        free(st); return -1;
    }

    /* szukamy pliku .cl w kilku miejscach */
    {
    const char *cl_paths[] = {
        "opencl/ocl_channel.cl",
        "genesis/src/hines/opencl/ocl_channel.cl",
        "/datadisk/od-kchlasta/5.Dev/GitHub/genesis-2.4/genesis/src/hines/opencl/ocl_channel.cl",
        NULL
    };
    int i;
    char *src = NULL;
    for (i = 0; cl_paths[i]; i++) {
        src = load_kernel_source(cl_paths[i]);
        if (src) break;
    }
    if (!src) {
        fprintf(stderr, "OCL: nie znaleziono ocl_channel.cl\n");
        free(st); return -1;
    }

    ocl_dev.program = clCreateProgramWithSource(ocl_dev.context, 1,
                            (const char **)&src, NULL, &err);
    free(src);
    } /* end cl_paths block */
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateProgram (%d)\n", err);
        free(st); return -1;
    }

    /* -cl-fast-relaxed-math: szybsze obliczenia zmiennoprzecinkowe na GPU */
    err = clBuildProgram(ocl_dev.program, 1, &ocl_dev.device,
                         "-cl-fast-relaxed-math", NULL, NULL);
    if (err != CL_SUCCESS) {
        char log[4096];
        clGetProgramBuildInfo(ocl_dev.program, ocl_dev.device,
                              CL_PROGRAM_BUILD_LOG, sizeof(log), log, NULL);
        fprintf(stderr, "OCL: blad kompilacji:\n%s\n", log);
        free(st); return -1;
    }

    ocl_dev.kernel = clCreateKernel(ocl_dev.program,
                                      "chip_channel_update", &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateKernel (%d)\n", err);
        free(st); return -1;
    }

    /* alokacja buforow GPU — wszystkie zmienne deklarowane na poczatku bloku (C89) */
    {
    int n   = hsolve->ncompts;
    int nc  = hsolve->nchips;
    int no  = hsolve->nops;
    /* +2 rows: one for [xdivs] row itself, one extra guard for interpolation
       (kernel reads tablist[base + ncols] which needs xdivs+1 rows minimum) */
    int nt  = (hsolve->xdivs > 0 && hsolve->ncols > 0)
              ? (hsolve->xdivs + 2) * hsolve->ncols : 1;
    int nx  = (hsolve->xdivs > 0) ? hsolve->xdivs + 2 : 1;
    int ns  = hsolve->sntab * 6;
    int ncols = hsolve->ncols;
    int xdivs = hsolve->xdivs;
    float fxmin  = (float)hsolve->xmin;
    float finvdx = (float)hsolve->invdx;
    int *opstart, *chipstart, *cpu_only;
    int unsup, ci;
    cl_mem buf_opstart, buf_chipstart;
    /* dummy tablica gdy brak tabeli — kernel nie bedzie jej uzywac */
    float dummy = 0.0f;
    float *fconv;

    if (n <= 0 || nc <= 0 || no <= 0) {
        fprintf(stderr, "OCL: hsolve nie zainicjalizowany (n=%d nc=%d no=%d)\n",
                n, nc, no);
        free(st); return -1;
    }

    if (ocl_has_degenerate_branch(hsolve)) {
        fprintf(stderr,
            "OCL: this hsolve contains a single-compartment branch off a "
            "branch point, which the tree-elimination kernel does not handle; "
            "acceleration disabled for this hsolve, computing on CPU.\n");
        free(st);
        return -1;
    }

    /* Indeksy budujemy PRZED alokacja buforow, bo cpu_only[] decyduje o tym,
       czy w ogole wolno uzyc GPU dla tego hsolve — odmowa na tym etapie nie
       zostawia zadnych zasobow do zwolnienia.

       build_comp_index() oznacza kompartmenty uzywajace operacji spoza
       zestawu kernela (SPIKE_OP, synchan, GHK, koncentracje). Kernel tych
       opkodow nie zna i — co gorsza — nie przeskakuje ich operandow: od
       pierwszego takiego opkodu strumien ops[] rozjezdza sie, kolejne
       odczyty chipow trafiaja w zle indeksy i wynik jest cicho bledny
       (Vm rozbiega sie juz w kroku 0, bez zadnego komunikatu).

       Maska byla dotad liczona i zwalniana bez uzycia, przez co ten blad
       byl niewidoczny dla wszystkich modeli walidacyjnych — zadny z nich
       nie uzywa synaps ani spike'ow. Dopoki kernel nie obsluguje tych
       opkodow, calosc hsolve liczymy na CPU. */
    build_comp_index(hsolve, &opstart, &chipstart, &cpu_only);
    unsup = 0;
    for (ci = 0; ci < n; ci++)
        if (cpu_only[ci]) unsup++;
    if (unsup > 0) {
        fprintf(stderr,
            "OCL: %d z %d kompartmentow uzywa operacji nieobslugiwanych przez "
            "kernel (SPIKE_OP/synchan/GHK/koncentracje); akceleracja wylaczona "
            "dla tego hsolve, obliczenia na CPU.\n", unsup, n);
        free(cpu_only);
        free(chipstart);
        free(opstart);
        free(st); return -1;
    }

    /* buf_vm is READ_WRITE: chip_channel_update reads it, chip_channel_multiloop
       reads AND writes it (voltage update inline each step). */
    st->buf_vm      = clCreateBuffer(ocl_dev.context,
                                CL_MEM_READ_WRITE, n*sizeof(float),  NULL, &err);
    st->buf_chip    = clCreateBuffer(ocl_dev.context,
                                CL_MEM_READ_WRITE, nc*sizeof(float), NULL, &err);
    st->buf_results = clCreateBuffer(ocl_dev.context,
                                CL_MEM_WRITE_ONLY, n*2*sizeof(float),NULL, &err);
    st->buf_tablist = clCreateBuffer(ocl_dev.context,
                                CL_MEM_READ_ONLY,  nt*sizeof(float), NULL, &err);
    st->buf_xvals   = clCreateBuffer(ocl_dev.context,
                                CL_MEM_READ_ONLY,  nx*sizeof(float), NULL, &err);
    st->buf_ops     = clCreateBuffer(ocl_dev.context,
                                CL_MEM_READ_ONLY,  no*sizeof(int),    NULL, &err);
    if (ns > 0)
        st->buf_stablist = clCreateBuffer(ocl_dev.context,
                                     CL_MEM_READ_ONLY, ns*sizeof(float), NULL, &err);

    /* host-side float scratch reused every step (ocl_chip_update / multiloop) */
    st->f_vm      = (float *)malloc(n*sizeof(float));
    st->f_chip    = (float *)malloc(nc*sizeof(float));
    st->f_results = (float *)malloc(n*2*sizeof(float));

    /* indeksy zbudowane wyzej (przed alokacja buforow); tu tylko upload —
       dane statyczne, wysylane tylko raz */
    buf_opstart = clCreateBuffer(ocl_dev.context,
                      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                      n*sizeof(int), opstart, &err);
    buf_chipstart = clCreateBuffer(ocl_dev.context,
                        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                        n*sizeof(int), chipstart, &err);
    free(cpu_only);
    free(chipstart);
    free(opstart);

    /* upload tabel — konwersja double->float, uzyj dummy jesli brak tabchannels */
    fconv = (float *)malloc((nt > nx ? nt : nx) * sizeof(float));
    if (hsolve->tablist && hsolve->xdivs > 0) {
        d2f(hsolve->tablist, fconv, nt);
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_tablist, CL_TRUE, 0,
            nt*sizeof(float), fconv, 0, NULL, NULL);
    } else {
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_tablist, CL_TRUE, 0,
            sizeof(float), &dummy, 0, NULL, NULL);
    }
    if (hsolve->xvals && hsolve->xdivs > 0) {
        d2f(hsolve->xvals, fconv, nx);
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_xvals, CL_TRUE, 0,
            nx*sizeof(float), fconv, 0, NULL, NULL);
    } else {
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_xvals, CL_TRUE, 0,
            sizeof(float), &dummy, 0, NULL, NULL);
    }
    free(fconv);
    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_ops, CL_TRUE,
                         0, no*sizeof(int), hsolve->ops, 0, NULL, NULL);
    if (ns > 0 && hsolve->stablist) {
        float *sconv = (float *)malloc(ns * sizeof(float));
        d2f(hsolve->stablist, sconv, ns);
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_stablist, CL_TRUE,
                             0, ns*sizeof(float), sconv, 0, NULL, NULL);
        free(sconv);
    }

    /* argumenty kernela — stale przez caly czas zycia */
    clSetKernelArg(ocl_dev.kernel,  0, sizeof(cl_mem), &st->buf_vm);
    clSetKernelArg(ocl_dev.kernel,  1, sizeof(cl_mem), &st->buf_chip);
    clSetKernelArg(ocl_dev.kernel,  2, sizeof(cl_mem), &st->buf_results);
    clSetKernelArg(ocl_dev.kernel,  3, sizeof(cl_mem), &st->buf_tablist);
    clSetKernelArg(ocl_dev.kernel,  4, sizeof(cl_mem), &st->buf_xvals);
    clSetKernelArg(ocl_dev.kernel,  5, sizeof(cl_mem), &st->buf_ops);
    clSetKernelArg(ocl_dev.kernel,  6, sizeof(cl_mem), &buf_opstart);
    clSetKernelArg(ocl_dev.kernel,  7, sizeof(cl_mem), &buf_chipstart);
    clSetKernelArg(ocl_dev.kernel,  8, sizeof(int),    &n);
    clSetKernelArg(ocl_dev.kernel,  9, sizeof(int),    &ncols);
    clSetKernelArg(ocl_dev.kernel, 10, sizeof(int),    &xdivs);
    clSetKernelArg(ocl_dev.kernel, 11, sizeof(float),  &fxmin);
    clSetKernelArg(ocl_dev.kernel, 12, sizeof(float),  &finvdx);

    /* --- multiloop kernel --- */
    ocl_dev.kernel_multi = clCreateKernel(ocl_dev.program,
                                            "chip_channel_multiloop", &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateKernel multiloop (%d)\n", err);
        free(st); return -1;
    }
    {
    /* args 0-12 identical to chip_channel_update, arg 13 = nsteps (set per-call) */
    int zero = 0;
    clSetKernelArg(ocl_dev.kernel_multi,  0, sizeof(cl_mem), &st->buf_vm);
    clSetKernelArg(ocl_dev.kernel_multi,  1, sizeof(cl_mem), &st->buf_chip);
    clSetKernelArg(ocl_dev.kernel_multi,  2, sizeof(cl_mem), &st->buf_results);
    clSetKernelArg(ocl_dev.kernel_multi,  3, sizeof(cl_mem), &st->buf_tablist);
    clSetKernelArg(ocl_dev.kernel_multi,  4, sizeof(cl_mem), &st->buf_xvals);
    clSetKernelArg(ocl_dev.kernel_multi,  5, sizeof(cl_mem), &st->buf_ops);
    clSetKernelArg(ocl_dev.kernel_multi,  6, sizeof(cl_mem), &buf_opstart);
    clSetKernelArg(ocl_dev.kernel_multi,  7, sizeof(cl_mem), &buf_chipstart);
    clSetKernelArg(ocl_dev.kernel_multi,  8, sizeof(int),    &n);
    clSetKernelArg(ocl_dev.kernel_multi,  9, sizeof(int),    &ncols);
    clSetKernelArg(ocl_dev.kernel_multi, 10, sizeof(int),    &xdivs);
    clSetKernelArg(ocl_dev.kernel_multi, 11, sizeof(float),  &fxmin);
    clSetKernelArg(ocl_dev.kernel_multi, 12, sizeof(float),  &finvdx);
    clSetKernelArg(ocl_dev.kernel_multi, 13, sizeof(int),    &zero); /* nsteps placeholder */
    }

    /* Multiloop mode: GENESIS_OCL_MULTILOOP=<nsteps> enables batching */
    {
        const char *env = getenv("GENESIS_OCL_MULTILOOP");
        if (env) {
            st->multiloop_total = atoi(env);
            if (st->multiloop_total > 0)
                printf("OCL: tryb multiloop — %d krokow w jednym dispatchu\n",
                       st->multiloop_total);
        }
    }

    st->ncompts     = n;
    st->nchips      = nc;
    st->nops        = no;
    st->initialized = 1;

    printf("OCL: gotowy (%d kompartmentow, %d chips)\n", n, nc);
    } /* end alokacja */
    hsolve->accel_state = st;
    ocl_state_register(st);
    return 0;
}

/* GENESIS 2.5 GPU-solve (Karol Chlasta, 2026-07-25): sort helper for
** computing each tree's backward-segment end bound once at init time --
** see GPU_HINES_SOLVE_DESIGN.md and do_pertree_validate's matching
** (O(n_trees) per-tree, so O(n_trees^2) total) search, done here once
** as an O(n_trees log n_trees) sort instead since this scales to
** realistic neuron counts (thousands) at solver-setup time, not
** per-step. */
typedef struct { int start; int idx; } OclTreeSortEntry;

static int ocl_tree_sort_cmp(const void *a, const void *b)
{
    return ((const OclTreeSortEntry *)a)->start - ((const OclTreeSortEntry *)b)->start;
}

/*
 * ocl_tree_buffers_init — uploads funcs[]/ravals[] and per-tree dispatch
 * metadata for hines_tree_eliminate (the real multicompartment solver),
 * and creates+configures that kernel. Called once, lazily, the first time
 * a multiloop batch actually needs it (i.e. hsolve->n_trees < ncompts --
 * real tree structure, not all-single-compartment). See hines_struct.h's
 * Hsolve field comments and GPU_HINES_SOLVE_DESIGN.md for what each of
 * these arrays means and why the kernel needs them in this exact form.
 */
static int ocl_tree_buffers_init(Hsolve *hsolve)
{
    OclHsolveState *st = (OclHsolveState *)hsolve->accel_state;
    cl_int err;
    int n_trees = hsolve->n_trees;
    int nfuncs  = hsolve->nfuncs;
    int nravals = hsolve->nravals;
    int *fwd_seg_end, *bwd_seg_end;
    float *fravals;
    OclTreeSortEntry *sorted;
    int i;

    fwd_seg_end = (int *)malloc(n_trees * sizeof(int));
    bwd_seg_end = (int *)malloc(n_trees * sizeof(int));

    /* forward: order already matches array index (discovery order), so
       each tree's end is simply the next tree's start, or (last tree)
       the position just before the forward-pass FINISH -- derived from
       the sentinel's bwd_seg_start exactly as do_pertree_validate does. */
    for (i = 0; i < n_trees; i++) {
        fwd_seg_end[i] = (i+1 < n_trees)
            ? hsolve->fwd_seg_start[i+1]
            : hsolve->bwd_seg_start[n_trees-1] - 1;
    }

    /* backward: discovery order != backward-loop order, so sort by
       bwd_seg_start to find each tree's "next" neighbor. The "-1" on
       both the sorted-neighbor and the final-tree case matches
       do_pertree_validate's derivation exactly (excludes, respectively,
       the next tree's own root CALC_RESULTS token, and the trailing
       global FINISH token). */
    sorted = (OclTreeSortEntry *)malloc(n_trees * sizeof(OclTreeSortEntry));
    for (i = 0; i < n_trees; i++) {
        sorted[i].start = hsolve->bwd_seg_start[i];
        sorted[i].idx   = i;
    }
    qsort(sorted, n_trees, sizeof(OclTreeSortEntry), ocl_tree_sort_cmp);
    for (i = 0; i < n_trees; i++) {
        int this_idx = sorted[i].idx;
        bwd_seg_end[this_idx] = (i+1 < n_trees)
            ? sorted[i+1].start - 1
            : hsolve->nfuncs - 1;
    }
    free(sorted);

    st->buf_funcs = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        nfuncs * sizeof(int), hsolve->funcs, &err);

    fravals = (float *)malloc(nravals * sizeof(float));
    d2f(hsolve->ravals, fravals, nravals);
    st->buf_ravals = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        nravals * sizeof(float), fravals, &err);
    free(fravals);

    st->buf_fwd_seg_start = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), hsolve->fwd_seg_start, &err);
    st->buf_fwd_seg_end = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), fwd_seg_end, &err);
    st->buf_bwd_seg_start = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), hsolve->bwd_seg_start, &err);
    st->buf_bwd_seg_end = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), bwd_seg_end, &err);
    st->buf_fwd_root_row = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), hsolve->fwd_root_row, &err);
    st->buf_fwd_raval_start = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), hsolve->fwd_raval_start, &err);
    st->buf_bwd_raval_start = clCreateBuffer(ocl_dev.context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n_trees * sizeof(int), hsolve->bwd_raval_start, &err);

    free(fwd_seg_end);
    free(bwd_seg_end);

    ocl_dev.kernel_tree = clCreateKernel(ocl_dev.program,
                                           "hines_tree_eliminate", &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateKernel hines_tree_eliminate (%d)\n", err);
        return -1;
    }
    clSetKernelArg(ocl_dev.kernel_tree,  0, sizeof(cl_mem), &st->buf_funcs);
    clSetKernelArg(ocl_dev.kernel_tree,  1, sizeof(cl_mem), &st->buf_ravals);
    clSetKernelArg(ocl_dev.kernel_tree,  2, sizeof(cl_mem), &st->buf_results);
    clSetKernelArg(ocl_dev.kernel_tree,  3, sizeof(cl_mem), &st->buf_vm);
    clSetKernelArg(ocl_dev.kernel_tree,  4, sizeof(cl_mem), &st->buf_fwd_seg_start);
    clSetKernelArg(ocl_dev.kernel_tree,  5, sizeof(cl_mem), &st->buf_fwd_seg_end);
    clSetKernelArg(ocl_dev.kernel_tree,  6, sizeof(cl_mem), &st->buf_bwd_seg_start);
    clSetKernelArg(ocl_dev.kernel_tree,  7, sizeof(cl_mem), &st->buf_bwd_seg_end);
    clSetKernelArg(ocl_dev.kernel_tree,  8, sizeof(cl_mem), &st->buf_fwd_root_row);
    clSetKernelArg(ocl_dev.kernel_tree,  9, sizeof(cl_mem), &st->buf_fwd_raval_start);
    clSetKernelArg(ocl_dev.kernel_tree, 10, sizeof(cl_mem), &st->buf_bwd_raval_start);
    clSetKernelArg(ocl_dev.kernel_tree, 11, sizeof(int),    &n_trees);

    st->n_trees = n_trees;
    st->tree_kernel_ready = 1;
    printf("OCL: kernel eliminacji drzew gotowy (%d drzew)\n", n_trees);
    return 0;
}

/*
 * ocl_multiloop_dispatch — uruchamia chip_channel_multiloop dla nsteps krokow
 *
 * Jeden upload vm+chip, jeden dispatch kernela (petla wewnetrzna), jeden download.
 * Eliminuje roundtrip CPU/GPU na kazdy krok: zamiast N*3 transferow jest 3 transfery.
 *
 * Po powrocie:
 *   hsolve->vm[]      = napięcia po nsteps krokach
 *   hsolve->chip[]    = stan bramek po nsteps krokach
 *   hsolve->results[] = tożsame (vm_final, 1.0) — CPU Hines => vm_new = vm_final
 */
/*
 * ocl_multiloop_dispatch_tree — GENESIS 2.5 (Karol Chlasta, 2026-07-25):
 * real multicompartment multiloop. One upload of vm[]/chip[], then nsteps
 * iterations of (chip_channel_update over ncompts work-items -> writes
 * results[]; hines_tree_eliminate over n_trees work-items -> reads
 * results[], writes vm[]) on the SAME in-order queue, so each iteration's
 * elimination kernel is guaranteed to see that iteration's own channel
 * kernel's output with no explicit sync needed -- then one download of
 * vm[]/chip[]. Unlike the old chip_channel_multiloop (single-compartment
 * only, see hines_tree_eliminate's own header comment and
 * GPU_HINES_SOLVE_DESIGN.md), this is the FIRST correct GPU path for
 * axially-coupled multicompartment trees that also batches K steps into
 * one host round trip (per-step dispatch, chanmode 4 without
 * GENESIS_OCL_MULTILOOP, was already correct but pays a host<->GPU
 * round trip every single step).
 */
static int ocl_multiloop_dispatch_tree(Hsolve *hsolve, int nsteps)
{
    OclHsolveState *st = (OclHsolveState *)hsolve->accel_state;
    int n  = hsolve->ncompts;
    int nc = hsolve->nchips;
    int step;
    cl_int err;
    struct timespec t0, t1;

    if (!st->tree_kernel_ready) {
        if (ocl_tree_buffers_init(hsolve) != 0) {
            fprintf(stderr, "OCL multiloop (tree): buffer init failed, fallback CPU\n");
            return do_chip_hh4_update(hsolve);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t0);

    d2f(hsolve->vm, st->f_vm, n);
    d2f(hsolve->chip, st->f_chip, nc);
    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_vm, CL_FALSE,
                         0, n*sizeof(float), st->f_vm, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_chip, CL_FALSE,
                         0, nc*sizeof(float), st->f_chip, 0, NULL, NULL);

    {
    size_t chan_local  = 64;
    size_t chan_global  = ((n + chan_local - 1) / chan_local) * chan_local;
    size_t tree_local  = 64;
    size_t tree_global = ((hsolve->n_trees + tree_local - 1) / tree_local) * tree_local;

    for (step = 0; step < nsteps; step++) {
        err = clEnqueueNDRangeKernel(ocl_dev.queue, ocl_dev.kernel,
                                      1, NULL, &chan_global, &chan_local,
                                      0, NULL, NULL);
        if (err != CL_SUCCESS) {
            fprintf(stderr, "OCL multiloop (tree): channel kernel error (%d) at step %d\n", err, step);
            return do_chip_hh4_update(hsolve);
        }
        err = clEnqueueNDRangeKernel(ocl_dev.queue, ocl_dev.kernel_tree,
                                      1, NULL, &tree_global, &tree_local,
                                      0, NULL, NULL);
        if (err != CL_SUCCESS) {
            fprintf(stderr, "OCL multiloop (tree): eliminate kernel error (%d) at step %d\n", err, step);
            return do_chip_hh4_update(hsolve);
        }
        /* Cheap insurance, not a fix (see the hard cap in
           ocl_multiloop_dispatch() for the real guard): periodic sync
           so the host<->device command queue never grows unbounded. */
        if ((step & 15) == 15) clFinish(ocl_dev.queue);
    }

    clEnqueueReadBuffer(ocl_dev.queue, st->buf_vm, CL_FALSE,
                        0, n*sizeof(float), st->f_vm, 0, NULL, NULL);
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_results, CL_FALSE,
                        0, n*2*sizeof(float), st->f_results, 0, NULL, NULL);
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_chip, CL_TRUE,
                        0, nc*sizeof(float), st->f_chip, 0, NULL, NULL);

    f2d(st->f_vm, hsolve->vm, n);
    f2d(st->f_results, hsolve->results, n*2);
    f2d(st->f_chip, hsolve->chip, nc);
    st->chip_on_gpu = 0;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    {
        unsigned long long total_ns =
            (unsigned long long)(t1.tv_sec - t0.tv_sec) * 1000000000ULL +
            (t1.tv_nsec - t0.tv_nsec);
        printf("OCL MULTILOOP (tree): %d krokow x 2 kernele | "
               "total %.1f ms | %.3f us/krok\n",
               nsteps, total_ns / 1e6, total_ns / 1e3 / nsteps);
    }
    }

    st->multiloop_called = 1;
    return 0;
}

static int ocl_multiloop_dispatch(Hsolve *hsolve, int nsteps)
{
    OclHsolveState *st = (OclHsolveState *)hsolve->accel_state;
    int n  = hsolve->ncompts;
    int nc = hsolve->nchips;
    cl_int err;

    struct timespec t0, t1;

    /* Real multicompartment tree structure (at least one tree has >1
       compartment): the old single-kernel path below only implements
       the isopotential single-compartment formula and silently drops
       axial coupling (see GPU_HINES_SOLVE_DESIGN.md) -- dispatch the
       validated two-kernel-per-step tree solver instead. Pure
       single-compartment networks (n_trees == ncompts) keep using the
       faster single-kernel path below, unchanged. */
    if (hsolve->n_trees > 0 && hsolve->n_trees < hsolve->ncompts) {
        /* GENESIS 2.5 GPU-solve, SAFETY CAP (Karol Chlasta, 2026-07-25):
        ** found empirically that ocl_multiloop_dispatch_tree triggers a
        ** driver-level hang/reset ("amdgpu: context lost, hard recovery")
        ** on an AMD Radeon 890M laptop iGPU once ncompts crosses a sharp,
        ** reproducible threshold -- confirmed WORKING at N=1400xNCOMP=16
        ** (22400 total compartments), confirmed HANGING at N=1500xNCOMP=16
        ** (24000), on every retry, REGARDLESS of kernel-launch sync
        ** strategy (tried: no sync, periodic clFlush, periodic clFinish
        ** every 16 steps, clFinish after EVERY single step, smaller
        ** work-group size -- NONE moved the threshold). The channel kernel
        ** alone (same kernel/size, per-step dispatch with a blocking
        ** readback every step) does not hang even at 32000 compartments,
        ** and the elimination kernel's logic is separately, extensively
        ** validated correct on CPU and on that same iGPU at smaller scale
        ** -- so this looked like a hardware/driver-specific limit on that
        ** one iGPU, not a logic bug, but the root cause was never
        ** understood.
        **
        ** CONFIRMED iGPU-SPECIFIC 2026-07-25 (later the same day): tested
        ** the EXACT hanging configuration (N=2000 x NCOMP=16, 32000
        ** compartments) on UMCS cluster inf02 (NVIDIA A40, OpenCL via the
        ** NVIDIA driver's ICD) -- ran correctly in 2.5ms, no hang. Scaled
        ** further on the A40 with no issue: N=5000xNCOMP=16 (80000 comps,
        ** ~6x faster than CPU) and N=10000xNCOMP=16 (160000 comps) both
        ** ran correctly (the only slow part at N=10000 was the SLI
        ** interpreter's own model-construction phase, ~2.5 minutes of
        ** pure CPU script execution unrelated to the GPU kernel at all).
        ** So the cap below is real insurance for integrated/display-
        ** sharing GPUs, but is NOT a fundamental limit of this design or
        ** of dedicated compute GPUs -- kept as a conservative DEFAULT,
        ** overridable via GENESIS_OCL_TREE_MAX_NCOMPTS (0 or negative =
        ** no cap) so cluster deployments aren't held back by a laptop's
        ** driver quirk. Still falls back to CPU (correct, just not GPU-
        ** accelerated for that hsolve) rather than risk a hang on
        ** whatever hardware IS in front of it, and disables multiloop
        ** entirely for the rest of the hsolve's run so subsequent steps
        ** don't retry the same doomed dispatch. */
        {
        static int cap_checked = 0;
        static long max_ncompts = 20000;
        if (!cap_checked) {
            const char *env = getenv("GENESIS_OCL_TREE_MAX_NCOMPTS");
            if (env) max_ncompts = atol(env);
            cap_checked = 1;
        }
        if (max_ncompts > 0 && hsolve->ncompts > max_ncompts) {
            fprintf(stderr,
                "OCL multiloop (tree): ncompts=%d exceeds the safe cap (%ld, "
                "override with GENESIS_OCL_TREE_MAX_NCOMPTS) -- known driver "
                "hang on some GPUs above ~22000-24000, NOT reproduced on UMCS "
                "cluster A40 up to 160000 -- see ocl_hsolve.c comment. Falling "
                "back to CPU for this hsolve; GENESIS_OCL_MULTILOOP disabled "
                "for the rest of this run.\n", hsolve->ncompts, max_ncompts);
            st->multiloop_total = 0;
            return do_chip_hh4_update(hsolve);
        }
        }
        return ocl_multiloop_dispatch_tree(hsolve, nsteps);
    }

    clock_gettime(CLOCK_MONOTONIC, &t0);

    /* upload vm[] i chip[] (pelny stan startowy) — konwersja double->float */
    d2f(hsolve->vm, st->f_vm, n);
    d2f(hsolve->chip, st->f_chip, nc);

    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_vm, CL_FALSE,
                         0, n*sizeof(float), st->f_vm, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_chip, CL_FALSE,
                         0, nc*sizeof(float), st->f_chip, 0, NULL, NULL);

    /* ustaw nsteps w argumencie 13 kernela multiloop */
    clSetKernelArg(ocl_dev.kernel_multi, 13, sizeof(int), &nsteps);

    /* dispatch: jeden work-item na kompartment, wszystkie nsteps krokow wewnatrz */
    {
    size_t local_size  = 64;
    size_t global_size = ((n + local_size - 1) / local_size) * local_size;
    cl_event ev;
    err = clEnqueueNDRangeKernel(ocl_dev.queue, ocl_dev.kernel_multi,
                                  1, NULL, &global_size, &local_size,
                                  0, NULL, &ev);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL multiloop: kernel error (%d), fallback CPU\n", err);
        return do_chip_hh4_update(hsolve);
    }

    /* download vm[] (napięcia po wszystkich krokach) i results[] (tożsame) i chip[] */
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_vm, CL_FALSE,
                        0, n*sizeof(float), st->f_vm, 0, NULL, NULL);
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_results, CL_FALSE,
                        0, n*2*sizeof(float), st->f_results, 0, NULL, NULL);
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_chip, CL_TRUE,
                        0, nc*sizeof(float), st->f_chip, 0, NULL, NULL);

    /* konwersja float->double z powrotem do hsolve */
    f2d(st->f_vm, hsolve->vm, n);
    f2d(st->f_results, hsolve->results, n*2);
    f2d(st->f_chip, hsolve->chip, nc);

    /* chip[] is now correct on CPU; GPU copy matches */
    st->chip_on_gpu = 0;

    clock_gettime(CLOCK_MONOTONIC, &t1);

    /* --- profiling i raport --- */
    {
    cl_ulong kstart, kend;
    unsigned long long kern_ns = 0;
    if (clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_START,
                                sizeof(kstart), &kstart, NULL) == CL_SUCCESS &&
        clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_END,
                                sizeof(kend), &kend, NULL) == CL_SUCCESS) {
        kern_ns = kend - kstart;
    }
    clReleaseEvent(ev);

    unsigned long long total_ns =
        (unsigned long long)(t1.tv_sec - t0.tv_sec) * 1000000000ULL +
        (t1.tv_nsec - t0.tv_nsec);

    printf("OCL MULTILOOP: %d krokow | kernel %.1f ms | "
           "total %.1f ms | %.3f us/krok\n",
           nsteps,
           kern_ns  / 1e6,
           total_ns / 1e6,
           total_ns / 1e3 / nsteps);
    }
    } /* end dispatch block */

    st->multiloop_called = 1;
    return 0;
}

/*
 * ocl_chip_update — wywolywana co krok zamiast do_chip_hh4_update
 *
 * Tryb normalny (persistent chip):
 *   Krok 0:  WriteBuffer(vm) + WriteBuffer(chip) + Kernel + ReadBuffer(results)
 *   Krok 1+: WriteBuffer(vm)                     + Kernel + ReadBuffer(results)
 *
 * Tryb multiloop (GENESIS_OCL_MULTILOOP=<nsteps>):
 *   Pierwsze wywolanie: jeden dispatch K krokow, download vm+chip+results.
 *   Kolejne wywolania (w obrebie tego samego K-krokowego batcha): no-op.
 *   results[] zawiera wartosci tożsame (vm_final, 1.0) — CPU Hines => vm = vm_final.
 *
 *   Tylko dla sieci jednokompartmentowych (brak solwera trojdiagonalnego).
 *
 * Jesli OpenCL nie dziala — automatyczny fallback na CPU.
 */
int ocl_chip_update(Hsolve *hsolve)
{
    OclHsolveState *st = (OclHsolveState *)hsolve->accel_state;

    if (!st || !st->initialized) {
        if (ocl_disabled)
            return do_chip_hh4_update(hsolve);
        if (ocl_init(hsolve) != 0) {
            ocl_disabled = 1;
            return do_chip_hh4_update(hsolve);
        }
        st = (OclHsolveState *)hsolve->accel_state;
        if (!st) return do_chip_hh4_update(hsolve);
    }

    /* --- tryb multiloop --- */
    if (st->multiloop_total > 0) {
        if (st->multiloop_called > 0) {
            /* GPU juz wykonal wszystkie kroki; hsolve->vm[] zawiera napięcia finalne.
               Zwroc 1 = sygnał dla hines.c żeby pominął do_euler_hsolve(). */
            st->multiloop_called++;
            return 1;
        }
        /* Pierwsze wywolanie: odpal caly batch na GPU.
           Po powrocie hsolve->vm[] = napięcia po nsteps krokach GPU.
           Zwroc 1 — Hines solve nie jest potrzebny (vm[] juz aktualny). */
        if (ocl_multiloop_dispatch(hsolve, st->multiloop_total) == 0)
            return 1;
        /* Dispatch nieudany — fallback do CPU, solve potrzebny (return 0) */
        return 0;
    }

    int n  = hsolve->ncompts;
    int nc = hsolve->nchips;

    struct timespec t0, t1, ttransfer;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    /* Always upload current vm[] (written by CPU Hines solver each step). */
    d2f(hsolve->vm, st->f_vm, n);
    clEnqueueWriteBuffer(ocl_dev.queue, st->buf_vm, CL_FALSE,
                         0, n*sizeof(float), st->f_vm, 0, NULL, NULL);

    /* Upload chip[] only on the first call — after that the GPU owns it. */
    if (!st->chip_on_gpu) {
        d2f(hsolve->chip, st->f_chip, nc);
        clEnqueueWriteBuffer(ocl_dev.queue, st->buf_chip, CL_FALSE,
                             0, nc*sizeof(float), st->f_chip, 0, NULL, NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &ttransfer);

    /* zaokraglamy global_size do wielokrotnosci 64 (optymalny rozmiar dla AMD) */
    size_t local_size  = 64;
    size_t global_size = ((n + local_size - 1) / local_size) * local_size;

    cl_event kern_event;
    cl_int err = clEnqueueNDRangeKernel(ocl_dev.queue, ocl_dev.kernel,
                                         1, NULL, &global_size, &local_size,
                                         0, NULL, &kern_event);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: kernel error (%d), fallback CPU\n", err);
        return do_chip_hh4_update(hsolve);
    }

    /* chip[] now lives on the GPU; CPU copy is stale. */
    st->chip_on_gpu = 1;

    /* CL_TRUE = bariera synchronizacji — czekamy na zakonczenie GPU */
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_results, CL_TRUE,
                        0, n*2*sizeof(float), st->f_results, 0, NULL, NULL);
    f2d(st->f_results, hsolve->results, n*2);

    /* accumulate profiling stats */
    clock_gettime(CLOCK_MONOTONIC, &t1);
    cl_ulong kstart, kend;
    if (clGetEventProfilingInfo(kern_event, CL_PROFILING_COMMAND_START,
                                sizeof(kstart), &kstart, NULL) == CL_SUCCESS &&
        clGetEventProfilingInfo(kern_event, CL_PROFILING_COMMAND_END,
                                sizeof(kend), &kend, NULL) == CL_SUCCESS) {
        st->prof_kernel_ns += (kend - kstart);
    }
    clReleaseEvent(kern_event);
    {
        unsigned long long dt_total =
            (unsigned long long)(t1.tv_sec - t0.tv_sec) * 1000000000ULL +
            (t1.tv_nsec - t0.tv_nsec);
        unsigned long long dt_transfer =
            (unsigned long long)(ttransfer.tv_sec - t0.tv_sec) * 1000000000ULL +
            (ttransfer.tv_nsec - t0.tv_nsec);
        st->prof_total_ns    += dt_total;
        st->prof_transfer_ns += dt_transfer;
        st->prof_calls++;
    }

    return 0;
}

/*
 * ocl_sync_chip — synchronizuje chip[] z GPU do CPU
 *
 * Wywolaj przed odczytem pol stanu bramek hsolve z poziomu skryptow GENESIS
 * (findsolvefield, HGET itp.). Nie musisz wywolywac po kazdym kroku —
 * wystarczy przed momentem, gdy CPU potrzebuje aktualnych wartosci.
 */
void ocl_sync_chip(Hsolve *hsolve)
{
    OclHsolveState *st = (OclHsolveState *)hsolve->accel_state;
    if (!st || !st->initialized || !st->chip_on_gpu) return;
    clEnqueueReadBuffer(ocl_dev.queue, st->buf_chip, CL_TRUE,
                        0, st->nchips * sizeof(float),
                        st->f_chip, 0, NULL, NULL);
    f2d(st->f_chip, hsolve->chip, st->nchips);
    st->chip_on_gpu = 0;
}

/*
 * ocl_cleanup — zwalnia wszystkie zasoby OpenCL
 * Wywolywana przy zamknieciu GENESIS (z h_delete lub atexit)
 */
void ocl_cleanup(void)
{
    OclStateNode *node;
    unsigned long long kern_ns = 0, total_ns = 0, transfer_ns = 0;
    unsigned long calls = 0;
    int multiloop_states = 0, multiloop_total = 0, multiloop_called = 0;

    /* Per-hsolve teardown. Profiling is aggregated rather than printed per
       solver: the one-solver-per-cell idiom produces thousands of states and a
       summary each would bury the run in output. */
    while (ocl_states) {
        OclHsolveState *st = ocl_states->st;
        node = ocl_states;
        ocl_states = node->next;
        if (st) {
            if (st->initialized) {
                clReleaseMemObject(st->buf_vm);
                clReleaseMemObject(st->buf_chip);
                clReleaseMemObject(st->buf_results);
                clReleaseMemObject(st->buf_tablist);
                clReleaseMemObject(st->buf_xvals);
                clReleaseMemObject(st->buf_ops);
                if (st->buf_stablist) clReleaseMemObject(st->buf_stablist);
                if (st->tree_kernel_ready) {
                    clReleaseMemObject(st->buf_funcs);
                    clReleaseMemObject(st->buf_ravals);
                    clReleaseMemObject(st->buf_fwd_seg_start);
                    clReleaseMemObject(st->buf_fwd_seg_end);
                    clReleaseMemObject(st->buf_bwd_seg_start);
                    clReleaseMemObject(st->buf_bwd_seg_end);
                    clReleaseMemObject(st->buf_fwd_root_row);
                    clReleaseMemObject(st->buf_fwd_raval_start);
                    clReleaseMemObject(st->buf_bwd_raval_start);
                }
                free(st->f_vm);
                free(st->f_chip);
                free(st->f_results);
            }
            kern_ns     += st->prof_kernel_ns;
            total_ns    += st->prof_total_ns;
            transfer_ns += st->prof_transfer_ns;
            calls       += st->prof_calls;
            if (st->multiloop_called > 0) {
                multiloop_states++;
                multiloop_total  = st->multiloop_total;
                multiloop_called = st->multiloop_called;
            }
            free(st);
        }
        free(node);
    }

    /* Device-level resources are shared, so they are released exactly once. */
    if (ocl_dev.kernel_tree)  clReleaseKernel(ocl_dev.kernel_tree);
    if (ocl_dev.kernel)       clReleaseKernel(ocl_dev.kernel);
    if (ocl_dev.kernel_multi) clReleaseKernel(ocl_dev.kernel_multi);
    if (ocl_dev.program)      clReleaseProgram(ocl_dev.program);
    if (ocl_dev.queue)        clReleaseCommandQueue(ocl_dev.queue);
    if (ocl_dev.context)      clReleaseContext(ocl_dev.context);

    if (multiloop_states > 0) {
        printf("OCL MULTILOOP SUMMARY (%d hsolve state(s))\n", multiloop_states);
        printf("  batch dispatched : 1 kernel call covering %d steps\n",
               multiloop_total);
        printf("  no-op steps      : %d (CPU Hines identity pass-through)\n",
               multiloop_called - 1);
        printf("  (timing per-dispatch printed at dispatch time above)\n");
    }
    if (calls > 0) {
        double kern_ms     = kern_ns     / 1e6;
        double total_ms    = total_ns    / 1e6;
        double transfer_ms = transfer_ns / 1e6;
        double per_call_us = kern_ns / (double)calls / 1e3;
        double gpu_fraction = (total_ms > 0.0) ? 100.0 * kern_ms / total_ms : 0.0;
        printf("OCL PROFILING SUMMARY (aggregated over all hsolve states)\n");
        printf("  steps profiled    : %lu\n",  calls);
        printf("  kernel total      : %.3f ms  (%.2f us/step)\n",
               kern_ms, per_call_us);
        printf("  vm upload (wall)  : %.3f ms  (%.2f us/step, step-0 also had chip)\n",
               transfer_ms, transfer_ms * 1e3 / calls);
        printf("  ocl_chip_update   : %.3f ms  (wall incl. transfers)\n", total_ms);
        printf("  GPU active frac   : %.2f%%  (kernel / ocl_chip_update wall)\n",
               gpu_fraction);
        printf("  chip[] transfers  : skipped (persistent GPU buffer after step 0)\n");
        printf("  NOTE: ocl_chip_update is only the channel-update fraction\n");
        printf("        of total step time. Hines solver runs on CPU.\n");
    }
    printf("OCL: zasoby zwolnione\n");
}

#endif /* USE_OPENCL */
