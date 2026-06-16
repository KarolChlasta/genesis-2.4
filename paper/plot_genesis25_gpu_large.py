#!/usr/bin/env python3
"""Summarize and plot large-model GPU benchmark campaign results."""

from __future__ import annotations

import csv
import math
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt


@dataclass
class GroupStats:
    benchmark: str
    config: str
    times: list[float]
    errors: list[int]
    exits: list[int]

    @property
    def n(self) -> int:
        return len(self.times)

    @property
    def mean(self) -> float:
        return sum(self.times) / self.n

    @property
    def std(self) -> float:
        if self.n < 2:
            return 0.0
        m = self.mean
        return math.sqrt(sum((x - m) ** 2 for x in self.times) / (self.n - 1))

    @property
    def ci95(self) -> float:
        return 1.96 * self.std / math.sqrt(self.n)

    @property
    def min(self) -> float:
        return min(self.times)

    @property
    def max(self) -> float:
        return max(self.times)

    @property
    def mean_errors(self) -> float:
        return sum(self.errors) / self.n

    @property
    def fail_count(self) -> int:
        return sum(1 for x in self.exits if x != 0)


def load_stats(path: Path) -> list[GroupStats]:
    grouped: dict[tuple[str, str], dict[str, list[float] | list[int]]] = defaultdict(
        lambda: {"times": [], "errors": [], "exits": []}
    )

    with path.open(newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            key = (row["benchmark"], row["config"])
            grouped[key]["times"].append(float(row["real_seconds"]))
            grouped[key]["errors"].append(int(row["error_lines"]))
            grouped[key]["exits"].append(int(row["exit_code"]))

    stats: list[GroupStats] = []
    for (benchmark, config), d in grouped.items():
        stats.append(
            GroupStats(
                benchmark=benchmark,
                config=config,
                times=d["times"],
                errors=d["errors"],
                exits=d["exits"],
            )
        )

    order = {
        "mesoscale_sparse_benchmark": 0,
        "biophysical_cellscale_benchmark": 1,
        "region_proxy_microcircuit_benchmark": 2,
    }
    stats.sort(key=lambda s: (order.get(s.benchmark, 99), s.config))
    return stats


def write_summary(path: Path, stats: list[GroupStats]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(
            [
                "benchmark",
                "mode",
                "config",
                "n",
                "mean_s",
                "sd_s",
                "ci95_s",
                "min_s",
                "max_s",
                "mean_error_lines",
                "fail_count",
            ]
        )
        for s in stats:
            w.writerow(
                [
                    s.benchmark,
                    "GPU",
                    s.config,
                    s.n,
                    f"{s.mean:.6f}",
                    f"{s.std:.6f}",
                    f"{s.ci95:.6f}",
                    f"{s.min:.6f}",
                    f"{s.max:.6f}",
                    f"{s.mean_errors:.2f}",
                    s.fail_count,
                ]
            )


def plot_grouped_bars(path: Path, stats: list[GroupStats]) -> None:
    fig, ax = plt.subplots(figsize=(10, 4.6))
    x = list(range(len(stats)))
    means = [s.mean for s in stats]
    cis = [s.ci95 for s in stats]
    colors = []
    for s in stats:
        if s.benchmark.startswith("mesoscale"):
            colors.append("#1f77b4")
        elif s.benchmark.startswith("biophysical"):
            colors.append("#ff7f0e")
        else:
            colors.append("#2ca02c")

    ax.bar(x, means, yerr=cis, capsize=5, color=colors)
    ax.set_xticks(x)
    ax.set_xticklabels([f"{s.benchmark}\n{s.config}" for s in stats], rotation=20, ha="right")
    ax.set_ylabel("Runtime (s)")
    ax.set_title("GENESIS 2.5 Proposal: Large-Model GPU Runtime (mean ± 95% CI)")
    ax.grid(axis="y", alpha=0.25)
    fig.tight_layout()
    fig.savefig(path, dpi=180)
    plt.close(fig)


def plot_scaling_per_benchmark(path: Path, stats: list[GroupStats]) -> None:
    grouped: dict[str, list[GroupStats]] = defaultdict(list)
    for s in stats:
        grouped[s.benchmark].append(s)

    fig, ax = plt.subplots(figsize=(8.5, 4.6))
    for benchmark, rows in grouped.items():
        rows = sorted(rows, key=lambda r: r.mean)
        labels = [r.config for r in rows]
        vals = [r.mean for r in rows]
        ax.plot(labels, vals, marker="o", linewidth=2, label=benchmark)

    ax.set_ylabel("Runtime (s)")
    ax.set_title("Large-Model GPU Scaling Trend by Benchmark")
    ax.grid(axis="y", alpha=0.25)
    ax.legend(frameon=False)
    fig.tight_layout()
    fig.savefig(path, dpi=180)
    plt.close(fig)


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    raw_csv = root / "genesis25_gpu_large_models_5rep.csv"
    summary_csv = root / "genesis25_gpu_large_models_5rep_summary.csv"
    fig_bar = figures / "fig4_gpu_large_runtime_ci.png"
    fig_scale = figures / "fig5_gpu_large_scaling_trend.png"

    stats = load_stats(raw_csv)
    write_summary(summary_csv, stats)
    plot_grouped_bars(fig_bar, stats)
    plot_scaling_per_benchmark(fig_scale, stats)

    print("Wrote:")
    print(raw_csv)
    print(summary_csv)
    print(fig_bar)
    print(fig_scale)


if __name__ == "__main__":
    main()
