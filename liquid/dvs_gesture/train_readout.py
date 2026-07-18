#!/usr/bin/env python3
"""Train the LSM linear readout on dumped liquid states and report accuracy plus
reservoir-quality metrics (separation property, effective rank).

Prepared by Karol Chlasta (karol@chlasta.pl).

Inputs (produced on the cluster by the GENESIS driver, see PLAN.md Stage 2):
  - <states_dir>/sample_XXXXX.state : one line of space-separated spike counts
    (the liquid state vector = per-reservoir-neuron spike count over the window)
  - <states_dir>/labels.csv         : sample_id,gesture_class,split

The reservoir stays fixed/random; ONLY this linear readout is trained
(reservoir-computing principle). Reporting test accuracy turns the model from a
spike dump into a functioning LSM.

Usage:
    python3 train_readout.py --states out_states/ --model ridge --out results/
"""
import argparse
import csv
import json
import os
import numpy as np


def load(states_dir):
    labels = {}
    with open(os.path.join(states_dir, "labels.csv")) as f:
        for row in csv.DictReader(f):
            labels[row["sample_id"]] = (int(row["gesture_class"]),
                                        row.get("split", "train"))
    X, y, split, ids = [], [], [], []
    for sid, (cls, sp) in sorted(labels.items()):
        path = os.path.join(states_dir, sid + ".state")
        if not os.path.exists(path):
            continue
        vec = np.loadtxt(path).ravel()
        X.append(vec)
        y.append(cls)
        split.append(sp)
        ids.append(sid)
    if not X:
        raise SystemExit(f"no .state files found in {states_dir}")
    width = max(v.size for v in X)
    X = np.vstack([np.pad(v, (0, width - v.size)) for v in X])
    return X, np.array(y), np.array(split), ids


def separation_property(X, y):
    """Maass separation: mean inter-class / mean intra-class centroid distance."""
    classes = np.unique(y)
    cents = {c: X[y == c].mean(axis=0) for c in classes}
    inter = [np.linalg.norm(cents[a] - cents[b])
             for i, a in enumerate(classes) for b in classes[i + 1:]]
    intra = [np.linalg.norm(X[y == c] - cents[c], axis=1).mean() for c in classes]
    inter_m = float(np.mean(inter)) if inter else 0.0
    intra_m = float(np.mean(intra)) if intra else 1e-9
    return inter_m / (intra_m + 1e-9), inter_m, intra_m


def effective_rank(X):
    """Effective rank = exp(entropy of normalized singular values)."""
    s = np.linalg.svd(X - X.mean(axis=0), compute_uv=False)
    s = s[s > 1e-12]
    if s.size == 0:
        return 0.0
    p = s / s.sum()
    return float(np.exp(-(p * np.log(p)).sum()))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--states", required=True)
    ap.add_argument("--model", default="ridge", choices=["ridge", "logistic"])
    ap.add_argument("--out", default="results")
    ap.add_argument("--test-frac", type=float, default=0.3,
                    help="used only if labels.csv has no test split")
    ap.add_argument("--seed", type=int, default=0)
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)

    from sklearn.linear_model import RidgeClassifier, LogisticRegression
    from sklearn.metrics import accuracy_score, confusion_matrix
    from sklearn.preprocessing import StandardScaler

    X, y, split, ids = load(args.states)

    if (split == "test").any():
        tr, te = split == "train", split == "test"
    else:
        rng = np.random.default_rng(args.seed)
        idx = rng.permutation(len(y))
        cut = int(len(y) * (1 - args.test_frac))
        tr = np.zeros(len(y), bool); tr[idx[:cut]] = True
        te = ~tr

    scaler = StandardScaler().fit(X[tr])
    Xs = scaler.transform(X)
    clf = (RidgeClassifier() if args.model == "ridge"
           else LogisticRegression(max_iter=2000, multi_class="auto"))
    clf.fit(Xs[tr], y[tr])
    pred = clf.predict(Xs[te])

    acc = float(accuracy_score(y[te], pred))
    sp, inter_m, intra_m = separation_property(X, y)
    erank = effective_rank(X)

    results = {
        "n_samples": int(len(y)), "n_train": int(tr.sum()), "n_test": int(te.sum()),
        "n_classes": int(len(np.unique(y))), "state_dim": int(X.shape[1]),
        "model": args.model, "test_accuracy": acc,
        "separation_property": sp, "inter_class_dist": inter_m,
        "intra_class_dist": intra_m, "effective_rank": erank,
        "confusion_matrix": confusion_matrix(y[te], pred).tolist(),
    }
    with open(os.path.join(args.out, "results.json"), "w") as f:
        json.dump(results, f, indent=2)

    print(f"test accuracy      : {acc:.3f}  ({len(np.unique(y))} classes, "
          f"chance ~{1/len(np.unique(y)):.3f})")
    print(f"separation (SP)    : {sp:.3f}  (inter {inter_m:.3g} / intra {intra_m:.3g})")
    print(f"effective rank     : {erank:.1f}  of state dim {X.shape[1]}")
    print(f"results -> {os.path.join(args.out, 'results.json')}")


if __name__ == "__main__":
    main()
