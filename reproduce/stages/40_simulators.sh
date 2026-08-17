#!/bin/sh
# Cross-simulator comparison. Optional: needs NEURON 9.x, and Arbor with CUDA
# for the GPU arm. See cluster_bringup/coreneuron/README.md for how the models
# were matched and why that matching had to be verified rather than assumed.
set -u
RESULTS=$1
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
H="$ROOT/cluster_bringup/coreneuron"

python3 -c "import neuron" 2>/dev/null || {
    echo "NEURON not importable; skipping. pip install neuron"
    exit 0
}
cp -f "$H/hh_multicomp_neuron.py" . 2>/dev/null || true
echo "Running the multi-compartment model under NEURON and CoreNEURON."
echo "CoreNEURON only takes over for cells registered with ParallelContext"
echo "under a gid; hh_multicomp_neuron.py does that, and the harness checks"
echo "for CoreNEURON's own nrn_setup output before trusting the timing."
sh "$H/bench_multicomp_cross.sh" 2>&1 | tail -12
