// genesis
// HH branching multicompartment benchmark — N neurons, each a soma with
// NBRANCHES dendrite branches (each BRANCH_LEN compartments long), real
// Hodgkin-Huxley Na+K on every compartment, one hsolve over all.
//
// Purpose (Karol Chlasta, 2026-07-25): hh_multicompartment_benchmark.g only
// builds LINEAR chains (no branch points at all) -- this script exists
// specifically to exercise the SIBARRAY_ELIM/FASTSIBARRAY_ELIM/COPY_ARRAY
// opcodes (only emitted for compartments with >1 child or with siblings) so
// GENESIS_VALIDATE_PERTREE's per-tree GPU kernel-entry protocol can be
// checked against a real branching topology, not just the linear-chain
// cases already validated (see GPU_HINES_SOLVE_DESIGN.md).
//
// Args:  [N_NEURONS] [N_STEPS] [NBRANCHES] [BRANCH_LEN]
// Env:   GENESIS_BENCH_CHANMODE (1=CPU reference, 4=accelerator/GPU default)
//        GENESIS_VALIDATE_PERTREE=1 to run the per-tree CPU validator
//
// Prepared by Karol Chlasta (karol@chlasta.pl).

int   N_NEURONS  = 20
int   N_STEPS    = 20
int   NBRANCHES  = 3
int   BRANCH_LEN = 3
float DT         = 10e-6
float INJECT     = 0.5e-9

float PI        = 3.141592653589793
float EREST_ACT = -0.070
float CM_DENS   = 0.01
float RM_DENS   = 0.333333
float RA_DENS   = 0.3
float GNA_DENS  = 1200.0
float GK_DENS   = 360.0
float ENA       = {EREST_ACT + 0.115}
float EK        = {EREST_ACT - 0.012}
float ELEAK     = {EREST_ACT + 0.010613}
float SOMA_L = 20e-6
float SOMA_D = 20e-6
float DEND_L = 50e-6
float DEND_D = 2e-6

// argv i is valid for i in 1..argc, so the guard for argv i is (argc > i-1).
if ({argc} > 0)
    N_NEURONS = {argv 1}
end
if ({argc} > 1)
    N_STEPS = {argv 2}
end
if ({argc} > 2)
    NBRANCHES = {argv 3}
end
if ({argc} > 3)
    BRANCH_LEN = {argv 4}
end

int CHANMODE = 4
int e_cm = {getenv GENESIS_BENCH_CHANMODE}
if ({e_cm} >= 1)
    CHANMODE = {e_cm}
end

echo "=== HH Branching Multicompartment Benchmark ==="
echo "Neurons:      " {N_NEURONS}
echo "Branches/cell:" {NBRANCHES}
echo "Comp/branch:  " {BRANCH_LEN}
echo "Comp/neuron:  " {1 + NBRANCHES * BRANCH_LEN}
echo "Steps:        " {N_STEPS}
echo "chanmode:     " {CHANMODE}
echo ""

include genesis/src/startup/schedule.g

// ---- channel prototypes (H&H 1952, SI rational-function form) ----
create neutral /library
pushe /library
create tabchannel Na_chan
setfield Na_chan Ek {ENA} Ik 0 Gk 0 Xpower 3 Ypower 1 Zpower 0
setupalpha Na_chan X \
    {100000.0 * (0.025 + EREST_ACT)} -100000.0 -1.0 {-1.0 * (0.025 + EREST_ACT)} -0.01 \
    4000.0 0.0 0.0 {0.0 - EREST_ACT} 0.018
setupalpha Na_chan Y \
    70.0 0.0 0.0 {0.0 - EREST_ACT} 0.02 \
    1000.0 0.0 1.0 {-0.03 - EREST_ACT} -0.01
create tabchannel K_chan
setfield K_chan Ek {EK} Ik 0 Gk 0 Xpower 4 Ypower 0 Zpower 0
setupalpha K_chan X \
    {10000.0 * (0.010 + EREST_ACT)} -10000.0 -1.0 {-1.0 * (0.010 + EREST_ACT)} -0.01 \
    125.0 0.0 0.0 {0.0 - EREST_ACT} 0.08
pope
disable /library

// ---- geometry-derived passive params ----
float soma_area  = SOMA_L * PI * SOMA_D
float soma_xarea = PI * (SOMA_D/2) * (SOMA_D/2)
float dend_area  = DEND_L * PI * DEND_D
float dend_xarea = PI * (DEND_D/2) * (DEND_D/2)

create neutral /net
int n, b, c
str cell, soma, comp, prev

echo "Building branched cells..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}

    // soma: root, current injected, one child per branch (a real branch
    // point -- NBRANCHES>1 is what triggers COPY_ARRAY/SIBARRAY_ELIM in
    // h_funcs_init's construction code, per hines_init.c).
    soma = {cell} @ "/soma"
    create compartment {soma}
    setfield {soma} Em {ELEAK} initVm {EREST_ACT} inject {INJECT} \
        Rm {RM_DENS / soma_area} Cm {CM_DENS * soma_area} \
        Ra {RA_DENS * SOMA_L / soma_xarea}
    setfield {soma} dia {SOMA_D} len {SOMA_L}
    copy /library/Na_chan {soma}/Na_chan
    setfield {soma}/Na_chan Gbar {GNA_DENS * {soma_area}}
    addmsg {soma}/Na_chan {soma} CHANNEL Gk Ek
    addmsg {soma} {soma}/Na_chan VOLTAGE Vm
    copy /library/K_chan {soma}/K_chan
    setfield {soma}/K_chan Gbar {GK_DENS * {soma_area}}
    addmsg {soma}/K_chan {soma} CHANNEL Gk Ek
    addmsg {soma} {soma}/K_chan VOLTAGE Vm

    for (b = 0; b < {NBRANCHES}; b = b + 1)
        prev = soma
        for (c = 0; c < {BRANCH_LEN}; c = c + 1)
            comp = {cell} @ "/b" @ {b} @ "_c" @ {c}
            create compartment {comp}
            setfield {comp} Em {ELEAK} initVm {EREST_ACT} \
                Rm {RM_DENS / dend_area} Cm {CM_DENS * dend_area} \
                Ra {RA_DENS * DEND_L / dend_xarea}
            setfield {comp} dia {DEND_D} len {DEND_L}
            copy /library/Na_chan {comp}/Na_chan
            setfield {comp}/Na_chan Gbar {GNA_DENS * {soma_area}}
            addmsg {comp}/Na_chan {comp} CHANNEL Gk Ek
            addmsg {comp} {comp}/Na_chan VOLTAGE Vm
            copy /library/K_chan {comp}/K_chan
            setfield {comp}/K_chan Gbar {GK_DENS * {soma_area}}
            addmsg {comp}/K_chan {comp} CHANNEL Gk Ek
            addmsg {comp} {comp}/K_chan VOLTAGE Vm
            addmsg {prev} {comp} AXIAL Vm
            addmsg {comp} {prev} RAXIAL Ra Vm
            prev = comp
        end
    end
end

setclock 0 {DT}
useclock /net/##[] 0

int total_comps = {N_NEURONS * (1 + NBRANCHES * BRANCH_LEN)}
echo "Configuring single hsolve (chanmode=" {CHANMODE} ", total comps=" {total_comps} ")..."
create hsolve /net/solver
setfield /net/solver path "/net/##[][TYPE=compartment]" chanmode {CHANMODE} calcmode 1
call /net/solver SETUP
useclock /net/solver 0
echo "ncompts: " {getfield /net/solver ncompts}

reset

walltimemark
step {N_STEPS + 10}
float t_total = {walltime}
float t_per_step = {t_total / {N_STEPS + 10}}
echo "RESULT_T_TOTAL=" {t_total}
echo "RESULT_T_PER_STEP=" {t_per_step}

// Numeric readout for CPU-vs-GPU parity checks: Vm of cell0's soma and of
// the last compartment of branch 0 (farthest point on one branch from the
// current injection at the soma).
str farcomp = "/net/cell0/b0_c" @ {BRANCH_LEN - 1}
call /net/solver HGET /net/cell0/soma
call /net/solver HGET {farcomp}
float vm_far = {getfield {farcomp} Vm}
echo "RESULT_VM_FAR=" {vm_far}
echo "RESULT_VM_SOMA=" {getfield /net/cell0/soma Vm}

echo ""
echo "=== done: N=" {N_NEURONS} " NBRANCHES=" {NBRANCHES} " BRANCH_LEN=" {BRANCH_LEN} " steps=" {N_STEPS} " chanmode=" {CHANMODE} " ==="
quit
