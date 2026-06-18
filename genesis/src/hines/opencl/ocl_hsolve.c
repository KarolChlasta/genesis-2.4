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

OclHsolveState ocl_state = {0};

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
    cl_int err;
    cl_platform_id platform;
    atexit(ocl_cleanup);

    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: brak platformy OpenCL (%d)\n", err);
        return -1;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1,
                         &ocl_state.device, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: brak GPU, probuje CPU\n");
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1,
                             &ocl_state.device, NULL);
        if (err != CL_SUCCESS) {
            fprintf(stderr, "OCL: brak urzadzenia (%d)\n", err);
            return -1;
        }
    }

    char devname[128];
    clGetDeviceInfo(ocl_state.device, CL_DEVICE_NAME,
                    sizeof(devname), devname, NULL);
    printf("OCL: urzadzenie: %s\n", devname);

    ocl_state.context = clCreateContext(NULL, 1, &ocl_state.device,
                                        NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateContext (%d)\n", err);
        return -1;
    }

    cl_queue_properties qprops[] = {
        CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0
    };
    ocl_state.queue = clCreateCommandQueueWithProperties(
                          ocl_state.context, ocl_state.device, qprops, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateCommandQueue (%d)\n", err);
        return -1;
    }

    /* szukamy pliku .cl w kilku miejscach */
    {
    const char *cl_paths[] = {
        "opencl/ocl_channel.cl",
        "genesis/src/hines/opencl/ocl_channel.cl",
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
        return -1;
    }

    ocl_state.program = clCreateProgramWithSource(ocl_state.context, 1,
                            (const char **)&src, NULL, &err);
    free(src);
    } /* end cl_paths block */
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateProgram (%d)\n", err);
        return -1;
    }

    /* -cl-fast-relaxed-math: szybsze obliczenia zmiennoprzecinkowe na GPU */
    err = clBuildProgram(ocl_state.program, 1, &ocl_state.device,
                         "-cl-fast-relaxed-math", NULL, NULL);
    if (err != CL_SUCCESS) {
        char log[4096];
        clGetProgramBuildInfo(ocl_state.program, ocl_state.device,
                              CL_PROGRAM_BUILD_LOG, sizeof(log), log, NULL);
        fprintf(stderr, "OCL: blad kompilacji:\n%s\n", log);
        return -1;
    }

    ocl_state.kernel = clCreateKernel(ocl_state.program,
                                      "chip_channel_update", &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateKernel (%d)\n", err);
        return -1;
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
    double xmin  = hsolve->xmin;
    double invdx = hsolve->invdx;
    int *opstart, *chipstart, *cpu_only;
    cl_mem buf_opstart, buf_chipstart;
    /* dummy tablica gdy brak tabeli — kernel nie bedzie jej uzywac */
    double dummy = 0.0;

    if (n <= 0 || nc <= 0 || no <= 0) {
        fprintf(stderr, "OCL: hsolve nie zainicjalizowany (n=%d nc=%d no=%d)\n",
                n, nc, no);
        return -1;
    }

    ocl_state.buf_vm      = clCreateBuffer(ocl_state.context,
                                CL_MEM_READ_ONLY,  n*sizeof(double),  NULL, &err);
    ocl_state.buf_chip    = clCreateBuffer(ocl_state.context,
                                CL_MEM_READ_WRITE, nc*sizeof(double), NULL, &err);
    ocl_state.buf_results = clCreateBuffer(ocl_state.context,
                                CL_MEM_WRITE_ONLY, n*2*sizeof(double),NULL, &err);
    ocl_state.buf_tablist = clCreateBuffer(ocl_state.context,
                                CL_MEM_READ_ONLY,  nt*sizeof(double), NULL, &err);
    ocl_state.buf_xvals   = clCreateBuffer(ocl_state.context,
                                CL_MEM_READ_ONLY,  nx*sizeof(double), NULL, &err);
    ocl_state.buf_ops     = clCreateBuffer(ocl_state.context,
                                CL_MEM_READ_ONLY,  no*sizeof(int),    NULL, &err);
    if (ns > 0)
        ocl_state.buf_stablist = clCreateBuffer(ocl_state.context,
                                     CL_MEM_READ_ONLY, ns*sizeof(double), NULL, &err);

    /* buduj indeksy i uploaduj dane statyczne (tabele, ops) — tylko raz */
    build_comp_index(hsolve, &opstart, &chipstart, &cpu_only);

    buf_opstart = clCreateBuffer(ocl_state.context,
                      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                      n*sizeof(int), opstart, &err);
    buf_chipstart = clCreateBuffer(ocl_state.context,
                        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                        n*sizeof(int), chipstart, &err);
    free(opstart); free(chipstart); free(cpu_only);

    /* upload tabel — uzyj dummy jesli brak tabchannels */
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_tablist, CL_TRUE, 0,
        nt*sizeof(double),
        (hsolve->tablist && hsolve->xdivs > 0) ? hsolve->tablist : &dummy,
        0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_xvals, CL_TRUE, 0,
        nx*sizeof(double),
        (hsolve->xvals && hsolve->xdivs > 0) ? hsolve->xvals : &dummy,
        0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_ops, CL_TRUE,
                         0, no*sizeof(int), hsolve->ops, 0, NULL, NULL);
    if (ns > 0 && hsolve->stablist)
        clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_stablist, CL_TRUE,
                             0, ns*sizeof(double), hsolve->stablist, 0, NULL, NULL);

    /* argumenty kernela — stale przez caly czas zycia */
    clSetKernelArg(ocl_state.kernel,  0, sizeof(cl_mem), &ocl_state.buf_vm);
    clSetKernelArg(ocl_state.kernel,  1, sizeof(cl_mem), &ocl_state.buf_chip);
    clSetKernelArg(ocl_state.kernel,  2, sizeof(cl_mem), &ocl_state.buf_results);
    clSetKernelArg(ocl_state.kernel,  3, sizeof(cl_mem), &ocl_state.buf_tablist);
    clSetKernelArg(ocl_state.kernel,  4, sizeof(cl_mem), &ocl_state.buf_xvals);
    clSetKernelArg(ocl_state.kernel,  5, sizeof(cl_mem), &ocl_state.buf_ops);
    clSetKernelArg(ocl_state.kernel,  6, sizeof(cl_mem), &buf_opstart);
    clSetKernelArg(ocl_state.kernel,  7, sizeof(cl_mem), &buf_chipstart);
    clSetKernelArg(ocl_state.kernel,  8, sizeof(int),    &n);
    clSetKernelArg(ocl_state.kernel,  9, sizeof(int),    &ncols);
    clSetKernelArg(ocl_state.kernel, 10, sizeof(int),    &xdivs);
    clSetKernelArg(ocl_state.kernel, 11, sizeof(double), &xmin);
    clSetKernelArg(ocl_state.kernel, 12, sizeof(double), &invdx);

    ocl_state.ncompts     = n;
    ocl_state.nchips      = nc;
    ocl_state.nops        = no;
    ocl_state.initialized = 1;

    printf("OCL: gotowy (%d kompartmentow, %d chips)\n", n, nc);
    } /* end alokacja */
    return 0;
}

/*
 * ocl_chip_update — wywolywana co krok zamiast do_chip_hh4_update
 *
 * Sekwencja:
 *   1. upload vm[] i chip[] na GPU (asynchronicznie)
 *   2. uruchomienie kernela: N work-items = N kompartmentow rownoleglie
 *   3. download chip[] (zaktualizowane stany bramek) i results[]
 *      ostatni read jest synchroniczny (CL_TRUE) — czekamy az GPU skonczy
 *
 * Jesli OpenCL nie dziala — automatyczny fallback na CPU.
 */
int ocl_chip_update(Hsolve *hsolve)
{
    if (!ocl_state.initialized) {
        if (ocl_init(hsolve) != 0)
            return do_chip_hh4_update(hsolve);
    }

    int n  = hsolve->ncompts;
    int nc = hsolve->nchips;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_vm, CL_FALSE,
                         0, n*sizeof(double), hsolve->vm, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_chip, CL_FALSE,
                         0, nc*sizeof(double), hsolve->chip, 0, NULL, NULL);

    /* zaokraglamy global_size do wielokrotnosci 64 (optymalny rozmiar dla AMD) */
    size_t local_size  = 64;
    size_t global_size = ((n + local_size - 1) / local_size) * local_size;

    cl_event kern_event;
    cl_int err = clEnqueueNDRangeKernel(ocl_state.queue, ocl_state.kernel,
                                         1, NULL, &global_size, &local_size,
                                         0, NULL, &kern_event);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: kernel error (%d), fallback CPU\n", err);
        return do_chip_hh4_update(hsolve);
    }

    clEnqueueReadBuffer(ocl_state.queue, ocl_state.buf_chip, CL_FALSE,
                        0, nc*sizeof(double), hsolve->chip, 0, NULL, NULL);
    /* CL_TRUE = bariera synchronizacji — czekamy na zakonczenie GPU */
    clEnqueueReadBuffer(ocl_state.queue, ocl_state.buf_results, CL_TRUE,
                        0, n*2*sizeof(double), hsolve->results, 0, NULL, NULL);

    /* accumulate profiling stats */
    clock_gettime(CLOCK_MONOTONIC, &t1);
    cl_ulong kstart, kend;
    if (clGetEventProfilingInfo(kern_event, CL_PROFILING_COMMAND_START,
                                sizeof(kstart), &kstart, NULL) == CL_SUCCESS &&
        clGetEventProfilingInfo(kern_event, CL_PROFILING_COMMAND_END,
                                sizeof(kend), &kend, NULL) == CL_SUCCESS) {
        ocl_state.prof_kernel_ns += (kend - kstart);
    }
    clReleaseEvent(kern_event);
    ocl_state.prof_total_ns +=
        (unsigned long long)(t1.tv_sec - t0.tv_sec) * 1000000000ULL +
        (t1.tv_nsec - t0.tv_nsec);
    ocl_state.prof_calls++;

    return 0;
}

/*
 * ocl_cleanup — zwalnia wszystkie zasoby OpenCL
 * Wywolywana przy zamknieciu GENESIS (z h_delete lub atexit)
 */
void ocl_cleanup(void)
{
    if (!ocl_state.initialized) return;
    clReleaseMemObject(ocl_state.buf_vm);
    clReleaseMemObject(ocl_state.buf_chip);
    clReleaseMemObject(ocl_state.buf_results);
    clReleaseMemObject(ocl_state.buf_tablist);
    clReleaseMemObject(ocl_state.buf_xvals);
    clReleaseMemObject(ocl_state.buf_ops);
    if (ocl_state.buf_stablist) clReleaseMemObject(ocl_state.buf_stablist);
    clReleaseKernel(ocl_state.kernel);
    clReleaseProgram(ocl_state.program);
    clReleaseCommandQueue(ocl_state.queue);
    clReleaseContext(ocl_state.context);
    ocl_state.initialized = 0;

    if (ocl_state.prof_calls > 0) {
        double kern_ms  = ocl_state.prof_kernel_ns / 1e6;
        double total_ms = ocl_state.prof_total_ns  / 1e6;
        double per_call_us = ocl_state.prof_kernel_ns / (double)ocl_state.prof_calls / 1e3;
        double gpu_fraction = (total_ms > 0.0)
                              ? 100.0 * kern_ms / total_ms : 0.0;
        printf("OCL PROFILING SUMMARY\n");
        printf("  steps profiled  : %lu\n",  ocl_state.prof_calls);
        printf("  kernel total    : %.3f ms  (%.2f us/step)\n",
               kern_ms, per_call_us);
        printf("  ocl_chip_update : %.3f ms  (wall incl. transfers)\n", total_ms);
        printf("  GPU active frac : %.2f%%  (kernel / ocl_chip_update wall)\n",
               gpu_fraction);
        printf("  NOTE: ocl_chip_update is only the channel-update fraction\n");
        printf("        of total step time. Hines solver runs on CPU.\n");
    }
    printf("OCL: zasoby zwolnione\n");
}

#endif /* USE_OPENCL */
