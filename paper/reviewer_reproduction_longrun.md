# Reviewer Reproduction Protocol: Long-Run CPU vs GPU (4 × 2h sessions)

This document describes how to reproduce the long-duration CPU vs GPU validation
runs used to stress-test the OpenCL acceleration claim.

## 1. Goal
Run the same mesoscale benchmark in two modes:
- CPU serial baseline (`genesis/genesis`)
- GPU OpenCL mode (`genesis/src/nxgenesis`)

Each mode runs for 1 hour per session (accumulating repeated benchmark calls),
with 4 independent sessions, giving ~8 hours of total wall-clock coverage.

## 2. Why sessions instead of one long run
Model construction time for N=30,000 neurons dominates each GENESIS invocation
(~26–37 s per run regardless of simulation step count). Step-count calibration
cannot reach multi-hour targets. Instead, each session runs the benchmark
repeatedly until SESSION_TARGET_SECONDS of cumulative wall time is accumulated.
Splitting into 4 sessions makes any individual session easy to rerun if
interrupted.

## 3. Required Files
- Benchmark script: `genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g`
- Runner: `paper/run_genesis25_cpu_gpu_longrun_4x2h.sh`

Output artifacts:
- Raw log rows: `paper/genesis25_cpu_gpu_longrun_raw.csv`
- Summary (per session, per mode): `paper/genesis25_cpu_gpu_longrun_summary.csv`

## 4. Command (all 4 sessions)
```bash
cd /path/to/genesis-2.4
./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
```

## 5. Rerunning a single session
```bash
cd /path/to/genesis-2.4
START_SESSION=3 END_SESSION=3 ./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
```
Rows from the rerun are appended to the raw CSV with the matching session number.

## 6. Optional Overrides
| Variable | Default | Meaning |
|---|---|---|
| `SESSIONS` | `4` | number of sessions |
| `SESSION_TARGET_SECONDS` | `3600` | target cumulative seconds per mode per session (1h) |
| `START_SESSION` | `1` | first session to run |
| `END_SESSION` | `SESSIONS` | last session to run |
| `NEURONS` | `30000` | neuron count passed to benchmark |
| `STEPS` | `20000` | simulation steps per invocation |
| `MAX_ITER_PER_SESSION` | `2000` | hard cap on iterations per session |

Example (run 2 sessions at 30 min each for a quick validation):
```bash
cd /path/to/genesis-2.4
SESSIONS=2 SESSION_TARGET_SECONDS=1800 ./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
```

## 7. Data Integrity Checks
After completion:
1. Confirm summary file exists: `paper/genesis25_cpu_gpu_longrun_summary.csv`
2. Check `exit_code = 0` and `error_lines = 0` for all measured rows in raw CSV.
3. Check `achieved_ratio` per session/mode is close to `1.0`.
4. Verify 4 sessions × 2 modes = 8 rows in summary.

## 8. Reporting Guidance
For manuscript text, report:
- host CPU/GPU identifiers,
- sessions completed, iterations per session, mean per-iteration wall-clock,
- whether GPU was faster/slower in this sustained-load regime.

Keep raw CSV artifacts unchanged for auditability.
