#!/bin/sh
# What does the periodic device sync in the tree multiloop cost?
#
# cuda_backend_multiloop_tree() calls cudaDeviceSynchronize() every 16 steps.
# The comment records it as defensive insurance after a hang on a laptop iGPU
# that never reproduced on the cluster cards, and each call drains the pipeline
# -- 313 of them over a 5010-step run. GENESIS_CUDA_SYNC_EVERY now sets the
# interval; 0 disables it. Correctness is checked at every setting, not just
# the timing: the recorded voltages must not move.
set -u
R="$HOME/genesis-2.5"
cd "$R" || exit 1
export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
export GENESIS_OCL_TREE_MAX_NCOMPTS=0
S="genesis/Scripts/benchmark/hh_multicompartment_createmap.g"
N=${N:-10000}
K=${K:-5000}
REPS=${REPS:-3}

echo "== sync interval sweep, N=$N K=$K on $(hostname) =="
for every in 16 64 256 0; do
    r=1
    while [ "$r" -le "$REPS" ]; do
        S1=$(date +%s%N)
        out=$(env GENESIS_BENCH_CHANMODE=4 GENESIS_BENCH_NCOMP=16 \
            GENESIS_CUDA_MULTILOOP=$((K + 10)) GENESIS_CUDA_SYNC_EVERY=$every \
            timeout 1800 ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" 2>&1)
        E1=$(date +%s%N)
        ker=$(echo "$out" | sed -n 's/.*total \([0-9.]*\) ms.*/\1/p' | head -1)
        vm=$(echo "$out"  | sed -n 's/^RESULT_VM_SOMA= *//p')
        awk "BEGIN{printf \"  sync_every=%-4s rep $r wall=%.2fs kernel=${ker}ms vm=${vm}\n\", \"$every\", ($E1-$S1)/1e9}"
        r=$((r + 1))
    done
done
