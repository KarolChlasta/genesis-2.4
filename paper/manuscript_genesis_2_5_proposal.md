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
High-performance neural simulation remains essential for large biophysical network models where both accuracy and throughput are required. We present a benchmark and release proposal for GENESIS 2.5, defined here as an accelerator-enabled successor to GENESIS 2.4 and Parallel GENESIS (PGENESIS) 2.4 on an AMD Ryzen AI 9 HX 370 platform (12 physical cores, 24 hardware threads) with integrated Radeon 890M graphics. The study combines validated CPU baseline measurements, MPI-oriented benchmarking guidance, and a repaired OpenCL execution path whose GPU kernel dispatch is now confirmed directly via device-side profiling rather than inferred from a successful build. We quantify wall-clock time, speedup, parallel efficiency, and run-to-run variability for CPU workloads, and we report OpenCL channel-update kernel timing with explicit device attribution; the kernel itself is confirmed correct and fast, but no end-to-end GPU speedup over CPU execution is yet demonstrated, since host-side dispatch overhead and the still-CPU-only Hines solve dominate total step time. CUDA support is proposed as a companion backend target for GENESIS 2.5, but is not validated in the current workspace.

Preliminary platform characterization indicates a single-socket x86_64 system with simultaneous multithreading and no NUMA partitioning, suitable for intra-node scaling analysis. The protocol targets strong scaling behavior from 1 to 24 MPI processes, with special attention to practical operating points where efficiency remains high while elapsed time improves substantially. The resulting framework is intended as a portable reference for validating both legacy CPU workflows and the proposed accelerator-aware GENESIS 2.5 release line.

## 1. Introduction
Neural simulation frameworks continue to support mechanistic investigations that are difficult to address with reduced models alone. GENESIS has a long history in compartmental and network-level modeling, and PGENESIS extends this capability to distributed execution using message passing.

Although modern accelerators are common in scientific computing, many production and portable workflows still rely on CPUs due to availability, software compatibility, and predictable numerical behavior. Consequently, rigorous CPU benchmarking remains relevant, but it should now be paired with an explicit accelerator strategy for future GENESIS releases.

In this manuscript, we use the name GENESIS 2.5 for a proposed version based on
GENESIS 2.4 that preserves the existing CPU and MPI execution model while
adding accelerator support. The current workspace confirms that the OpenCL
channel-update kernel executes correctly on real Hodgkin-Huxley channel
workloads, profiles its cost directly, and establishes the benchmark/reporting
structure -- including the verification step needed to avoid mistaking a
non-dispatching run for a GPU result -- that a CUDA backend should follow when
added under the same release umbrella.

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
- Ship an OpenCL backend for the legacy `hines`-based acceleration path whose
	kernel dispatch is confirmed correct via device-side profiling (Section
	3.5), even though end-to-end speedup over CPU execution remains future
	work.
- Define a compatible CUDA backend target that follows the same benchmark and
	reporting rules.
- Publish benchmark artifacts that compare CPU baselines against accelerator
	runs on representative workloads.

Release criteria for this proposal:
- Reproducible CPU benchmark baselines remain stable.
- OpenCL builds cleanly with documented flags, and a benchmark exercising a
	real `chanmode=4`/`calcmode=1` `hsolve` with attached ion channels
	completes end-to-end while emitting a non-empty `OCL PROFILING SUMMARY`
	confirming the channel-update kernel actually dispatched for every
	profiled step. A clean build and a non-crashing run are not, by
	themselves, sufficient -- an earlier draft of this proposal treated them
	as such and reported a CPU-only result as a validated OpenCL benchmark
	(Section 3.5); that criterion gap is closed here.
- Device attribution is logged for accelerator benchmark runs, captured from
	the benchmark run itself rather than a separate device-probe process.
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

**Binary choice and OpenCL dispatch are independent conditions, and both must
be checked.** Two failure modes were found and corrected during this work and
must be guarded against in any future comparison:

1. `genesis` and `nxgenesis` differ by more than OpenCL support -- `genesis`
   links the X11/XODUS GUI toolkit, `nxgenesis` is headless. Linking X11 alone
   was found to add a real, reproducible per-element-creation overhead during
   network construction (scaling with element count, concentrated in kernel
   /system CPU time) that is unrelated to GPU acceleration and can produce
   misleading "speedup" ratios of several-fold on benchmarks dominated by
   construction rather than simulation time. Full investigation:
   `paper/x11_binary_confound_investigation.md`. A clean comparison must use
   the *same* binary for both arms (e.g. headless `nxgenesis` built once with
   and once without `USE_OPENCL=1`).
2. Invoking `nxgenesis` on a script that creates no `hsolve` element, or an
   `hsolve` with `chanmode=4`/`5` but no attached ion channels, never
   dispatches to the OpenCL channel-update kernel regardless of how the
   binary was built -- the call silently falls back to (or never leaves) the
   CPU path. This was the root cause of an earlier, retracted result in
   Section 3.5.

Accordingly, a run is only counted as a GPU/OpenCL measurement in this paper
if it produces a non-empty `OCL PROFILING SUMMARY` (`steps profiled` matching
the expected step count) at exit, in addition to using the headless binary.
Wall-clock time alone, or the presence of OpenCL symbols in the binary, is
not sufficient evidence of GPU dispatch.

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
- Build `nxgenesis` with `USE_OPENCL=1` for the OpenCL path whose kernel
	dispatch is confirmed via profiling (Section 3.5).
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

**Retraction of an earlier result.** An earlier draft of this section reported
10-replicate wall-clock timings for `genesis/Scripts/benchmark/ocl_benchmark.g`
(mean 0.235 s at 100 neurons) as a "validated OpenCL benchmark," supported by a
device-attribution log showing the AMD Radeon 890M detected via `rusticl`. On
inspection, the cited execution logs (`paper/nxgenesis_opencl_benchmark_with_device.log`,
`paper/nxgenesis_opencl_benchmark_device_log.txt`) show no `OCL` initialization
or kernel-dispatch output at all, and the reported wall-clock times (~25-31 ms
of total CPU time for 50,000 steps) are consistent with the script's network,
which builds only passive RC compartments with `chanmode=4` but zero ion
channels. An `hsolve` in that configuration has no channel state to solve
(`givals` is empty) and is silently treated as a passive solve, so the GPU
channel-update kernel is never invoked. The device-attribution log came from a
separate, disconnected OpenCL device probe, not from the benchmark run itself.
The build succeeding and the script completing without error were
insufficient evidence that the OpenCL path had actually executed; the result
is withdrawn and replaced below.

**Corrected methodology.** We built a new benchmark,
`genesis/Scripts/benchmark/ocl_hh_benchmark.g`, that creates a single `hsolve`
(`chanmode=4`, `calcmode=1`) covering N Hodgkin-Huxley neurons with real
`tabchannel` Na (X^3 Y^1) and K (X^4) gating tables, the minimum configuration
under which `hsolve` actually allocates per-channel state and dispatches to
the OpenCL channel-update kernel. Fixing this benchmark also surfaced and
resolved a GPU page fault in the legacy OpenCL kernel, caused by the
per-compartment boundary markers in the flat instruction array (`COMPT_OP`,
`FCOMPT_OP`, `LCOMPT_OP`) being only partially checked; both the kernel and
its host-side index builder now use the same boundary test as the CPU
interpreter. GPU dispatch was confirmed directly rather than inferred: the
OpenCL command queue was built with `CL_QUEUE_PROFILING_ENABLE`, and each
simulation step's kernel execution time and total `ocl_chip_update` wall time
(upload, dispatch, download) were accumulated and reported at exit.

Table 2 reports kernel and host-path timing for N = 100-2000 neurons, dt = 50
us, 5000 profiled steps each, on the same AMD Radeon 890M via `rusticl`
(Mesa/X.org) device confirmed in `paper/profiling_runs/ocl_profile_N100.txt`
(device line: `OCL: urzadzenie: gfx1150`; readiness line:
`OCL: gotowy (100 kompartmentow, 1100 chips)`).

Table 2. OpenCL channel-update kernel profiling, `ocl_hh_benchmark.g`, 5000
steps per N.

| N neurons | kernel time/step | `ocl_chip_update` wall/step | GPU active fraction | total step time |
|---:|---:|---:|---:|---:|
| 100  | 4.96 us  | 49.0 us  | 10.13% | 61.3 us |
| 500  | 6.42 us  | 79.4 us  | 8.09%  | 124.2 us |
| 1000 | 10.52 us | 116.9 us | 9.00%  | 209.9 us |
| 2000 | 13.44 us | 134.5 us | 9.99%  | 323.1 us |

Raw logs: `paper/profiling_runs/ocl_profile_N{100,500,1000,2000}.txt`.

**Interpretation.** The GPU channel-update kernel itself is genuinely cheap
(single-digit to low-double-digit microseconds per step) and is confirmed to
execute correctly across all tested sizes with no crashes. However, the
kernel is only 8-10% of `ocl_chip_update`'s own wall time; the remaining
90%+ is host-side dispatch and transfer overhead (two buffer uploads, one
kernel enqueue, two buffer downloads, fully serialized once per simulation
step). `ocl_chip_update` is in turn only the channel-update fraction of the
total step time reported in the rightmost column -- the Hines tridiagonal
solve (forward elimination and back substitution) still runs entirely on the
CPU and is untouched by this kernel. Consequently, this benchmark
demonstrates that the OpenCL path is functionally correct and exercised, but
does **not** demonstrate an end-to-end wall-clock speedup over CPU execution,
and no such speedup is claimed. Realizing one would require batching kernel
dispatch and buffer transfers across multiple steps and/or moving the
tridiagonal solve itself onto the accelerator, as discussed in
`paper/PLAN_gpu_rewrite.md`.

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
equivalence across accelerator backends, or any CUDA implementation status.

More importantly, the single workflow validated here demonstrates only that
the OpenCL channel-update kernel dispatches and executes correctly -- not an
end-to-end wall-clock speedup over CPU execution. An earlier version of this
workflow's result (Section 3.5) was itself a CPU-only artifact mistaken for a
GPU measurement, because a clean build and a non-crashing run were treated as
sufficient evidence of GPU dispatch; that error was caught only by inspecting
the run's own logs for explicit kernel-initialization output, and it
motivated the verification requirement introduced in Section 2.2.1. Given the
profiled kernel time is a small fraction of total step time (Section 3.5),
and that the campaign comparing `genesis` against `nxgenesis` directly was
separately found to be confounded by an unrelated build difference (X11
linkage; see `paper/x11_binary_confound_investigation.md`), readers should not
infer any GPU-vs-CPU speedup from this manuscript -- only that a GPU
execution path exists, is now correctly verifiable, and is currently
dispatch-overhead-bound rather than compute-bound. The full command-level
record and remaining scope are provided in `paper/gpu_acceleration_attempt.md`.

## 5. Conclusion
This study provides a reproducible benchmark and release proposal for GENESIS
2.5 on a modern mobile AMD platform. The present workspace establishes stable
CPU baselines, an accelerator-aware reporting protocol that requires
device-side confirmation of GPU kernel dispatch rather than inferring it from
a successful build, and an OpenCL channel-update kernel confirmed to execute
correctly and efficiently in isolation. End-to-end GPU acceleration has not
yet been demonstrated -- the confirmed kernel cost is dominated by per-step
host dispatch overhead and by the Hines solve, which remains CPU-only -- so
this workspace anchors the verification methodology and the diagnosis of
what a broader OpenCL/CUDA-enabled successor to GENESIS 2.4 would need to
address, rather than a demonstrated speedup.

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
