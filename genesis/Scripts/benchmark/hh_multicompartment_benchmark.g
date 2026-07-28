// genesis
// HH multicompartment benchmark — N neurons, each a linear cable of NCOMP
// Hodgkin-Huxley compartments (Na + K on every compartment), one hsolve over all.
//
// This is the COMPUTE-BOUND workload class where GPU acceleration is meaningful
// (cf. Arbor ~200x/GPU, NeuroGPU). Unlike the single-compartment squid benchmark,
// the per-step Hines tree solve scales with total compartments = N * NCOMP.
//
// Args:  [N_NEURONS] [N_STEPS] [NCOMP]
// Env:   GENESIS_BENCH_CHANMODE  (1 = CPU Hines reference; 4 = accelerator/GPU, default)
//        GENESIS_CUDA_MULTILOOP=<N_STEPS>  for the CUDA multiloop GPU arm
//
// Prepared by Karol Chlasta (karol@chlasta.pl).

int   N_NEURONS = 1000
int   N_STEPS   = 5000
int   NCOMP     = 16
float DT        = 10e-6
float INJECT    = 0.5e-9

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
// soma (comp0) and dendrite (comp1..) geometry
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

// NCOMP and CHANMODE via environment (robust: getenv of an unset var casts to 0,
// which is < 1, so we fall back to the defaults). Runner always sets them.
int e_ncomp = {getenv GENESIS_BENCH_NCOMP}
if ({e_ncomp} >= 1)
    NCOMP = {e_ncomp}
end
int CHANMODE = 4
int e_cm = {getenv GENESIS_BENCH_CHANMODE}
if ({e_cm} >= 1)
    CHANMODE = {e_cm}
end

echo "=== HH Multicompartment Benchmark ==="
echo "Neurons:   " {N_NEURONS}
echo "Comp/neuron:" {NCOMP}
echo "Total comps:" {N_NEURONS * NCOMP}
echo "Steps:     " {N_STEPS}
echo "chanmode:  " {CHANMODE}
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
int n, c
str cell, comp, prev

echo "Building cables..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}
    for (c = 0; c < {NCOMP}; c = c + 1)
        comp = {cell} @ "/c" @ {c}
        create compartment {comp}
        if ({c} == 0)
            setfield {comp} Em {ELEAK} initVm {EREST_ACT} inject {INJECT} \
                Rm {RM_DENS / soma_area} Cm {CM_DENS * soma_area} \
                Ra {RA_DENS * SOMA_L / soma_xarea}
            setfield {comp} dia {SOMA_D} len {SOMA_L}
        else
            setfield {comp} Em {ELEAK} initVm {EREST_ACT} \
                Rm {RM_DENS / dend_area} Cm {CM_DENS * dend_area} \
                Ra {RA_DENS * DEND_L / dend_xarea}
            setfield {comp} dia {DEND_D} len {DEND_L}
        end
        // Na + K on every compartment (active dendrites -> more compute)
        copy /library/Na_chan {comp}/Na_chan
        setfield {comp}/Na_chan Gbar {GNA_DENS * {soma_area}}
        addmsg {comp}/Na_chan {comp} CHANNEL Gk Ek
        addmsg {comp} {comp}/Na_chan VOLTAGE Vm
        copy /library/K_chan {comp}/K_chan
        setfield {comp}/K_chan Gbar {GK_DENS * {soma_area}}
        addmsg {comp}/K_chan {comp} CHANNEL Gk Ek
        addmsg {comp} {comp}/K_chan VOLTAGE Vm
        // link to previous compartment (linear cable)
        if ({c} > 0)
            prev = {cell} @ "/c" @ {c - 1}
            addmsg {prev} {comp} AXIAL Vm
            addmsg {comp} {prev} RAXIAL Ra Vm
        end
    end
end

setclock 0 {DT}
useclock /net/##[] 0

echo "Configuring single hsolve (chanmode=" {CHANMODE} ", N*NCOMP=" {N_NEURONS * NCOMP} " comps)..."
create hsolve /net/solver
setfield /net/solver path "/net/##[][TYPE=compartment]" chanmode {CHANMODE} calcmode 1
call /net/solver SETUP
useclock /net/solver 0
echo "ncompts: " {getfield /net/solver ncompts}

reset

// walltimemark/{walltime}: see hh1952_squid_multiloop_benchmark.g for the
// full rationale (CLOCK_MONOTONIC wall time, not getrusage -- blind to
// GPU-side compute; and the multiloop "first step dispatches everything"
// quirk, which is why warm-up + measured steps are combined into one call).
// Combining is a no-op for CPU/per-step GPU (sequential step calls execute
// literally either way) and required for correctness in multiloop mode, so
// one structure works for all three chanmode/dispatch arms alike.
walltimemark
step {N_STEPS + 10}
float t_total = {walltime}
float t_per_step = {t_total / {N_STEPS + 10}}
echo "RESULT_T_TOTAL=" {t_total}
echo "RESULT_T_PER_STEP=" {t_per_step}

// Numeric readout for CPU-vs-GPU parity checks (Karol Chlasta, 2026-07-25):
// Vm of cell0's LAST compartment (far end of the cable from the current
// injection at compartment 0) -- only reaches a non-trivial value if axial
// coupling correctly propagated the signal down the cable. A broken/skipped
// elimination (e.g. multiloop mode, which never runs do_euler_hsolve) would
// leave this at rest regardless of what the soma does.
//
// HGET sync (found 2026-07-25, cf. hh1952_ap_verify.g): in chanmode 4/5,
// getfield reads the element's own field storage, which the accelerator
// path does NOT keep in sync every step -- HGET pulls the solver's
// internal Vm array back into element fields on demand. Without this call
// getfield always returns the untouched initVm regardless of what the
// solver actually computed.
str farcomp = "/net/cell0/c" @ {NCOMP - 1}
call /net/solver HGET /net/cell0/c0
call /net/solver HGET {farcomp}
float vm_far = {getfield {farcomp} Vm}
echo "RESULT_VM_FAR=" {vm_far}
echo "RESULT_VM_SOMA=" {getfield /net/cell0/c0 Vm}

echo ""
echo "=== done: N=" {N_NEURONS} " NCOMP=" {NCOMP} " steps=" {N_STEPS} " chanmode=" {CHANMODE} " ==="
quit
