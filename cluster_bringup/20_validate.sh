#!/bin/sh
# Numerical parity check: fp32 CUDA path vs fp64 CPU path on HH1952 AP.
# Must print "PARITY: PASS" (|CPU-CUDA| < 1e-6 V) before any CUDA speedup claim.
# VALIDATED on UMCS inf03 (A100) 2026-07-23: |CPU-CUDA| = 7.0e-8 V.
#
# Two things that matter (learned the hard way, recorded for reviewers):
#   * Run from the REPO ROOT so the script's `include genesis/src/startup/
#     schedule.g` resolves — otherwise the solver no-ops and Vm stays at rest
#     (-0.07 V), giving a FALSE pass.
#   * stdin from /dev/null so the batch binary can't block waiting for input.
# Prepared by Karol Chlasta (karol@chlasta.pl).
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
cd "$ROOT"

: "${CUDA_HOME:=/storage/opt/cuda/cuda-12.8}"
export LD_LIBRARY_PATH="$CUDA_HOME/lib64:${LD_LIBRARY_PATH:-}"
V=genesis/Scripts/benchmark/hh1952_ap_verify.g
BIN_CPU=./genesis/src/nxgenesis_nocl
BIN_GPU=./genesis/src/nxgenesis
LOG="$HERE/validate_parity_$(hostname)_$(date +%F).log"

for b in "$BIN_CPU" "$BIN_GPU"; do
  [ -x "$b" ] || { echo "ERROR: missing $b — run 10_build.sh first"; exit 1; }
done

{
  echo "===== PARITY CHECK  $(hostname)  $(date '+%F %T %Z') ====="
  nvidia-smi --query-gpu=name,compute_cap,driver_version --format=csv,noheader | head -1
  echo "CUDA_HOME=$CUDA_HOME  script=$V  (N=8 steps=200)"
  echo; echo "----- CPU (fp64) -----"
  cpu_out=$(timeout 120 "$BIN_CPU" -nosimrc -notty -batch "$V" 8 200 </dev/null 2>&1)
  echo "$cpu_out" | grep -E "completed .* steps|NEURONS_AGREE|RESULT_VM|schedule.g"
  echo; echo "----- CUDA (fp32, GENESIS_CUDA_MULTILOOP=210) -----"
  gpu_out=$(timeout 120 env GENESIS_CUDA_MULTILOOP=210 "$BIN_GPU" -nosimrc -notty -batch "$V" 8 200 </dev/null 2>&1)
  echo "$gpu_out" | grep -E "CUDA: device|CUDA MULTILOOP:|NEURONS_AGREE|RESULT_VM"

  cpu_vm=$(echo "$cpu_out" | sed -n 's/^RESULT_VM= *//p' | tail -1)
  gpu_vm=$(echo "$gpu_out" | sed -n 's/^RESULT_VM= *//p' | tail -1)
  echo; echo "CPU  RESULT_VM = $cpu_vm"
  echo "CUDA RESULT_VM = $gpu_vm"
  awk -v a="$cpu_vm" -v b="$gpu_vm" 'BEGIN{
    d=a-b; if(d<0)d=-d;
    printf "|CPU-CUDA|     = %.3e V\n", d;
    print (d<1e-6 ? "PARITY: PASS" : "PARITY: FAIL");
  }'
} 2>&1 | tee "$LOG"
echo "log -> $LOG"
