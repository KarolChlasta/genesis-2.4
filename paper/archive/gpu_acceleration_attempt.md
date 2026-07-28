# Accelerator Enablement Log for Proposed GENESIS 2.5

## Objective
Document the accelerator enablement status for a proposed GENESIS 2.5 release,
defined as GENESIS 2.4 plus first-class accelerator support. The validated path
in this workspace is OpenCL on AMD Radeon 890M; CUDA is part of the proposed
release scope but is not validated here.

## Environment Observations
- GPU detected:
  - `66:00.0 Display controller: Advanced Micro Devices, Inc. [AMD/ATI] Strix [Radeon 880M / 890M] (rev c1)`
- Existing `nxgenesis` linkage includes OpenCL runtime library:
  - `libOpenCL.so.1 => /usr/lib/x86_64-linux-gnu/libOpenCL.so.1`

## Step 1: Run Bundled OpenCL Benchmark Script
Command shape:
- `genesis/src/nxgenesis -nosimrc -notty -batch genesis/Scripts/benchmark/ocl_benchmark.g 100`

Outcome (initial state):
- The original script execution returned many parser errors (`syntax error`) and
  did not provide usable benchmark output.

Outcome (after repair in current workspace):
- The script was repaired and now runs end-to-end under `genesis/genesis` for
  the same 100-neuron case (with external wall-clock timing).
- This removed script parsing as the primary GPU-path blocker.

## Step 2: Rebuild `nxgenesis` with OpenCL Compile Flag
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
  - device: `AMD Radeon 890M Graphics (radeonsi, strix1, ACO)`
  - device type: `GPU`

## Reproducibility Notes
To reproduce the validated OpenCL build and rerun the benchmark, install the
OpenCL headers/dev package for the host distro if needed, then rebuild with
`USE_OPENCL=1`.

Recommended verification after install:
1. Preserve the repaired benchmark script path (already validated).
2. Keep the `hines` build fixes that allow `USE_OPENCL=1` compilation.
3. Keep this probe+benchmark combined log path in future runs to preserve
  explicit platform/device attribution.

## RETRACTION (2026-06-18)
The benchmark run described above (`ocl_benchmark.g`, Step 1-2) does not
demonstrate GPU dispatch. That script builds only passive RC compartments
with zero ion channels attached to its `chanmode=4` `hsolve` objects; with no
channel state to solve, the OpenCL channel-update kernel is never invoked,
regardless of how `nxgenesis` was built. The execution logs cited above
(`paper/nxgenesis_opencl_benchmark_with_device.log`,
`paper/nxgenesis_opencl_benchmark_device_log.txt`) confirm this directly: they
contain no `OCL` initialization or kernel-dispatch output, and report ~25-31
ms of total CPU time for 50,000 steps, consistent with trivial passive-compartment
arithmetic. The device-attribution log was produced by a separate OpenCL probe
program, disconnected from the benchmark run, and its presence does not imply
the benchmark itself used the GPU. "The binary contains OpenCL symbols and the
script ran without error" is not sufficient evidence of GPU dispatch.

A corrected benchmark, `genesis/Scripts/benchmark/ocl_hh_benchmark.g`, builds a
single `hsolve` with real `tabchannel` Hodgkin-Huxley channels (the minimum
configuration under which `hsolve` actually dispatches to the OpenCL kernel),
and confirms dispatch directly via `CL_QUEUE_PROFILING_ENABLE` and an `OCL
PROFILING SUMMARY` printed at exit. Results: `paper/profiling_runs/ocl_profile_N{100,500,1000,2000}.txt`,
discussed in `paper/manuscript_genesis_2_5_proposal.md` Section 3.5 and
`paper/PLAN_gpu_rewrite.md`. The kernel is confirmed fast and correct but is a
small fraction of total step time; no end-to-end speedup is claimed.

## Reporting Statement (for manuscript) -- SUPERSEDED, see retraction above
~~Accelerator enablement now supports an evidence-based GENESIS 2.5 proposal:
`nxgenesis USE_OPENCL=1` compiles and runs the repaired benchmark script with
OpenCL-linked symbols present in the executable. Explicit platform/device
attribution was captured via probe+benchmark logging, identifying a GPU device
named `AMD Radeon 890M Graphics` on platform `rusticl`.~~ CUDA remains future
work within the proposed GENESIS 2.5 scope and should not be reported as a
validated backend from the current workspace.
