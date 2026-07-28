#!/usr/bin/env python3
"""Figure for the multi-compartment GPU tree-elimination speed sweep.

Reads the weekend-campaign CSVs from cluster_bringup/logs/ (linear-chain
topology, NCOMP=16, CPU vs GPU tree-multiloop, 10 replicates, N=100-50,000
on A40/A100/RTX 4090; 10 replicates, N=100-1,000 locally on the WarsawIQ AMD
Radeon 890M integrated GPU, capped there by the iGPU driver hang documented
in GPU_HINES_SOLVE_DESIGN.md) and plots step-phase speedup vs N, mean +/- std
error bars, matching the visual style of
plot_genesis25_ocl_multiloop_scaling.py (fig8/fig9) for consistency.

Branching topology (hh_branching_multicompartment_benchmark.g) was swept
identically and gives statistically indistinguishable speedups (see
manuscript text) -- omitted here to avoid near-duplicate overlapping
lines; see cluster_bringup/logs/weekend_campaign_*.csv for the raw data.
"""

from __future__ import annotations

import csv
import statistics
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class Row:
    n: int
    total: int
    mode: str
    t_per_step: float


def format_size_tick(size: int) -> str:
    if size % 1000 == 0:
        return f"{size // 1000}k"
    return str(size)


def load(path: Path, topology: str = "linear-chain") -> list[Row]:
    rows = []
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r["topology"] != topology:
                continue
            rows.append(Row(
                n=int(r["n_neurons"]), total=int(r["total_comps"]),
                mode=r["mode"], t_per_step=float(r["t_per_step_s"]),
            ))
    return rows


def speedup_by_n(rows: list[Row]) -> tuple[list[int], list[float], list[float]]:
    by_n: dict[int, dict[str, list[float]]] = {}
    for r in rows:
        by_n.setdefault(r.n, {}).setdefault(r.mode, []).append(r.t_per_step)
    ns = sorted(by_n)
    means, stds = [], []
    for n in ns:
        cpu = by_n[n]["CPU"]; gpu = by_n[n]["GPU"]
        cpu_m = statistics.mean(cpu)
        gpu_vals = [cpu_m / g for g in gpu]  # per-replicate speedup using mean CPU
        means.append(statistics.mean(gpu_vals))
        stds.append(statistics.stdev(gpu_vals) if len(gpu_vals) > 1 else 0.0)
    return ns, means, stds


def main() -> None:
    root = Path(__file__).resolve().parent.parent
    logs = root.parent / "cluster_bringup" / "logs"
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    a40 = load(logs / "weekend_campaign_inf02_A40_20260725_212053.csv")
    a100 = load(logs / "weekend_campaign_inf03_A100_20260725_212113.csv")
    rtx4090 = load(logs / "weekend_campaign_wiq_RTX4090_20260727_194140.csv")
    amd = load(logs / "weekend_campaign_local_AMD890M_20260725.csv")

    n_a40, sp_a40, std_a40 = speedup_by_n(a40)
    n_a100, sp_a100, std_a100 = speedup_by_n(a100)
    n_rtx4090, sp_rtx4090, std_rtx4090 = speedup_by_n(rtx4090)
    n_amd, sp_amd, std_amd = speedup_by_n(amd)

    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(8.5, 6.2))

    # Fixed categorical colors + distinct marker shapes (identity not on
    # color alone): A40 orange/circle, A100 green/square, RTX 4090
    # purple/diamond, AMD-890M blue/triangle -- all pairwise distinguishable
    # under deuteranopia/protanopia (no red used, and blue/purple are well
    # separated from orange and green).
    ax.errorbar(n_a40, sp_a40, yerr=std_a40, color="#9c5315", linewidth=2.2,
                marker="o", markersize=6, capsize=3, label="UMCS A40 (sm_86, 10 reps)")
    ax.errorbar(n_a100, sp_a100, yerr=std_a100, color="#1e7f4f", linewidth=2.2,
                marker="s", markersize=6, capsize=3, label="UMCS A100 (sm_80, 10 reps)")
    ax.errorbar(n_rtx4090, sp_rtx4090, yerr=std_rtx4090, color="#7b3f9e", linewidth=2.2,
                marker="D", markersize=6, capsize=3,
                label="WarsawIQ RTX 4090 (sm_89, 10 reps)")
    ax.errorbar(n_amd, sp_amd, yerr=std_amd, color="#2a5fa8", linewidth=2.2,
                marker="^", markersize=7, capsize=3,
                label="WarsawIQ AMD Radeon 890M (iGPU, 10 reps)")
    ax.axhline(1.0, color="#444444", linewidth=1.2, linestyle="--")

    # Annotate only a subset (first, last, and every other point) -- with
    # 13 N values per series on a log-y axis, labeling every point crowds
    # the middle of the curve even with alternating offsets.
    def label_subset(ns, sps, color, dy):
        idxs = list(range(0, len(ns), 2))
        if idxs[-1] != len(ns) - 1:
            idxs.append(len(ns) - 1)
        for i in idxs:
            ax.annotate(f"{sps[i]:.1f}x", (ns[i], sps[i]), textcoords="offset points",
                        xytext=(0, dy), ha="center", fontsize=7.5, color=color)

    label_subset(n_a40, sp_a40, "#9c5315", -16)
    label_subset(n_a100, sp_a100, "#1e7f4f", 11)
    label_subset(n_rtx4090, sp_rtx4090, "#7b3f9e", -16)

    ax.set_xlabel("N neurons (linear chain, NCOMP=16 compartments each)")
    ax.set_ylabel("Step-phase speedup (CPU/GPU), log scale")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.yaxis.set_major_formatter(mticker.ScalarFormatter())
    ax.yaxis.set_minor_formatter(mticker.NullFormatter())
    ax.set_xticks(n_a40)
    ax.set_xticklabels([format_size_tick(x) for x in n_a40], rotation=30, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.grid(True, axis="y", alpha=0.35)
    ax.legend(loc="upper left")
    ax.set_title("GENESIS 2.5: multi-compartment GPU tree-elimination speedup\n(UMCS cluster + WarsawIQ, mean $\\pm$ std, 10 replicates)")

    fig.tight_layout()
    out = figures / "fig10_multicompartment_speedup.png"
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print("Wrote:", out)
    for label, ns, sps, stds in [("A40", n_a40, sp_a40, std_a40),
                                   ("A100", n_a100, sp_a100, std_a100),
                                   ("RTX-4090", n_rtx4090, sp_rtx4090, std_rtx4090),
                                   ("AMD-890M", n_amd, sp_amd, std_amd)]:
        for n, s, sd in zip(ns, sps, stds):
            print(f"  {label} N={n}: {s:.2f}x +/- {sd:.2f}")


if __name__ == "__main__":
    main()
