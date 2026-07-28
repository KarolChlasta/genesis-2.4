#!/bin/bash
#
# run_benchmark.sh — uruchamia benchmark GENESIS dla CPU i GPU,
# porownuje wyniki i wyswietla speedup
#
# Wymagania:
#   - GENESIS skompilowany bez OpenCL: genesis_cpu
#   - GENESIS skompilowany z OpenCL:   genesis_gpu  (make USE_OPENCL=1)
#   - python3 z matplotlib (opcjonalnie, do wykresu)
#
# Uzycie:
#   ./run_benchmark.sh

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
GENESIS_CPU="${GENESIS_CPU:-genesis}"
GENESIS_GPU="${GENESIS_GPU:-genesis_gpu}"
BENCH_SCRIPT="${SCRIPT_DIR}/ocl_benchmark.g"
RESULT_FILE="${SCRIPT_DIR}/benchmark_result.csv"

# rozmiary sieci do przetestowania
NEURON_COUNTS=(10 50 100 500 1000)

echo "================================================"
echo " GENESIS OpenCL Benchmark"
echo " CPU binary: ${GENESIS_CPU}"
echo " GPU binary: ${GENESIS_GPU}"
echo "================================================"
echo ""

# wyczysc poprzednie wyniki
rm -f "${RESULT_FILE}"

# --- uruchom CPU ---
echo ">>> Testy CPU"
for N in "${NEURON_COUNTS[@]}"; do
    echo -n "  N=${N} neuronow... "
    ${GENESIS_CPU} -nox "${BENCH_SCRIPT}" ${N} 2>/dev/null
    echo "OK"
done

# --- uruchom GPU ---
if command -v "${GENESIS_GPU}" &>/dev/null; then
    echo ""
    echo ">>> Testy GPU (OpenCL)"
    for N in "${NEURON_COUNTS[@]}"; do
        echo -n "  N=${N} neuronow... "
        ${GENESIS_GPU} -nox "${BENCH_SCRIPT}" ${N} 2>/dev/null
        echo "OK"
    done
else
    echo ""
    echo "UWAGA: ${GENESIS_GPU} nie znaleziony — pomijam testy GPU"
    echo "Skompiluj: cd genesis/src && make USE_OPENCL=1"
fi

# --- wyswietl wyniki ---
echo ""
echo "================================================"
echo " Wyniki (z ${RESULT_FILE})"
echo "================================================"
echo ""
printf "%-6s %-8s %-12s %-12s %-10s\n" \
    "Mode" "Neurons" "t_total[s]" "t/step[ms]" "t/compt[us]"
echo "------------------------------------------------------"

while IFS=',' read -r mode neurons compts steps t_total t_step t_compt; do
    [[ "$mode" == "mode" ]] && continue  # skip header
    printf "%-6s %-8s %-12.4f %-12.4f %-10.4f\n" \
        "$mode" "$neurons" "$t_total" \
        "$(echo "$t_step * 1000" | bc -l)" \
        "$t_compt"
done < "${RESULT_FILE}"

# --- oblicz speedup ---
echo ""
echo "================================================"
echo " Speedup GPU vs CPU"
echo "================================================"
python3 - <<'PYEOF'
import csv, sys
from collections import defaultdict

results = defaultdict(dict)
try:
    with open("benchmark_result.csv") as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row['neurons'])
            results[n][row['mode']] = float(row['t_total'])
except FileNotFoundError:
    print("Brak pliku wynikow")
    sys.exit(0)

print(f"{'Neurons':>8} {'CPU[s]':>10} {'GPU[s]':>10} {'Speedup':>10}")
print("-" * 42)
for n in sorted(results.keys()):
    cpu = results[n].get('CPU')
    gpu = results[n].get('GPU')
    if cpu and gpu:
        speedup = cpu / gpu
        print(f"{n:>8} {cpu:>10.3f} {gpu:>10.3f} {speedup:>9.2f}x")
    elif cpu:
        print(f"{n:>8} {cpu:>10.3f} {'N/A':>10} {'N/A':>10}")

# opcjonalny wykres
try:
    import matplotlib.pyplot as plt
    neurons = sorted(results.keys())
    speedups = [results[n]['CPU']/results[n]['GPU']
                for n in neurons
                if 'CPU' in results[n] and 'GPU' in results[n]]
    if speedups:
        plt.figure(figsize=(8,5))
        plt.plot(neurons[:len(speedups)], speedups, 'o-', color='royalblue', linewidth=2)
        plt.axhline(y=1.0, color='red', linestyle='--', label='CPU baseline')
        plt.xlabel('Liczba neuronow')
        plt.ylabel('Speedup (CPU/GPU)')
        plt.title('GENESIS OpenCL — przyspieszenie GPU vs CPU\n(AMD Radeon 890M)')
        plt.grid(True, alpha=0.3)
        plt.legend()
        plt.tight_layout()
        plt.savefig('benchmark_speedup.png', dpi=150)
        print("\nWykres zapisany: benchmark_speedup.png")
except ImportError:
    pass
PYEOF

echo ""
echo "Gotowe. Pelne wyniki: ${RESULT_FILE}"
