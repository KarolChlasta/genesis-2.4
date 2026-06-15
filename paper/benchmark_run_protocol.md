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
