#!/usr/bin/env python3
"""Encode DVS128 Gesture recordings into per-sample retina spike schedules
for Wójcik's PGENESIS LSM (16x16 retina).

Prepared by Karol Chlasta (karol@chlasta.pl).

Output per sample: a `.spk` file with lines  "i j t_ms"  (1-based retina pixel
indices matching retina_{i}_{j}, spike time in ms within the window), plus a
shared labels.csv (sample_id,gesture_class,split). These are consumed on the
cluster by the GENESIS driver (see PLAN.md, Stage 2).

Loader: uses `tonic` if installed (recommended, handles the official DVS128
Gesture download + AEDAT parsing). Otherwise point --npy-dir at a folder of
per-sample .npz files each holding structured events (fields x,y,t,p) + 'label'.

Usage:
    python3 encode_dvs_to_retina.py --out out/ --split train --grid 16 \
        --window-ms 500 --bins 10 --thresh 1 --max-per-class 20
"""
import argparse
import csv
import os
import sys
import numpy as np

NATIVE = 128  # DVS128 sensor is 128x128


def iter_tonic(split):
    """Yield (events_structured, label) from the tonic DVS128 Gesture dataset."""
    import tonic  # noqa: local import so the file imports without tonic present
    ds = tonic.datasets.DVSGesture(save_to="./data", train=(split == "train"))
    for events, label in ds:
        yield events, int(label)


def iter_npz(npy_dir):
    """Fallback: each .npz has structured 'events' (x,y,t,p) and scalar 'label'."""
    for fn in sorted(os.listdir(npy_dir)):
        if not fn.endswith(".npz"):
            continue
        d = np.load(os.path.join(npy_dir, fn))
        yield d["events"], int(d["label"])


def encode_one(events, grid, window_us, bins, thresh):
    """events: structured array with x,y,t (and p). Returns list of (i,j,t_ms).

    Spatial downsample NATIVE->grid, keep first `window_us`, split into `bins`
    time slices; a retina pixel emits a spike in a slice when its event count in
    that slice reaches `thresh` (event-count -> spike, stays sparse/event-driven).
    """
    x = events["x"].astype(np.int64)
    y = events["y"].astype(np.int64)
    t = events["t"].astype(np.int64)
    t0 = t.min()
    t = t - t0
    keep = t < window_us
    x, y, t = x[keep], y[keep], t[keep]
    if x.size == 0:
        return []

    scale = NATIVE / grid
    gi = np.clip((x / scale).astype(np.int64), 0, grid - 1)
    gj = np.clip((y / scale).astype(np.int64), 0, grid - 1)
    slot = np.clip((t * bins // window_us).astype(np.int64), 0, bins - 1)

    # 3D histogram: (grid, grid, bins) event counts
    hist = np.zeros((grid, grid, bins), dtype=np.int64)
    np.add.at(hist, (gi, gj, slot), 1)

    bin_ms = (window_us / bins) / 1000.0
    out = []
    idx = np.argwhere(hist >= thresh)  # (i, j, slice) meeting threshold
    for i, j, s in idx:
        t_ms = round((s + 0.5) * bin_ms, 3)  # spike at slice center
        # +1: GENESIS retina objects are retina_{i}_{j} with 1-based indices
        out.append((int(i) + 1, int(j) + 1, t_ms))
    out.sort(key=lambda r: (r[2], r[0], r[1]))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True, help="output directory")
    ap.add_argument("--split", default="train", choices=["train", "test"])
    ap.add_argument("--npy-dir", default=None, help="fallback .npz dir (no tonic)")
    ap.add_argument("--grid", type=int, default=16)
    ap.add_argument("--window-ms", type=float, default=500.0)
    ap.add_argument("--bins", type=int, default=10)
    ap.add_argument("--thresh", type=int, default=1)
    ap.add_argument("--max-per-class", type=int, default=0,
                    help="0 = all; else cap samples per class (fast pilots)")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)
    window_us = int(args.window_ms * 1000)

    if args.npy_dir:
        source = iter_npz(args.npy_dir)
    else:
        try:
            source = iter_tonic(args.split)
        except ImportError:
            sys.exit("tonic not installed; install it or pass --npy-dir. "
                     "See PLAN.md Stage 1.")

    labels_path = os.path.join(args.out, "labels.csv")
    per_class = {}
    n = 0
    with open(labels_path, "w", newline="") as lf:
        w = csv.writer(lf)
        w.writerow(["sample_id", "gesture_class", "split"])
        for events, label in source:
            if args.max_per_class:
                per_class[label] = per_class.get(label, 0) + 1
                if per_class[label] > args.max_per_class:
                    continue
            spikes = encode_one(events, args.grid, window_us, args.bins, args.thresh)
            if not spikes:
                continue
            sid = f"sample_{n:05d}"
            with open(os.path.join(args.out, sid + ".spk"), "w") as sf:
                for i, j, t_ms in spikes:
                    sf.write(f"{i} {j} {t_ms}\n")
            w.writerow([sid, label, args.split])
            n += 1

    print(f"Wrote {n} samples to {args.out}  (labels: {labels_path})")


if __name__ == "__main__":
    main()
