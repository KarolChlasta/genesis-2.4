#!/usr/bin/env bash
# Long-run CPU vs GPU stress validation: 4 independent 2h sessions.
#
# Rationale: model construction time dominates (~26-37 s per run at N=30000),
# so step-count calibration is not usable. Instead, each session runs the
# benchmark repeatedly until SESSION_TARGET_SECONDS is accumulated.
# Splitting into 4 separate sessions makes it easy to rerun any failed block.
#
# Usage (run all 4 sessions sequentially):
#   ./paper/run_genesis25_cpu_gpu_long7h_calibrated.sh
#
# Rerun a single session (e.g. session 3 only):
#   START_SESSION=3 END_SESSION=3 ./paper/run_genesis25_cpu_gpu_long7h_calibrated.sh
#
# The raw CSV is appended across invocations, so reruns of individual sessions
# will add rows. Use session= and mode= columns to filter when aggregating.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

CPU=genesis/src/nxgenesis_nocl
GPU=genesis/src/nxgenesis
SCRIPT=genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g

SESSIONS="${SESSIONS:-4}"
SESSION_TARGET_SECONDS="${SESSION_TARGET_SECONDS:-7200}"   # 2h per session
START_SESSION="${START_SESSION:-1}"
END_SESSION="${END_SESSION:-$SESSIONS}"
NEURONS="${NEURONS:-30000}"
STEPS="${STEPS:-20000}"
MAX_ITER_PER_SESSION="${MAX_ITER_PER_SESSION:-2000}"
TIMEOUT_SINGLE="${TIMEOUT_SINGLE:-300}"

RAW=paper/genesis25_cpu_gpu_longrun_raw.csv
SUMMARY=paper/genesis25_cpu_gpu_longrun_summary.csv

# Write header only if file does not exist yet.
if [[ ! -f "$RAW" ]]; then
  echo "session,mode,phase,iteration,neurons,steps,real_seconds,error_lines,exit_code" > "$RAW"
fi

run_one() {
  local session="$1" mode="$2" exe="$3" phase="$4" iter="$5"
  local t0 t1 dt err ec

  t0=$(date +%s%N)
  set +e
  timeout "$TIMEOUT_SINGLE" "$exe" -nosimrc -notty -batch "$SCRIPT" "$NEURONS" "$STEPS" \
    >/tmp/gen25_longrun.log 2>&1
  ec=$?
  set -e
  t1=$(date +%s%N)

  dt=$(awk -v a="$t0" -v b="$t1" 'BEGIN{printf "%.6f", (b-a)/1e9}')
  err=$(grep -c '\*\* Error' /tmp/gen25_longrun.log || true)

  echo "$session,$mode,$phase,$iter,$NEURONS,$STEPS,$dt,$err,$ec" >> "$RAW"
  echo "[$(date +%T)] session=$session $mode $phase iter=$iter wall=${dt}s err=$err rc=$ec"
}

run_session() {
  local session="$1" mode="$2" exe="$3"
  local cumul=0 iter=0

  echo "--- session $session $mode warm-up ---"
  run_one "$session" "$mode" "$exe" warmup 0

  echo "--- session $session $mode timed loop (target ${SESSION_TARGET_SECONDS}s) ---"
  while (( iter < MAX_ITER_PER_SESSION )); do
    if awk -v c="$cumul" -v t="$SESSION_TARGET_SECONDS" 'BEGIN{exit (c >= t)}'; then
      : # keep going
    else
      break
    fi
    iter=$(( iter + 1 ))
    run_one "$session" "$mode" "$exe" run "$iter"
    last_dt=$(awk -F, -v s="$session" -v m="$mode" -v i="$iter" \
      '$1==s && $2==m && $3=="run" && $4==i {print $7}' "$RAW" | tail -n1)
    cumul=$(awk -v c="$cumul" -v d="$last_dt" 'BEGIN{printf "%.6f", c+d}')
    echo "  session $session $mode cumulative: ${cumul}s / ${SESSION_TARGET_SECONDS}s"
  done

  echo "--- session $session $mode done: $iter iters, total ${cumul}s ---"
}

for s in $(seq "$START_SESSION" "$END_SESSION"); do
  echo "=== SESSION $s / $SESSIONS ==="
  run_session "$s" CPU "$CPU"
  run_session "$s" GPU "$GPU"
  echo "=== SESSION $s complete ==="
done

python3 - <<'PY'
import csv, statistics

raw = 'paper/genesis25_cpu_gpu_longrun_raw.csv'
out = 'paper/genesis25_cpu_gpu_longrun_summary.csv'

rows = list(csv.DictReader(open(raw, newline='', encoding='utf-8')))

# Per-session, per-mode stats
by_sm = {}
for r in rows:
    if r['phase'] != 'run':
        continue
    key = (int(r['session']), r['mode'])
    by_sm.setdefault(key, []).append(float(r['real_seconds']))

with open(out, 'w', newline='', encoding='utf-8') as f:
    w = csv.writer(f)
    w.writerow(['session', 'mode', 'neurons', 'steps', 'n_iters',
                'total_s', 'mean_s', 'sd_s', 'min_s', 'max_s',
                'session_target_s', 'achieved_ratio'])
    for (session, mode), vals in sorted(by_sm.items()):
        n = len(vals)
        total = sum(vals)
        mean = total / n
        sd = statistics.stdev(vals) if n > 1 else 0.0
        nr = next(r for r in rows if r['session']==str(session)
                  and r['mode']==mode and r['phase']=='run')
        target = float(nr.get('session_target_s', 7200)) if 'session_target_s' in nr else 7200.0
        # fall back to env default
        import os
        target = float(os.environ.get('SESSION_TARGET_SECONDS', 7200))
        ratio = total / target
        w.writerow([session, mode, nr['neurons'], nr['steps'], n,
                    f'{total:.3f}', f'{mean:.6f}', f'{sd:.6f}',
                    f'{min(vals):.6f}', f'{max(vals):.6f}',
                    f'{target:.0f}', f'{ratio:.6f}'])
        print(f"  session={session} {mode}: {n} iters, "
              f"total={total:.1f}s, mean={mean:.3f}s, sd={sd:.3f}s, ratio={ratio:.4f}")

print('Wrote', out)
PY

echo "All sessions finished."
