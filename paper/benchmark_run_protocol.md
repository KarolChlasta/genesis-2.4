# Benchmark and Release Protocol for Proposed GENESIS 2.5

## Objective
Produce reproducible CPU and accelerator benchmark data for a proposed
GENESIS 2.5 release, defined here as GENESIS 2.4 with accelerator support
extended and packaged as the next version.

## Scope
- Serial baseline: nxgenesis
- Parallel runs: nxpgenesis (MPI)
- Accelerator run: OpenCL-enabled nxgenesis on Radeon 890M
- Forward-compatible release target: CUDA backend under the same accelerator
   support umbrella for GENESIS 2.5
- Process counts: 1, 2, 4, 6, 8, 12, 16, 20, 24
- Replicates: 10 per process count after 1 warm-up

## Release Naming Note
For the manuscript and benchmark artifacts in this workspace, "GENESIS 2.5"
refers to the proposed successor to GENESIS 2.4 that retains the existing CPU
and MPI workflows while adding first-class accelerator support. The OpenCL path
is the validated implementation in the current workspace; CUDA is included as a
release target and compatibility goal, not as a validated result from this host.

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
- Accelerator/runtime comparison against the serial CPU baseline where relevant

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

## Accelerator Enablement Record for Proposed GENESIS 2.5
The accelerator enablement log, executed commands, and remaining backend scope
for the proposed GENESIS 2.5 release are documented in:

- paper/gpu_acceleration_attempt.md

Summary:
- GPU hardware is present and the OpenCL runtime path is available.
- The bundled `ocl_benchmark.g` script was repaired and now runs in batch mode.
- OpenCL-enabled `nxgenesis` rebuild now succeeds after regenerating stale
   `hines` generated artifacts and patching the `hines` partial-link rule.
- Explicit device-level attribution is now captured with a minimal probe and
   combined benchmark log artifact.
- CUDA should be described as a planned GENESIS 2.5 backend target; no CUDA
   build or benchmark result is validated in this workspace.

Attribution artifact:
- Probe source: `paper/opencl_probe.c`
- Combined log: `paper/nxgenesis_opencl_benchmark_with_device.log`
- Reported platform/device in current run:
   - platform_name: rusticl
   - platform_vendor: Mesa/X.org
   - device_name: AMD Radeon 890M Graphics (radeonsi, strix1, ACO, DRM 3.64, 6.17.0-121035-tuxedo)
   - device_vendor: AMD
   - device_type: GPU

## OpenCL Benchmark Baseline for Proposed GENESIS 2.5
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

## Live Development Log
- 2026-06-16: OpenCL probe reconfirmed device attribution on this host:
   platform `rusticl` (Mesa/X.org), device `AMD Radeon 890M Graphics` (GPU).
- 2026-06-16: Direct benchmark run with `nxgenesis` for 100 neurons and 50,000
   steps completed with external wall-clock `0.236620 s`.
- 2026-06-16: Additional 10-replicate OpenCL datasets collected (1 warm-up +
   10 measured runs each):
   - `paper/ocl_benchmark_500n_50000s_10rep.csv`: mean 0.320949 s, SD 0.008065 s,
      95% CI 0.004999 s, min 0.314361 s, max 0.341359 s.
   - `paper/ocl_benchmark_1000n_50000s_10rep.csv`: mean 0.407377 s,
      SD 0.009007 s, 95% CI 0.005582 s, min 0.395060 s, max 0.425419 s.
- 2026-06-16: Larger direct scale checks completed successfully:
   - 5,000 neurons, 50,000 steps: wall-clock 3.020149 s
   - 10,000 neurons, 50,000 steps: wall-clock 9.178209 s
- 2026-06-16: Existing `genesis/Scripts/benchmark/run_benchmark.sh` is still
   unstable for large sweeps in this environment (segmentation violation seen in
   one batch run); direct per-size invocations remain the trusted method.
- 2026-06-16: Three new benchmark scripts prepared for GENESIS 2.5 proposal:
   - `genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g`
   - `genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g`
   - `genesis/Scripts/benchmark/region_proxy_microcircuit_benchmark.g`
- 2026-06-16: Smoke-test status on `nxgenesis -nosimrc -notty -batch`:
   - mesoscale: clean start/run (`ERR=0`) for 200 neurons, 2000 steps
   - biophysical: clean start/run (`ERR=0`) for 64 neurons, 2000 steps
   - region-proxy: clean start/run (`ERR=0`) for 20000 steps (default grid)
   Note: script-reported `cpu` deltas are still too coarse for publication timing;
   external wall-clock remains the authoritative timing method.
- 2026-06-16: Full benchmark campaign executed (1 warm-up + 10 measured
   replicates each) for all three new scripts on both CPU (`genesis/genesis`) and
   GPU/OpenCL (`genesis/src/nxgenesis`) with zero GENESIS runtime errors in all
   measured runs (`error_lines=0`, `exit_code=0`).

   Raw data:
   - `paper/genesis25_three_benchmarks_10rep.csv`

   Summary statistics:
   - `paper/genesis25_three_benchmarks_summary.csv`

   Mean wall-clock comparison:
   - `mesoscale_sparse_benchmark` (`N=10000`, `steps=20000`)
      - CPU: 4.373315 s
      - GPU: 4.426878 s
      - speedup (CPU/GPU): 0.987901
   - `biophysical_cellscale_benchmark` (`N=1000`, `steps=20000`)
      - CPU: 0.292831 s
      - GPU: 0.309391 s
      - speedup (CPU/GPU): 0.946475
   - `region_proxy_microcircuit_benchmark` (`steps=20000`, default grid)
      - CPU: 0.240748 s
      - GPU: 0.242243 s
      - speedup (CPU/GPU): 0.993829

   Interpretation note:
   - For these specific parameterizations, OpenCL did not yet deliver wall-clock
      speedup over the current CPU binary. Next optimization passes should focus
      on larger workloads, OpenCL kernel/dispatch profiling, and reducing model
      construction overhead relative to stepping cost.

- 2026-06-16: Additional larger-model GPU campaign completed (1 warm-up + 5
   measured replicates per configuration) using `genesis/src/nxgenesis`, with
   all runs successful (`mean_error_lines=0`, `fail_count=0`).

   Raw data:
   - `paper/genesis25_gpu_large_models_5rep.csv`

   Summary statistics:
   - `paper/genesis25_gpu_large_models_5rep_summary.csv`

   Means (GPU only):
   - `mesoscale_sparse_benchmark`
      - `N20000_S20000`: 13.244784 s
      - `N30000_S20000`: 26.929601 s
   - `biophysical_cellscale_benchmark`
      - `N2000_S20000`: 0.391455 s
      - `N4000_S20000`: 0.777843 s
   - `region_proxy_microcircuit_benchmark`
      - `EX120x120_INH60x60_S20000`: 0.274024 s
      - `EX160x160_INH80x80_S20000`: 0.310092 s

   Figure artifacts for manuscript:
   - `paper/figures/fig4_gpu_large_runtime_ci.png`
   - `paper/figures/fig5_gpu_large_scaling_trend.png`
