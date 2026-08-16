#!/bin/bash
# Measure the VAnet2 population firing rate, so the GENESIS/CoreNEURON
# comparison can be normalised by network activity rather than assumed equal.
set -u
R="$HOME/genesis-2.5"
W="$HOME/vanet2_spikecount"
rm -rf "$W"; mkdir -p "$W"
cp "$R"/genesis/Scripts/VAnet2/*.g "$R"/genesis/Scripts/VAnet2/*.p "$W"/ 2>/dev/null
cp "$HOME/spikecount.g" "$W"/

cd "$W" || exit 1
# Insert the instrumentation after the network is built and outputs are set up,
# but before the run block.
sed -i 's|^if(batch)|include spikecount.g\nif(batch)|' VAnet2-batch.g
grep -n "include spikecount.g" VAnet2-batch.g

printf 'setenv SIMPATH . %s/genesis/startup %s/genesis/Scripts/neurokit %s/genesis/Scripts/neurokit/prototypes\nsetenv SIMNOTES %s/.notes\nsetenv GENESIS_HELP %s/genesis/Doc\nschedule\n' \
    "$R" "$R" "$R" "$HOME" "$R" > .simrc

timeout 1800 "$R/genesis/src/nxgenesis_nocl" -notty -batch VAnet2-batch.g > out.log 2>&1
echo "rc=$?"
if [ -s spikes_all.txt ]; then
    N=$(wc -l < spikes_all.txt)
    echo "total spikes = $N"
    awk -v n="$N" 'BEGIN{printf "population mean rate = %.2f Hz  (%d cells, 5.0 s)\n", n/4000/5.0, 4000}'
    echo "--- first lines ---"; head -3 spikes_all.txt
else
    echo "NO SPIKE FILE"; tail -15 out.log
fi
