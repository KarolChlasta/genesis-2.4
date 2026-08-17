#!/bin/sh
# Reproduce the figures reported in the GENESIS 2.5 paper.
#
#   sh reproduce/run_all.sh --quick     ~15 min, the accelerator claims
#   sh reproduce/run_all.sh             ~90 min, adds the full sweeps
#   sh reproduce/run_all.sh --with-neuron   adds the cross-simulator comparison
#
# Every stage writes a CSV under reproduce/results/ and appends one line per
# claim to reproduce/results/summary.csv. compare.py then prints measured
# against published with a pass/fail per claim, so the output is a verdict
# rather than a pile of numbers to interpret.
#
# What you need: Linux x86_64, GCC, GNU make, a CUDA 12.x toolkit and an NVIDIA
# GPU. --with-neuron additionally needs NEURON 9.x (pip install neuron) and,
# for the Arbor arm, an Arbor built with CUDA. Neither is required for the
# GENESIS claims, which are the ones this paper makes.
#
# Numbers will not match to the last digit. GPU clock state, card model and
# host CPU all move them; the tolerances in expected.csv are set accordingly,
# and the shape of each result -- which arm wins, and by roughly how much --
# is what should reproduce.
set -u

HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/.." && pwd)
RESULTS="$HERE/results"
mkdir -p "$RESULTS"
SUMMARY="$RESULTS/summary.csv"

MODE=quick
WITH_NEURON=0
for a in "$@"; do
    case "$a" in
        --quick) MODE=quick ;;
        --full)  MODE=full ;;
        --with-neuron) WITH_NEURON=1 ;;
        -h|--help) sed -n '2,25p' "$0"; exit 0 ;;
        *) echo "unknown option: $a" >&2; exit 2 ;;
    esac
done
[ "$#" -eq 0 ] && MODE=full

cd "$ROOT" || exit 1
echo "claim,measured,units" > "$SUMMARY"

say() { printf '\n=== %s ===\n' "$1"; }

# ---------------------------------------------------------------- environment
say "environment"
uname -srm
gcc --version | head -1
if command -v nvidia-smi >/dev/null 2>&1; then
    nvidia-smi --query-gpu=name,driver_version,memory.total --format=csv,noheader
    USED=$(nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits | head -1)
    if [ "$USED" -gt 500 ]; then
        echo
        echo "WARNING: $USED MiB is already allocated on this GPU by another"
        echo "process. Timings taken now will be inflated -- in our own runs a"
        echo "foreign job raised every GPU figure by ~30% while leaving the CPU"
        echo "arm untouched. Wait for the card before trusting these results."
        echo
    fi
else
    echo "nvidia-smi not found: no GPU stage can run" >&2
    exit 1
fi

# CUDA is not always on PATH; the build needs nvcc.
[ -n "${CUDA_HOME:-}" ] || CUDA_HOME=$(ls -d /usr/local/cuda* /storage/opt/cuda/cuda-12.8 2>/dev/null | head -1)
[ -x "$CUDA_HOME/bin/nvcc" ] && PATH="$CUDA_HOME/bin:$PATH" && export PATH CUDA_HOME
command -v nvcc >/dev/null 2>&1 || { echo "nvcc not found; set CUDA_HOME" >&2; exit 1; }
export LD_LIBRARY_PATH="$CUDA_HOME/lib64:${LD_LIBRARY_PATH:-}"
nvcc --version | tail -2 | head -1

# Above 20000 compartments the batched tree solver otherwise declines the model
# and falls back to per-step dispatch, which measures a different code path.
export GENESIS_OCL_TREE_MAX_NCOMPTS=0

# --------------------------------------------------------------------- build
say "build"
if [ -x genesis/src/nxgenesis ] && [ -x genesis/src/nxgenesis_nocl ] && [ "${SKIP_BUILD:-0}" = 1 ]; then
    echo "using existing binaries (SKIP_BUILD=1)"
else
    sh cluster_bringup/10_build.sh > "$RESULTS/build.log" 2>&1 \
        || { echo "build failed, see $RESULTS/build.log" >&2; tail -20 "$RESULTS/build.log"; exit 1; }
    echo "built genesis/src/nxgenesis and nxgenesis_nocl"
fi

# --------------------------------------------------------------- correctness
say "correctness: fp32 accelerator against the fp64 CPU solver"
sh "$HERE/stages/10_correctness.sh" "$RESULTS" | tee "$RESULTS/correctness.txt"

# ------------------------------------------------------------- accelerator
say "accelerator speedup (this is the paper's central claim)"
sh "$HERE/stages/20_speedup.sh" "$RESULTS" "$MODE" | tee "$RESULTS/speedup.txt"

# --------------------------------------------------------------- crossover
if [ "$MODE" = full ]; then
    say "run-length crossover"
    sh "$HERE/stages/30_crossover.sh" "$RESULTS" | tee "$RESULTS/crossover.txt"
fi

# ------------------------------------------------------- other simulators
if [ "$WITH_NEURON" = 1 ]; then
    say "cross-simulator comparison"
    sh "$HERE/stages/40_simulators.sh" "$RESULTS" | tee "$RESULTS/simulators.txt"
fi

# ------------------------------------------------------------------ figures
# The numbers are what gets checked; the figures fall out of them. These are the
# same scripts that made the paper's, reading the CSVs just produced, so a
# reviewer gets the paper's plots drawn from their own hardware.
say "figures from the measurements just taken"
if python3 -c "import matplotlib" 2>/dev/null; then
    for s in plot_crossover.py plot_multicompartment_sweep.py; do
        [ -f "paper/scripts/$s" ] || continue
        python3 "paper/scripts/$s" 2>&1 | tail -1 || echo "  $s: skipped (needs its full sweep)"
    done
else
    echo "matplotlib not installed; skipping figures (numbers are unaffected)"
fi

# ----------------------------------------------------------------- verdict
say "measured against published"
python3 "$HERE/compare.py" "$SUMMARY" "$HERE/expected.csv"
echo
echo "Raw results: $RESULTS"
echo "Figures:     paper/figures/"
