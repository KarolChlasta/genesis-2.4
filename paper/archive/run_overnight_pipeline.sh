#!/usr/bin/env bash
# Overnight benchmark pipeline for GENESIS 2.5 paper.
#
# Stages (sequential):
#   1. Extreme 5-rep paired CPU/GPU campaign       (~20 min)
#   2. Extreme figures (fig8, fig9)                (~1 min)
#   3. Long-run 4x2h sessions (SESSION_TARGET=3600) (~8 h)
#   4. Final summary print
#
# Usage:
#   cd /path/to/genesis-2.4
#   nohup ./paper/run_overnight_pipeline.sh > paper/overnight_pipeline.log 2>&1 &
#   echo "Pipeline PID: $!"
#
# Check progress:
#   tail -f paper/overnight_pipeline.log
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

LOG=paper/overnight_pipeline.log
STAGE_SEP="================================================================"

ts() { date '+%F %T'; }

log() {
  echo "[$(ts)] $*"
}

log "$STAGE_SEP"
log "GENESIS 2.5 overnight pipeline started"
log "Host: $(hostname)  PID: $$"
log "$STAGE_SEP"

# ── Stage 1: extreme 5-rep ────────────────────────────────────────────────────
log ""
log "STAGE 1/3: Extreme paired CPU/GPU 5-rep campaign"
log "  Script: paper/run_genesis25_cpu_gpu_extreme_5rep.sh"
log "  Expected duration: ~20 min"
log ""

T0=$(date +%s)
bash paper/run_genesis25_cpu_gpu_extreme_5rep.sh
T1=$(date +%s)

log ""
log "STAGE 1 done in $(( T1 - T0 ))s"
log ""

# ── Stage 2: extreme figures ──────────────────────────────────────────────────
log "$STAGE_SEP"
log "STAGE 2/3: Generate extreme figures (fig8, fig9)"
log ""

T0=$(date +%s)
python3 paper/plot_genesis25_extreme.py
T1=$(date +%s)

log "STAGE 2 done in $(( T1 - T0 ))s"
log ""

# ── Stage 3: long-run 4 x 2h sessions ────────────────────────────────────────
log "$STAGE_SEP"
log "STAGE 3/3: Long-run 4x2h sessions (SESSION_TARGET_SECONDS=3600 per mode)"
log "  Script: paper/run_genesis25_cpu_gpu_longrun_4x2h.sh"
log "  Sessions: 4  |  Per session: 1h CPU + 1h GPU  |  Total: ~8h"
log "  Rerun any session: START_SESSION=N END_SESSION=N ./paper/run_genesis25_cpu_gpu_longrun_4x2h.sh"
log ""

T0=$(date +%s)
SESSION_TARGET_SECONDS=3600 bash paper/run_genesis25_cpu_gpu_longrun_4x2h.sh
T1=$(date +%s)

log ""
log "STAGE 3 done in $(( T1 - T0 ))s"
log ""

# ── Final summary ─────────────────────────────────────────────────────────────
log "$STAGE_SEP"
log "ALL STAGES COMPLETE"
log ""
log "Artifacts produced:"
log "  paper/genesis25_cpu_gpu_extreme_5rep.csv"
log "  paper/genesis25_cpu_gpu_extreme_5rep_summary.csv"
log "  paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv"
log "  paper/figures/fig8_extreme_runtime_ci.png"
log "  paper/figures/fig9_extreme_speedup.png"
log "  paper/genesis25_cpu_gpu_longrun_raw.csv"
log "  paper/genesis25_cpu_gpu_longrun_summary.csv"
log ""

if [[ -f paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv ]]; then
  log "Extreme speedup summary:"
  python3 - <<'PY'
import csv, statistics
rows = list(csv.DictReader(open('paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv')))
by_bench = {}
for r in rows:
    by_bench.setdefault(r['benchmark'], []).append(float(r['speedup_cpu_over_gpu']))
for bench, vals in sorted(by_bench.items()):
    label = bench.replace('_benchmark','').replace('_',' ')
    print(f"  {label}: mean speedup={sum(vals)/len(vals):.4f}  "
          f"min={min(vals):.4f}  max={max(vals):.4f}")
PY
fi

if [[ -f paper/genesis25_cpu_gpu_longrun_summary.csv ]]; then
  log ""
  log "Long-run session summary:"
  python3 - <<'PY'
import csv
rows = list(csv.DictReader(open('paper/genesis25_cpu_gpu_longrun_summary.csv')))
for r in rows:
    print(f"  session={r['session']} {r['mode']}: "
          f"{r['n_iters']} iters  total={float(r['total_s'])/3600:.2f}h  "
          f"mean={float(r['mean_s']):.2f}s  ratio={r['achieved_ratio']}")
PY
fi

log ""
log "Pipeline finished at $(ts)"
log "$STAGE_SEP"
