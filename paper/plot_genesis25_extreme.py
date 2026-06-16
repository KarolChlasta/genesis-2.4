#!/usr/bin/env python3
"""Figures from the extreme paired CPU/GPU 5-rep campaign."""

from __future__ import annotations

import csv
import sys
from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


BENCH_LABELS = {
    "mesoscale_sparse_benchmark": "Mesoscale",
    "biophysical_cellscale_benchmark": "Biophysical",
    "region_proxy_microcircuit_benchmark": "Region proxy",
}
COLORS = {
    "CPU": "#1f4e79",
    "GPU": "#b84c00",
}
BENCH_ORDER = list(BENCH_LABELS)


def load_summary(path: Path):
    rows = []
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append(r)
    return rows


def load_raw(path: Path):
    rows = []
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append(r)
    return rows


def plot_runtime_ci(summary_rows, raw_rows, out: Path) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")

    # collect per (benchmark, size, mode) → list of real_seconds from raw
    raw_vals: dict = defaultdict(list)
    for r in raw_rows:
        key = (r["benchmark"], int(r["size_value"]), r["mode"])
        raw_vals[key].append(float(r["real_seconds"]))

    # collect summary stats
    stats: dict = {}
    for r in summary_rows:
        key = (r["benchmark"], int(r["size_value"]), r["mode"])
        stats[key] = {
            "mean": float(r["mean_s"]),
            "ci95": float(r["ci95_s"]),
        }

    benches = [b for b in BENCH_ORDER if any(r["benchmark"] == b for r in summary_rows)]
    fig, axes = plt.subplots(1, len(benches), figsize=(6.0 * len(benches), 5.0))
    if len(benches) == 1:
        axes = [axes]

    for ax, bench in zip(axes, benches):
        sizes = sorted({int(r["size_value"]) for r in summary_rows if r["benchmark"] == bench})
        for mode, color in COLORS.items():
            xs, ys, yerr = [], [], []
            for size in sizes:
                k = (bench, size, mode)
                if k not in stats:
                    continue
                xs.append(size)
                ys.append(stats[k]["mean"])
                yerr.append(stats[k]["ci95"])
                # jitter replicate dots
                jitter = -0.02 if mode == "CPU" else 0.02
                for v in raw_vals.get(k, []):
                    ax.scatter(size * (1 + jitter), v, color=color, s=14,
                               alpha=0.45, zorder=3, linewidths=0)

            ax.errorbar(xs, ys, yerr=yerr, label=mode, color=color,
                        linewidth=2.0, marker="o", markersize=6,
                        capsize=4, zorder=4)

        ax.set_title(BENCH_LABELS.get(bench, bench), fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        ax.set_xscale("log")
        ax.set_xticks(sizes)
        ax.set_xticklabels(
            [f"{s//1000}k" if s >= 1000 else str(s) for s in sizes],
            rotation=20, ha="right",
        )
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, axis="y", alpha=0.35)

    axes[0].set_ylabel("Runtime (s)")
    axes[0].legend(framealpha=0.9)
    fig.suptitle("GENESIS 2.5 Extreme Sizes: CPU vs GPU Runtime (5 reps, 95% CI)",
                 fontsize=12, y=1.02)
    fig.tight_layout()
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print(f"Wrote {out}")


def plot_speedup(speedup_rows, out: Path) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")

    benches = [b for b in BENCH_ORDER if any(r["benchmark"] == b for r in speedup_rows)]
    fig, axes = plt.subplots(1, len(benches), figsize=(6.0 * len(benches), 5.0), sharey=True)
    if len(benches) == 1:
        axes = [axes]

    for ax, bench in zip(axes, benches):
        rows = sorted(
            [r for r in speedup_rows if r["benchmark"] == bench],
            key=lambda r: int(r["size_value"]),
        )
        xs = [int(r["size_value"]) for r in rows]
        ys = [float(r["speedup_cpu_over_gpu"]) for r in rows]

        color = {"mesoscale_sparse_benchmark": "#0b6e99",
                 "biophysical_cellscale_benchmark": "#9c5315",
                 "region_proxy_microcircuit_benchmark": "#1e7f4f"}.get(bench, "#444")

        ax.plot(xs, ys, color=color, linewidth=2.2, marker="o", markersize=6)
        ax.axhline(1.0, color="#444", linewidth=1.2, linestyle="--")

        ax.set_title(BENCH_LABELS.get(bench, bench), fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        ax.set_xscale("log")
        ax.set_xticks(xs)
        ax.set_xticklabels(
            [f"{x//1000}k" if x >= 1000 else str(x) for x in xs],
            rotation=20, ha="right",
        )
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, axis="y", alpha=0.35)

    axes[0].set_ylabel("Speedup (CPU / GPU)")
    fig.suptitle("GENESIS 2.5 Extreme Sizes: CPU/GPU Speedup", fontsize=12, y=1.02)
    fig.tight_layout()
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print(f"Wrote {out}")


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    summary_path = root / "genesis25_cpu_gpu_extreme_5rep_summary.csv"
    raw_path     = root / "genesis25_cpu_gpu_extreme_5rep.csv"
    speedup_path = root / "genesis25_cpu_gpu_extreme_5rep_speedup.csv"

    for p in (summary_path, raw_path, speedup_path):
        if not p.exists():
            print(f"Missing: {p} — run run_genesis25_cpu_gpu_extreme_5rep.sh first", file=sys.stderr)
            sys.exit(1)

    summary_rows = load_summary(summary_path)
    raw_rows     = load_raw(raw_path)
    speedup_rows = load_summary(speedup_path)

    plot_runtime_ci(summary_rows, raw_rows, figures / "fig8_extreme_runtime_ci.png")
    plot_speedup(speedup_rows, figures / "fig9_extreme_speedup.png")


if __name__ == "__main__":
    main()
