#!/usr/bin/env python3
"""Figure: GENESIS 2.5 against NEURON and CoreNEURON on the Vogels-Abbott network.

One measure (wall-clock time for the same simulation), so the bars carry a single
hue rather than a categorical palette; GENESIS is the one entity the reader is
being asked to locate, so it alone is accented. Sorted fastest-first, values
labelled directly, no legend -- with a single series the title names it.

Data: cluster_bringup/coreneuron/README.md, all arms single-threaded CPU on UMCS
node inf03, 4000 cells, 5.0 s simulated, dt = 0.05 ms.
"""

from __future__ import annotations

from pathlib import Path

import matplotlib.pyplot as plt

ACCENT = "#1e7f4f"   # GENESIS -- same green as the A100 series in fig10
NEUTRAL = "#8a8f98"  # the simulators being compared against
INK = "#222222"

# label, mean seconds, std (None = single run), replicates
ROWS = [
    ("GENESIS 2.5\n(no accelerator)", 46.9, 2.1, 3),
    ("CoreNEURON 9.0.2", 76.5, 0.3, 3),
    ("NEURON 8.0.2", 76.5, None, 1),
    ("NEURON 9.0.2", 95.8, 0.2, 3),
    ("NEURON 9.0.2\n(ChannelBuilder)", 123.3, None, 1),
]

# 4000 cells x 100,000 steps of simulated time
NEURON_STEPS = 4000 * 100_000


def main() -> None:
    root = Path(__file__).resolve().parent.parent
    figures = root / "figures"
    figures.mkdir(exist_ok=True)

    rows = sorted(ROWS, key=lambda r: r[1])
    labels = [r[0] for r in rows]
    means = [r[1] for r in rows]
    errs = [r[2] if r[2] is not None else 0.0 for r in rows]
    single = [r[3] == 1 for r in rows]

    plt.style.use("seaborn-v0_8-whitegrid")
    fig, ax = plt.subplots(figsize=(8.0, 4.0))

    y = range(len(rows))
    colors = [ACCENT if "GENESIS" in l else NEUTRAL for l in labels]
    bars = ax.barh(list(y), means, xerr=errs, height=0.62, color=colors,
                   error_kw={"ecolor": "#444444", "capsize": 3, "lw": 1.2},
                   zorder=3)
    # A single run is not a mean; hatch it so the distinction is not colour-only.
    for b, is_single in zip(bars, single):
        if is_single:
            b.set_hatch("//")
            b.set_edgecolor("#ffffff")
            b.set_linewidth(0.0)

    for i, (l, m, e, n) in enumerate(rows):
        thr = NEURON_STEPS / m / 1e6
        note = f"{m:.1f} s" if n > 1 else f"{m:.1f} s (single run)"
        ax.text(m + (e or 0) + 2.5, i, f"{note}   |   {thr:.1f}M steps/s",
                va="center", ha="left", fontsize=9, color=INK)

    ax.set_yticks(list(y))
    ax.set_yticklabels(labels, fontsize=9.5)
    ax.invert_yaxis()
    ax.set_xlabel("Wall-clock time for the 5 s simulation (s), lower is better")
    ax.set_xlim(0, 168)
    ax.grid(True, axis="x", alpha=0.35)
    ax.grid(False, axis="y")
    for side in ("top", "right", "left"):
        ax.spines[side].set_visible(False)
    ax.tick_params(axis="y", length=0)

    ax.set_title("Vogels–Abbott COBAHH network, 4000 cells, 5 s, dt = 0.05 ms\n"
                 "single-threaded CPU, one cluster node", fontsize=11)

    fig.tight_layout()
    out = figures / "fig12_coreneuron_comparison.png"
    fig.savefig(out, dpi=320, bbox_inches="tight")
    plt.close(fig)
    print("Wrote:", out)


if __name__ == "__main__":
    main()
