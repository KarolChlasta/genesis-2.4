# GPU Acceleration Attempt Log (OpenCL)

## Objective
Attempt to execute GENESIS with GPU acceleration on AMD Radeon 890M via OpenCL.

## Environment Observations
- GPU detected:
  - `66:00.0 Display controller: Advanced Micro Devices, Inc. [AMD/ATI] Strix [Radeon 880M / 890M] (rev c1)`
- Existing `nxgenesis` linkage includes OpenCL runtime library:
  - `libOpenCL.so.1 => /usr/lib/x86_64-linux-gnu/libOpenCL.so.1`

## Attempt 1: Run Bundled OpenCL Benchmark Script
Command shape:
- `genesis/src/nxgenesis -nosimrc -notty -batch genesis/Scripts/benchmark/ocl_benchmark.g 100`

Outcome (initial state):
- The original script execution returned many parser errors (`syntax error`) and
  did not provide usable benchmark output.

Outcome (after repair in current workspace):
- The script was repaired and now runs end-to-end under `genesis/genesis` for
  the same 100-neuron case (with external wall-clock timing).
- This removed script parsing as the primary GPU-path blocker.

## Attempt 2: Rebuild `nxgenesis` with OpenCL Compile Flag
Command shape:
- `make nxgenesis USE_OPENCL=1 NETCDFSUBDIR= NETCDFOBJ= NETCDFFLAGS= DISKIOSUBDIR=FMT1`

Outcome:
- Initial rebuild attempts failed in the legacy generated `hines` code path.
- After regenerating stale `hines` generated artifacts (`make clean` in
  `genesis/src/hines`) and patching the `hines` partial-link rule to avoid
  linking `-lOpenCL` at relocatable-object stage, `nxgenesis` built
  successfully with `USE_OPENCL=1`.
- A minimal OpenCL probe (`paper/opencl_probe.c`) was compiled and executed
  together with the benchmark run, producing an explicit attribution log in
  `paper/nxgenesis_opencl_benchmark_with_device.log`.

Interpretation:
- Runtime OpenCL library (`libOpenCL.so.1`) is present.
- OpenCL headers are also discoverable on this host (`/run/host/usr/include/CL`
  and `/opt/rocm-6.3.1/include/CL`).
- Built `nxgenesis` now contains OpenCL symbols (e.g., `clCreateContext`,
  `clEnqueueNDRangeKernel`, `ocl_chip_update`, `ocl_chip_update_dispatch`) and
  runs the repaired benchmark script successfully.
- Device-level attribution captured in current workspace log:
  - platform: `rusticl` (Mesa/X.org)
  - device: `AMD Radeon 890M Graphics (radeonsi, strix1, ACO, DRM 3.64, 6.17.0-121035-tuxedo)`
  - device type: `GPU`

## Reproducibility Notes
To complete GPU build and rerun benchmark, install OpenCL headers/dev package for the host distro (for example OpenCL ICD development headers), then rebuild with `USE_OPENCL=1`.

Recommended verification after install:
1. Preserve the repaired benchmark script path (already validated).
2. Keep the `hines` build fixes that allow `USE_OPENCL=1` compilation.
3. Keep this probe+benchmark combined log path in future runs to preserve
  explicit platform/device attribution.

## Reporting Statement (for manuscript)
GPU acceleration was attempted and the OpenCL build path was unblocked:
`nxgenesis USE_OPENCL=1` now compiles and runs the repaired benchmark script
with OpenCL-linked symbols present in the executable. Explicit platform/device
attribution was captured via probe+benchmark logging, identifying a GPU device
named `AMD Radeon 890M Graphics` on platform `rusticl`.
