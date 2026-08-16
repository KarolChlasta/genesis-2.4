#!/bin/bash
# Re-confirm the GENESIS VAnet2 wall time on the node that ran CoreNEURON,
# uninstrumented, so the head-to-head rests on same-node measurements.
set -u
R="$HOME/genesis-2.5"
W="$HOME/vanet2_timing"
rm -rf "$W"; mkdir -p "$W"
cp "$R"/genesis/Scripts/VAnet2/*.g "$R"/genesis/Scripts/VAnet2/*.p "$W"/ 2>/dev/null
cd "$W" || exit 1
printf 'setenv SIMPATH . %s/genesis/startup %s/genesis/Scripts/neurokit %s/genesis/Scripts/neurokit/prototypes\nsetenv SIMNOTES %s/.notes\nsetenv GENESIS_HELP %s/genesis/Doc\nschedule\n' \
    "$R" "$R" "$R" "$HOME" "$R" > .simrc

echo "node=$(hostname)"
for r in 1 2 3; do
    S=$(date +%s%N)
    timeout 1800 "$R/genesis/src/nxgenesis_nocl" -notty -batch VAnet2-batch.g > "out_$r.log" 2>&1
    RC=$?
    E=$(date +%s%N)
    awk "BEGIN{printf \"rep $r wall=%.2f s rc=$RC\n\", ($E-$S)/1e9}"
done
