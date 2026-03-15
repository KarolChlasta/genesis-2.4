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

    int op_i = 0, chip_i = 0;

    for (int c = 0; c < n; c++) {
        opstart[c]   = op_i;
        chipstart[c] = chip_i;
        chip_i += 2; /* Em/Rm + inject */

        int op;
        while ((op = hsolve->ops[op_i++]) != LCOMPT_OP) {
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

    ocl_state.queue = clCreateCommandQueueWithProperties(
                          ocl_state.context, ocl_state.device, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: clCreateCommandQueue (%d)\n", err);
        return -1;
    }

    /* szukamy pliku .cl w kilku miejscach */
    const char *cl_paths[] = {
        "opencl/ocl_channel.cl",
        "genesis/src/hines/opencl/ocl_channel.cl",
        NULL
    };
    char *src = NULL;
    for (int i = 0; cl_paths[i]; i++) {
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

    /* alokacja buforow GPU */
    int n  = hsolve->ncompts;
    int nc = hsolve->nchips;
    int no = hsolve->nops;
    int nt = (hsolve->xdivs + 1) * hsolve->ncols;
    int nx = hsolve->xdivs + 2;
    int ns = hsolve->sntab * 6;

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
    int *opstart, *chipstart, *cpu_only;
    build_comp_index(hsolve, &opstart, &chipstart, &cpu_only);

    cl_mem buf_opstart = clCreateBuffer(ocl_state.context,
                             CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                             n*sizeof(int), opstart, &err);
    cl_mem buf_chipstart = clCreateBuffer(ocl_state.context,
                               CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                               n*sizeof(int), chipstart, &err);
    free(opstart); free(chipstart); free(cpu_only);

    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_tablist, CL_TRUE,
                         0, nt*sizeof(double), hsolve->tablist, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_xvals, CL_TRUE,
                         0, nx*sizeof(double), hsolve->xvals, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_ops, CL_TRUE,
                         0, no*sizeof(int), hsolve->ops, 0, NULL, NULL);
    if (ns > 0)
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
    clSetKernelArg(ocl_state.kernel,  8, sizeof(int),    &hsolve->ncols);
    clSetKernelArg(ocl_state.kernel,  9, sizeof(int),    &hsolve->xdivs);
    clSetKernelArg(ocl_state.kernel, 10, sizeof(double), &hsolve->xmin);
    clSetKernelArg(ocl_state.kernel, 11, sizeof(double), &hsolve->invdx);

    ocl_state.ncompts     = n;
    ocl_state.nchips      = nc;
    ocl_state.nops        = no;
    ocl_state.initialized = 1;

    printf("OCL: gotowy (%d kompartmentow, %d chips)\n", n, nc);
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

    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_vm, CL_FALSE,
                         0, n*sizeof(double), hsolve->vm, 0, NULL, NULL);
    clEnqueueWriteBuffer(ocl_state.queue, ocl_state.buf_chip, CL_FALSE,
                         0, nc*sizeof(double), hsolve->chip, 0, NULL, NULL);

    /* zaokraglamy global_size do wielokrotnosci 64 (optymalny rozmiar dla AMD) */
    size_t local_size  = 64;
    size_t global_size = ((n + local_size - 1) / local_size) * local_size;

    cl_int err = clEnqueueNDRangeKernel(ocl_state.queue, ocl_state.kernel,
                                         1, NULL, &global_size, &local_size,
                                         0, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OCL: kernel error (%d), fallback CPU\n", err);
        return do_chip_hh4_update(hsolve);
    }

    clEnqueueReadBuffer(ocl_state.queue, ocl_state.buf_chip, CL_FALSE,
                        0, nc*sizeof(double), hsolve->chip, 0, NULL, NULL);
    /* CL_TRUE = bariera synchronizacji — czekamy na zakonczenie GPU */
    clEnqueueReadBuffer(ocl_state.queue, ocl_state.buf_results, CL_TRUE,
                        0, n*2*sizeof(double), hsolve->results, 0, NULL, NULL);
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
    printf("OCL: zasoby zwolnione\n");
}

#endif /* USE_OPENCL */
