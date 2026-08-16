#!/bin/bash
# Verify the compiled nahh/khh reproduce the ChannelBuilder channels, then
# time CoreNEURON. Three arms, all on this node, same model, same dt:
#   A  NEURON CPU, compiled mod channels
#   B  NEURON CPU, original ChannelBuilder channels (x86_64 hidden)
#   C  CoreNEURON CPU, compiled mod channels
# A vs B is the correctness check; A vs C is the CoreNEURON speedup.
export PATH="$HOME/.local/bin:$PATH"
D="$HOME/coreneuron_cmp/destexhe_benchmarks/NEURON/cobahh"
cd "$D" || exit 1

cat > run_plain.py <<'EOF'
from neuron import h
h.load_file("stdrun.hoc")
h.cvode.cache_efficient(1)
h("mosinit=0")
h.load_file("init.hoc")
EOF

cat > run_core.py <<'EOF'
from neuron import h, coreneuron
h.load_file("stdrun.hoc")
h.cvode.cache_efficient(1)
coreneuron.enable = True
coreneuron.gpu = False
h("mosinit=0")
h.load_file("init.hoc")
EOF

PY=$(command -v python3.12)

echo "=== A: NEURON CPU, compiled mod channels ==="
rm -f out.dat
S=$(date +%s%N); timeout 1700 "$PY" run_plain.py > A_mod.log 2>&1; RC=$?; E=$(date +%s%N)
awk "BEGIN{printf \"A wall=%.2f s rc=$RC\n\", ($E-$S)/1e9}"
grep -E "RunTime|SetupTime" A_mod.log
[ -f out.dat ] && { cp out.dat out_A_mod.dat; echo "A spikes=$(wc -l < out.dat)"; }

echo "=== B: NEURON CPU, ChannelBuilder (original) ==="
mv x86_64 x86_64_hidden
rm -f out.dat
S=$(date +%s%N); timeout 1700 "$PY" run_plain.py > B_chanbuild.log 2>&1; RC=$?; E=$(date +%s%N)
awk "BEGIN{printf \"B wall=%.2f s rc=$RC\n\", ($E-$S)/1e9}"
grep -E "RunTime|SetupTime" B_chanbuild.log
[ -f out.dat ] && { cp out.dat out_B_chanbuild.dat; echo "B spikes=$(wc -l < out.dat)"; }
mv x86_64_hidden x86_64

echo "=== A vs B agreement ==="
if [ -f out_A_mod.dat ] && [ -f out_B_chanbuild.dat ]; then
    if cmp -s out_A_mod.dat out_B_chanbuild.dat; then
        echo "IDENTICAL spike trains"
    else
        echo "differ: A=$(wc -l < out_A_mod.dat) B=$(wc -l < out_B_chanbuild.dat) spikes"
        echo "first divergence:"; diff out_A_mod.dat out_B_chanbuild.dat | head -4
    fi
fi

echo "=== C: CoreNEURON CPU, compiled mod channels ==="
rm -f out.dat
S=$(date +%s%N); timeout 1700 "$PY" run_core.py > C_core.log 2>&1; RC=$?; E=$(date +%s%N)
awk "BEGIN{printf \"C wall=%.2f s rc=$RC\n\", ($E-$S)/1e9}"
grep -iE "RunTime|SetupTime|Solver Time|does not exist|error" C_core.log | head -6
[ -f out.dat ] && { cp out.dat out_C_core.dat; echo "C spikes=$(wc -l < out.dat)"; }
echo "=== done ==="
