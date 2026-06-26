#!/usr/bin/env python3
"""CPU (fp64) vs GPU multiloop (fp32) scaling sweep for ocl_hh_benchmark.g.

Replaces the retired run_genesis25_cpu_gpu_longrun_4x2h.sh / mesoscale_sparse_benchmark.g
combination, which never created an hsolve and therefore never dispatched to the GPU
(CPU-vs-CPU only). This sweep uses ocl_hh_benchmark.g (real tabchannel HH channels,
hsolve chanmode=4/calcmode=1) and the chip_channel_multiloop kernel, the only path
measured to give a genuine end-to-end win on this hardware (see
project_gpu_fp32_port.md). CPU arm uses nxgenesis_nocl (compiled without USE_OPENCL,
rebuilt 2026-06-26 to include the hines_init.c scheduler fix); GPU arm uses nxgenesis
with GENESIS_OCL_MULTILOOP set, reading the kernel's own clock_gettime dispatch report
rather than GENESIS's {cpu} timer (which undercounts GPU-blocked wall time -- see
methodological note in the manuscript, Section "fp32 port and post-scheduler-fix
verification").
"""

from __future__ import annotations

import csv
import os
import re
import statistics
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SCRIPT = "genesis/Scripts/benchmark/ocl_hh_benchmark.g"
CPU_BIN = "genesis/src/nxgenesis_nocl"
GPU_BIN = "genesis/src/nxgenesis"
STEPS = 5000

NS = [500, 1000, 2000, 5000, 10000, 20000]
REPS = 30
# N=50000 dropped from the statistical sweep: a single dry-run timing showed
# ~90s wall time per run there (vs ~3s reported step time) -- construction cost
# scales far worse than linearly (~O(N^2)-ish from the two anchor points), which
# would dominate a 30-rep sweep (~90min alone) and conflates a script-interpreter
# scaling issue with the GPU-vs-CPU question this sweep is meant to answer.
# Single observation (not part of this sweep's stats): N=50000 cpu wall=94.84s,
# gpu wall=84.29s, both step-loop times tiny (cpu=3.11s, gpu dispatch=2.32s).
# Flagged as a separate finding -- see project_gpu_fp32_port.md.
WARMUP = 1  # one extra untimed rep per (N, mode), excluded from stats

RAW_CSV = ROOT / "paper" / "genesis25_ocl_multiloop_scaling_raw.csv"
SUMMARY_CSV = ROOT / "paper" / "genesis25_ocl_multiloop_scaling_summary.csv"

CPU_STEP_RE = re.compile(r"completed (\d+) steps in ([\d.]+) cpu seconds")
GPU_DISPATCH_RE = re.compile(r"OCL MULTILOOP:.*?total ([\d.]+) ms", re.S)


def run_cpu(n: int) -> float:
    out = subprocess.run(
        [str(ROOT / CPU_BIN), "-nosimrc", "-notty", "-batch", SCRIPT, str(n), str(STEPS)],
        capture_output=True, text=True, cwd=ROOT,
    ).stdout
    matches = CPU_STEP_RE.findall(out)
    if not matches:
        raise RuntimeError(f"CPU run N={n}: no step-loop timing found:\n{out[-1500:]}")
    return float(matches[-1][1])


def run_gpu(n: int) -> float:
    env = os.environ.copy()
    env["GENESIS_OCL_MULTILOOP"] = str(STEPS)
    out = subprocess.run(
        [str(ROOT / GPU_BIN), "-nosimrc", "-notty", "-batch", SCRIPT, str(n), str(STEPS)],
        capture_output=True, text=True, cwd=ROOT, env=env,
    ).stdout
    m = GPU_DISPATCH_RE.search(out)
    if not m:
        raise RuntimeError(f"GPU run N={n}: no multiloop dispatch line found:\n{out[-1500:]}")
    return float(m.group(1)) / 1000.0


def main() -> None:
    t_start = time.time()
    raw_rows: list[tuple[int, str, int, float]] = []

    with RAW_CSV.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N", "mode", "rep", "seconds"])

        for n in NS:
            for _ in range(WARMUP):
                run_cpu(n)
                run_gpu(n)

            for rep in range(REPS):
                c = run_cpu(n)
                raw_rows.append((n, "CPU", rep, c))
                w.writerow([n, "CPU", rep, f"{c:.6f}"])
                f.flush()

            for rep in range(REPS):
                g = run_gpu(n)
                raw_rows.append((n, "GPU", rep, g))
                w.writerow([n, "GPU", rep, f"{g:.6f}"])
                f.flush()

            elapsed = time.time() - t_start
            print(f"[{elapsed:6.1f}s] N={n} done ({REPS} reps x 2 modes)", file=sys.stderr)

    with SUMMARY_CSV.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N", "cpu_mean_s", "cpu_sd_s", "cpu_ci95_s",
                     "gpu_mean_s", "gpu_sd_s", "gpu_ci95_s", "speedup"])
        for n in NS:
            cpu_vals = [r[3] for r in raw_rows if r[0] == n and r[1] == "CPU"]
            gpu_vals = [r[3] for r in raw_rows if r[0] == n and r[1] == "GPU"]
            cm, cs = statistics.mean(cpu_vals), statistics.stdev(cpu_vals)
            gm, gs = statistics.mean(gpu_vals), statistics.stdev(gpu_vals)
            # 95% CI via normal approximation (REPS=30 is large enough)
            c_ci = 1.96 * cs / (len(cpu_vals) ** 0.5)
            g_ci = 1.96 * gs / (len(gpu_vals) ** 0.5)
            speedup = cm / gm
            w.writerow([n, f"{cm:.6f}", f"{cs:.6f}", f"{c_ci:.6f}",
                        f"{gm:.6f}", f"{gs:.6f}", f"{g_ci:.6f}", f"{speedup:.4f}"])
            print(f"N={n:6d}  CPU={cm:.4f}+-{c_ci:.4f}s  GPU={gm:.4f}+-{g_ci:.4f}s  speedup={speedup:.2f}x")

    total = time.time() - t_start
    print(f"\nDone in {total:.1f}s. Wrote {RAW_CSV} and {SUMMARY_CSV}", file=sys.stderr)


if __name__ == "__main__":
    main()
