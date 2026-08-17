#!/usr/bin/env python3
"""Measured against published, one verdict per claim.

The numbers are the claims, so these are what get checked. Figures follow from
them: the plotting scripts in paper/scripts/ read the same CSVs, so a reviewer
who runs this pack can regenerate the paper's figures from their own hardware.

Tolerances live in expected.csv and are deliberately loose. GPU clock state,
card model and host CPU all move absolute timings; what should reproduce is the
shape of each result -- which arm wins, and roughly by how much. A run that
lands outside tolerance is worth looking into, not automatically a failure of
the software.
"""

# Deliberately plain Python: no annotations, no f-string niceties beyond 3.6,
# no third-party imports. A reviewer's cluster may ship python3.6, and a
# reproduction pack that needs its own toolchain installed first is not one.
import csv
import sys
import os


def load_measured(path):
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            try:
                out[row["claim"]] = (float(row["measured"]), row.get("units", ""))
            except (KeyError, ValueError):
                continue
    return out


def main():
    if len(sys.argv) != 3:
        print("usage: compare.py <summary.csv> <expected.csv>", file=sys.stderr)
        return 2
    measured = load_measured(sys.argv[1])
    expected_path = sys.argv[2]

    rows, checked, passed, missing = [], 0, 0, 0
    with open(expected_path, newline="") as f:
        for e in csv.DictReader(f):
            claim = e["claim"]
            exp = float(e["expected"])
            tol = float(e["tolerance_pct"])
            got = measured.get(claim)
            if got is None:
                rows.append((claim, e["table"], f"{exp:g}", "not run", "-", ""))
                missing += 1
                continue
            val = got[0]
            checked += 1
            # The correctness claim is an order of magnitude, not a value.
            if claim == "correctness_fp32":
                ok = val <= exp * 10
                delta = f"{val:.1e}"
            else:
                ok = abs(val - exp) <= exp * tol / 100.0
                delta = f"{(val - exp) / exp * 100:+.0f}%"
            passed += ok
            rows.append((claim, e["table"], f"{exp:g}", f"{val:g}", delta,
                         "ok" if ok else "OUTSIDE"))

    w = max(len(r[0]) for r in rows) + 2
    print(f"{'claim':<{w}}{'table':<16}{'published':>10}{'measured':>12}{'delta':>9}  verdict")
    print("-" * (w + 55))
    for claim, table, exp, got, delta, verdict in rows:
        print(f"{claim:<{w}}{table:<16}{exp:>10}{got:>12}{delta:>9}  {verdict}")

    print()
    if checked:
        print(f"{passed}/{checked} claims reproduced within tolerance", end="")
        print(f"; {missing} not run in this mode" if missing else "")
    else:
        print("nothing measured -- did a stage fail?")

    if checked and passed < checked:
        print()
        print("A claim outside tolerance is usually hardware, not a defect:")
        print("  - a GPU shared with another job inflates every GPU figure")
        print("  - a cold card runs 1.2-1.8x slower than a warm one")
        print("  - absolute timings track the host CPU and card model")
        print("Check nvidia-smi and re-run before concluding anything.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
