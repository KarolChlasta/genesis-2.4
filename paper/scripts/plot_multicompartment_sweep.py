#!/usr/bin/env python3
"""Figure for the multi-compartment GPU tree-elimination speed sweep.

Plots both speedup definitions for the two UMCS cards, because they answer
different questions and quoting only the first overstates the result:

  step-phase   times the simulation loop alone -- what the kernel can do
  end-to-end   wall clock around the whole process -- what a user experiences

At K=200 steps the unaccelerated construction phase dominates, so the
end-to-end curve sits far below the step-phase one; Fig. fig_campaign_ksweep
shows it climbing toward that ceiling as K grows.

The step-phase series come from the weekend campaign (explicit SLI construction
loop); the end-to-end series build the same population with a single createmap
from a prototype, as network models do. Construction method does not affect the
step-phase figures, which exclude construction.

WarsawIQ hardware (RTX 4090, AMD Radeon 890M) is omitted from the refreshed
publication; the sweep now rests on the two UMCS cluster cards.

Branching topology was swept identically and gives statistically
indistinguishable speedups -- omitted to avoid near-duplicate overlapping
lines; see cluster_bringup/logs/weekend_campaign_*.csv for the raw data.
"""

from __future__ import annotations

import csv
import statistics
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker

A40_COLOR = "#9c5315"
A100_COLOR = "#1e7f4f"


def format_size_tick(size: int) -> str:
    if size % 1000 == 0:
        return f"{size // 1000}k"
    return str(size)


def _speedup(by_n: dict[int, dict[str, list[float]]]) -> tuple[list[int], list[float], list[float]]:
    """Per-replicate GPU speedup against the mean CPU time, by N.

    Points where an arm has no usable replicate are dropped rather than
    plotted as zero.
    """
    ns, means, stds = [], [], []
    for n in sorted(by_n):
        cpu = by_n[n].get("cpu") or []
        gpu = by_n[n].get("gpu") or []
        if not cpu or not gpu:
            continue
        cpu_m = statistics.mean(cpu)
        vals = [cpu_m / g for g in gpu if g > 0]
        if not vals:
            continue
        ns.append(n)
        means.append(statistics.mean(vals))
        stds.append(statistics.stdev(vals) if len(vals) > 1 else 0.0)
    return ns, means, stds


def load_step_phase(path: Path, topology: str = "linear-chain"):
    by_n: dict[int, dict[str, list[float]]] = {}
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r.get("topology") != topology:
                continue
            by_n.setdefault(int(r["n_neurons"]), {}).setdefault(
                r["mode"].lower(), []).append(float(r["t_per_step_s"]))
    return _speedup(by_n)


def load_end_to_end(*paths: Path):
    """Wall-clock sweep, optionally spread over several files.

    A refill file covering a single N is concatenated onto the main sweep, so
    a point re-measured after a failed block replaces rather than duplicates
    the bad one.
    """
    by_n: dict[int, dict[str, list[float]]] = {}
    for path in paths:
        if not path.exists():
            continue
        with path.open(newline="", encoding="utf-8") as f:
            for r in csv.DictReader(f):
                wall = float(r["wall_s"])
                # A block where every replicate finished in milliseconds means
                # the binary never ran (a busy card); such rows are not data.
                if wall < 0.01:
                    continue
                by_n.setdefault(int(r["n_neurons"]), {}).setdefault(
                    r["mode"].lower(), []).append(wall)
    return _speedup(by_n)


def main() -> None:
    root = Path(__file__).resolve().parent.parent
    logs = root.parent / "cluster_bringup" / "logs"
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    n_a40_sp, sp_a40, sd_a40 = load_step_phase(
        logs / "weekend_campaign_inf02_A40_20260816_clean.csv")
    n_a100_sp, sp_a100, sd_a100 = load_step_phase(
        logs / "weekend_campaign_inf03_A100_20260816_clean.csv")

    n_a40_e2e, e2e_a40, sde_a40 = load_end_to_end(
        logs / "multicomp_walltime_createmap_inf02_A40_clean.csv")
    n_a100_e2e, e2e_a100, sde_a100 = load_end_to_end(
        logs / "multicomp_walltime_createmap_inf03_A100_clean.csv")

    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(8.5, 6.2))

    # Colour identifies the card, line style the metric: solid = step-phase,
    # dashed = end-to-end. Both hues stay distinguishable under deuteranopia
    # and protanopia, and neither identity depends on colour alone.
    ax.errorbar(n_a40_sp, sp_a40, yerr=sd_a40, color=A40_COLOR, linewidth=2.2,
                marker="o", markersize=6, capsize=3,
                label="A40 step-phase (simulation loop only)")
    ax.errorbar(n_a100_sp, sp_a100, yerr=sd_a100, color=A100_COLOR, linewidth=2.2,
                marker="s", markersize=6, capsize=3,
                label="A100 step-phase (simulation loop only)")
    ax.errorbar(n_a40_e2e, e2e_a40, yerr=sde_a40, color=A40_COLOR, linewidth=2.2,
                marker="o", markersize=6, capsize=3, linestyle="--",
                markerfacecolor="white",
                label="A40 end-to-end (incl. construction)")
    ax.errorbar(n_a100_e2e, e2e_a100, yerr=sde_a100, color=A100_COLOR, linewidth=2.2,
                marker="s", markersize=6, capsize=3, linestyle="--",
                markerfacecolor="white",
                label="A100 end-to-end (incl. construction)")
    ax.axhline(1.0, color="#444444", linewidth=1.2, linestyle=":")
    ax.annotate("parity with CPU", (n_a40_sp[0], 1.0), textcoords="offset points",
                xytext=(4, 5), fontsize=8, color="#444444")

    # Label the endpoints only: with four series over 13 N values, annotating
    # every point buries the curves.
    for ns, vals, color, dy in (
        (n_a40_sp, sp_a40, A40_COLOR, -15),
        (n_a100_sp, sp_a100, A100_COLOR, 10),
        (n_a40_e2e, e2e_a40, A40_COLOR, -15),
        (n_a100_e2e, e2e_a100, A100_COLOR, 10),
    ):
        if ns:
            ax.annotate(f"{vals[-1]:.1f}x", (ns[-1], vals[-1]),
                        textcoords="offset points", xytext=(0, dy),
                        ha="center", fontsize=8, color=color)

    ax.set_xlabel("N neurons (linear chain, NCOMP=16 compartments each)")
    ax.set_ylabel("Speedup vs CPU, log scale")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.yaxis.set_major_formatter(mticker.ScalarFormatter())
    ax.yaxis.set_minor_formatter(mticker.NullFormatter())
    ax.set_xticks(n_a40_sp)
    ax.set_xticklabels([format_size_tick(x) for x in n_a40_sp], rotation=30, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.grid(True, axis="y", alpha=0.35)
    ax.legend(loc="upper left", fontsize=9)
    ax.set_title("GENESIS 2.5: multi-compartment GPU tree-elimination speedup\n"
                 "(UMCS A40/A100, mean $\\pm$ std, 10 replicates)")

    fig.tight_layout()
    out = figures / "fig10_multicompartment_speedup.png"
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print("Wrote:", out)


if __name__ == "__main__":
    main()
