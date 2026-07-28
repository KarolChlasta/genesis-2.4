#!/usr/bin/env python3
"""Generate publication-style GPU scaling figures with dense point coverage."""

from __future__ import annotations

import csv
import math
import re
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import ticker as mticker


@dataclass
class Sample:
    benchmark: str
    size: int
    runtime_s: float
    error_lines: int
    exit_code: int


@dataclass
class GroupStats:
    benchmark: str
    size: int
    runtimes: list[float]
    error_lines: list[int]
    exit_codes: list[int]

    @property
    def n(self) -> int:
        return len(self.runtimes)

    @property
    def mean(self) -> float:
        return sum(self.runtimes) / self.n

    @property
    def sd(self) -> float:
        if self.n < 2:
            return 0.0
        m = self.mean
        return math.sqrt(sum((x - m) ** 2 for x in self.runtimes) / (self.n - 1))

    @property
    def ci95(self) -> float:
        return 1.96 * self.sd / math.sqrt(self.n)

    @property
    def min(self) -> float:
        return min(self.runtimes)

    @property
    def max(self) -> float:
        return max(self.runtimes)

    @property
    def mean_error_lines(self) -> float:
        return sum(self.error_lines) / self.n

    @property
    def fail_count(self) -> int:
        return sum(1 for x in self.exit_codes if x != 0)


def format_size_tick(size: int) -> str:
    if size % 1000 == 0:
        return f"{size // 1000}k"
    if size >= 1000:
        return f"{size / 1000:.1f}k"
    return str(size)


def parse_size_from_large_config(config: str) -> int:
    n_match = re.search(r"N(\d+)_S", config)
    if n_match:
        return int(n_match.group(1))

    ex_inh_match = re.search(r"EX(\d+)x(\d+)_INH(\d+)x(\d+)_S", config)
    if ex_inh_match:
        exx, exy, inhx, inhy = (int(ex_inh_match.group(i)) for i in range(1, 5))
        return exx * exy + inhx * inhy

    raise ValueError(f"Cannot parse config size from: {config}")


def load_samples(root: Path) -> list[Sample]:
    samples: list[Sample] = []

    base_csv = root / "genesis25_three_benchmarks_10rep.csv"
    with base_csv.open(newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            if row["mode"] != "GPU":
                continue
            benchmark = row["benchmark"]
            if benchmark == "region_proxy_microcircuit_benchmark":
                size = 80 * 80 + 40 * 40
            else:
                size = int(row["neurons"])
            samples.append(
                Sample(
                    benchmark=benchmark,
                    size=size,
                    runtime_s=float(row["wall_seconds"]),
                    error_lines=int(row["error_lines"]),
                    exit_code=int(row["exit_code"]),
                )
            )

    large_csv = root / "genesis25_gpu_large_models_5rep.csv"
    with large_csv.open(newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            samples.append(
                Sample(
                    benchmark=row["benchmark"],
                    size=parse_size_from_large_config(row["config"]),
                    runtime_s=float(row["real_seconds"]),
                    error_lines=int(row["error_lines"]),
                    exit_code=int(row["exit_code"]),
                )
            )

    dense_csv = root / "genesis25_gpu_scaling_dense_3rep.csv"
    with dense_csv.open(newline="", encoding="utf-8") as f:
        r = csv.DictReader(f)
        for row in r:
            samples.append(
                Sample(
                    benchmark=row["benchmark"],
                    size=int(row["size_value"]),
                    runtime_s=float(row["real_seconds"]),
                    error_lines=int(row["error_lines"]),
                    exit_code=int(row["exit_code"]),
                )
            )

    return samples


def group_stats(samples: list[Sample]) -> list[GroupStats]:
    grouped: dict[tuple[str, int], dict[str, list[float] | list[int]]] = defaultdict(
        lambda: {"runtimes": [], "errors": [], "exits": []}
    )

    for s in samples:
        key = (s.benchmark, s.size)
        grouped[key]["runtimes"].append(s.runtime_s)
        grouped[key]["errors"].append(s.error_lines)
        grouped[key]["exits"].append(s.exit_code)

    rows: list[GroupStats] = []
    for (benchmark, size), d in grouped.items():
        rows.append(
            GroupStats(
                benchmark=benchmark,
                size=size,
                runtimes=d["runtimes"],
                error_lines=d["errors"],
                exit_codes=d["exits"],
            )
        )

    order = {
        "mesoscale_sparse_benchmark": 0,
        "biophysical_cellscale_benchmark": 1,
        "region_proxy_microcircuit_benchmark": 2,
    }
    rows.sort(key=lambda x: (order.get(x.benchmark, 99), x.size))
    return rows


def write_summary(path: Path, rows: list[GroupStats]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(
            [
                "benchmark",
                "mode",
                "size",
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
        for r in rows:
            w.writerow(
                [
                    r.benchmark,
                    "GPU",
                    r.size,
                    r.n,
                    f"{r.mean:.6f}",
                    f"{r.sd:.6f}",
                    f"{r.ci95:.6f}",
                    f"{r.min:.6f}",
                    f"{r.max:.6f}",
                    f"{r.mean_error_lines:.2f}",
                    r.fail_count,
                ]
            )


def plot_runtime_scaling(path: Path, samples: list[Sample], rows: list[GroupStats]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, axes = plt.subplots(1, 3, figsize=(16.8, 4.8), sharey=False)

    names = [
        "mesoscale_sparse_benchmark",
        "biophysical_cellscale_benchmark",
        "region_proxy_microcircuit_benchmark",
    ]
    colors = {
        "mesoscale_sparse_benchmark": "#0B6E99",
        "biophysical_cellscale_benchmark": "#9C5315",
        "region_proxy_microcircuit_benchmark": "#1E7F4F",
    }
    labels = {
        "mesoscale_sparse_benchmark": "Mesoscale",
        "biophysical_cellscale_benchmark": "Biophysical",
        "region_proxy_microcircuit_benchmark": "Region proxy",
    }

    for i, bench in enumerate(names):
        ax = axes[i]
        bench_samples = [s for s in samples if s.benchmark == bench]
        bench_rows = [r for r in rows if r.benchmark == bench]

        # Replicate points (transparency keeps it readable while showing spread).
        ax.scatter(
            [s.size for s in bench_samples],
            [s.runtime_s for s in bench_samples],
            s=22,
            alpha=0.35,
            color=colors[bench],
            linewidths=0,
        )

        xs = [r.size for r in bench_rows]
        ys = [r.mean for r in bench_rows]
        ylow = [max(r.mean - r.ci95, 0.0) for r in bench_rows]
        yhigh = [r.mean + r.ci95 for r in bench_rows]
        ax.plot(xs, ys, color=colors[bench], linewidth=2.2, marker="o", markersize=5)
        ax.fill_between(xs, ylow, yhigh, color=colors[bench], alpha=0.18)

        ax.set_title(labels[bench], fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        ax.set_xscale("log")
        ax.set_xticks(xs)
        ax.set_xticklabels([format_size_tick(x) for x in xs], rotation=20, ha="right")
        # Keep only explicit major x tick labels; suppress auto scientific minor labels.
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, axis="y", alpha=0.35)
        if i == 0:
            ax.set_ylabel("Runtime (s)")

    fig.suptitle("GENESIS 2.5 GPU Scaling: Replicates, Means, and 95% CI", fontsize=13, y=1.03)
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def plot_normalized_cost(path: Path, rows: list[GroupStats]) -> None:
    plt.style.use("seaborn-v0_8-whitegrid")
    fig, axes = plt.subplots(1, 3, figsize=(15.8, 4.8), sharey=True)

    series = {
        "mesoscale_sparse_benchmark": ("#0B6E99", "Mesoscale"),
        "biophysical_cellscale_benchmark": ("#9C5315", "Biophysical"),
        "region_proxy_microcircuit_benchmark": ("#1E7F4F", "Region proxy"),
    }

    for i, (bench, (color, label)) in enumerate(series.items()):
        ax = axes[i]
        bench_rows = [r for r in rows if r.benchmark == bench]
        xs = [r.size for r in bench_rows]
        ys = [r.mean / r.size for r in bench_rows]
        ax.plot(xs, ys, marker="o", linewidth=2.1, markersize=5, color=color)

        ax.set_xscale("log")
        ax.set_yscale("log")
        ax.set_xticks(xs)
        ax.set_xticklabels([format_size_tick(x) for x in xs], rotation=20, ha="right")
        # Keep only explicit major x tick labels; suppress auto scientific minor labels.
        ax.xaxis.set_minor_locator(mticker.NullLocator())
        ax.xaxis.set_minor_formatter(mticker.NullFormatter())
        ax.tick_params(axis="x", labelsize=8)
        ax.grid(True, which="both", alpha=0.28)
        ax.set_title(label, fontsize=11, pad=8)
        ax.set_xlabel("Model size (cells)")
        if i == 0:
            ax.set_ylabel("Runtime per cell (s/cell)")

    fig.suptitle("Normalized Cost Trend (lower is better)", fontsize=13, y=1.02)
    fig.tight_layout()
    fig.savefig(path, dpi=320, bbox_inches="tight")
    plt.close(fig)


def main() -> None:
    root = Path(__file__).resolve().parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    out_summary = root / "genesis25_gpu_scaling_publication_summary.csv"
    out_fig1 = figures / "fig4_gpu_large_runtime_ci.png"
    out_fig2 = figures / "fig5_gpu_large_scaling_trend.png"

    samples = load_samples(root)
    rows = group_stats(samples)

    write_summary(out_summary, rows)
    plot_runtime_scaling(out_fig1, samples, rows)
    plot_normalized_cost(out_fig2, rows)

    print("Wrote:")
    print(out_summary)
    print(out_fig1)
    print(out_fig2)


if __name__ == "__main__":
    main()
