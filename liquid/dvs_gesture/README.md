# DVS128 Gesture on the PGENESIS LSM

Make Wójcik's Liquid State Machine *classify* a well-known event-based benchmark
(IBM DVS128 Gesture, 11 gestures) — adding the missing trained readout so the
model demonstrates computation, not just spiking. Full design in [PLAN.md](PLAN.md).

## Status

| Stage | Component | State |
|---|---|---|
| 1 | `encode_dvs_to_retina.py` — DVS events → 16×16 retina spikes + labels | **done, tested** (synthetic) |
| 2 | GENESIS `.g` driver — inject / run / dump liquid states | **designed** (validate on cluster; see PLAN.md open points) |
| 3 | `train_readout.py` — linear readout + accuracy + SP/rank metrics | **done, tested** (synthetic) |

## Quick start (offline parts)

```bash
# Stage 1 — encode (needs `tonic`, or point --npy-dir at .npz samples)
python3 encode_dvs_to_retina.py --out out_enc/ --split train --grid 16 \
    --window-ms 500 --bins 10 --thresh 1 --max-per-class 20

# Stage 3 — after the cluster produces out_states/*.state + labels.csv
python3 train_readout.py --states out_states/ --model ridge --out results/
```

## Reservoir-computing principle

The liquid (reservoir) stays **fixed/random**; only the linear readout is trained.
Test accuracy on held-out gestures turns the model into a functioning LSM; the
same runs also feed the GENESIS 2.5 CPU/GPU/MPI timing story (A40/A100/H200).

Prepared by Karol Chlasta (karol@chlasta.pl).
