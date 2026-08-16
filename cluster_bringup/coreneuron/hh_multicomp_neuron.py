#!/usr/bin/env python3
"""The GENESIS multi-compartment benchmark, rebuilt in NEURON.

The Vogels-Abbott comparison runs on CPU on both sides, because that network is
a spiking one and the GENESIS accelerator declines it. This model is the one the
accelerator does support -- N neurons, each a linear chain of NCOMP compartments,
Hodgkin-Huxley channels, current injection, no synapses -- so the same benchmark
can be run with the GPU actually in use, which is what this paper is about.

Geometry and passive properties follow
genesis/Scripts/benchmark/hh_multicompartment_createmap.g:

    soma        20 um long, 20 um diameter
    dendrite    50 um long,  2 um diameter, NCOMP-1 of them in a chain
    Cm          1 uF/cm2        (GENESIS CM_DENS 0.01 F/m2)
    Rm          3333.3 ohm cm2  (GENESIS RM_DENS 0.333333 ohm m2)
    Ra          30 ohm cm       (GENESIS RA_DENS 0.3 ohm m)
    gNa         0.12 S/cm2      (GENESIS 1200 S/m2)
    gK          0.036 S/cm2     (GENESIS 360 S/m2)
    Eleak       -59.387 mV, Ena +45 mV, Ek -82 mV, rest -70 mV
    inject      0.5 nA into compartment 0
    dt          0.01 ms

NEURON's built-in hh is the same Hodgkin-Huxley formulation (m^3h, n^4) as the
setupalpha rates GENESIS builds, so the arithmetic per compartment per step
matches even where a rate constant differs in the last digit. This is a
throughput benchmark; it is not a claim that the two produce identical voltages.
"""

import os
import sys
import time

from neuron import h

N = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
STEPS = int(sys.argv[2]) if len(sys.argv) > 2 else 5000
NCOMP = int(os.environ.get("BENCH_NCOMP", "16"))
USE_CORENEURON = os.environ.get("USE_CORENEURON", "0") == "1"
USE_GPU = os.environ.get("USE_GPU", "0") == "1"

h.load_file("stdrun.hoc")
h.cvode.cache_efficient(1)

EREST = -70.0
build_t0 = time.time()

cells = []
clamps = []
for i in range(N):
    secs = []
    for j in range(NCOMP):
        s = h.Section(name=f"c{i}_{j}")
        if j == 0:
            s.L, s.diam = 20.0, 20.0
        else:
            s.L, s.diam = 50.0, 2.0
        s.nseg = 1
        s.cm = 1.0
        s.Ra = 30.0
        s.insert("pas")
        s.g_pas = 1.0 / 3333.33
        s.e_pas = -59.387
        s.insert("hh")
        s.gnabar_hh = 0.12
        s.gkbar_hh = 0.036
        s.gl_hh = 0.0          # leak is carried by pas, as in the GENESIS model
        s.ena = 45.0
        s.ek = -82.0
        if j > 0:
            s.connect(secs[j - 1](1.0), 0.0)
        secs.append(s)
    ic = h.IClamp(secs[0](0.5))
    ic.delay, ic.dur, ic.amp = 0.0, 1e9, 0.5   # nA, on throughout
    clamps.append(ic)
    cells.append(secs)

# CoreNEURON only takes over for cells registered with ParallelContext under a
# gid. Without this it silently leaves the run on NEURON's own solver and
# reports nothing, which is indistinguishable from a CoreNEURON run except that
# the timings come out identical to the plain arm.
pc = h.ParallelContext()
netcons = []
for i, secs in enumerate(cells):
    pc.set_gid2node(i, pc.id())
    nc = h.NetCon(secs[0](0.5)._ref_v, None, sec=secs[0])
    pc.cell(i, nc)
    netcons.append(nc)

build_t = time.time() - build_t0

h.dt = 0.01
h.tstop = STEPS * h.dt
h.v_init = EREST

if USE_CORENEURON:
    from neuron import coreneuron
    coreneuron.enable = True
    coreneuron.gpu = USE_GPU

run_t0 = time.time()
h.stdinit()
if USE_CORENEURON:
    pc.psolve(h.tstop)
else:
    h.continuerun(h.tstop)
run_t = time.time() - run_t0

print(f"RESULT_N={N} RESULT_NCOMP={NCOMP} RESULT_TOTAL_COMPS={N * NCOMP} "
      f"RESULT_STEPS={STEPS}")
print(f"RESULT_BUILD_S={build_t:.3f}")
print(f"RESULT_RUN_S={run_t:.3f}")
print(f"RESULT_WALL_S={build_t + run_t:.3f}")
print(f"RESULT_VM_SOMA={cells[0][0](0.5).v:.6f}")
print(f"RESULT_VM_FAR={cells[0][NCOMP - 1](0.5).v:.6f}")
