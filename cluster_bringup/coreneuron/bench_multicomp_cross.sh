#!/bin/bash
# Cross-simulator benchmark on a model the GENESIS accelerator supports.
#
# The Vogels-Abbott comparison is CPU-on-both-sides, because that network is
# spiking and the accelerator declines it. For a paper about GPU acceleration
# that leaves the central claim untested across simulators. This runs the
# multi-compartment HH benchmark instead -- current-driven, no synapses, which
# is exactly what the accelerator handles -- so the GPU arm is real.
#
# GENESIS numbers for the same configuration come from
# cluster_bringup/logs/multicomp_ksweep_inf02_A40_20260816.csv (N=10000,
# K=5000): CPU 116.75 s, GPU 2.05 s, both end-to-end.
set -u
N=${N:-10000}
STEPS=${STEPS:-5000}
REPS=${REPS:-3}
cd "$HOME" || exit 1

echo "== NEURON multi-compartment HH, N=$N NCOMP=16 K=$STEPS on $(hostname) =="

# CoreNEURON needs a mechanism library even when the model uses only built-ins.
W="$HOME/nrn_multicomp"
mkdir -p "$W" && cd "$W"
if [ ! -f x86_64/libcorenrnmech.so ]; then
    nrnivmodl -coreneuron . > build.log 2>&1
    ls x86_64/libcorenrnmech.so >/dev/null 2>&1 || echo "WARN: no coreneuron lib; CPU arm only"
fi
cp -f "$HOME/hh_multicomp_neuron.py" .

run_arm() {
    label=$1; env_str=$2
    for r in $(seq 1 "$REPS"); do
        out=$(env $env_str timeout 3600 python3.12 hh_multicomp_neuron.py "$N" "$STEPS" 2>&1)
        w=$(echo "$out" | sed -n 's/^RESULT_WALL_S=//p')
        b=$(echo "$out" | sed -n 's/^RESULT_BUILD_S=//p')
        s=$(echo "$out" | sed -n 's/^RESULT_RUN_S=//p')
        v=$(echo "$out" | sed -n 's/^RESULT_VM_SOMA=//p')
        if [ -z "$w" ]; then
            echo "  $label rep $r FAILED"; echo "$out" | tail -4; return 1
        fi
        # CoreNEURON is silent when it declines to take over, and the timings
        # then match the plain NEURON arm exactly. Require its own output as
        # proof that the arm measured what it claims to.
        engaged=""
        case "$label" in
          coreneuron*) echo "$out" | grep -q "nrn_setup" && engaged="[coreneuron confirmed]" || engaged="[WARNING: CoreNEURON DID NOT ENGAGE]" ;;
        esac
        echo "  $label rep $r wall=${w}s build=${b}s run=${s}s vm_soma=${v} $engaged"
    done
}

echo "--- NEURON 9.0.2 CPU ---"
run_arm "neuron" "USE_CORENEURON=0"

echo "--- CoreNEURON CPU ---"
run_arm "coreneuron" "USE_CORENEURON=1 USE_GPU=0"
