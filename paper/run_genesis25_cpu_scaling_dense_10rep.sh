#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

CPU=genesis/genesis
OUT=paper/genesis25_cpu_scaling_dense_10rep.csv
SUMMARY=paper/genesis25_cpu_scaling_dense_10rep_summary.csv

echo "benchmark,mode,size_key,size_value,steps,replicate,real_seconds,error_lines,exit_code" > "$OUT"

run_neuron_case() {
  local bench="$1"; local n="$2"; local steps="$3"; local script="$4"
  timeout 1200 "$CPU" -nosimrc -notty -batch "$script" "$n" "$steps" >/tmp/cpu_dense10_warmup.log 2>&1 || true
  for rep in $(seq 1 10); do
    local t0 t1 dt err ec
    t0=$(date +%s%N)
    set +e
    timeout 1200 "$CPU" -nosimrc -notty -batch "$script" "$n" "$steps" >/tmp/cpu_dense10.log 2>&1
    ec=$?
    set -e
    t1=$(date +%s%N)
    dt=$(awk -v a="$t0" -v b="$t1" 'BEGIN{printf "%.6f", (b-a)/1e9}')
    err=$(grep -c '\*\* Error' /tmp/cpu_dense10.log || true)
    echo "$bench,CPU,neurons,$n,$steps,$rep,$dt,$err,$ec" >> "$OUT"
    echo "[$(date +%H:%M:%S)] $bench n=$n rep=$rep wall=$dt err=$err rc=$ec"
  done
}

run_region_case() {
  local exn="$1"; local inh="$2"; local steps="$3"
  local total=$((exn*exn + inh*inh))
  timeout 1200 "$CPU" -nosimrc -notty -batch genesis/Scripts/benchmark/region_proxy_microcircuit_benchmark.g "$steps" "$exn" "$exn" "$inh" "$inh" >/tmp/cpu_dense10_warmup.log 2>&1 || true
  for rep in $(seq 1 10); do
    local t0 t1 dt err ec
    t0=$(date +%s%N)
    set +e
    timeout 1200 "$CPU" -nosimrc -notty -batch genesis/Scripts/benchmark/region_proxy_microcircuit_benchmark.g "$steps" "$exn" "$exn" "$inh" "$inh" >/tmp/cpu_dense10.log 2>&1
    ec=$?
    set -e
    t1=$(date +%s%N)
    dt=$(awk -v a="$t0" -v b="$t1" 'BEGIN{printf "%.6f", (b-a)/1e9}')
    err=$(grep -c '\*\* Error' /tmp/cpu_dense10.log || true)
    echo "region_proxy_microcircuit_benchmark,CPU,region_cells,$total,$steps,$rep,$dt,$err,$ec" >> "$OUT"
    echo "[$(date +%H:%M:%S)] region total=$total rep=$rep wall=$dt err=$err rc=$ec"
  done
}

run_neuron_case mesoscale_sparse_benchmark 10000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_neuron_case mesoscale_sparse_benchmark 12000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_neuron_case mesoscale_sparse_benchmark 16000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_neuron_case mesoscale_sparse_benchmark 20000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_neuron_case mesoscale_sparse_benchmark 24000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_neuron_case mesoscale_sparse_benchmark 30000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g

run_neuron_case biophysical_cellscale_benchmark 1000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_neuron_case biophysical_cellscale_benchmark 1500 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_neuron_case biophysical_cellscale_benchmark 2000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_neuron_case biophysical_cellscale_benchmark 3000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_neuron_case biophysical_cellscale_benchmark 4000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_neuron_case biophysical_cellscale_benchmark 5000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g

run_region_case 80 40 20000
run_region_case 100 50 20000
run_region_case 120 60 20000
run_region_case 140 70 20000
run_region_case 160 80 20000
run_region_case 180 90 20000

python3 - <<'PY'
import csv
from collections import defaultdict

inp='paper/genesis25_cpu_scaling_dense_10rep.csv'
out='paper/genesis25_cpu_scaling_dense_10rep_summary.csv'
rows=defaultdict(list)
errs=defaultdict(list)
fails=defaultdict(int)
with open(inp,newline='',encoding='utf-8') as f:
    r=csv.DictReader(f)
    for row in r:
        k=(row['benchmark'], row['size_key'], row['size_value'], row['steps'])
        t=float(row['real_seconds'])
        rows[k].append(t)
        errs[k].append(int(row['error_lines']))
        if int(row['exit_code'])!=0:
            fails[k]+=1
with open(out,'w',newline='',encoding='utf-8') as f:
    w=csv.writer(f)
    w.writerow(['benchmark','mode','size_key','size_value','steps','n','mean_s','sd_s','ci95_s','min_s','max_s','mean_error_lines','fail_count'])
    for k in sorted(rows.keys()):
        vals=rows[k]
        n=len(vals)
        m=sum(vals)/n
        sd=(sum((x-m)**2 for x in vals)/(n-1))**0.5 if n>1 else 0.0
        ci=1.96*sd/(n**0.5)
        w.writerow([k[0],'CPU',k[1],k[2],k[3],n,f'{m:.6f}',f'{sd:.6f}',f'{ci:.6f}',f'{min(vals):.6f}',f'{max(vals):.6f}',f'{sum(errs[k])/n:.2f}',fails[k]])
print('Wrote', inp)
print('Wrote', out)
PY

echo "Dense CPU 10-rep campaign finished."
