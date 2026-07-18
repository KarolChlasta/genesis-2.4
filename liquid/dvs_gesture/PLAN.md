# DVS128 Gesture on Wójcik's PGENESIS LSM — implementation plan

Turn the LSM from a spike-dump demo into a functioning Liquid State Machine that
**classifies a well-known event-based benchmark** (IBM DVS128 Gesture, 11 hand
gestures from a 128×128 event camera), by adding the missing pieces: a real
spatiotemporal input, extracted liquid states, and a **trained linear readout**
with accuracy + reservoir-quality metrics.

Prepared by Karol Chlasta (karol@chlasta.pl).

## Why DVS128 Gesture

- Already **event/spike-based** `(x, y, t, polarity)` → maps natively onto the
  model's 16×16 `retina` layer; no artificial rate-encoding needed.
- Real **temporal** content → finally exercises the liquid's fading memory
  (the static `pimpulse.g` patterns do not).
- **Reservoir-SNN precedent** on this dataset exists → comparable, publishable.
- 11 classes → readout is an 11-way linear classifier on liquid states — exactly
  the component the model lacks today.

## Data flow (three stages)

```
DVS events ──[Python: encode]──▶ per-sample retina spike schedule (.spk) + labels.csv
   .spk ──[GENESIS on cluster: inject → run → dump]──▶ per-sample liquid state vector (.state)
   .state + labels ──[Python: train]──▶ linear readout, accuracy, SP/rank metrics, plots
```

### Stage 1 — Encode (Python, offline) — `encode_dvs_to_retina.py`
For each recording:
1. Load events (via `tonic` if available, else AEDAT/npy reader).
2. Spatial downsample 128×128 → **16×16** (bin x,y by 8; the model's retina grid).
3. Optionally merge polarities (or keep 2 channels → 2×16×16 if we later widen).
4. Time-window: take a fixed window (default 500 ms) split into `T` bins; per
   retina pixel emit a spike at each bin whose event count exceeds a threshold
   (event-count → spike, keeps it sparse and event-driven).
5. Write one `sample_XXXXX.spk` (lines `i j t_ms`) + append to `labels.csv`
   (`sample_id,gesture_class,subject,split`). Keep the official train/test split.

### Stage 2 — Simulate (GENESIS/PGENESIS, on cluster) — `.g` driver (to build+validate on cluster)
The current `pgmwojcik.g` runs **one** stimulus then `quit`. New driver loops over
samples:
```
for each sample s:
    reset                                  # fresh liquid state
    inject s's spatiotemporal input onto the retina
    step <window>                          # let the liquid respond
    read per-neuron spike counts in window # = liquid state vector (features)
    append state vector + s to s.state     # dump for offline training
```

**Integration details discovered from the model code (must be handled):**

1. **Retina is distributed, not a single 16×16 grid.** From `pfunctions.g`
   (`rmake_retina`) and `pimpulse.g`, cells are addressed as
   `retina_{i}_{j}@{npos}` with `i,j ∈ 1..patchdim` on each of the
   `NodesNumber = pdim²` nodes. So a global DVS pixel `(gi,gj) ∈ 1..16` must be
   mapped to `(npos, i, j)`. Natural mapping = tile the 16×16 grid into a
   `pdim×pdim` array of `patchdim×patchdim` blocks; `npos` = row-major block index,
   `(i,j)` = position within the block. **This mapping must be confirmed against
   the model's own retina layout on the cluster** (positions currently ignore
   `npos`, so the intended global geometry needs to be pinned down first).

2. **Reading a schedule inside SLI is awkward.** Cleaner and idiomatic: have the
   Python encoder emit, per sample, a **generated GENESIS include**
   `sample_XXXXX.g` containing the concrete wiring/timing calls (using the
   mapping above), and the driver simply `include`s it. This sidesteps SLI file
   parsing entirely. (Encoder currently writes `.spk`; add a `--emit-g` mode once
   the mapping + generator model are fixed.)

3. **Spike timing.** The model drives the retina via spike *generators*
   (`rmake_spike_generator`, `spike_rate`) wired with `rmake_synapse`. Injecting a
   precise per-pixel spike *time* needs either one generator per active pixel with
   a scheduled/timed firing, or a time-varying input object. **This is the main
   open model-design question** — resolve it experimentally on the cluster.

- **State readout:** liquid state = spike count per reservoir neuron over the
  window (the `spikehistory` objects already record spikes; sum per neuron).
  Feature dim = pdim²·1024, fed to the linear readout.
- **Reproducibility:** set a fixed `randseed` per node so runs are comparable.
- Runs headless via `start.sh`; on UMCS use inf04/inf05 (see `../LAUNCH.md`).
- **This SLI is model surgery → write and validate it on the cluster**, not blind.
  The offline stages (1 and 3) are already implemented and tested here.

### Stage 3 — Train readout + metrics (Python, offline) — `train_readout.py`
1. Load all `.state` vectors + `labels.csv`; apply official train/test split.
2. Train a **linear** readout (ridge / logistic regression) — this is the LSM
   readout; the reservoir stays fixed/random (reservoir-computing principle).
3. Report **test accuracy** + confusion matrix.
4. Reservoir-quality metrics on states: **separation property** (mean inter-class
   / mean intra-class state distance) and **effective rank** (SVD) — the standard
   Maass/Legenstein diagnostics that justify the liquid.
5. Save plots + a `results.json`.

## What lands where

| Piece | Where | Status |
|---|---|---|
| Event → retina encoder | Python (`encode_dvs_to_retina.py`) | offline, in this folder |
| Sample-loop driver + schedule injection | GENESIS SLI (new `.g`) | design here; build+validate on cluster |
| Liquid-state dump | GENESIS SLI | design here; validate on cluster |
| Readout training + SP/rank metrics | Python (`train_readout.py`) | offline, in this folder |
| Fixed RNG seed | `pparameters.g` / driver | small change |

## Realistic expectations

- 16×16 retina is coarse (native DVS is 128×128) → accuracy below large-SNN SOTA
  (~98%). Fine for a proof-of-concept ("the LSM computes") and for the CPU/GPU/MPI
  benchmark story. Higher accuracy later by widening the retina (32×32/64×64),
  which needs **decoupling grid size from `pdim`** (see `../RUN_STATUS.md` notes).
- Start small: validate the whole pipeline on a 2–3 class subset before all 11.

## Path to higher retina resolution (why not 128×128 from the start)

We start at 16×16 because that is the model's *current* retina — zero model change,
fastest route to a working end-to-end pipeline. Going higher is a target, not a
starting point, for three concrete reasons.

1. **"16" is hardcoded and coupled to `pdim` and the readout.** `patchdim = 16/pdim`
   (pparameters.g); the retina is tiled as `retina_{i}_{j}@{npos}` over `pdim²`
   nodes, and `pimpulse.g` hardcodes a 10×10 readout geometry. Changing 16→N
   touches loops in `pfunctions.g`/`pimpulse.g` and needs the **grid-size ↔ `pdim`
   decoupling** refactor. (`pdim` must divide the grid: for 128 that's 1/2/4/…/128.)

2. **Retina cells are full multicompartmental HH neurons, not pixels.**
   - 16×16 = **256** HH neurons
   - 32×32 = 1,024 · 64×64 = 4,096 · **128×128 = 16,384** (64× the current input)

3. **The real blocker — synapse count under dense wiring.** Retina→reservoir
   connectivity uses `connect_prob = 0.8` (dense), so synapses scale as
   `retina × reservoir × prob`:
   - now (retina 256, reservoir 65,536 at pdim=8): order ~10⁷ synapses
   - at 128×128 retina: **~64× more** (order ~10⁸–10⁹) → memory/time blow-up,
     independent of GPU.

**How to actually get there:**
- Do the **grid-size ↔ `pdim` decoupling** refactor (prerequisite for any N).
- Replace dense `0.8` with **sparse, distance-dependent local receptive fields** —
  exactly the declared-but-unused Maass `λ`/`C` (pparameters.g). Then synapses grow
  ~linearly, not quadratically, making 64×64/128×128 tractable (esp. on H200).
- Scale **incrementally**: 16 → 32 → 64, measuring accuracy vs cost.

**Is 128 even needed?** DVS-Gesture gestures are large whole-arm motions; many
works downsample to **32×32 or 64×64** with little accuracy loss. Practical plan:
16×16 to close the loop → 32–64 (post-refactor) as the sweet spot → 128×128 as the
ceiling after refactor + sparse connectivity.

## Related work & comparability

**Deckers, Tsang, Van Leekwijck, Latré — "Extended liquid state machines for
speech recognition", Frontiers in Neuroscience, 2022**
(<https://www.frontiersin.org/journals/neuroscience/articles/10.3389/fnins.2022.1023470/full>).
A recent, peer-reviewed playbook for improving LSMs — closely aligned with this
plan:

- **Validates our readout choice:** they train only a linear classifier (logistic
  regression) on spike counts — exactly what `train_readout.py` does.
- **A concrete recipe for improving the reservoir** (matches the improvement axes
  we identified for the Wójcik liquid), with quantified gains (+5.2% accuracy,
  −20% spikes):
  1. **E/I balance → edge-of-chaos** dynamics,
  2. **spike-frequency adaptation (SFA)** → larger memory capacity,
  3. **neuronal heterogeneity** (diverse membrane time constants).
- **Benchmarks:** SHD, TI-46, Google Speech Commands, N-TIDIGITS (speech /
  neuromorphic-audio).

**Where we differ / our niche:**
- They use conductance-based **LIF**; our liquid is **multicompartmental
  Hodgkin–Huxley** (more biophysical, more expensive → our GPU/MPI acceleration
  story matters more).
- They have **no HPC angle**; the GENESIS 2.5 CUDA/MPI acceleration
  (A40/A100/H200) is our distinct contribution — complementary to their
  algorithmic work.

## Optional / complementary task: SHD (Spiking Heidelberg Digits)

Besides DVS-Gesture (vision), **SHD** is worth considering — it is spike-native
(cochlear channels over time), smaller and simpler to inject than downsampled DVS,
and gives **direct comparability with Deckers et al.** ("we compared against
Deckers et al. on SHD" is a strong paper line). Same three-stage pipeline; only
the Stage-1 encoder changes (audio-spike channels → input layer instead of a
16×16 retina). Could run alongside or instead of DVS-Gesture.

## Tie-in with the GENESIS 2.5 paper

Same model yields **accuracy on a recognized benchmark** AND **wall-clock across
A40/A100/H200 + MPI scaling** — i.e. "GENESIS 2.5 runs a biologically realistic
LSM that recognises event-camera gestures at X%, Y× faster on H200."

## Milestones

1. Encoder produces `.spk` + `labels.csv` for a 2-class subset (offline). ✅ first
2. Cluster: driver injects one `.spk`, liquid responds, state dumped. (bring-up)
3. Cluster: batch all samples → `.state` files.
4. Offline: train readout, get accuracy + SP/rank on the 2-class subset.
5. Scale to 11 classes; add CPU/GPU/MPI timing.
