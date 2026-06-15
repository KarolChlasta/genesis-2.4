# CPU Benchmark Run Protocol for GENESIS/PGENESIS

## Objective
Produce reproducible strong-scaling data for CPU-only execution on AMD Ryzen AI 9 HX 370.

## Scope
- Serial baseline: nxgenesis
- Parallel runs: nxpgenesis (MPI)
- Process counts: 1, 2, 4, 6, 8, 12, 16, 20, 24
- Replicates: 10 per process count after 1 warm-up

## Pre-Run Checklist
1. Confirm GENESIS and PGENESIS are built successfully.
2. Record software versions:
   - gcc --version
   - mpirun --version
   - git rev-parse --short HEAD
3. Capture machine metadata:
   - lscpu
   - uname -a
4. Ensure idle machine state (close heavy apps).

## Suggested Invocation Pattern
Use a non-graphical script and batch mode where possible. Example shape:

mpirun -np <N> /path/to/nxpgenesis -altsimrc /path/to/.psimrc -notty -batch <script.g>

If the pgenesis wrapper is configured for MPI, equivalent wrapper command:

pgenesis -nox -nodes <N> <script.g>

## Timing Collection
Preferred method:
- Use /usr/bin/time with a stable format.

Example:

/usr/bin/time -f "%e" mpirun -np <N> /path/to/nxpgenesis -altsimrc /path/to/.psimrc -notty -batch <script.g>

Record elapsed seconds in paper/benchmark_results_template.csv.

## Data Quality Rules
- Discard warm-up run for each N.
- If a run fails, rerun that replicate and annotate reason in notes.
- If variance is high (CV > 5%), collect extra replicates (up to 20).

## Reporting
Compute and report:
- Mean and standard deviation of T_N
- Speedup S_N = T_1 / T_N
- Efficiency E_N = S_N / N
- 95% CI of T_N

## Executed Complex-Model Baseline (Current Workspace)
- Executable: genesis/src/nxgenesis
- Model: genesis/Scripts/chemesis/Cal8.g
- Mode: -nosimrc -notty -batch
- Replicates: 30
- Timing method: wall-clock from nanosecond timestamps around each run

Observed wall-clock results:
- Mean runtime: 0.953592 s
- SD runtime: 0.012490 s
- 95% CI half-width: 0.004469 s
- Min runtime: 0.914810 s
- Max runtime: 0.979712 s

Data file:
- paper/cal8_nxgenesis_benchmark.csv

Notes:
- This model emits repeated non-fatal "** Error" lines in headless mode
   related to missing GUI/CHEMESIS helpers, but simulation stepping completes.
- Error lines were tracked per replicate (111 each) for transparency.

## Second Complex Workload (Current Workspace)
- Executable: genesis/src/nxgenesis
- Model: genesis/Scripts/chemesis/Cal7difshell.g
- Mode: -nosimrc -notty -batch
- Replicates: 30

Observed wall-clock results:
- Mean runtime: 0.668489 s
- SD runtime: 0.006950 s
- 95% CI half-width: 0.002487 s
- Min runtime: 0.659863 s
- Max runtime: 0.680299 s
- Mean error lines per run: 17

Data file:
- paper/cal7difshell_nxgenesis_benchmark.csv

## Figure Suggestions
1. Runtime vs process count
2. Speedup vs process count with ideal linear line
3. Efficiency vs process count
4. Runtime variance (boxplots) across N

## Implemented Plotting Pipeline (Current Workspace)
From the `paper` directory:

python3 plot_cpu_benchmarks.py

This generates:
- table1_runtime_summary.csv
- figures/fig1_mean_runtime_ci.png
- figures/fig2_runtime_boxplot.png
- figures/fig3_headless_error_lines.png

## GPU Attempt Record
The OpenCL/GPU acceleration attempt, executed commands, and failure causes are
documented in:

- paper/gpu_acceleration_attempt.md

Summary:
- GPU hardware is present and OpenCL runtime library is available.
- The bundled `ocl_benchmark.g` script was repaired and now runs in batch mode.
- OpenCL-enabled `nxgenesis` rebuild now succeeds after regenerating stale
   `hines` generated artifacts and patching the `hines` partial-link rule.
- Explicit device-level attribution is now captured with a minimal probe and
   combined benchmark log artifact.

Attribution artifact:
- Probe source: `paper/opencl_probe.c`
- Combined log: `paper/nxgenesis_opencl_benchmark_with_device.log`
- Reported platform/device in current run:
   - platform_name: rusticl
   - platform_vendor: Mesa/X.org
   - device_name: AMD Radeon 890M Graphics (radeonsi, strix1, ACO, DRM 3.64, 6.17.0-121035-tuxedo)
   - device_vendor: AMD
   - device_type: GPU

## Repaired OpenCL-Benchmark Script (Current Workspace)
- Executable: genesis/genesis
- Model script: genesis/Scripts/benchmark/ocl_benchmark.g
- Workload: 100 neurons, 50000 steps
- Replicates: 10
- Timing method: external wall-clock (`date +%s%N`) around each run, because
   script-level `cpu` output is too coarse and reports zero in final summary

Observed wall-clock results:
- Mean runtime: 0.235174 s
- SD runtime: 0.003432 s
- 95% CI half-width: 0.002127 s
- Min runtime: 0.229314 s
- Max runtime: 0.240475 s

Data file:
- paper/ocl_benchmark_100n_50000s_10rep.csv
