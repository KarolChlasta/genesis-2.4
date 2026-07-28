#!/usr/bin/env python3
"""Figure for the O(n^2)->O(n) model-construction fix.

Reads experiments/data/construction_scaling_before_after.csv (local
machine, hh_branching_multicompartment_benchmark.g, full wall time:
construction + hsolve SETUP + timed step phase) and plots wall time vs N
on log-log axes for the "before" (pre-fix, single replicate, only 4
points -- N=16000+ never finished within the tested budgets and are
omitted, not zero) and "after" (post-fix, 3 replicates, 9 points up to
N=100,000) variants, alongside a fitted power-law exponent for each. The
"after" series shows mean +/- 1 std error bars across replicates.
"""

from __future__ import annotations

import csv
import math
import statistics
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class Row:
    rep: int
    n: int
    ncompts: int
    t: float
    variant: str


def load(path: Path) -> list[Row]:
    rows = []
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append(Row(
                rep=int(r["rep"]), n=int(r["n_neurons"]),
                ncompts=int(r["ncompts"]), t=float(r["total_wallclock_s"]),
                variant=r["variant"],
            ))
    return rows


def fit_exponent(ns: list[int], ts: list[float]) -> float:
    lx = [math.log(n) for n in ns]
    ly = [math.log(t) for t in ts]
    n = len(lx)
    mx = sum(lx) / n
    my = sum(ly) / n
    num = sum((x - mx) * (y - my) for x, y in zip(lx, ly))
    den = sum((x - mx) ** 2 for x in lx)
    return num / den


def aggregate(rows: list[Row]) -> tuple[list[int], list[float], list[float]]:
    by_n: dict[int, list[float]] = {}
    for r in rows:
        by_n.setdefault(r.n, []).append(r.t)
    ns = sorted(by_n)
    means = [statistics.mean(by_n[n]) for n in ns]
    stds = [statistics.stdev(by_n[n]) if len(by_n[n]) > 1 else 0.0 for n in ns]
    return ns, means, stds


def main() -> None:
    root = Path(__file__).resolve().parent
    data = root.parent / "experiments" / "data" / "construction_scaling_before_after.csv"
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    rows = load(data)
    before = [r for r in rows if r.variant == "before"]
    after = [r for r in rows if r.variant == "after"]

    n_before, t_before, _ = aggregate(before)
    n_after, t_after, std_after = aggregate(after)

    k_before = fit_exponent(n_before, t_before)
    k_after = fit_exponent(n_after, t_after)

    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(6.4, 4.6))

    ax.plot(n_before, t_before, color="#b0413e", linewidth=2.2, marker="o",
            markersize=6, label=f"before fix (exponent {k_before:.2f})")
    ax.errorbar(n_after, t_after, yerr=std_after, color="#1e7f4f", linewidth=2.2,
                marker="s", markersize=6, capsize=3,
                label=f"after fix (exponent {k_after:.2f}, 3 reps)")

    ax.axvline(31000, color="#444444", linewidth=1.0, linestyle=":")
    ax.text(31000, 0.6, "Blue Brain microcircuit\nscale (~31k neurons)",
            transform=ax.get_xaxis_transform(), ha="right", va="bottom",
            fontsize=8, color="#444444")

    ax.set_xlabel("N neurons (4 branches x 4 compartments + soma each)")
    ax.set_ylabel("Total wall time (construction + hsolve SETUP + step), s")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.xaxis.set_major_formatter(mticker.ScalarFormatter())
    ax.yaxis.set_major_formatter(mticker.ScalarFormatter())
    ax.grid(True, which="both", alpha=0.3)
    ax.legend()
    ax.set_title("GENESIS 2.5: model-construction scaling, before/after\nthe O(n²)→O(n) kernel fix (local machine)")

    fig.tight_layout()
    out = figures / "fig11_construction_scaling.png"
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print("Wrote:", out)
    print(f"before exponent: {k_before:.3f}")
    print(f"after exponent:  {k_after:.3f}")
    for n, m, s in zip(n_after, t_after, std_after):
        print(f"  N={n}: mean={m:.3f}s std={s:.3f}s cv={100*s/m:.1f}%")


if __name__ == "__main__":
    main()
