#!/usr/bin/env python3
"""The GENESIS multi-compartment benchmark, rebuilt in Arbor.

Third implementation of the same model, after GENESIS
(hh_multicompartment_createmap.g) and NEURON (hh_multicomp_neuron.py). Arbor is
the one competitor whose GPU backend is reachable on this cluster -- it targets
CUDA directly, where CoreNEURON offloads through OpenACC and needs NVIDIA's
compilers -- so this is what makes a GPU-to-GPU comparison possible.

Geometry and properties as in the other two:
    soma        20 um long, 20 um diameter
    dendrite    50 um long, 2 um diameter, 15 in a chain
    cm          0.01 F/m2, rL 30 ohm cm
    pas         g = 1/3333.33 S/cm2, e = -59.387 mV
    hh          gnabar 0.12, gkbar 0.036 S/cm2, gl 0 (leak is in pas)
    iclamp      0.5 nA at the soma, on throughout
    dt          0.01 ms

One control volume per segment reproduces the 16 compartments the other two
simulators integrate, so the per-step work matches.
"""

import os
import sys
import time

import arbor as A

N = int(sys.argv[1]) if len(sys.argv) > 1 else 100
STEPS = int(sys.argv[2]) if len(sys.argv) > 2 else 5000
NCOMP = int(os.environ.get("BENCH_NCOMP", "16"))
USE_GPU = os.environ.get("USE_GPU", "0") == "1"
DT = 0.01


def make_cell():
    tree = A.segment_tree()
    # soma, then NCOMP-1 dendrite segments end to end
    prox = A.mpoint(0, 0, 0, 10.0)
    dist = A.mpoint(20, 0, 0, 10.0)
    p = tree.append(A.mnpos, prox, dist, tag=1)
    x = 20.0
    for _ in range(NCOMP - 1):
        p = tree.append(p, A.mpoint(x, 0, 0, 1.0), A.mpoint(x + 50.0, 0, 0, 1.0), tag=2)
        x += 50.0

    decor = A.decor()
    decor.set_property(Vm=-70.0, cm=0.01, rL=30.0)
    decor.paint('(all)', A.density('pas', {'g': 1.0 / 3333.33, 'e': -59.387}))
    decor.paint('(all)', A.density('hh', {'gnabar': 0.12, 'gkbar': 0.036, 'gl': 0.0}))
    decor.place('(location 0 0.5)', A.iclamp(0.0, 1e9, 0.5), 'ic')
    # One CV per segment: the 16 compartments the other simulators use.
    decor.discretization(A.cv_policy_every_segment())
    return A.cable_cell(A.morphology(tree), decor)


class Bench(A.recipe):
    def __init__(self, n):
        A.recipe.__init__(self)
        self.n = n
        self.cell = make_cell()
        self.props = A.neuron_cable_properties()
        self.props.catalogue = A.default_catalogue()

    def num_cells(self):
        return self.n

    def cell_kind(self, gid):
        return A.cell_kind.cable

    def cell_description(self, gid):
        return self.cell

    def global_properties(self, kind):
        return self.props

    def connections_on(self, gid):
        return []

    def event_generators(self, gid):
        return []

    def probes(self, gid):
        return []


build_t0 = time.time()
recipe = Bench(N)
ctx = A.context(gpu_id=0) if USE_GPU else A.context()
hint = A.partition_hint()
hint.prefer_gpu = USE_GPU
decomp = A.partition_load_balance(recipe, ctx)
sim = A.simulation(recipe, ctx, decomp)
build_t = time.time() - build_t0

run_t0 = time.time()
sim.run(tfinal=STEPS * DT, dt=DT)
run_t = time.time() - run_t0

print(f"RESULT_N={N} RESULT_NCOMP={NCOMP} RESULT_TOTAL_COMPS={N * NCOMP} RESULT_STEPS={STEPS}")
print(f"RESULT_GPU={'1' if USE_GPU else '0'} RESULT_HAS_GPU={ctx.has_gpu}")
print(f"RESULT_BUILD_S={build_t:.3f}")
print(f"RESULT_RUN_S={run_t:.3f}")
print(f"RESULT_WALL_S={build_t + run_t:.3f}")
