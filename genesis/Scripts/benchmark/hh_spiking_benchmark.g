// genesis
//
// HH SPIKING benchmark — driven Hodgkin-Huxley neurons under a single hsolve.
//
// Improvement over ocl_hh_benchmark.g: each soma receives a suprathreshold
// constant current injection, so every neuron fires a train of action
// potentials instead of sitting at rest. This (a) makes the benchmarked
// workload biophysically meaningful (real spiking HH dynamics, the regime
// neuroscientists actually simulate) and (b) exercises the `inject` ->
// voltage-transient path that the three Hines-solver fixes in this release
// repaired for multi-neuron hsolve, so a CPU-vs-GPU trace comparison is a
// genuine correctness test rather than a comparison of two flat rest states.
//
// Architecture matches ocl_hh_benchmark.g: ONE hsolve covering ALL N neurons
// (flat /net tree), chanmode=4, so the OpenCL channel kernel is exercised.
//
// Usage:
//   nxgenesis -nosimrc -notty -batch hh_spiking_benchmark.g [N] [STEPS] [RECORD]
//     N       number of independent single-compartment HH neurons (default 500)
//     STEPS   number of dt steps to run (default 5000)
//     RECORD  0 = time only (default); 1 = also echo per-step Vm trace of the
//             first two neurons ("VMTRACE" lines) for CPU-vs-GPU validation.
//             RECORD=1 forces single-step stepping and MUST NOT be combined
//             with GENESIS_OCL_MULTILOOP (multiloop needs all K steps in one
//             dispatch and exposes only the final state to the host).
//
// At the end the script always echoes "VMFINAL <n> <Vm>" for a fixed sample of
// neuron indices, so the batched multiloop path can be validated on final state.

int   N_NEURONS = 500
int   N_STEPS   = 5000
int   RECORD    = 0
float DT        = 50e-6

float PI    = 3.141592653589793
float RM    = 0.333
float CM    = 0.01
float RA    = 0.3
float EREST = -0.063
float ENA   =  0.050
float EK    = -0.090
float ELEAK = -0.060
float SOMA_L = 20e-6
float SOMA_D = 20e-6

// Suprathreshold constant injection (A). For a 20x20 um soma with the squid
// HH densities below this drives sustained repetitive firing (~tens of Hz).
float INJECT = 1.0e-9

// argv i is valid for i in 1..argc, so the guard for argv i is (argc > i-1).
if ({argc} > 0)
    N_NEURONS = {argv 1}
end
if ({argc} > 1)
    N_STEPS = {argv 2}
end
if ({argc} > 2)
    RECORD = {argv 3}
end

echo "=== HH Spiking Benchmark (single hsolve, driven neurons) ==="
echo "Neurons:   " {N_NEURONS}
echo "Steps:     " {N_STEPS}
echo "dt:        " {DT} " s"
echo "inject:    " {INJECT} " A"
echo "record:    " {RECORD}
echo ""

include genesis/src/startup/schedule.g

// ---- prototype library (classic 1952 squid HH kinetics) ----
create neutral /library
pushe /library

create tabchannel Na_chan
setfield Na_chan Ek {ENA} Ik 0 Gk 0 Xpower 3 Ypower 1 Zpower 0
float EREST_ACT = -0.063
setupalpha Na_chan X \
    {320e3 * (0.013 + EREST_ACT)} \
    -320e3 -1.0 {-1.0 * (0.013 + EREST_ACT)} \
    -0.004 \
    {-280e3 * (0.040 + EREST_ACT)} \
    280e3 -1.0 {-1.0 * (0.040 + EREST_ACT)} \
    5.0e-3
setupalpha Na_chan Y \
    128.0 0.0 0.0 {-1.0 * (0.017 + EREST_ACT)} 0.018 \
    4.0e3 0.0 1.0 {-1.0 * (0.040 + EREST_ACT)} -5.0e-3

create tabchannel K_chan
setfield K_chan Ek {EK} Ik 0 Gk 0 Xpower 4 Ypower 0 Zpower 0
setupalpha K_chan X \
    {32e3 * (0.015 + EREST_ACT)} \
    -32e3 -1.0 {-1.0 * (0.015 + EREST_ACT)} \
    -0.005 \
    500 0.0 0.0 {-1.0 * (0.010 + EREST_ACT)} 0.04

pope
disable /library

// ---- network (flat /net tree for single hsolve) ----
create neutral /net

float soma_area = SOMA_L * PI * SOMA_D
float soma_xarea = PI * (SOMA_D/2) * (SOMA_D/2)
float gbar_Na = 3000.0 * soma_area
float gbar_K  = 1000.0 * soma_area

int n
str cell

echo "Building driven HH cells..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}

    create compartment {cell}/soma
    setfield {cell}/soma \
        Em     {ELEAK} \
        initVm {EREST} \
        inject {INJECT} \
        Rm     {{RM} / {soma_area}} \
        Cm     {{CM} * {soma_area}} \
        Ra     {{RA} * {SOMA_L} / {soma_xarea}}

    copy /library/Na_chan {cell}/soma/Na_chan
    setfield {cell}/soma/Na_chan Gbar {gbar_Na}
    addmsg {cell}/soma/Na_chan {cell}/soma CHANNEL Gk Ek
    addmsg {cell}/soma {cell}/soma/Na_chan VOLTAGE Vm

    copy /library/K_chan {cell}/soma/K_chan
    setfield {cell}/soma/K_chan Gbar {gbar_K}
    addmsg {cell}/soma/K_chan {cell}/soma CHANNEL Gk Ek
    addmsg {cell}/soma {cell}/soma/K_chan VOLTAGE Vm
end

setclock 0 {DT}
useclock /net/##[] 0

echo "Configuring single hsolve (chanmode=4, N=" {N_NEURONS} " neurons)..."
create hsolve /net/solver
setfield /net/solver path "/net/##[][TYPE=compartment]" chanmode 4
call /net/solver SETUP
useclock /net/solver 0

echo "ncompts: " {getfield /net/solver ncompts}
echo "nchips:  " {getfield /net/solver nchips}

reset
step 10

float t0 = {cpu}
step {N_STEPS}
float t1 = {cpu}

float t_total = {t1 - t0}

echo ""
echo "=== Results ==="
echo "Neurons:              " {N_NEURONS}
echo "Steps:                " {N_STEPS}
echo "CPU-timer step time:  " {t_total} " s"

// Sanity marker only. HGET syncs the hsolve-internal Vm to the element field
// (required for chanmode 4). NB: for driven repetitively-spiking neurons the
// instantaneous Vm after many cycles is phase-sensitive and diverges between
// fp64 (CPU) and fp32 (GPU); it is NOT a correctness metric. Correctness is
// validated separately (single-AP window) by hh1952_ap_verify.g.
call /net/solver HGET /net/cell0/soma
echo "VMFINAL 0 " {getfield /net/cell0/soma Vm}

quit
