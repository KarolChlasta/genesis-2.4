#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

static void print_info_string(cl_platform_id p, cl_platform_info key, const char *label) {
    size_t sz = 0;
    if (clGetPlatformInfo(p, key, 0, NULL, &sz) != CL_SUCCESS || sz == 0) {
        printf("%s: <unavailable>\n", label);
        return;
    }
    char *buf = (char *)malloc(sz);
    if (!buf) {
        printf("%s: <alloc-failed>\n", label);
        return;
    }
    if (clGetPlatformInfo(p, key, sz, buf, NULL) == CL_SUCCESS) {
        printf("%s: %s\n", label, buf);
    } else {
        printf("%s: <read-failed>\n", label);
    }
    free(buf);
}

static void print_device_string(cl_device_id d, cl_device_info key, const char *label) {
    size_t sz = 0;
    if (clGetDeviceInfo(d, key, 0, NULL, &sz) != CL_SUCCESS || sz == 0) {
        printf("%s: <unavailable>\n", label);
        return;
    }
    char *buf = (char *)malloc(sz);
    if (!buf) {
        printf("%s: <alloc-failed>\n", label);
        return;
    }
    if (clGetDeviceInfo(d, key, sz, buf, NULL) == CL_SUCCESS) {
        printf("%s: %s\n", label, buf);
    } else {
        printf("%s: <read-failed>\n", label);
    }
    free(buf);
}

int main(void) {
    cl_int err;
    cl_uint nplat = 0;
    err = clGetPlatformIDs(0, NULL, &nplat);
    if (err != CL_SUCCESS || nplat == 0) {
        fprintf(stderr, "OpenCL probe error: no platform (err=%d)\n", err);
        return 1;
    }

    cl_platform_id *plats = (cl_platform_id *)calloc(nplat, sizeof(cl_platform_id));
    if (!plats) {
        fprintf(stderr, "OpenCL probe error: alloc failed\n");
        return 1;
    }
    err = clGetPlatformIDs(nplat, plats, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "OpenCL probe error: clGetPlatformIDs failed (err=%d)\n", err);
        free(plats);
        return 1;
    }

    cl_platform_id selected_platform = NULL;
    cl_device_id selected_device = NULL;

    for (cl_uint i = 0; i < nplat; i++) {
        cl_uint ngpu = 0;
        clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_GPU, 0, NULL, &ngpu);
        if (ngpu > 0) {
            selected_platform = plats[i];
            clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_GPU, 1, &selected_device, NULL);
            break;
        }
    }

    if (!selected_device) {
        for (cl_uint i = 0; i < nplat; i++) {
            cl_uint ncpu = 0;
            clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_CPU, 0, NULL, &ncpu);
            if (ncpu > 0) {
                selected_platform = plats[i];
                clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_CPU, 1, &selected_device, NULL);
                break;
            }
        }
    }

    if (!selected_device) {
        fprintf(stderr, "OpenCL probe error: no GPU/CPU device found\n");
        free(plats);
        return 2;
    }

    printf("OPENCL_PROBE_SELECTED\n");
    print_info_string(selected_platform, CL_PLATFORM_NAME, "platform_name");
    print_info_string(selected_platform, CL_PLATFORM_VENDOR, "platform_vendor");
    print_device_string(selected_device, CL_DEVICE_NAME, "device_name");
    print_device_string(selected_device, CL_DEVICE_VENDOR, "device_vendor");

    cl_device_type dtype = 0;
    if (clGetDeviceInfo(selected_device, CL_DEVICE_TYPE, sizeof(dtype), &dtype, NULL) == CL_SUCCESS) {
        if (dtype & CL_DEVICE_TYPE_GPU) printf("device_type: GPU\n");
        else if (dtype & CL_DEVICE_TYPE_CPU) printf("device_type: CPU\n");
        else printf("device_type: OTHER\n");
    }

    free(plats);
    return 0;
}
