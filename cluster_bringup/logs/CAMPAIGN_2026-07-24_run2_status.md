# Corrected campaign, run 2 (2026-07-24, launched 20:10) — status

Env-empty-string bug from run 1 is confirmed fixed: CPU-arm wall-clock values
are no longer a uniform ~0.002s "instant failure" signature — they now vary
meaningfully by N (e.g. up to several seconds at N=50000), confirming the CPU
binary genuinely executes.

## Progress as of ~23:15
N=500 through 50000: **complete** (40/40 rows = 10 reps x 2 K x 2 arms) on
both A100 (inf03) and A40 (inf02). N=100000 in progress, much slower than run
1's CUDA-only timing (started 22:25/22:26, only 2-3/40 rows after ~50 min) —
likely will not finish all 10 reps before the `timeout 4h` safety cutoff
(~00:10); that's fine, partial data is still safely written incrementally.

## New finding: K=0/K=50000 subtraction is too noisy at N=500..50000
Step-phase deltas (mean(K=50000) − mean(K=0)) are **mostly negative or near
zero** for both arms across this whole N range — physically impossible for a
compute workload (more steps must take ≥ as long). Example at N=50000:
- CPU step, A100: **+3.73 s** (plausible, positive)
- CPU step, A40: **−5.60 s** (impossible — noise exceeds signal)

Conclusion: at these N, run-to-run wall-clock variance (OS scheduling, shared
no-queue cluster, cache effects) is comparable to or larger than the true
step-phase compute cost, making the two-K-value external subtraction method
unreliable here. This is a **methodology** limitation, not a bug — do not quote
any speedup number derived from this data.

## What IS trustworthy right now
The CUDA binary's own **internal kernel self-report** (`CUDA MULTILOOP: ...
us/step`, printed by the binary itself, not measured externally) has been
accurate and low-noise every time we've checked it tonight — it should be the
basis for the GPU-side number in any redesigned campaign. The CPU side needs
an equivalent low-noise measurement (e.g. many more reps to average out
variance, a much larger K so the true signal dominates noise, or a GENESIS-
internal timer around just the step loop rather than external wall-clock
subtraction across two separate process invocations).

## Recommendation
Let the current run 2 finish/timeout (no harm, safe, incremental writes) --
its N=500-50000 data is already fully collected and won't change. Do NOT
derive a speedup claim from it. Design a properly noise-robust measurement
(larger K, more reps, and/or an internal-timer approach) as a deliberate next
step, not another blind large sweep.
