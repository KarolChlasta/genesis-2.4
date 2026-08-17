# Reproducing the paper's results

One command:

```sh
sh reproduce/run_all.sh --quick        # ~15 min, the accelerator claims
sh reproduce/run_all.sh                # ~90 min, adds the full sweeps
sh reproduce/run_all.sh --with-neuron  # adds the cross-simulator comparison
```

It builds GENESIS, checks the accelerator against the CPU solver, measures the
speedups, regenerates the figures from what it just measured, and prints each
published number beside yours with a verdict:

```
claim                     table            published    measured    delta  verdict
correctness_fp32          text                 1e-07       7e-08  7.0e-08  ok
ksweep_k5000              tab:mcksweep            57        55.2      -3%  ok
```

## What you need

Linux x86_64, GCC, GNU make, a CUDA 12.x toolkit and an NVIDIA GPU. Set
`CUDA_HOME` if `nvcc` is not on your `PATH`. `--with-neuron` also wants NEURON
9.x (`pip install neuron`); the Arbor arm additionally needs an Arbor built with
CUDA, since the published wheels are CPU-only.

Nothing here needs root, a scheduler, or the UMCS cluster.

## What is checked, and what merely follows

**The numbers are the claims**, so those are what `compare.py` checks against
`expected.csv`. **The figures follow from them** -- the plotting scripts under
`paper/scripts/` read the CSVs this pack writes, so you get the paper's figures
drawn from your own hardware rather than ours. That is a stronger check than
matching numbers alone, because it shows the same shape, not just the same
endpoint.

## Your numbers will differ, and that is expected

Absolute timings track the host CPU, the card model, and how warm the card is.
Tolerances in `expected.csv` are set accordingly, and what should reproduce is
the shape of each result: which arm wins, and roughly by how much.

Three things move results enough to be worth knowing about, all of them found
the hard way while producing this paper:

**A GPU shared with another job.** A foreign process on the card once raised
every GPU figure by ~30% while leaving the CPU arm untouched, and the speedup
curve stayed smooth and entirely plausible. `run_all.sh` warns if the card is
already in use; heed it.

**A cold card.** The first run after the GPU has been idle is 1.2-1.8x slower
than a warm one. The pack takes several replicates for this reason. Do not
compare one short run against a published campaign.

**`GENESIS_OCL_TREE_MAX_NCOMPTS`.** Above 20,000 compartments the batched tree
solver otherwise declines the model and falls back to per-step dispatch, which
is a different code path and looks like a 3-7x GPU slowdown. `run_all.sh` sets
it; if you run the benchmarks by hand, set it too.

## If a claim lands outside tolerance

Check `nvidia-smi` for other jobs, re-run, and compare the *ratios* rather than
the absolute seconds. A number outside tolerance on different hardware is
usually hardware. If the ordering itself inverts -- the CPU arm beating the GPU
at large N, say -- that is worth reporting to karol@chlasta.pl.

## Layout

| path | what it is |
|---|---|
| `run_all.sh` | the entry point |
| `stages/` | one script per claim group, runnable on their own |
| `expected.csv` | published values and tolerances |
| `compare.py` | measured against published, with a verdict |
| `results/` | written by the run: CSVs, logs, `summary.csv` |

The underlying benchmarks live in `cluster_bringup/`, and the cross-simulator
harness, including how the NEURON and Arbor models were matched to the GENESIS
one, in `cluster_bringup/coreneuron/README.md`.
