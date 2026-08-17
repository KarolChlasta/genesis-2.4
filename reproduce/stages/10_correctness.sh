#!/bin/sh
# fp32 accelerator against the fp64 CPU solver on the same model.
#
# This runs first because a speedup from a kernel that computes the wrong thing
# is not a result. The published claim is agreement to ~1e-7 V, which is the
# fp32 floor rather than anything specific to this kernel.
set -u
RESULTS=$1
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
cd "$ROOT" || exit 1
B=genesis/Scripts/benchmark

cpu=$(./genesis/src/nxgenesis_nocl -nosimrc -notty -batch $B/hh1952_ap_verify.g 8 200 2>&1 \
        | sed -n 's/^RESULT_VM_SOMA= *//p')
gpu=$(GENESIS_CUDA_MULTILOOP=210 ./genesis/src/nxgenesis -nosimrc -notty -batch \
        $B/hh1952_ap_verify.g 8 200 2>&1 | sed -n 's/^RESULT_VM_SOMA= *//p')

if [ -z "$cpu" ] || [ -z "$gpu" ]; then
    echo "FAILED to obtain voltages (cpu='$cpu' gpu='$gpu')"
    exit 1
fi
d=$(awk "BEGIN{d=$cpu-$gpu; print (d<0?-d:d)}")
printf 'CPU fp64 Vm = %s\nGPU fp32 Vm = %s\n|difference| = %s V\n' "$cpu" "$gpu" "$d"
echo "correctness_fp32,$d,V" >> "$RESULTS/summary.csv"
