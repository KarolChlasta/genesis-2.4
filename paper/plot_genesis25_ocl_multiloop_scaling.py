#!/usr/bin/env python3
"""Figures for the OCL multiloop (fp32) vs CPU (fp64) scaling sweep.

Reads genesis25_ocl_multiloop_scaling_summary.csv (see
run_genesis25_ocl_multiloop_scaling.py) and produces a runtime-with-CI figure
and a speedup figure, matching the visual style of
plot_genesis25_cpu_gpu_speedup.py (fig6/fig7) for consistency across the paper.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class Row:
    n: int
    cpu_mean: float
    cpu_ci95: float
    gpu_mean: float
    gpu_ci95: float
    speedup: float


def format_size_tick(size: int) -> str:
    if size % 1000 == 0:
        return f"{size // 1000}k"
    return str(size)


def load_summary(path: Path) -> list[Row]:
    rows = []
    with path.open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            rows.append(Row(
                n=int(r["N"]),
                cpu_mean=float(r["cpu_mean_s"]), cpu_ci95=float(r["cpu_ci95_s"]),
                gpu_mean=float(r["gpu_mean_s"]), gpu_ci95=float(r["gpu_ci95_s"]),
                speedup=float(r["speedup"]),
            ))
    return sorted(rows, key=lambda x: x.n)


def plot_runtime(path: Path, rows: list[Row]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(6.4, 4.6))

    xs = [r.n for r in rows]
    cpu_y = [r.cpu_mean for r in rows]
    cpu_lo = [max(r.cpu_mean - r.cpu_ci95, 0.0) for r in rows]
    cpu_hi = [r.cpu_mean + r.cpu_ci95 for r in rows]
    gpu_y = [r.gpu_mean for r in rows]
    gpu_lo = [max(r.gpu_mean - r.gpu_ci95, 0.0) for r in rows]
    gpu_hi = [r.gpu_mean + r.gpu_ci95 for r in rows]

    ax.plot(xs, cpu_y, color="#1f4e79", linewidth=2.2, marker="o", markersize=5, label="CPU (fp64, scheduler-fixed)")
    ax.fill_between(xs, cpu_lo, cpu_hi, color="#1f4e79", alpha=0.18)
    ax.plot(xs, gpu_y, color="#9c5315", linewidth=2.2, marker="o", markersize=5, label="GPU multiloop (fp32)")
    ax.fill_between(xs, gpu_lo, gpu_hi, color="#9c5315", alpha=0.18)

    ax.set_xlabel("N neurons")
    ax.set_ylabel("Step-loop wall time, 5000 steps (s)")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xticks(xs)
    ax.set_xticklabels([format_size_tick(x) for x in xs], rotation=20, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.grid(True, axis="y", alpha=0.35)
    ax.legend()
    ax.set_title("GENESIS 2.5: CPU vs GPU-multiloop step-loop time (95% CI, n=30)")

    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def plot_speedup(path: Path, rows: list[Row]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(6.4, 4.6))

    xs = [r.n for r in rows]
    ys = [r.speedup for r in rows]

    ax.plot(xs, ys, color="#1e7f4f", linewidth=2.2, marker="o", markersize=6)
    ax.axhline(1.0, color="#444444", linewidth=1.2, linestyle="--")
    for x, y in zip(xs, ys):
        ax.annotate(f"{y:.1f}x", (x, y), textcoords="offset points", xytext=(0, 8), ha="center")

    ax.set_xlabel("N neurons")
    ax.set_ylabel("Speedup (CPU/GPU)")
    ax.set_xscale("log")
    ax.set_xticks(xs)
    ax.set_xticklabels([format_size_tick(x) for x in xs], rotation=20, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.grid(True, axis="y", alpha=0.35)
    ax.set_title("GENESIS 2.5: end-to-end speedup, GPU multiloop mode (n=30)")

    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    rows = load_summary(root / "genesis25_ocl_multiloop_scaling_summary.csv")

    plot_runtime(figures / "fig8_ocl_multiloop_runtime_ci.png", rows)
    plot_speedup(figures / "fig9_ocl_multiloop_speedup.png", rows)

    print("Wrote:")
    print(figures / "fig8_ocl_multiloop_runtime_ci.png")
    print(figures / "fig9_ocl_multiloop_speedup.png")


if __name__ == "__main__":
    main()
