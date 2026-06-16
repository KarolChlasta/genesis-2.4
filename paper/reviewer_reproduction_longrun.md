# Reviewer Reproduction Protocol: Long-Run CPU vs GPU (~7h target)

This document describes how to reproduce the long-duration CPU vs GPU validation
runs used to stress-test the OpenCL acceleration claim.

## 1. Goal
Run the same mesoscale benchmark in two modes:
- CPU serial baseline (`genesis/genesis`)
- GPU OpenCL mode (`genesis/src/nxgenesis`)

Both runs are calibrated to target about 7 hours each (25200 s) using pilot
measurements on the same host.

## 2. Required Files
- Benchmark script: `genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g`
- Runner: `paper/run_genesis25_cpu_gpu_long7h_calibrated.sh`

Output artifacts:
- Raw log rows: `paper/genesis25_cpu_gpu_long7h_raw.csv`
- Long-run summary: `paper/genesis25_cpu_gpu_long7h_summary.csv`

## 3. Host Preparation
1. Ensure idle machine state (close heavy background applications).
2. Ensure binaries exist and are executable:
   - `genesis/genesis`
   - `genesis/src/nxgenesis`
3. Run from repository root.

## 4. Command (default ~7h target)
```bash
cd /path/to/genesis-2.4
./paper/run_genesis25_cpu_gpu_long7h_calibrated.sh
```

## 5. Optional Overrides
The runner supports environment overrides:
- `TARGET_SECONDS` (default `25200`)
- `NEURONS` (default `30000`)
- `PILOT_STEPS` (default `200000`)
- `MIN_STEPS` (default `1000000`)
- `MAX_STEPS` (default `60000000`)

Example (5h target, bigger model):
```bash
cd /path/to/genesis-2.4
TARGET_SECONDS=18000 NEURONS=40000 ./paper/run_genesis25_cpu_gpu_long7h_calibrated.sh
```

## 6. Calibration Logic
1. Warm-up in CPU and GPU mode.
2. Pilot run with `PILOT_STEPS` for CPU and GPU separately.
3. Compute target steps per mode:

$$
steps_{target} = round\left(\frac{TARGET\_SECONDS}{pilot\_seconds} \cdot PILOT\_STEPS\right)
$$

4. Clamp by `[MIN_STEPS, MAX_STEPS]` safeguards.
5. Execute one long run per mode with calibrated steps.

## 7. Data Integrity Checks
After completion:
1. Confirm summary file exists:
   - `paper/genesis25_cpu_gpu_long7h_summary.csv`
2. Confirm `exit_code = 0` for both `CPU` and `GPU` rows.
3. Confirm `error_lines = 0` or explicitly report non-zero values.
4. Compare achieved target ratio:

$$
ratio = \frac{real\_seconds}{25200}
$$

Values close to `1.0` indicate successful 7h targeting.

## 8. Reporting Guidance
For manuscript text, report:
- host CPU/GPU identifiers,
- calibrated steps used for CPU and GPU,
- realized wall-clock times,
- whether GPU was faster/slower in this long-run regime.

Keep raw CSV artifacts unchanged for auditability.
