#!/usr/bin/env python3
"""Generate corrected GPU figures (fig4, fig5, fig7) using valid multiloop data.

Replaces the earlier figures that used passive-compartment benchmarks where
OCL was never dispatched.  Source data: genesis25_ocl_multiloop_scaling_raw.csv
(30 replicates per N, both CPU fp64 and GPU fp32 multiloop arms).
"""

from __future__ import annotations

import csv
import math
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class Sample:
    n: int
    mode: str
    seconds: float


@dataclass
class GroupStats:
    n: int
    mode: str
    runtimes: list

    @property
    def count(self):
        return len(self.runtimes)

    @property
    def mean(self):
        return sum(self.runtimes) / self.count

    @property
    def sd(self):
        if self.count < 2:
            return 0.0
        m = self.mean
        return math.sqrt(sum((x - m) ** 2 for x in self.runtimes) / (self.count - 1))

    @property
    def ci95(self):
        return 1.96 * self.sd / math.sqrt(self.count)


def format_n(n: int) -> str:
    if n >= 1000 and n % 1000 == 0:
        return f"{n // 1000}k"
    if n >= 1000:
        return f"{n / 1000:.0f}k"
    return str(n)


def load_raw(path: Path) -> list[Sample]:
    samples = []
    with path.open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            samples.append(Sample(
                n=int(row["N"]),
                mode=row["mode"],
                seconds=float(row["seconds"]),
            ))
    return samples


def compute_stats(samples: list[Sample]) -> dict[tuple, GroupStats]:
    grouped = defaultdict(list)
    for s in samples:
        grouped[(s.n, s.mode)].append(s.seconds)
    return {
        k: GroupStats(n=k[0], mode=k[1], runtimes=v)
        for k, v in grouped.items()
    }


# --------------------------------------------------------------------------
# fig4: GPU multiloop runtime CI (mirrors fig6 CPU-only style)
# --------------------------------------------------------------------------

def plot_fig4(path: Path, samples: list[Sample], stats: dict) -> None:
    """GPU multiloop step-loop runtime with replicates and 95% CI."""
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(7.2, 4.8))

    gpu_stats = sorted(
        [v for k, v in stats.items() if v.mode == "GPU"],
        key=lambda x: x.n,
    )
    gpu_samples = [s for s in samples if s.mode == "GPU"]

    color = "#1e7f4f"
    xs = [g.n for g in gpu_stats]
    ys = [g.mean for g in gpu_stats]
    ylo = [max(g.mean - g.ci95, 0.0) for g in gpu_stats]
    yhi = [g.mean + g.ci95 for g in gpu_stats]

    # Replicate scatter
    ax.scatter(
        [s.n for s in gpu_samples],
        [s.seconds for s in gpu_samples],
        s=18, alpha=0.30, color=color, linewidths=0,
    )
    ax.plot(xs, ys, color=color, linewidth=2.2, marker="o", markersize=5,
            label="GPU multiloop (fp32)")
    ax.fill_between(xs, ylo, yhi, color=color, alpha=0.18)

    ax.set_xlabel("N neurons")
    ax.set_ylabel("Runtime (s)")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xticks(xs)
    ax.set_xticklabels([format_n(x) for x in xs], rotation=20, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.tick_params(axis="x", labelsize=9)
    ax.grid(True, axis="y", alpha=0.35)
    ax.legend(fontsize=9)
    ax.set_title(
        "GENESIS 2.5 GPU Multiloop: Step-loop Runtime with 95% CI (n=30)",
        fontsize=12, pad=8,
    )
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


# --------------------------------------------------------------------------
# fig5: normalized cost (s/neuron) for GPU multiloop — mirrors original
#        3-panel normalized-cost style collapsed to one panel
# --------------------------------------------------------------------------

def plot_fig5(path: Path, stats: dict) -> None:
    """GPU multiloop normalized cost (runtime per neuron, log-log)."""
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(6.4, 4.8))

    gpu_stats = sorted(
        [v for k, v in stats.items() if v.mode == "GPU"],
        key=lambda x: x.n,
    )
    cpu_stats = sorted(
        [v for k, v in stats.items() if v.mode == "CPU"],
        key=lambda x: x.n,
    )

    color_gpu = "#1e7f4f"
    color_cpu = "#1f4e79"

    xs_gpu = [g.n for g in gpu_stats]
    ys_gpu = [g.mean / g.n for g in gpu_stats]
    xs_cpu = [g.n for g in cpu_stats]
    ys_cpu = [g.mean / g.n for g in cpu_stats]

    ax.plot(xs_cpu, ys_cpu, marker="o", linewidth=2.1, markersize=5,
            color=color_cpu, label="CPU (fp64)")
    ax.plot(xs_gpu, ys_gpu, marker="o", linewidth=2.1, markersize=5,
            color=color_gpu, label="GPU multiloop (fp32)")

    ax.set_xscale("log")
    ax.set_yscale("log")
    all_xs = sorted(set(xs_gpu + xs_cpu))
    ax.set_xticks(all_xs)
    ax.set_xticklabels([format_n(x) for x in all_xs], rotation=20, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.tick_params(axis="x", labelsize=9)
    ax.grid(True, which="both", alpha=0.28)
    ax.set_xlabel("N neurons")
    ax.set_ylabel("Runtime per neuron (s/neuron)")
    ax.legend(fontsize=9)
    ax.set_title(
        "Normalized Cost: Runtime per Neuron — GPU Multiloop vs CPU (lower is better)",
        fontsize=11, pad=8,
    )
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


# --------------------------------------------------------------------------
# fig7: GPU multiloop speedup — replaces the ~1.0 passive-compartment result
# --------------------------------------------------------------------------

def plot_fig7(path: Path, stats: dict) -> None:
    """Actual GPU multiloop speedup (CPU/GPU), replacing the passive-compartment null result."""
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(7.2, 4.8))

    ns = sorted(set(k[0] for k in stats.keys()))
    speedups = []
    for n in ns:
        cpu = stats.get((n, "CPU"))
        gpu = stats.get((n, "GPU"))
        if cpu and gpu:
            speedups.append((n, cpu.mean / gpu.mean))

    xs = [s[0] for s in speedups]
    ys = [s[1] for s in speedups]

    color = "#1e7f4f"
    ax.plot(xs, ys, color=color, linewidth=2.2, marker="o", markersize=6)
    ax.axhline(1.0, color="#444444", linewidth=1.2, linestyle="--", label="1× (no speedup)")

    for x, y in zip(xs, ys):
        ax.annotate(
            f"{y:.1f}×",
            (x, y), textcoords="offset points",
            xytext=(0, 9), ha="center", fontsize=9,
        )

    ax.set_xlabel("N neurons")
    ax.set_ylabel("Speedup (CPU/GPU)")
    ax.set_xscale("log")
    ax.set_xticks(xs)
    ax.set_xticklabels([format_n(x) for x in xs], rotation=20, ha="right")
    ax.xaxis.set_minor_locator(mticker.NullLocator())
    ax.xaxis.set_minor_formatter(mticker.NullFormatter())
    ax.tick_params(axis="x", labelsize=9)
    ax.grid(True, axis="y", alpha=0.35)
    ax.legend(fontsize=9)
    ax.set_title(
        "GPU Multiloop Speedup: CPU(fp64) / GPU(fp32) — HH1952 neurons, K=5000 steps (n=30)",
        fontsize=11, pad=8,
    )
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    raw_path = root / "genesis25_ocl_multiloop_scaling_raw.csv"
    samples = load_raw(raw_path)
    stats = compute_stats(samples)

    out4 = figures / "fig4_gpu_large_runtime_ci.png"
    out5 = figures / "fig5_gpu_large_scaling_trend.png"
    out7 = figures / "fig7_cpu_gpu_speedup.png"

    plot_fig4(out4, samples, stats)
    plot_fig5(out5, stats)
    plot_fig7(out7, stats)

    print("Wrote:")
    for p in (out4, out5, out7):
        print(f"  {p}")


if __name__ == "__main__":
    main()
