// Self-test for the new walltimemark/walltime SLI functions (GENESIS 2.5).
// Sanity checks: (1) elapsed time for a real workload is sane and non-zero,
// (2) back-to-back marks with near-zero work give a near-zero (but still
// measurable, non-negative) delta, (3) a longer workload gives a
// proportionally larger delta -- confirming real signal, not a stuck/broken
// timer. Karol Chlasta, 2026-07-25.

include genesis/src/startup/schedule.g

echo "=== walltime self-test ==="

// (1) trivial delta: mark, do ~nothing, read back
walltimemark
float t_trivial = {walltime}
echo "trivial delta (expect ~0, >= 0): " {t_trivial}

// (2) small workload: build N neurons, mark, sleep-equivalent via a loop
int i
walltimemark
for (i = 0; i < 200000; i = i + 1)
end
float t_small = {walltime}
echo "small-loop delta (expect small, > 0): " {t_small}

// (3) bigger workload: 10x more iterations -- should scale up roughly 10x
walltimemark
for (i = 0; i < 2000000; i = i + 1)
end
float t_big = {walltime}
echo "big-loop delta (expect ~10x small, > 0): " {t_big}

float ratio = {t_big / t_small}
echo "ratio big/small (expect roughly 5-15): " {ratio}

quit
