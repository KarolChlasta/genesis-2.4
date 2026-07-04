#!/usr/bin/env python3
"""GENESIS 2.5 overnight benchmark campaign (wall-clock, publication-grade).

Four studies, every observation written incrementally (interrupt-safe), bounded
by a hard wall-clock deadline.

  STUDY 1 -- Wall-clock CPU-vs-GPU scaling at fixed simulation length (headline).
    Whole-process wall time via time.monotonic() (identical instrumentation on
    both arms) at K=STEPS and at K=0 (construction only). Step-phase wall =
    full - construction. Cross-checked against each arm's internal timer
    (CPU: GENESIS {cpu}; GPU: kernel clock_gettime dispatch report) -- the two
    agree, which is what licenses the wall-clock subtraction. Neuroscience
    metrics: throughput (neuron-steps/s), real-time factor (bio s / wall s).

  STUDY 2 -- Speedup vs simulation length (N fixed, K swept).
    Shows the construction cost amortizing as the simulated duration grows, so
    end-to-end speedup rises with K -- the regime where a GPU actually pays off.

  STUDY 3 -- fp32(GPU) vs fp64(CPU) numerical divergence (correctness).
    hh1952_ap_verify.g at increasing step counts over three execution paths
    (CPU, GPU per-step, GPU multiloop). RESULT_VM + NEURONS_AGREE. Bounds the
    accelerator's numerical fidelity and shows fp32 spike-phase drift onset.

  STUDY 4 -- Long-run reproducibility (fills the remaining window).
    Re-measures three N points at intervals until the deadline, so thermal /
    temporal stability of the speedup is documented rather than assumed.

  Arms (headless, no X11 confound; differ only by USE_OPENCL):
    CPU: genesis/src/nxgenesis_nocl        (fp64, no OpenCL)
    GPU: genesis/src/nxgenesis + GENESIS_OCL_MULTILOOP=K   (fp32 multiloop)
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
CPU_BIN = ROOT / "genesis/src/nxgenesis_nocl"
GPU_BIN = ROOT / "genesis/src/nxgenesis"
TIMING_G = "genesis/Scripts/benchmark/hh_spiking_benchmark.g"
VERIFY_G = "genesis/Scripts/benchmark/hh1952_ap_verify.g"

STEPS = 50000                   # headline simulation length (2.5 s biological)
DT = 50e-6
BIO_SECONDS = STEPS * DT

# STUDY 1: (N, full_reps, construction_reps). Reps taper with per-run cost.
SWEEP = [
    (500,   40, 8),
    (1000,  40, 8),
    (2000,  30, 6),
    (5000,  24, 6),
    (10000, 16, 4),
    (20000, 10, 3),
    (50000, 5,  2),
]

# STUDY 2: speedup vs simulation length at a mid-size, GPU-well-utilised N.
KSWEEP_N = 5000
KSWEEP_K = [5000, 10000, 20000, 50000, 100000, 200000]
KSWEEP_REPS = 12

# STUDY 3: divergence vs simulated time.
VERIFY_N = 8
VERIFY_STEPS = [100, 200, 400, 800, 1600, 3200, 6400]

# STUDY 4: reproducibility points, re-measured every REPRO_INTERVAL_S.
REPRO_NS = [2000, 5000, 10000]
REPRO_REPS = 6
REPRO_INTERVAL_S = 25 * 60

DEADLINE_S = 8.0 * 3600         # matches the requested 8 h window; studies 1-3
                                # (the paper data) finish in ~1 h, study 4
                                # (reproducibility loop) fills the remainder

P = ROOT / "experiments" / "data"
P.mkdir(parents=True, exist_ok=True)
RAW = P / "campaign_wallclock_raw.csv"
SUMMARY = P / "campaign_wallclock_summary.csv"
KSWEEP_CSV = P / "campaign_ksweep.csv"
DIVERGENCE = P / "campaign_divergence.csv"
REPRO_CSV = P / "campaign_reproducibility.csv"
LOG = P / "campaign_progress.log"

CPU_STEP_RE = re.compile(r"completed (\d+) steps in ([\d.]+) cpu seconds")
GPU_DISPATCH_RE = re.compile(r"(?:OCL|CUDA) MULTILOOP:.*?total ([\d.]+) ms")
RESULT_VM_RE = re.compile(r"RESULT_VM=\s*(-?[\d.]+)")
AGREE_RE = re.compile(r"NEURONS_AGREE:\s*(YES|NO)")

_t0 = time.time()


def log(msg: str) -> None:
    line = f"[{time.time() - _t0:8.1f}s] {msg}"
    print(line, file=sys.stderr, flush=True)
    with LOG.open("a") as f:
        f.write(line + "\n")


def deadline_reached() -> bool:
    return (time.time() - _t0) > DEADLINE_S


def run_once(binary: Path, script: str, n: int, steps: int, multiloop):
    env = os.environ.copy()
    if multiloop is not None:
        env["GENESIS_OCL_MULTILOOP"] = str(multiloop)
    else:
        env.pop("GENESIS_OCL_MULTILOOP", None)
    t = time.monotonic()
    p = subprocess.run(
        [str(binary), "-nosimrc", "-notty", "-batch", script, str(n), str(steps)],
        capture_output=True, text=True, cwd=ROOT, env=env,
    )
    return time.monotonic() - t, p.stdout


def cpu_step_time(out):
    m = CPU_STEP_RE.findall(out)
    return float(m[-1][1]) if m else None


def gpu_dispatch_ms(out):
    m = GPU_DISPATCH_RE.findall(out)
    return float(m[-1]) if m else None


def med(v):
    return statistics.median(v) if v else float("nan")


def ci95(v):
    return 1.96 * statistics.stdev(v) / (len(v) ** 0.5) if len(v) > 1 else 0.0


# --------------------------------------------------------------------------
def study1(raw_writer, raw_fh):
    rows = []
    for n, full_reps, con_reps in SWEEP:
        if deadline_reached():
            log(f"deadline before N={n}; ending study1"); break
        for arm, binary in (("CPU", CPU_BIN), ("GPU", GPU_BIN)):
            ml = STEPS if arm == "GPU" else None
            ml0 = 1 if arm == "GPU" else None
            run_once(binary, TIMING_G, n, STEPS, ml)  # warmup
            for rep in range(con_reps):
                w, _ = run_once(binary, TIMING_G, n, 0, ml0)
                rows.append((n, arm, "construct", w, ""))
                raw_writer.writerow([1, n, arm, "construct", rep, f"{w:.6f}", ""]); raw_fh.flush()
            for rep in range(full_reps):
                w, out = run_once(binary, TIMING_G, n, STEPS, ml)
                intern = cpu_step_time(out) if arm == "CPU" else gpu_dispatch_ms(out)
                intern = "" if intern is None else f"{intern:.6f}"
                rows.append((n, arm, "full", w, intern))
                raw_writer.writerow([1, n, arm, "full", rep, f"{w:.6f}", intern]); raw_fh.flush()
                if deadline_reached():
                    break
        log(f"STUDY1 N={n} done")
    return rows


def summarize_study1(rows):
    with SUMMARY.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N",
                    "cpu_full_wall_med_s", "cpu_construct_wall_med_s", "cpu_step_wall_med_s", "cpu_step_wall_ci95_s",
                    "gpu_full_wall_med_s", "gpu_construct_wall_med_s", "gpu_step_wall_med_s", "gpu_step_wall_ci95_s",
                    "speedup_step_wall", "speedup_end2end_wall",
                    "gpu_throughput_nsteps_per_s", "gpu_realtime_factor",
                    "cpu_internal_step_med_s", "gpu_internal_dispatch_med_s"])
        for n in sorted({r[0] for r in rows}):
            def sel(arm, kind):
                return [r[3] for r in rows if r[0] == n and r[1] == arm and r[2] == kind]
            cf, cc = sel("CPU", "full"), sel("CPU", "construct")
            gf, gc = sel("GPU", "full"), sel("GPU", "construct")
            if not (cf and gf):
                continue
            cfm, ccm, gfm, gcm = med(cf), med(cc), med(gf), med(gc)
            cstep = [x - ccm for x in cf]
            gstep = [x - gcm for x in gf]
            csm, gsm = med(cstep), med(gstep)
            sp_step = csm / gsm if gsm > 0 else float("nan")
            sp_e2e = cfm / gfm if gfm > 0 else float("nan")
            thr = n * STEPS / gsm if gsm > 0 else float("nan")
            rtf = BIO_SECONDS / gsm if gsm > 0 else float("nan")
            ci = [float(r[4]) for r in rows if r[0] == n and r[1] == "CPU" and r[2] == "full" and r[4]]
            gi = [float(r[4]) / 1000 for r in rows if r[0] == n and r[1] == "GPU" and r[2] == "full" and r[4]]
            w.writerow([n, f"{cfm:.6f}", f"{ccm:.6f}", f"{csm:.6f}", f"{ci95(cstep):.6f}",
                        f"{gfm:.6f}", f"{gcm:.6f}", f"{gsm:.6f}", f"{ci95(gstep):.6f}",
                        f"{sp_step:.3f}", f"{sp_e2e:.3f}", f"{thr:.1f}", f"{rtf:.4f}",
                        f"{med(ci):.6f}" if ci else "", f"{med(gi):.6f}" if gi else ""])
    log(f"wrote {SUMMARY}")


# --------------------------------------------------------------------------
def study2():
    with KSWEEP_CSV.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N", "K", "cpu_step_wall_med_s", "gpu_step_wall_med_s",
                    "speedup_step", "cpu_full_med_s", "gpu_full_med_s", "speedup_end2end"])
        n = KSWEEP_N
        # one construction baseline per arm (K-independent)
        run_once(CPU_BIN, TIMING_G, n, 0, None)
        ccm = med([run_once(CPU_BIN, TIMING_G, n, 0, None)[0] for _ in range(4)])
        gcm = med([run_once(GPU_BIN, TIMING_G, n, 0, 1)[0] for _ in range(4)])
        for k in KSWEEP_K:
            if deadline_reached():
                log("deadline in study2"); break
            cf = [run_once(CPU_BIN, TIMING_G, n, k, None)[0] for _ in range(KSWEEP_REPS)]
            gf = [run_once(GPU_BIN, TIMING_G, n, k, k)[0] for _ in range(KSWEEP_REPS)]
            cfm, gfm = med(cf), med(gf)
            csm, gsm = cfm - ccm, gfm - gcm
            w.writerow([n, k, f"{csm:.6f}", f"{gsm:.6f}",
                        f"{csm/gsm:.3f}" if gsm > 0 else "",
                        f"{cfm:.6f}", f"{gfm:.6f}", f"{cfm/gfm:.3f}" if gfm > 0 else ""])
            f.flush()
            log(f"STUDY2 N={n} K={k}: step-speedup={csm/gsm:.2f}x end2end={cfm/gfm:.2f}x")


# --------------------------------------------------------------------------
def study3():
    with DIVERGENCE.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N", "steps", "cpu_vm", "gpu_perstep_vm", "gpu_multiloop_vm",
                    "abs_dev_perstep_V", "abs_dev_multiloop_V",
                    "cpu_agree", "gpu_perstep_agree", "gpu_multiloop_agree"])
        for steps in VERIFY_STEPS:
            if deadline_reached():
                break
            _, co = run_once(CPU_BIN, VERIFY_G, VERIFY_N, steps, None)
            _, po = run_once(GPU_BIN, VERIFY_G, VERIFY_N, steps, None)
            _, mo = run_once(GPU_BIN, VERIFY_G, VERIFY_N, steps, steps + 10)

            def vm(o):
                m = RESULT_VM_RE.search(o); return float(m.group(1)) if m else None

            def ag(o):
                m = AGREE_RE.search(o); return m.group(1) if m else "?"
            cv, pv, mv = vm(co), vm(po), vm(mo)
            dp = abs(cv - pv) if cv is not None and pv is not None else float("nan")
            dm = abs(cv - mv) if cv is not None and mv is not None else float("nan")
            w.writerow([VERIFY_N, steps,
                        f"{cv:.9f}" if cv is not None else "",
                        f"{pv:.9f}" if pv is not None else "",
                        f"{mv:.9f}" if mv is not None else "",
                        f"{dp:.3e}", f"{dm:.3e}", ag(co), ag(po), ag(mo)])
            f.flush()
            log(f"STUDY3 steps={steps}: dev_perstep={dp:.2e} dev_multiloop={dm:.2e}")


# --------------------------------------------------------------------------
def study4():
    with REPRO_CSV.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["elapsed_s", "N", "cpu_step_wall_med_s", "gpu_step_wall_med_s", "speedup_step"])
        while not deadline_reached():
            cycle_start = time.time()
            for n in REPRO_NS:
                if deadline_reached():
                    break
                ccm = med([run_once(CPU_BIN, TIMING_G, n, 0, None)[0] for _ in range(2)])
                gcm = med([run_once(GPU_BIN, TIMING_G, n, 0, 1)[0] for _ in range(2)])
                cf = [run_once(CPU_BIN, TIMING_G, n, STEPS, None)[0] for _ in range(REPRO_REPS)]
                gf = [run_once(GPU_BIN, TIMING_G, n, STEPS, STEPS)[0] for _ in range(REPRO_REPS)]
                csm, gsm = med(cf) - ccm, med(gf) - gcm
                w.writerow([f"{time.time()-_t0:.0f}", n, f"{csm:.6f}", f"{gsm:.6f}",
                            f"{csm/gsm:.3f}" if gsm > 0 else ""])
                f.flush()
                log(f"STUDY4 t={time.time()-_t0:.0f}s N={n}: step-speedup={csm/gsm:.2f}x")
            # pace to REPRO_INTERVAL_S between cycle starts
            sleep = REPRO_INTERVAL_S - (time.time() - cycle_start)
            while sleep > 0 and not deadline_reached():
                time.sleep(min(30, sleep)); sleep -= 30


def main():
    LOG.write_text("")
    log(f"campaign start. deadline={DEADLINE_S/3600:.1f}h. K={STEPS}. "
        f"CPU={CPU_BIN.name} GPU={GPU_BIN.name}")
    if not CPU_BIN.exists() or not GPU_BIN.exists():
        log("FATAL missing binaries"); sys.exit(1)
    with RAW.open("w", newline="") as raw_fh:
        rw = csv.writer(raw_fh)
        rw.writerow(["study", "N", "arm", "kind", "rep", "wall_s", "internal"])
        rows = study1(rw, raw_fh)
    summarize_study1(rows)
    log("=== STUDY 2 (K-sweep) ===");        study2()
    log("=== STUDY 3 (divergence) ===");     study3()
    log("=== STUDY 4 (reproducibility) ==="); study4()
    log(f"campaign COMPLETE in {(time.time()-_t0)/3600:.2f}h")


if __name__ == "__main__":
    main()
