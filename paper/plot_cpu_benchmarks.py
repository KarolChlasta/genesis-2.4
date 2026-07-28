#!/usr/bin/env python3
"""Generate summary table and publication-style figures for CPU benchmark CSVs."""

from __future__ import annotations

import csv
import math
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt


@dataclass
class ModelStats:
    name: str
    times: list[float]
    errors: list[int]

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
        mean = self.mean
        var = sum((x - mean) ** 2 for x in self.times) / (self.n - 1)
        return math.sqrt(var)

    @property
    def cv_pct(self) -> float:
        return 100.0 * self.std / self.mean

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


def load_csv(path: Path, name: str) -> ModelStats:
    times: list[float] = []
    errors: list[int] = []
    with path.open(newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            times.append(float(row["real_seconds"]))
            errors.append(int(row["error_lines"]))
    return ModelStats(name=name, times=times, errors=errors)


def save_summary_table(path: Path, stats: list[ModelStats]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(
            [
                "model",
                "n",
                "mean_s",
                "sd_s",
                "cv_pct",
                "ci95_s",
                "min_s",
                "max_s",
                "mean_error_lines",
            ]
        )
        for s in stats:
            w.writerow(
                [
                    s.name,
                    s.n,
                    f"{s.mean:.6f}",
                    f"{s.std:.6f}",
                    f"{s.cv_pct:.2f}",
                    f"{s.ci95:.6f}",
                    f"{s.min:.6f}",
                    f"{s.max:.6f}",
                    f"{s.mean_errors:.2f}",
                ]
            )


def plot_mean_ci(path: Path, stats: list[ModelStats]) -> None:
    names = [s.name for s in stats]
    means = [s.mean for s in stats]
    cis = [s.ci95 for s in stats]

    fig, ax = plt.subplots(figsize=(7, 4))
    ax.bar(names, means, yerr=cis, capsize=6, color=["#1f77b4", "#ff7f0e"])
    ax.set_ylabel("Runtime (s)")
    ax.set_title("Mean Runtime with 95% CI")
    ax.grid(axis="y", alpha=0.25)
    fig.tight_layout()
    fig.savefig(path, dpi=180)
    plt.close(fig)


def plot_boxplot(path: Path, stats: list[ModelStats]) -> None:
    fig, ax = plt.subplots(figsize=(7, 4))
    ax.boxplot(
        [s.times for s in stats],
        tick_labels=[s.name for s in stats],
        showmeans=True,
    )
    ax.set_ylabel("Runtime (s)")
    ax.set_title("Runtime Distribution Across Replicates")
    ax.grid(axis="y", alpha=0.25)
    fig.tight_layout()
    fig.savefig(path, dpi=180)
    plt.close(fig)


def plot_error_lines(path: Path, stats: list[ModelStats]) -> None:
    names = [s.name for s in stats]
    errs = [s.mean_errors for s in stats]

    fig, ax = plt.subplots(figsize=(7, 4))
    ax.bar(names, errs, color=["#2ca02c", "#d62728"])
    ax.set_ylabel("Mean error lines per run")
    ax.set_title("Headless Diagnostics Volume")
    ax.grid(axis="y", alpha=0.25)
    fig.tight_layout()
    fig.savefig(path, dpi=180)
    plt.close(fig)


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    cal8 = load_csv(root / "cal8_nxgenesis_benchmark.csv", "Cal8.g")
    cal7 = load_csv(root / "cal7difshell_nxgenesis_benchmark.csv", "Cal7difshell.g")
    stats = [cal8, cal7]

    save_summary_table(root / "table1_runtime_summary.csv", stats)
    plot_mean_ci(figures / "fig1_mean_runtime_ci.png", stats)
    plot_boxplot(figures / "fig2_runtime_boxplot.png", stats)
    plot_error_lines(figures / "fig3_headless_error_lines.png", stats)

    print("Wrote:")
    print(root / "table1_runtime_summary.csv")
    print(figures / "fig1_mean_runtime_ci.png")
    print(figures / "fig2_runtime_boxplot.png")
    print(figures / "fig3_headless_error_lines.png")


if __name__ == "__main__":
    main()
