// genesis
//
// OCL HH Benchmark — exercises the OpenCL code path via hsolve chanmode=4.
//
// Architecture: ONE hsolve object covering ALL N neurons (flat /net tree).
// This matches how production GENESIS networks would use hsolve and ensures
// the OCL buffers are sized for the full N-neuron batch.
//
// Key requirements for OCL activation:
//   1. tabchannel ion channels (hsolve chanmode=4 only supports tabchannel,
//      not old-style hh_channel — those give SETUP "unknown element type")
//   2. chanmode=4, calcmode=1 on hsolve
//   3. schedule.g must be included (addtask CLASS=hsolver not in -nosimrc)
//   4. useclock network BEFORE hsolve SETUP; useclock solver AFTER SETUP
//
// Usage:
//   nxgenesis -nosimrc -notty -batch ocl_hh_benchmark.g [N_NEURONS] [N_STEPS]
//
// OCL profiling summary printed to stdout at GENESIS exit (via atexit).

int   N_NEURONS = 500
int   N_STEPS   = 5000
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

if ({argc} > 1)
    N_NEURONS = {argv 1}
end
if ({argc} > 2)
    N_STEPS = {argv 2}
end

echo "=== OCL HH Benchmark (single hsolve, N neurons) ==="
echo "Neurons:   " {N_NEURONS}
echo "Steps:     " {N_STEPS}
echo "dt:        " {DT} " s"
echo ""

// Default simulation schedule (bypassed by -nosimrc):
// Required for CLASS=hsolver PROCESS task
include genesis/src/startup/schedule.g

// ---- prototype library ----
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

echo "Building HH cells..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}

    create compartment {cell}/soma
    setfield {cell}/soma \
        Em     {ELEAK} \
        initVm {EREST} \
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

// Schedule compartments/channels BEFORE hsolve SETUP
// (hsolve SETUP calls HsolveBlock on compartments/channels;
//  scheduler then skips those; only hsolve itself gets PROCESS)
useclock /net/##[] 0

// ---- single hsolve covering all N neurons ----
echo "Configuring single hsolve (chanmode=4, calcmode=1, N=" {N_NEURONS} " neurons)..."
create hsolve /net/solver
setfield /net/solver \
    path "/net/##[][TYPE=compartment]" \
    chanmode 4 \
    calcmode 1
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
float t_per_step = {t_total / N_STEPS}
float t_per_neuron_us = {t_per_step / N_NEURONS * 1e6}

echo ""
echo "=== Results ==="
echo "Neurons:              " {N_NEURONS}
echo "Steps:                " {N_STEPS}
echo "Total wall time:      " {t_total} " s"
echo "Time per step:        " {t_per_step} " s"
echo "Time per neuron/step: " {t_per_neuron_us} " us"
echo ""
echo "(OCL PROFILING SUMMARY printed at exit by atexit handler)"

quit
