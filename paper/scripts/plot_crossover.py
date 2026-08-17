#!/usr/bin/env python3
"""Where GENESIS 2.5 overtakes Arbor, as a function of run length.

Both simulators are linear in the number of steps, with different intercepts and
slopes: Arbor starts ahead on setup, GENESIS advances each step more cheaply.
The lines therefore cross, and the crossing is the result -- neither simulator
is faster in general, and a single-run-length comparison would report whichever
side of it the author happened to pick.

Reads whatever K values are present, so it works with the two-point measurement
and with a fuller sweep. Only the GPU arms are plotted; the CPU arms belong to a
different comparison and are two orders of magnitude away.
"""

from __future__ import annotations

import csv
import statistics
from pathlib import Path

import matplotlib.pyplot as plt

GENESIS_COLOR = "#1e7f4f"
ARBOR_COLOR = "#9c5315"
INK = "#222222"


def load(logs: Path) -> dict[str, dict[int, list[float]]]:
    """GPU wall times by simulator and step count, from every matching CSV."""
    out: dict[str, dict[int, list[float]]] = {}
    for path in sorted(logs.glob("cross_simulator_*.csv")) + sorted(logs.glob("crossover_*.csv")):
        with path.open(newline="", encoding="utf-8") as f:
            for r in csv.DictReader(f):
                backend = (r.get("backend") or "GPU").upper()
                if "GPU" not in backend:
                    continue
                try:
                    k, w = int(r["n_steps"]), float(r["wall_s"])
                except (KeyError, ValueError):
                    continue
                out.setdefault(r["simulator"], {}).setdefault(k, []).append(w)
    return out


def fit(ks: list[int], ts: list[float]) -> tuple[float, float]:
    """Least-squares intercept and per-step slope."""
    n = len(ks)
    mx, my = sum(ks) / n, sum(ts) / n
    sxx = sum((k - mx) ** 2 for k in ks)
    sxy = sum((k - mx) * (t - my) for k, t in zip(ks, ts))
    slope = sxy / sxx if sxx else 0.0
    return my - slope * mx, slope


def main() -> None:
    root = Path(__file__).resolve().parent.parent
    logs = root.parent / "cluster_bringup" / "logs"
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    data = load(logs)
    series = {}
    for name, color in (("GENESIS 2.5", GENESIS_COLOR), ("Arbor 0.10.0", ARBOR_COLOR)):
        by_k = data.get(name)
        if not by_k:
            continue
        ks = sorted(by_k)
        means = [statistics.mean(by_k[k]) for k in ks]
        sds = [statistics.stdev(by_k[k]) if len(by_k[k]) > 1 else 0.0 for k in ks]
        series[name] = (ks, means, sds, color, fit(ks, means))

    if len(series) < 2:
        raise SystemExit(f"need both simulators, found {list(series)}")

    (gk, _, _, _, (g0, g1)) = series["GENESIS 2.5"]
    (_, _, _, _, (a0, a1)) = series["Arbor 0.10.0"]
    cross = (a0 - g0) / (g1 - a1) if g1 != a1 else None

    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(8.0, 5.0))

    kmax = max(max(s[0]) for s in series.values()) * 1.05
    for name, (ks, means, sds, color, (c0, c1)) in series.items():
        ax.errorbar(ks, means, yerr=sds, color=color, marker="o", markersize=7,
                    linestyle="none", capsize=3, zorder=3, label=f"{name} (measured)")
        xs = [0, kmax]
        ax.plot(xs, [c0 + c1 * x for x in xs], color=color, linewidth=1.6,
                linestyle="--", alpha=0.85, zorder=2,
                label=f"{name}: {c0:.2f} s + {c1 * 1e6:.1f} $\\mu$s/step")

    if cross and 0 < cross < kmax:
        ycross = g0 + g1 * cross
        ax.axvline(cross, color="#444444", linewidth=1.0, linestyle=":", zorder=1)
        ax.plot([cross], [ycross], marker="D", color=INK, markersize=7, zorder=4)
        ax.annotate(f"crossover\nK $\\approx$ {cross:,.0f} steps\n({cross * 0.01:.0f} ms simulated)",
                    (cross, ycross), textcoords="offset points", xytext=(14, -34),
                    fontsize=9, color=INK)

    ax.set_xlabel("K, simulation steps (dt = 0.01 ms)")
    ax.set_ylabel("Wall-clock time (s), lower is better")
    ax.set_xlim(0, kmax)
    ax.set_ylim(0, None)
    ax.grid(True, alpha=0.35)
    ax.legend(loc="upper left", fontsize=8.5)
    ax.set_title("GPU wall clock vs run length, 10,000 neurons $\\times$ 16 compartments\n"
                 "UMCS A100; Arbor leads on setup, GENESIS 2.5 on cost per step",
                 fontsize=11)

    fig.tight_layout()
    out = figures / "fig13_crossover.png"
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print("Wrote:", out)
    if cross:
        print(f"crossover K = {cross:.0f} ({cross * 0.01:.1f} ms simulated)")


if __name__ == "__main__":
    main()
