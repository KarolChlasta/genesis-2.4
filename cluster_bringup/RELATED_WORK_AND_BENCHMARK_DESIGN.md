# Related work & benchmark design — GENESIS 2.5 GPU acceleration

Literature-grounded rationale for how to benchmark the GENESIS 2.5 CUDA backend,
and where GENESIS sits among brain simulators. For the paper's Related Work /
Methods and to justify the workload choice. Karol Chlasta, 2026-07-23.

## Two classes of neural simulator (and where GENESIS is)

| Class | Examples | Bottleneck | GPU benefit |
|---|---|---|---|
| Point-neuron (LIF) | NEST, GeNN, NEST GPU | spike communication / memory | moderate |
| **Detailed multicompartment (HH, morphology)** | NEURON, **Arbor**, CoreNEURON, NeuroGPU, **GENESIS** | **compute: Hines tree solve + per-compartment channels** | **large** |

GENESIS 2.5 is a **detailed multicompartment** simulator. That is precisely the
class where GPUs pay off — but only when neurons carry enough compartments and
channels to make the per-step Hines solve substantial.

## What the literature shows

- **Point-neuron scale (GPU):** GeNN simulates up to ~3.5M neurons / ~3×10¹²
  synapses on a high-end GPU; a macaque visual-cortex model of 4.13M neurons /
  24×10⁹ synapses runs GPU-accelerated; real-time achieved at ~100k neurons.
  Network construction <1 s on an A100 (NEST GPU / GeNN build on-device).
  [GeNN vs NEST](https://www.biorxiv.org/content/10.1101/2022.05.13.491646v1.full),
  [procedural connectivity](https://www.biorxiv.org/content/10.1101/2020.04.27.063693v2.full).
- **Detailed multicompartment (GPU) — our class:** Arbor reports up to **200×
  speedup on a single GPU** and ~800× on 4 GPUs; NeuroGPU accelerates
  biophysically detailed multi-compartment neurons on GPUs.
  [Arbor](https://www.researchgate.net/publication/331958503),
  [NeuroGPU](https://pmc.ncbi.nlm.nih.gov/articles/PMC9887806/).
- **Whole-brain scale** is supercomputer territory (e.g. CORTEX on Fugaku) and
  only at reduced detail. [CORTEX/Fugaku](https://arxiv.org/pdf/2406.03762).
- **Runtime/procedural network construction** is an active topic — relevant to the
  GENESIS construction bottleneck below. [arXiv:2306.09855](https://arxiv.org/html/2306.09855v1).

## Why our first benchmark was the wrong workload

`hh1952_squid_multiloop_benchmark.g` uses **single-compartment** neurons. Per step
that is almost no compute (one 1×1 solve + a couple of channel evals per neuron),
so on the A100:
- end-to-end wall-clock was dominated by **model construction** (SLI, O(N) serial:
  ~34 s at N=20000), not compute;
- the per-step compute signal was below measurement noise (subtraction method gave
  noise, even negative values);
- chanmode 4 on the CPU binary is an identity pass-through → not a valid CPU
  reference (must use chanmode 1).

This is a *workload* problem, not a backend problem: there is nothing to
accelerate in a single-compartment model. The CUDA backend itself is validated
(|CPU−CUDA| = 7e-8 V, see `VALIDATION.md`).

## Redesigned benchmark (compute-bound, literature-aligned)

1. **Multicompartment HH cells** — each neuron a cable of C compartments with Na/K
   channels per compartment. Sweep C (e.g. 4, 16, 64, 128) and N. The Hines solve
   then scales with total compartments and the GPU can show Arbor-class speedups.
2. **Fair arms:** CPU = chanmode 1 (real CPU Hines); GPU = chanmode 4 + CUDA
   multiloop. Both integrate; cross-check numerical parity.
3. **Isolate compute from construction:** time only the step loop (fine-grained
   wall-clock around `step`, or two-step-count subtraction). Report compute-only
   speedup (headline) and end-to-end wall-clock (honest) separately.
4. **Report construction cost explicitly** — it is a real GENESIS limitation vs
   NEST GPU/GeNN (<1 s build); frames future work (runtime/procedural build).
5. **Cross-hardware:** A100 (inf03, sm_80) vs A40 (inf02, sm_86); optionally MPI
   (PGENESIS) for the multi-node axis.
6. **Flagship model:** the Wójcik LSM is multicompartmental HH → a real, published-
   class compute-bound model, not a toy.

## "Can we simulate a brain on UMCS?"

A **brain region / cortical microcircuit in full HH detail — yes**; a whole human
brain — no. One A100 handles ~millions of point neurons or ~10⁵–10⁶ detailed
compartments; UMCS adds A40 + 128-core nodes + MPI (PGENESIS). Whole-brain (8.6×10¹⁰
neurons) needs Fugaku/JUWELS-scale machines and reduced detail.
