#!/bin/sh
# Read-only recon of a compute node (run ON inf02 / inf03, not on miranda).
# Gathers everything needed to fill in the build/benchmark steps. Changes nothing.
# Prepared by Karol Chlasta (karol@chlasta.pl).
set -u
echo "=================================================================="
echo " Recon: $(hostname)   $(date '+%Y-%m-%d %H:%M:%S')"
echo "=================================================================="

echo "-- CPU --"
echo "nproc = $(nproc)"
lscpu 2>/dev/null | grep -E "^Model name|^Socket|^Core|^Thread|^CPU\(s\):" | sed 's/^/  /'

echo "-- Memory --"
free -h 2>/dev/null | head -2 | sed 's/^/  /'

echo "-- GPU --"
if command -v nvidia-smi >/dev/null 2>&1; then
  nvidia-smi --query-gpu=name,compute_cap,memory.total,driver_version --format=csv | sed 's/^/  /'
else
  echo "  nvidia-smi NOT found"
fi

echo "-- CUDA toolkit --"
if command -v nvcc >/dev/null 2>&1; then nvcc --version | tail -2 | sed 's/^/  /';
else echo "  nvcc NOT on PATH  ->  try: module avail | grep -i cuda ; module load <cuda>"; fi

echo "-- Modules (cuda / mpi / gcc) --"
( module avail 2>&1 | grep -iE "cuda|mpi|openmpi|mpich|gcc|nvhpc" || echo "  (module system: none, or 'module avail' empty)" ) | sed 's/^/  /' | head -25

echo "-- Build deps --"
for t in gcc g++ make flex bison mpirun mpicc git; do
  printf "  %-8s " "$t"; command -v "$t" 2>/dev/null || echo "MISSING"
done

echo "-- Tools in /storage/opt --"
ls -1 /storage/opt 2>/dev/null | sed 's/^/  /' | head -40 || echo "  (no /storage/opt)"

echo "-- Suggested nvcc -arch (from GPU compute capability) --"
if command -v nvidia-smi >/dev/null 2>&1; then
  cc=$(nvidia-smi --query-gpu=compute_cap --format=csv,noheader 2>/dev/null | head -1 | tr -d '. ')
  [ -n "$cc" ] && echo "  -arch=sm_${cc}" || echo "  (could not read compute_cap)"
fi
echo "=================================================================="
