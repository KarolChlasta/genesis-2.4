#!/usr/bin/env python3
"""Create CPU-only and CPU-vs-GPU speedup figures for GENESIS 2.5 scaling results."""

from __future__ import annotations

import csv
import math
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class StatRow:
    benchmark: str
    mode: str
    size: int
    mean_s: float
    ci95_s: float


def format_size_tick(size: int) -> str:
    if size % 1000 == 0:
        return f"{size // 1000}k"
    if size >= 1000:
        return f"{size / 1000:.1f}k"
    return str(size)


def load_summary(path: Path) -> list[StatRow]:
    rows: list[StatRow] = []
    with path.open(newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            rows.append(
                StatRow(
                    benchmark=row["benchmark"],
                    mode=row["mode"],
                    size=int(row["size_value"]),
                    mean_s=float(row["mean_s"]),
                    ci95_s=float(row["ci95_s"]),
                )
            )
    return rows


def plot_cpu_only(path: Path, cpu_rows: list[StatRow]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    names = [
        "mesoscale_sparse_benchmark",
        "biophysical_cellscale_benchmark",
        "region_proxy_microcircuit_benchmark",
    ]
    colors = {
        "mesoscale_sparse_benchmark": "#1f4e79",
        "biophysical_cellscale_benchmark": "#8a3b12",
        "region_proxy_microcircuit_benchmark": "#1e6b43",
    }
    labels = {
        "mesoscale_sparse_benchmark": "Mesoscale",
        "biophysical_cellscale_benchmark": "Biophysical",
        "region_proxy_microcircuit_benchmark": "Region proxy",
    }

    fig, axes = plt.subplots(1, 3, figsize=(16.8, 4.8), sharey=False)
    for i, bench in enumerate(names):
        ax = axes[i]
        rows = sorted([r for r in cpu_rows if r.benchmark == bench], key=lambda x: x.size)
        xs = [r.size for r in rows]
        ys = [r.mean_s for r in rows]
        ylow = [max(r.mean_s - r.ci95_s, 0.0) for r in rows]
        yhigh = [r.mean_s + r.ci95_s for r in rows]

        ax.plot(xs, ys, color=colors[bench], linewidth=2.2, marker="o", markersize=5)
        ax.fill_between(xs, ylow, yhigh, color=colors[bench], alpha=0.18)

        ax.set_title(labels[bench], fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        ax.set_xscale("log")
        ax.set_xticks(xs)
        ax.set_xticklabels([format_size_tick(x) for x in xs], rotation=20, ha="right")
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, axis="y", alpha=0.35)
        if i == 0:
            ax.set_ylabel("CPU runtime (s)")

    fig.suptitle("GENESIS 2.5 CPU Scaling: Mean Runtime and 95% CI", fontsize=13, y=1.03)
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def plot_speedup(path: Path, cpu_rows: list[StatRow], gpu_rows: list[StatRow]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    names = [
        "mesoscale_sparse_benchmark",
        "biophysical_cellscale_benchmark",
        "region_proxy_microcircuit_benchmark",
    ]
    colors = {
        "mesoscale_sparse_benchmark": "#0b6e99",
        "biophysical_cellscale_benchmark": "#9c5315",
        "region_proxy_microcircuit_benchmark": "#1e7f4f",
    }
    labels = {
        "mesoscale_sparse_benchmark": "Mesoscale",
        "biophysical_cellscale_benchmark": "Biophysical",
        "region_proxy_microcircuit_benchmark": "Region proxy",
    }

    cpu_map = {(r.benchmark, r.size): r for r in cpu_rows}
    gpu_map = {(r.benchmark, r.size): r for r in gpu_rows}

    fig, axes = plt.subplots(1, 3, figsize=(16.8, 4.8), sharey=True)
    for i, bench in enumerate(names):
        ax = axes[i]
        sizes = sorted(
            s
            for (b, s) in cpu_map.keys()
            if b == bench and (b, s) in gpu_map
        )
        vals = [cpu_map[(bench, s)].mean_s / gpu_map[(bench, s)].mean_s for s in sizes]

        ax.plot(sizes, vals, color=colors[bench], linewidth=2.2, marker="o", markersize=5)
        ax.axhline(1.0, color="#444444", linewidth=1.2, linestyle="--")

        ax.set_title(labels[bench], fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        ax.set_xscale("log")
        ax.set_xticks(sizes)
        ax.set_xticklabels([format_size_tick(x) for x in sizes], rotation=20, ha="right")
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, axis="y", alpha=0.35)
        if i == 0:
            ax.set_ylabel("Speedup (CPU/GPU)")

    fig.suptitle("OpenCL Acceleration Effect: CPU/GPU Speedup", fontsize=13, y=1.03)
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def write_speedup_table(path: Path, cpu_rows: list[StatRow], gpu_rows: list[StatRow]) -> None:
    cpu_map = {(r.benchmark, r.size): r for r in cpu_rows}
    gpu_map = {(r.benchmark, r.size): r for r in gpu_rows}

    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["benchmark", "size", "cpu_mean_s", "gpu_mean_s", "speedup_cpu_over_gpu"])
        for (benchmark, size), c in sorted(cpu_map.items()):
            g = gpu_map.get((benchmark, size))
            if g is None:
                continue
            speedup = c.mean_s / g.mean_s
            w.writerow([benchmark, size, f"{c.mean_s:.6f}", f"{g.mean_s:.6f}", f"{speedup:.6f}"])


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    cpu_summary = root / "genesis25_cpu_scaling_dense_10rep_summary.csv"
    gpu_summary = root / "genesis25_gpu_scaling_dense_10rep_summary.csv"

    cpu_rows = load_summary(cpu_summary)
    gpu_rows = load_summary(gpu_summary)

    plot_cpu_only(figures / "fig6_cpu_dense_runtime_ci.png", cpu_rows)
    plot_speedup(figures / "fig7_cpu_gpu_speedup.png", cpu_rows, gpu_rows)
    write_speedup_table(root / "genesis25_cpu_gpu_speedup_dense_10rep.csv", cpu_rows, gpu_rows)

    print("Wrote:")
    print(figures / "fig6_cpu_dense_runtime_ci.png")
    print(figures / "fig7_cpu_gpu_speedup.png")
    print(root / "genesis25_cpu_gpu_speedup_dense_10rep.csv")


if __name__ == "__main__":
    main()
