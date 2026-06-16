# Toward GENESIS 2.5: CPU and Accelerator Enablement of GENESIS 2.4 on a Modern Mobile x86 Platform

## Candidate Journal Scope
This manuscript is written in a style suitable for computational neuroscience or scientific computing journals (for example, Journal of Computational Neuroscience, Frontiers in Neuroinformatics, or PLOS ONE technical benchmark format).

## Title
Toward GENESIS 2.5: Extending GENESIS 2.4 with OpenCL/CUDA Accelerator Support on AMD Ryzen AI 9 HX 370

## Running Title
GENESIS 2.5 Accelerator Proposal

## Authors
- First Author Name, Affiliation
- Second Author Name, Affiliation

## Corresponding Author
- Name, email, address

## Keywords
GENESIS, PGENESIS, OpenCL, CUDA, GPU benchmarking, CPU benchmarking, strong scaling

## Abstract
High-performance neural simulation remains essential for large biophysical network models where both accuracy and throughput are required. We present a benchmark and release proposal for GENESIS 2.5, defined here as an accelerator-enabled successor to GENESIS 2.4 and Parallel GENESIS (PGENESIS) 2.4 on an AMD Ryzen AI 9 HX 370 platform (12 physical cores, 24 hardware threads) with integrated Radeon 890M graphics. The study combines validated CPU baseline measurements, MPI-oriented benchmarking guidance, and a repaired OpenCL execution path that now builds and runs end-to-end. We quantify wall-clock time, speedup, parallel efficiency, and run-to-run variability for CPU workloads, and we document an initial OpenCL benchmark with explicit device attribution. CUDA support is proposed as a companion backend target for GENESIS 2.5, but is not validated in the current workspace.

Preliminary platform characterization indicates a single-socket x86_64 system with simultaneous multithreading and no NUMA partitioning, suitable for intra-node scaling analysis. The protocol targets strong scaling behavior from 1 to 24 MPI processes, with special attention to practical operating points where efficiency remains high while elapsed time improves substantially. The resulting framework is intended as a portable reference for validating both legacy CPU workflows and the proposed accelerator-aware GENESIS 2.5 release line.

## 1. Introduction
Neural simulation frameworks continue to support mechanistic investigations that are difficult to address with reduced models alone. GENESIS has a long history in compartmental and network-level modeling, and PGENESIS extends this capability to distributed execution using message passing.

Although modern accelerators are common in scientific computing, many production and portable workflows still rely on CPUs due to availability, software compatibility, and predictable numerical behavior. Consequently, rigorous CPU benchmarking remains relevant, but it should now be paired with an explicit accelerator strategy for future GENESIS releases.

In this manuscript, we use the name GENESIS 2.5 for a proposed version based on
GENESIS 2.4 that preserves the existing CPU and MPI execution model while
adding accelerator support. The current workspace validates the OpenCL path and
establishes the benchmark/reporting structure that a CUDA backend should follow
when added under the same release umbrella.

This work focuses on three questions:
1. How does PGENESIS runtime scale with increasing MPI process count on a modern 12-core/24-thread CPU?
2. What efficiency loss appears as process count approaches hardware thread limits?
3. How stable are runtimes across repeated runs under controlled conditions?

## 1.1 GENESIS 2.5 Proposal
The proposed GENESIS 2.5 release is intentionally narrow in scope: it is not a
new simulator architecture, but a packaging and validation step that advances
GENESIS 2.4 into an accelerator-aware release line.

Core release goals:
- Preserve existing serial `genesis`, headless `nxgenesis`, and MPI-oriented
	PGENESIS workflows.
- Ship a validated OpenCL backend for the legacy `hines`-based acceleration
	path.
- Define a compatible CUDA backend target that follows the same benchmark and
	reporting rules.
- Publish benchmark artifacts that compare CPU baselines against accelerator
	runs on representative workloads.

Release criteria for this proposal:
- Reproducible CPU benchmark baselines remain stable.
- OpenCL builds cleanly with documented flags and executes the repaired
	benchmark script end-to-end.
- Device attribution is logged for accelerator benchmark runs.
- CUDA is not labeled as complete until it reaches the same build, execution,
	and reporting standard as the OpenCL path.

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
- Kernel: Linux 6.17.0
- Architecture: x86_64
- OpenCL platform: rusticl (Mesa/X.org)
- OpenCL device: AMD Radeon 890M Graphics (GPU)

### 2.2.1 CPU-vs-GPU Comparison Semantics
To avoid ambiguity in acceleration claims, CPU and GPU runs in this paper are
paired on the same benchmark scripts and size grid, with the same step count and
replicate policy.

- CPU baseline in this comparison: serial `genesis` batch execution (single
	process, no MPI launcher).
- GPU baseline in this comparison: serial `nxgenesis` batch execution using
	OpenCL offload on AMD Radeon 890M.
- MPI (`nxpgenesis`) is treated as a separate scaling dimension and is not
	combined with OpenCL acceleration claims in the same speedup figure.

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

Accelerator-enabled release target:
- Build `nxgenesis` with `USE_OPENCL=1` for the validated OpenCL path.
- Preserve the `hines` build fixes required for accelerator compilation.
- Treat CUDA as a planned backend for GENESIS 2.5, to be integrated behind the
	same accelerator-facing interfaces and benchmark protocol.

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
workloads used in the baseline CPU benchmark phase.

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

### 3.5 Accelerator Enablement for Proposed GENESIS 2.5
We evaluated the integrated AMD Radeon 890M through OpenCL as the validated
accelerator path for the proposed GENESIS 2.5 release. Hardware detection
confirmed GPU presence, the benchmark script `genesis/Scripts/benchmark/ocl_benchmark.g`
was repaired for reproducible batch execution, and rebuilding `nxgenesis` with
`USE_OPENCL=1` now succeeds after targeted fixes in the legacy `hines` build
path.

The resulting OpenCL benchmark produced the following 10-replicate runtime
statistics for the 100-neuron, 50,000-step workload:

| Workload | n | Mean (s) | SD (s) | 95% CI (s) | Min (s) | Max (s) |
|---|---:|---:|---:|---:|---:|---:|
| ocl_benchmark.g | 10 | 0.235174 | 0.003432 | 0.002127 | 0.229314 | 0.240475 |

Explicit platform/device attribution was captured in
`paper/nxgenesis_opencl_benchmark_with_device.log`, identifying the platform as
`rusticl` (Mesa/X.org) and the device as `AMD Radeon 890M Graphics`.

CUDA support should be presented as planned future work within the GENESIS 2.5
release concept. No CUDA build, kernel path, or benchmark result is validated
in the current workspace, so the accelerator results reported here are limited
to OpenCL.

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

An additional limitation is that accelerator validation is presently limited to
one OpenCL-enabled workflow and one host/device combination. The current
results do not establish cross-vendor portability, kernel-level numerical
equivalence across accelerator backends, or any CUDA implementation status. The
full command-level record and remaining scope are provided in
`paper/gpu_acceleration_attempt.md`.

## 5. Conclusion
This study provides a reproducible benchmark and release proposal for GENESIS
2.5 on a modern mobile AMD platform. The present workspace establishes stable
CPU baselines, an accelerator-aware reporting protocol, and a validated OpenCL
execution path that can anchor a broader OpenCL/CUDA-enabled successor to
GENESIS 2.4.

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
