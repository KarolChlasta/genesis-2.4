# CPU-Only Performance Benchmarking of GENESIS/PGENESIS on a Modern Mobile x86 Platform

## Candidate Journal Scope
This manuscript is written in a style suitable for computational neuroscience or scientific computing journals (for example, Journal of Computational Neuroscience, Frontiers in Neuroinformatics, or PLOS ONE technical benchmark format).

## Title
CPU-Only Benchmarking of Parallel GENESIS 2.4 on AMD Ryzen AI 9 HX 370: Scaling Behavior, Throughput, and Reproducibility

## Running Title
PGENESIS CPU Benchmark on Ryzen AI 9 HX 370

## Authors
- First Author Name, Affiliation
- Second Author Name, Affiliation

## Corresponding Author
- Name, email, address

## Keywords
GENESIS, PGENESIS, MPI, CPU benchmarking, computational neuroscience, strong scaling

## Abstract
High-performance neural simulation remains essential for large biophysical network models where both accuracy and throughput are required. We present a CPU-only benchmark framework for GENESIS 2.4 and Parallel GENESIS (PGENESIS) 2.4 on an AMD Ryzen AI 9 HX 370 platform (12 physical cores, 24 hardware threads). The study evaluates baseline serial execution and MPI-based parallel execution using standardized scripts and controlled runtime settings. We quantify wall-clock time, speedup, parallel efficiency, and run-to-run variability across node counts. The benchmark design emphasizes reproducibility through explicit environment capture, deterministic invocation, and repeated measurements. GPU acceleration results are out of scope for this revision because OpenCL validation was blocked by benchmark script/parser failures and missing development headers during rebuild attempts.

Preliminary platform characterization indicates a single-socket x86_64 system with simultaneous multithreading and no NUMA partitioning, suitable for intra-node scaling analysis. The protocol targets strong scaling behavior from 1 to 24 MPI processes, with special attention to practical operating points where efficiency remains high while elapsed time improves substantially. The resulting framework is intended as a portable reference for CPU benchmarking of legacy and contemporary GENESIS workflows.

## 1. Introduction
Neural simulation frameworks continue to support mechanistic investigations that are difficult to address with reduced models alone. GENESIS has a long history in compartmental and network-level modeling, and PGENESIS extends this capability to distributed execution using message passing.

Although modern accelerators are common in scientific computing, many production and portable workflows still rely on CPUs due to availability, software compatibility, and predictable numerical behavior. Consequently, rigorous CPU benchmarking remains relevant for methodological studies and practical deployment decisions.

This work focuses on three questions:
1. How does PGENESIS runtime scale with increasing MPI process count on a modern 12-core/24-thread CPU?
2. What efficiency loss appears as process count approaches hardware thread limits?
3. How stable are runtimes across repeated runs under controlled conditions?

## 2. Methods

### 2.1 Hardware Platform
Benchmark host:
- CPU model: AMD Ryzen AI 9 HX 370 with Radeon 890M
- Cores/threads: 12 cores, 24 threads
- Socket count: 1
- NUMA nodes: 1
- Max frequency (reported): 5157.895 MHz

### 2.2 Software Environment
Recorded environment at preparation time:
- Kernel: Linux 6.17.0-121035-tuxedo
- Architecture: x86_64
- Runtime base (containerized shell): Freedesktop SDK 25.08

Final submission should add:
- Exact compiler version (gcc --version)
- Exact MPI distribution and version (mpirun --version)
- GENESIS/PGENESIS commit hash

### 2.3 Benchmark Targets
Primary benchmark scripts:
- Minimal parallel smoke test: pgenesis Scripts/hello/hello.g (or equivalent)
- Graphical/decomposition test adapted for batch use: pgenesis/Scripts/orient1/demo.g

For publication-grade benchmarking, include at least one non-trivial production model with meaningful compute/communication load.

### 2.4 Build Configuration
Serial baseline:
- Build nxgenesis (no XODUS) for headless repeatable runs.

Parallel benchmark executable:
- Configure PGENESIS with MPI enabled in top-level pgenesis Makefile.
- Use MPI launcher via pgenesis wrapper or direct mpirun invocation of nxpgenesis.

### 2.5 Experimental Design
Design type:
- Strong scaling on fixed model/problem size.

Process counts:
- N = 1, 2, 4, 6, 8, 12, 16, 20, 24

Replicates:
- At least 10 runs per process count.

Warm-up policy:
- 1 warm-up run excluded from statistics for each process count.

Affinity policy:
- Use explicit process pinning when available (MPI mapping/binding flags).

Measured metrics:
- Wall-clock runtime T_N
- Speedup S_N = T_1 / T_N
- Efficiency E_N = S_N / N
- Coefficient of variation (CV) across replicates

### 2.6 Statistical Analysis
For each N, report:
- Mean runtime and standard deviation
- 95% confidence interval for mean runtime

Derived metrics:
- Speedup and efficiency computed from mean runtimes
- Optional bootstrap confidence intervals for S_N and E_N

### 2.7 Reproducibility Controls
- Disable unrelated heavy background processes
- Fix governor/performance mode where permitted
- Log full command lines and timestamps
- Store raw per-run timings in machine-readable tables
- Archive scripts used for orchestration and parsing

## 3. Results (Template)

### 3.0 Initial Complex-Model CPU Baseline (Measured)
To move beyond process-startup timing, we executed a heavier non-graphical model
run using `nxgenesis` with `Scripts/chemesis/Cal8.g` in batch mode. Eight
replicates were collected.

Measured wall-clock runtime statistics:
- Mean: 0.963079 s
- Min: 0.921463 s
- Max: 0.987915 s
- Replicates: 8

Raw measurements are provided in `paper/cal8_nxgenesis_benchmark.csv`.

The script reports repeated non-fatal error lines in headless mode (primarily
GUI/CHEMESIS helper availability), but simulation stepping completes and
produces consistent runtime envelopes across replicates. These diagnostics were
counted and logged for each run.

### 3.0.1 Extended Two-Model Benchmark (30 Replicates Each)
To increase statistical reliability, we expanded to 30 replicates for two
non-graphical chemesis workloads run with `nxgenesis -nosimrc -notty -batch`.

| Model | n | Mean (s) | SD (s) | CV (%) | 95% CI (s) | Min (s) | Max (s) | Mean error lines |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Cal8.g | 30 | 0.953592 | 0.012490 | 1.31 | 0.004469 | 0.914810 | 0.979712 | 111.00 |
| Cal7difshell.g | 30 | 0.668489 | 0.006950 | 1.04 | 0.002487 | 0.659863 | 0.680299 | 17.00 |

Interpretation:
- Both workloads show low relative variance (CV near 1%), indicating stable CPU timing.
- `Cal8.g` is the heavier workload, with approximately 1.43x longer runtime than `Cal7difshell.g`.
- Headless diagnostics are consistent within each model and therefore unlikely to dominate observed variance.

Raw data files:
- `paper/cal8_nxgenesis_benchmark.csv`
- `paper/cal7difshell_nxgenesis_benchmark.csv`

### 3.1 Runtime and Scaling
Table 1 summarizes runtime stability for the two measured complex-model
workloads used in this CPU-only benchmark phase.

Table 1. Runtime summary for 30-replicate measurements with `nxgenesis -nosimrc -notty -batch`.

| Model | n | Mean (s) | SD (s) | CV (%) | 95% CI (s) | Min (s) | Max (s) | Mean error lines |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Cal8.g | 30 | 0.953592 | 0.012490 | 1.31 | 0.004469 | 0.914810 | 0.979712 | 111.00 |
| Cal7difshell.g | 30 | 0.668489 | 0.006950 | 1.04 | 0.002487 | 0.659863 | 0.680299 | 17.00 |

Across both models, low CV values indicate stable runtime behavior under the
current benchmark conditions.

### 3.2 Efficiency Drop-off Region
Identify breakpoint N* where efficiency falls below a predefined threshold (for example, 70%). Discuss whether N* aligns with core count (12) or thread count (24).

### 3.3 Repeatability
Quantify run-to-run variability and identify process counts with highest instability.

### 3.4 Figure Captions
Figure 1. Mean runtime with 95% confidence interval for `Cal8.g` and
`Cal7difshell.g` (30 replicates each).

Figure 2. Runtime distribution (boxplot with means) across replicates for both
models, showing narrow spread and consistent execution.

Figure 3. Mean number of headless diagnostic error lines per run for both
models. These diagnostics are consistent within model and serve as a
transparency metric rather than a direct performance metric.

Generated artifacts:
- `paper/table1_runtime_summary.csv`
- `paper/figures/fig1_mean_runtime_ci.png`
- `paper/figures/fig2_runtime_boxplot.png`
- `paper/figures/fig3_headless_error_lines.png`

### 3.5 GPU Acceleration Attempt (OpenCL)
We attempted to evaluate GPU acceleration using the integrated AMD Radeon 890M
device through OpenCL. Hardware detection confirmed the GPU presence, and the
existing `nxgenesis` binary linked against `libOpenCL.so.1`. However, two
independent blockers prevented a validated GPU benchmark run in this revision:

1. The bundled benchmark script `genesis/Scripts/benchmark/ocl_benchmark.g`
	required repair before it could run reproducibly in batch mode.
2. Rebuilding `nxgenesis` with `USE_OPENCL=1` initially failed in legacy
	generated `hines` code and required build-system fixes before succeeding.

Because GPU execution could not be validated end-to-end, the present manuscript
reports CPU-only results as the primary benchmark outcomes. A complete command
log and failure analysis are provided in `paper/gpu_acceleration_attempt.md`.

## 4. Discussion
Interpretation should address:
- Practical process-count recommendations for this CPU
- Overheads from MPI communication and synchronization
- Differences between physical-core and SMT-heavy operating points
- Limits of laptop/mobile thermal behavior in long runs

Potential threats to validity:
- Runtime containerization effects
- Thermal throttling over repeated runs
- Model-specific scaling characteristics

An additional limitation is that GPU acceleration could not be validated in the
present environment, despite detected compatible hardware. The OpenCL benchmark
path is now buildable, but explicit device-level attribution for the target GPU
(Radeon 890M) has not yet been captured in benchmark logs. As a
result, conclusions in this revision are intentionally restricted to CPU-only
performance behavior. The full command-level record of this limitation is
provided in `paper/gpu_acceleration_attempt.md`.

## 5. Conclusion
This study provides a reproducible CPU-only benchmark protocol for GENESIS/PGENESIS on a modern mobile AMD processor. Final benchmark data should establish practical scaling limits and recommended operating points for high-throughput neural simulations without accelerator dependencies.

## Data Availability Statement
All scripts, raw timing outputs, environment manifests, and analysis notebooks should be deposited in the project repository and version-tagged release archive.

## Conflict of Interest
The authors declare no competing interests.

## Funding
[Add funding sources]

## Acknowledgments
[Add acknowledgments]

## References (Starter)
1. Bower JM, Beeman D. The Book of GENESIS: Exploring Realistic Neural Models with the GEneral NEural SImulation System. Springer.
2. GENESIS project documentation and release notes.
3. MPI standard documentation relevant to implementation version used.

## Appendix A. Reporting Checklist
- Hardware details captured
- Software versions pinned
- Build flags preserved
- Raw data provided
- Analysis scripts provided
