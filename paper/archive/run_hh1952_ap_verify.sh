#!/bin/bash
# HH1952 multi-step AP verification
# Runs CPU and GPU multiloop for N=2, 50, 500 neurons over 200 steps.
# Checks: (1) all N neurons agree, (2) CPU and GPU multiloop agree to 1e-5 V.
#
# Usage: ./paper/run_hh1952_ap_verify.sh
# Requires: genesis/src/nxgenesis and genesis/src/nxgenesis_nocl in PATH or cwd

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BENCH="$SCRIPT_DIR/genesis/Scripts/benchmark/hh1952_ap_verify.g"
CPU_BIN="$SCRIPT_DIR/genesis/src/nxgenesis_nocl"
GPU_BIN="$SCRIPT_DIR/genesis/src/nxgenesis"
N_STEPS=200
WARMUP=10
TOTAL=$((N_STEPS + WARMUP))

OCL_ICD_VENDORS="${OCL_ICD_VENDORS:-/run/host/etc/OpenCL/vendors}"
LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-/opt/rocm/lib}"

export OCL_ICD_VENDORS LD_LIBRARY_PATH

echo "=== HH1952 Multi-step AP Verification ==="
echo "N_STEPS=$N_STEPS  WARMUP=$WARMUP  TOTAL=$TOTAL"
echo "OCL_ICD_VENDORS=$OCL_ICD_VENDORS"
echo ""

pass=0
fail=0

for N in 2 50 500; do
    echo "---- N=$N ----"

    cpu_out=$("$CPU_BIN" -nosimrc -notty -batch "$BENCH" "$N" "$N_STEPS" 2>/dev/null)
    cpu_vm=$(echo "$cpu_out" | grep "^RESULT_VM=" | cut -d= -f2 | tr -d ' ')
    cpu_agree=$(echo "$cpu_out" | grep "^NEURONS_AGREE:" | awk '{print $2}')

    gpu_out=$(GENESIS_OCL_MULTILOOP=$TOTAL \
        "$GPU_BIN" -nosimrc -notty -batch "$BENCH" "$N" "$N_STEPS" 2>/dev/null)
    gpu_vm=$(echo "$gpu_out" | grep "^RESULT_VM=" | cut -d= -f2 | tr -d ' ')
    gpu_agree=$(echo "$gpu_out" | grep "^NEURONS_AGREE:" | awk '{print $2}')

    echo "  CPU  cell0 Vm = $cpu_vm  (neurons_agree=$cpu_agree)"
    echo "  GPU  cell0 Vm = $gpu_vm  (neurons_agree=$gpu_agree)"

    # Compare CPU vs GPU using awk (no bc needed)
    match=$(awk -v a="$cpu_vm" -v b="$gpu_vm" 'BEGIN {
        diff = a - b; if (diff < 0) diff = -diff;
        print (diff < 1e-5) ? "YES" : "NO (" diff ")"
    }')
    echo "  CPU==GPU:       $match"

    if [[ "$cpu_agree" == "YES" && "$gpu_agree" == "YES" && "$match" == "YES" ]]; then
        echo "  PASS"
        pass=$((pass + 1))
    else
        echo "  FAIL"
        fail=$((fail + 1))
    fi
    echo ""
done

echo "=== Summary ==="
echo "PASS: $pass / $((pass + fail))"
if [[ $fail -eq 0 ]]; then
    echo "ALL PASS: CPU and GPU multiloop agree for N=2, 50, 500"
    exit 0
else
    echo "FAILURES: $fail"
    exit 1
fi
