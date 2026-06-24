#!/bin/bash
# run_genesis25_multiloop_benchmark.sh
#
# CPU vs GPU multiloop benchmark for GENESIS 2.5
#
# Compares:
#   CPU arm:           nxgenesis_nocl          (pure CPU Hines + channel update)
#   GPU multiloop arm: nxgenesis + GENESIS_OCL_MULTILOOP=<N_STEPS>
#                      (all steps dispatched in one GPU kernel)
#
# Prerequisites:
#   - nxgenesis built with USE_OPENCL=1 (see REPLICATION.md)
#   - nxgenesis_nocl built without USE_OPENCL
#   - GPU with cl_khr_fp64 support (AMD ROCm or CUDA; NOT Mesa rusticl on RDNA iGPU)
#     To check: run nxgenesis ... | grep "OCL: tryb multiloop"
#     If "nie wspiera fp64" appears, GPU will not be used.
#
# Usage:
#   ./paper/run_genesis25_multiloop_benchmark.sh [N_NEURONS] [N_STEPS] [N_REPS]
#
# Defaults: N_NEURONS=2000  N_STEPS=5000  N_REPS=3

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

CPU_BIN="$REPO_ROOT/genesis/src/nxgenesis_nocl"
GPU_BIN="$REPO_ROOT/genesis/src/nxgenesis"
BENCH_SCRIPT="$REPO_ROOT/genesis/Scripts/benchmark/ocl_hh_benchmark.g"

N_NEURONS="${1:-2000}"
N_STEPS="${2:-5000}"
N_REPS="${3:-3}"

echo "==========================================="
echo "GENESIS 2.5 CPU vs GPU Multiloop Benchmark"
echo "==========================================="
echo "Neurons:   $N_NEURONS"
echo "Steps:     $N_STEPS"
echo "Reps:      $N_REPS"
echo "CPU bin:   $CPU_BIN"
echo "GPU bin:   $GPU_BIN (GENESIS_OCL_MULTILOOP=$N_STEPS)"
echo "-------------------------------------------"

if [ ! -x "$CPU_BIN" ]; then
    echo "ERROR: $CPU_BIN not found. Build with: make nxgenesis && cp nxgenesis nxgenesis_nocl"
    exit 1
fi
if [ ! -x "$GPU_BIN" ]; then
    echo "ERROR: $GPU_BIN not found. Build with: USE_OPENCL=1 (see REPLICATION.md)"
    exit 1
fi

# CSV output
CSV="$SCRIPT_DIR/genesis25_multiloop_benchmark.csv"
echo "mode,neurons,steps,rep,wall_seconds,genesis_step_seconds" > "$CSV"

# ---- helper: run one arm and extract timing ----
run_arm() {
    local mode="$1"    # CPU or GPU
    local bin="$2"
    local env_prefix="$3"
    local rep="$4"

    local tmpout
    tmpout="$(mktemp)"

    local t0 t1 wall_s
    t0="$(date +%s%N)"
    eval "$env_prefix \"$bin\" -nosimrc -notty -batch \"$BENCH_SCRIPT\" $N_NEURONS $N_STEPS" \
        > "$tmpout" 2>&1
    t1="$(date +%s%N)"
    wall_s="$(python3 -c "print(round(($t1 - $t0) / 1e9, 3))")"

    # Extract GENESIS "completed N_STEPS steps in X cpu seconds" (second occurrence = real run)
    local genesis_step_s
    genesis_step_s="$(grep -oP "completed ${N_STEPS} steps in \K[\d.]+" "$tmpout" 2>/dev/null | head -1 || echo "N/A")"

    # Print OCL multiloop diagnostic if present
    if grep -q "OCL MULTILOOP" "$tmpout" 2>/dev/null; then
        echo "  [GPU multiloop dispatch timing:]"
        grep "OCL MULTILOOP" "$tmpout" | sed 's/^/    /'
    fi
    if grep -q "nie wspiera fp64" "$tmpout" 2>/dev/null; then
        echo "  WARNING: GPU fp64 not supported — GPU arm ran on CPU!"
        echo "           Use ROCm OpenCL runtime for GPU execution."
    fi

    echo "$mode,$N_NEURONS,$N_STEPS,$rep,$wall_s,$genesis_step_s" >> "$CSV"
    echo "  wall=$wall_s s  genesis_step=${genesis_step_s}s"
    rm -f "$tmpout"
}

# ---- CPU runs ----
echo ""
echo "--- CPU arm ---"
CPU_WALL_TOTAL=0
for rep in $(seq 1 $N_REPS); do
    echo -n "  rep $rep: "
    run_arm "CPU" "$CPU_BIN" "" "$rep"
done

# ---- GPU multiloop runs ----
echo ""
echo "--- GPU multiloop arm ---"
GPU_WALL_TOTAL=0
for rep in $(seq 1 $N_REPS); do
    echo -n "  rep $rep: "
    run_arm "GPU_multiloop" "$GPU_BIN" "GENESIS_OCL_MULTILOOP=$N_STEPS" "$rep"
done

# ---- Summary ----
echo ""
echo "==========================================="
echo "Results written to: $CSV"
python3 - << PYEOF
import csv, statistics
rows = list(csv.DictReader(open("$CSV")))
for mode in ("CPU", "GPU_multiloop"):
    walls = [float(r["wall_seconds"]) for r in rows if r["mode"] == mode]
    gsteps = [float(r["genesis_step_seconds"]) for r in rows
              if r["mode"] == mode and r["genesis_step_seconds"] not in ("N/A","")]
    if walls:
        print(f"  {mode:<20} wall: mean={statistics.mean(walls):.3f}s  "
              f"stdev={statistics.stdev(walls) if len(walls)>1 else 0:.3f}s")
    if gsteps:
        print(f"  {mode:<20}  step: mean={statistics.mean(gsteps):.3f}s")

walls_cpu  = [float(r["wall_seconds"]) for r in rows if r["mode"] == "CPU"]
walls_gpu  = [float(r["wall_seconds"]) for r in rows if r["mode"] == "GPU_multiloop"]
if walls_cpu and walls_gpu:
    speedup = statistics.mean(walls_cpu) / statistics.mean(walls_gpu)
    print(f"\n  Wall-clock speedup (CPU / GPU_multiloop): {speedup:.1f}x")
PYEOF
echo "==========================================="
