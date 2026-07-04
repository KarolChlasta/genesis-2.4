#!/usr/bin/env python3
"""Publication figures for the GENESIS 2.5 overnight campaign.

Reads the campaign summary CSVs written by run_overnight_campaign.py and emits
four figures into paper/figures/. Colourblind-safe Okabe-Ito palette; single
y-axis per panel (throughput and real-time factor are separate stacked panels,
never a dual axis); 95% CI error bars where available. Gracefully skips a figure
whose CSV is not present yet, so it can be run while the campaign is still going.
"""
from __future__ import annotations

import csv
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

P = Path(__file__).resolve().parent
FIG = P / "figures"
FIG.mkdir(exist_ok=True)

# Okabe-Ito colourblind-safe qualitative palette
BLUE, ORANGE, GREEN, VERM = "#0072B2", "#E69F00", "#009E73", "#D55E00"
plt.rcParams.update({
    "font.size": 11, "axes.grid": True, "grid.alpha": 0.3,
    "grid.linewidth": 0.6, "axes.axisbelow": True,
    "figure.dpi": 150, "savefig.bbox": "tight",
})


def read(path: Path):
    if not path.exists():
        return None
    with path.open() as f:
        rows = list(csv.DictReader(f))
    return rows or None


def fnum(r, k):
    try:
        return float(r[k])
    except (KeyError, ValueError, TypeError):
        return None


# --------------------------------------------------------------------------
def fig_speedup():
    rows = read(P / "campaign_final_table.csv")
    if not rows:
        print("skip speedup: no final table"); return
    N    = [int(r["N"]) for r in rows]
    sus  = [fnum(r, "speedup_sustained") for r in rows]
    sing = [fnum(r, "speedup_singlerun") for r in rows]
    e2e  = [fnum(r, "end2end_singlerun") for r in rows]
    fig, ax = plt.subplots(figsize=(7.2, 4.8))
    ax.plot(N, sus,  "-o", color=BLUE,   lw=2, ms=7, label="Step-phase, sustained (warm GPU)")
    ax.plot(N, sing, "-s", color=ORANGE, lw=2, ms=7, label="Step-phase, single cold-start run")
    ax.plot(N, e2e,  "-^", color=GREEN,  lw=2, ms=7, label="End-to-end, single run (incl. build)")
    ax.axhline(1.0, color="0.5", lw=1, ls="--")
    ax.text(N[-1], 1.15, "parity (1×)", color="0.4", fontsize=9, va="bottom", ha="right")
    ax.set_xscale("log")
    ax.set_ylim(0, 21)
    ax.set_xlabel("Number of HH neurons  $N$  (single hsolve, $K$=50000 steps)")
    ax.set_ylabel("Speedup  (CPU fp64 / GPU fp32)")
    ax.set_title("GENESIS 2.5 OpenCL multiloop speedup — AMD Radeon 890M", pad=12)
    # opaque framed legend, placed in the empty upper-right where all curves are low
    leg = ax.legend(frameon=True, framealpha=0.95, edgecolor="0.6",
                    facecolor="white", loc="upper right", fontsize=9,
                    borderpad=0.7, labelspacing=0.5)
    leg.get_frame().set_linewidth(0.8)
    # annotate the peak beside the marker (not above, to clear the title)
    i = max(range(len(sus)), key=lambda k: (sus[k] or 0))
    ax.annotate(f"{sus[i]:.0f}×", (N[i], sus[i]), textcoords="offset points",
                xytext=(-6, 8), ha="right", color=BLUE, fontsize=11, fontweight="bold")
    fig.savefig(FIG / "fig_campaign_speedup.png")
    plt.close(fig)
    print("wrote fig_campaign_speedup.png")


def fig_throughput():
    rows = read(P / "campaign_wallclock_summary.csv")
    if not rows:
        print("skip throughput: no summary yet"); return
    N   = [int(r["N"]) for r in rows]
    thr = [(fnum(r, "gpu_throughput_nsteps_per_s") or 0) / 1e6 for r in rows]
    rtf = [fnum(r, "gpu_realtime_factor") for r in rows]
    fig, (a1, a2) = plt.subplots(2, 1, figsize=(7, 6), sharex=True)
    a1.plot(N, thr, "-o", color=GREEN, lw=2, ms=7)
    a1.set_ylabel("GPU throughput\n(M neuron-steps / s)")
    a1.set_title("GENESIS 2.5 GPU throughput and real-time factor vs network size")
    a2.plot(N, rtf, "-o", color=VERM, lw=2, ms=7)
    a2.axhline(1.0, color="0.5", lw=1, ls="--")
    a2.text(N[0], 1.05, "real time (1×)", color="0.4", fontsize=9, va="bottom")
    a2.set_ylabel("GPU real-time factor\n(bio s / wall s)")
    a2.set_xlabel("Number of HH neurons  $N$")
    a2.set_xscale("log")
    fig.savefig(FIG / "fig_campaign_throughput.png")
    plt.close(fig)
    print("wrote fig_campaign_throughput.png")


def fig_ksweep():
    rows = read(P / "campaign_ksweep.csv")
    if not rows:
        print("skip ksweep: no csv yet"); return
    K   = [int(r["K"]) for r in rows]
    st  = [fnum(r, "speedup_step") for r in rows]
    e2e = [fnum(r, "speedup_end2end") for r in rows]
    n = rows[0]["N"]
    fig, ax = plt.subplots(figsize=(7, 4.4))
    ax.plot(K, st, "-o", color=BLUE, lw=2, ms=7, label="Step-phase")
    ax.plot(K, e2e, "-s", color=ORANGE, lw=2, ms=7, label="End-to-end")
    ax.axhline(1.0, color="0.5", lw=1, ls="--")
    ax.set_xscale("log")
    ax.set_xlabel(f"Simulation length  $K$  (steps;  $N$={n} neurons)")
    ax.set_ylabel("Speedup  (CPU fp64 / GPU fp32)")
    ax.set_title("End-to-end speedup approaches step-phase as the run lengthens")
    ax.legend(frameon=False, loc="upper left")
    fig.savefig(FIG / "fig_campaign_ksweep.png")
    plt.close(fig)
    print("wrote fig_campaign_ksweep.png")


def fig_divergence():
    rows = read(P / "campaign_divergence.csv")
    if not rows:
        print("skip divergence: no csv yet"); return
    steps = [int(r["steps"]) for r in rows]
    dp = [fnum(r, "abs_dev_perstep_V") for r in rows]
    dm = [fnum(r, "abs_dev_multiloop_V") for r in rows]
    fig, ax = plt.subplots(figsize=(7, 4.4))
    ax.plot(steps, dp, "-o", color=BLUE, lw=2, ms=7, label="GPU per-step vs CPU")
    ax.plot(steps, dm, "-s", color=ORANGE, lw=2, ms=7, label="GPU multiloop vs CPU")
    ax.set_yscale("log")
    ax.set_xlabel("Simulated steps  (dt = 10 µs;  driven, spiking)")
    ax.set_ylabel("|Vm(GPU fp32) − Vm(CPU fp64)|  (V)")
    ax.set_title("fp32 accelerator vs fp64 CPU: single-neuron voltage agreement")
    ax.legend(frameon=False, loc="upper left")
    fig.savefig(FIG / "fig_campaign_divergence.png")
    plt.close(fig)
    print("wrote fig_campaign_divergence.png")


if __name__ == "__main__":
    fig_speedup()
    fig_throughput()
    fig_ksweep()
    fig_divergence()
