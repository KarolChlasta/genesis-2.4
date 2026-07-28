#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

CPU=genesis/src/nxgenesis_nocl
GPU=genesis/src/nxgenesis
OUT=paper/genesis25_cpu_gpu_extreme_5rep.csv
SUMMARY=paper/genesis25_cpu_gpu_extreme_5rep_summary.csv
SPEEDUP=paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv

echo "benchmark,size_key,size_value,config,steps,replicate,mode,real_seconds,error_lines,exit_code" > "$OUT"

run_one() {
  local mode="$1"
  local exe="$2"
  local benchmark="$3"
  local size_key="$4"
  local size_value="$5"
  local config="$6"
  local steps="$7"
  local rep="$8"
  local script="$9"
  shift 9
  local args=("$@")

  local t0 t1 dt err ec
  t0=$(date +%s%N)
  set +e
  timeout 1800 "$exe" -nosimrc -notty -batch "$script" "${args[@]}" >/tmp/gen25_extreme.log 2>&1
  ec=$?
  set -e
  t1=$(date +%s%N)
  dt=$(awk -v a="$t0" -v b="$t1" 'BEGIN{printf "%.6f", (b-a)/1e9}')
  err=$(grep -c '\*\* Error' /tmp/gen25_extreme.log || true)

  echo "$benchmark,$size_key,$size_value,$config,$steps,$rep,$mode,$dt,$err,$ec" >> "$OUT"
  echo "[$(date +%H:%M:%S)] $benchmark $config rep=$rep mode=$mode wall=$dt err=$err rc=$ec"
}

run_case_neurons() {
  local benchmark="$1"
  local neurons="$2"
  local steps="$3"
  local script="$4"
  local config="N${neurons}_S${steps}"

  timeout 1800 "$CPU" -nosimrc -notty -batch "$script" "$neurons" "$steps" >/tmp/gen25_extreme_warmup.log 2>&1 || true
  timeout 1800 "$GPU" -nosimrc -notty -batch "$script" "$neurons" "$steps" >/tmp/gen25_extreme_warmup.log 2>&1 || true

  for rep in $(seq 1 5); do
    run_one CPU "$CPU" "$benchmark" neurons "$neurons" "$config" "$steps" "$rep" "$script" "$neurons" "$steps"
    run_one GPU "$GPU" "$benchmark" neurons "$neurons" "$config" "$steps" "$rep" "$script" "$neurons" "$steps"
  done
}

run_case_region() {
  local exn="$1"
  local inh="$2"
  local steps="$3"
  local benchmark="region_proxy_microcircuit_benchmark"
  local total=$((exn*exn + inh*inh))
  local config="EX${exn}x${exn}_INH${inh}x${inh}_S${steps}"
  local script="genesis/Scripts/benchmark/region_proxy_microcircuit_benchmark.g"

  timeout 1800 "$CPU" -nosimrc -notty -batch "$script" "$steps" "$exn" "$exn" "$inh" "$inh" >/tmp/gen25_extreme_warmup.log 2>&1 || true
  timeout 1800 "$GPU" -nosimrc -notty -batch "$script" "$steps" "$exn" "$exn" "$inh" "$inh" >/tmp/gen25_extreme_warmup.log 2>&1 || true

  for rep in $(seq 1 5); do
    run_one CPU "$CPU" "$benchmark" region_cells "$total" "$config" "$steps" "$rep" "$script" "$steps" "$exn" "$exn" "$inh" "$inh"
    run_one GPU "$GPU" "$benchmark" region_cells "$total" "$config" "$steps" "$rep" "$script" "$steps" "$exn" "$exn" "$inh" "$inh"
  done
}

# Mesoscale: larger than previous dense campaign
run_case_neurons mesoscale_sparse_benchmark 35000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g
run_case_neurons mesoscale_sparse_benchmark 45000 20000 genesis/Scripts/benchmark/mesoscale_sparse_benchmark.g

# Biophysical: larger than previous dense campaign
run_case_neurons biophysical_cellscale_benchmark 7000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g
run_case_neurons biophysical_cellscale_benchmark 10000 20000 genesis/Scripts/benchmark/biophysical_cellscale_benchmark.g

# Region proxy: larger maps
run_case_region 200 100 20000
run_case_region 240 120 20000

python3 - <<'PY'
import csv
from collections import defaultdict

inp='paper/genesis25_cpu_gpu_extreme_5rep.csv'
out='paper/genesis25_cpu_gpu_extreme_5rep_summary.csv'
out_speed='paper/genesis25_cpu_gpu_extreme_5rep_speedup.csv'

groups=defaultdict(list)
errs=defaultdict(list)
fails=defaultdict(int)

with open(inp,newline='',encoding='utf-8') as f:
    r=csv.DictReader(f)
    for row in r:
        key=(row['benchmark'],row['size_key'],row['size_value'],row['config'],row['steps'],row['mode'])
        t=float(row['real_seconds'])
        groups[key].append(t)
        errs[key].append(int(row['error_lines']))
        if int(row['exit_code']) != 0:
            fails[key]+=1

with open(out,'w',newline='',encoding='utf-8') as f:
    w=csv.writer(f)
    w.writerow(['benchmark','size_key','size_value','config','steps','mode','n','mean_s','sd_s','ci95_s','min_s','max_s','mean_error_lines','fail_count'])
    for key in sorted(groups.keys()):
        vals=groups[key]
        n=len(vals)
        m=sum(vals)/n
        sd=(sum((x-m)**2 for x in vals)/(n-1))**0.5 if n>1 else 0.0
        ci=1.96*sd/(n**0.5)
        w.writerow([*key,n,f'{m:.6f}',f'{sd:.6f}',f'{ci:.6f}',f'{min(vals):.6f}',f'{max(vals):.6f}',f'{sum(errs[key])/n:.2f}',fails[key]])

cpu_mean={}
gpu_mean={}
with open(out,newline='',encoding='utf-8') as f:
    r=csv.DictReader(f)
    for row in r:
        k=(row['benchmark'],row['size_key'],row['size_value'],row['config'],row['steps'])
        if row['mode']=='CPU':
            cpu_mean[k]=float(row['mean_s'])
        elif row['mode']=='GPU':
            gpu_mean[k]=float(row['mean_s'])

with open(out_speed,'w',newline='',encoding='utf-8') as f:
    w=csv.writer(f)
    w.writerow(['benchmark','size_key','size_value','config','steps','cpu_mean_s','gpu_mean_s','speedup_cpu_over_gpu'])
    for k in sorted(cpu_mean.keys()):
        if k not in gpu_mean:
            continue
        s=cpu_mean[k]/gpu_mean[k]
        w.writerow([*k,f'{cpu_mean[k]:.6f}',f'{gpu_mean[k]:.6f}',f'{s:.6f}'])

print('Wrote', inp)
print('Wrote', out)
print('Wrote', out_speed)
PY

echo "Extreme paired CPU/GPU campaign finished."
