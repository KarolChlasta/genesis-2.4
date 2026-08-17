#!/bin/bash
# Does Arbor's lead survive a realistic run length?
#
# At K=5000 Arbor finishes in 1.56 s against our 1.75 s, but profiling showed
# our excess over kernel time is a fixed 0.21 s of dispatch setup rather than
# per-step work. If that is the whole story, the gap should close as K grows,
# since our warm kernel (66 us/step) is faster than Arbor's entire simulation
# phase at K=5000. This measures both at K=50000 -- 500 ms of simulated time,
# which is an ordinary length for a modelling study.
set -u
N=${N:-10000}
K=${K:-50000}
REPS=${REPS:-3}
export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:${LD_LIBRARY_PATH:-}"
export GENESIS_OCL_TREE_MAX_NCOMPTS=0

echo "== N=$N K=$K on $(hostname) =="
nvidia-smi --query-gpu=name,memory.used --format=csv,noheader

echo "--- GENESIS 2.5 GPU ---"
cd "$HOME/genesis-2.5" || exit 1
S="genesis/Scripts/benchmark/hh_multicompartment_createmap.g"
for r in $(seq 1 "$REPS"); do
    S1=$(date +%s%N)
    out=$(env GENESIS_BENCH_CHANMODE=4 GENESIS_BENCH_NCOMP=16 \
        GENESIS_CUDA_MULTILOOP=$((K + 10)) \
        timeout 3600 ./genesis/src/nxgenesis -nosimrc -notty -batch "$S" "$N" "$K" 2>&1)
    E1=$(date +%s%N)
    ker=$(echo "$out" | sed -n 's/.*total \([0-9.]*\) ms.*/\1/p' | head -1)
    awk "BEGIN{printf \"  genesis-gpu rep $r wall=%.2fs kernel=${ker}ms\n\", ($E1-$S1)/1e9}"
done

echo "--- Arbor 0.10 GPU ---"
P="$HOME/opt/arbor-gpu/lib/python3.13/site-packages"
export PYTHONPATH="$P"
export LD_LIBRARY_PATH="/storage/opt/cuda/cuda-12.8/lib64:$HOME/opt/arbor-gpu/lib:${LD_LIBRARY_PATH:-}"
cd "$HOME" || exit 1
for r in $(seq 1 "$REPS"); do
    out=$(USE_GPU=1 timeout 3600 "$HOME/opt/miniforge/bin/python3" hh_multicomp_arbor.py "$N" "$K" 2>&1)
    w=$(echo "$out" | sed -n 's/^RESULT_WALL_S=//p')
    b=$(echo "$out" | sed -n 's/^RESULT_BUILD_S=//p')
    s=$(echo "$out" | sed -n 's/^RESULT_RUN_S=//p')
    [ -n "$w" ] || { echo "  arbor-gpu rep $r FAILED"; echo "$out" | tail -4; break; }
    echo "  arbor-gpu rep $r wall=${w}s build=${b}s run=${s}s"
done
