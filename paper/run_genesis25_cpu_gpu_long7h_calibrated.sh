#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

CPU=genesis/genesis
GPU=genesis/src/nxgenesis
SCRIPT=genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g

# Tunables (can be overridden via env vars).
TARGET_SECONDS="${TARGET_SECONDS:-25200}"      # 7h target per mode
NEURONS="${NEURONS:-30000}"                    # stable large mesoscale size
PILOT_STEPS="${PILOT_STEPS:-200000}"           # pilot used for runtime calibration
MIN_STEPS="${MIN_STEPS:-1000000}"              # floor to avoid too-short long run
MAX_STEPS="${MAX_STEPS:-60000000}"             # guardrail against accidental overshoot

RAW=paper/genesis25_cpu_gpu_long7h_raw.csv
SUMMARY=paper/genesis25_cpu_gpu_long7h_summary.csv

echo "mode,phase,neurons,steps,real_seconds,error_lines,exit_code" > "$RAW"

run_once() {
  local mode="$1"
  local exe="$2"
  local phase="$3"
  local steps="$4"

  local t0 t1 dt err ec
  t0=$(date +%s%N)
  set +e
  timeout 43200 "$exe" -nosimrc -notty -batch "$SCRIPT" "$NEURONS" "$steps" >/tmp/gen25_long7h.log 2>&1
  ec=$?
  set -e
  t1=$(date +%s%N)

  dt=$(awk -v a="$t0" -v b="$t1" 'BEGIN{printf "%.6f", (b-a)/1e9}')
  err=$(grep -c '\*\* Error' /tmp/gen25_long7h.log || true)

  echo "$mode,$phase,$NEURONS,$steps,$dt,$err,$ec" >> "$RAW"
  echo "[$(date +%F' '%T)] mode=$mode phase=$phase neurons=$NEURONS steps=$steps wall=$dt err=$err rc=$ec"
}

# Warm-ups
run_once CPU "$CPU" warmup 10000 || true
run_once GPU "$GPU" warmup 10000 || true

# Pilot calibration
run_once CPU "$CPU" pilot "$PILOT_STEPS"
run_once GPU "$GPU" pilot "$PILOT_STEPS"

CPU_PILOT=$(awk -F, '$1=="CPU" && $2=="pilot" {print $5}' "$RAW" | tail -n 1)
GPU_PILOT=$(awk -F, '$1=="GPU" && $2=="pilot" {print $5}' "$RAW" | tail -n 1)

if [[ -z "$CPU_PILOT" || -z "$GPU_PILOT" ]]; then
  echo "Pilot calibration failed: missing pilot runtimes." >&2
  exit 1
fi

CPU_STEPS=$(awk -v p="$CPU_PILOT" -v bs="$PILOT_STEPS" -v tgt="$TARGET_SECONDS" 'BEGIN{v=int((tgt/p)*bs+0.5); if(v<1) v=1; print v}')
GPU_STEPS=$(awk -v p="$GPU_PILOT" -v bs="$PILOT_STEPS" -v tgt="$TARGET_SECONDS" 'BEGIN{v=int((tgt/p)*bs+0.5); if(v<1) v=1; print v}')

# Clamp to safe bounds.
if [[ "$CPU_STEPS" -lt "$MIN_STEPS" ]]; then CPU_STEPS="$MIN_STEPS"; fi
if [[ "$GPU_STEPS" -lt "$MIN_STEPS" ]]; then GPU_STEPS="$MIN_STEPS"; fi
if [[ "$CPU_STEPS" -gt "$MAX_STEPS" ]]; then CPU_STEPS="$MAX_STEPS"; fi
if [[ "$GPU_STEPS" -gt "$MAX_STEPS" ]]; then GPU_STEPS="$MAX_STEPS"; fi

echo "Calibrated steps: CPU=$CPU_STEPS GPU=$GPU_STEPS (target ${TARGET_SECONDS}s)"

# Long runs (~7h each, sequential for isolation)
run_once CPU "$CPU" long "$CPU_STEPS"
run_once GPU "$GPU" long "$GPU_STEPS"

python3 - <<'PY'
import csv
raw='paper/genesis25_cpu_gpu_long7h_raw.csv'
out='paper/genesis25_cpu_gpu_long7h_summary.csv'
rows=list(csv.DictReader(open(raw,newline='',encoding='utf-8')))
long=[r for r in rows if r['phase']=='long']
with open(out,'w',newline='',encoding='utf-8') as f:
    w=csv.writer(f)
    w.writerow(['mode','neurons','steps','real_seconds','error_lines','exit_code','target_seconds','achieved_target_ratio'])
    for r in long:
        target=25200.0
        ratio=float(r['real_seconds'])/target if target>0 else 0.0
        w.writerow([r['mode'],r['neurons'],r['steps'],r['real_seconds'],r['error_lines'],r['exit_code'],f'{target:.0f}',f'{ratio:.6f}'])
print('Wrote', out)
PY

echo "Long calibrated campaign finished."
