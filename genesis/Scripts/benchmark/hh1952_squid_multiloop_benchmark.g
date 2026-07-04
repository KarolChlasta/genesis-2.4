// genesis
//
// HH1952 Squid Axon Benchmark — exercises the OpenCL multiloop GPU path with
// channel kinetics and conductance densities taken directly from
//
//   Hodgkin AL, Huxley AF (1952). A quantitative description of membrane
//   current and its application to conduction and excitation in nerve.
//   J Physiol 117:500-544.
//
// Kinetics (alpha_m, beta_m, alpha_h, beta_h, alpha_n, beta_n) are converted
// to GENESIS SI units (volts, seconds, siemens/m^2) from the original mV/ms
// rate constants as encoded in the bundled GENESIS squid tutorial
// (genesis/Scripts/squid/squid_proto.g, attributed to M. Nelson, Caltech,
// 4/89, itself citing H&H 1952 directly), NOT re-derived from secondary
// sources. Conductance densities (GNa=120, GK=36, Gleak=0.3 mmho/cm^2) and
// Cm=1 uF/cm^2 are H&H's Table 3 values. EREST_ACT=-0.070 V matches the
// modern-convention alternative the same source file documents
// ("you may change EREST_ACT to -70.0").
//
// Architecture mirrors ocl_hh_benchmark.g: ONE hsolve covering ALL N
// independent single-compartment "axons" (space-clamped, no spatial
// cable -- matching H&H's own space-clamp experimental condition), so the
// chip_channel_multiloop GPU kernel applies directly. ocl_hh_benchmark.g's
// rate constants were NOT a verified SI conversion of any specific source
// (confirmed by deriving and checking against squid_proto.g numerically at
// V=EREST_ACT) and is left as-is; this script is the literature-traceable
// replacement for benchmarks that need a directly citable model.
//
// Usage:
//   nxgenesis -nosimrc -notty -batch hh1952_squid_multiloop_benchmark.g [N_NEURONS] [N_STEPS]

int   N_NEURONS = 500
int   N_STEPS   = 5000
float DT        = 10e-6

float PI       = 3.141592653589793
float EREST_ACT = -0.070
float CM_DENS   = 0.01        // F/m^2   = 1 uF/cm^2 (H&H Table 3)
float RM_DENS   = 0.333333    // ohm*m^2 = 1/(3 S/m^2) = 1/(0.3 mmho/cm^2) (H&H Table 3 leak)
float RA_DENS   = 0.3         // ohm*m   (axial; irrelevant for a single space-clamped compartment)
float GNA_DENS  = 1200.0      // S/m^2   = 120 mmho/cm^2 (H&H Table 3)
float GK_DENS   = 360.0       // S/m^2   = 36 mmho/cm^2  (H&H Table 3)
float ENA       = {EREST_ACT + 0.115}     // +115 mV relative to rest (H&H)
float EK        = {EREST_ACT - 0.012}     // -12 mV relative to rest (H&H)
float ELEAK     = {EREST_ACT + 0.010613}  // +10.613 mV relative to rest (H&H)
float SOMA_L = 20e-6
float SOMA_D = 20e-6

if ({argc} > 1)
    N_NEURONS = {argv 1}
end
if ({argc} > 2)
    N_STEPS = {argv 2}
end

echo "=== HH1952 Squid Axon Benchmark (single hsolve, N neurons) ==="
echo "Neurons:   " {N_NEURONS}
echo "Steps:     " {N_STEPS}
echo "dt:        " {DT} " s"
echo ""

include genesis/src/startup/schedule.g

// ---- prototype library ----
create neutral /library
pushe /library

// Na: m^3 h^1 (H&H 1952, eq. 14-17 with original mV/ms constants:
//   alpha_m(d)=0.1*(25-d)/(exp((25-d)/10)-1)   beta_m(d)=4*exp(-d/18)
//   alpha_h(d)=0.07*exp(-d/20)                 beta_h(d)=1/(1+exp(-(d-30)/10))
// d = depolarization from rest in mV; converted to SI rational-function
// parameters (A+B*V)/(C+exp((V+D)/F)) with V in volts.)
create tabchannel Na_chan
setfield Na_chan Ek {ENA} Ik 0 Gk 0 Xpower 3 Ypower 1 Zpower 0
setupalpha Na_chan X \
    {100000.0 * (0.025 + EREST_ACT)} -100000.0 -1.0 {-1.0 * (0.025 + EREST_ACT)} -0.01 \
    4000.0 0.0 0.0 {0.0 - EREST_ACT} 0.018
setupalpha Na_chan Y \
    70.0 0.0 0.0 {0.0 - EREST_ACT} 0.02 \
    1000.0 0.0 1.0 {-0.03 - EREST_ACT} -0.01

// K: n^4 (H&H 1952, eq. 12-13:
//   alpha_n(d)=0.01*(10-d)/(exp((10-d)/10)-1)  beta_n(d)=0.125*exp(-d/80))
create tabchannel K_chan
setfield K_chan Ek {EK} Ik 0 Gk 0 Xpower 4 Ypower 0 Zpower 0
setupalpha K_chan X \
    {10000.0 * (0.010 + EREST_ACT)} -10000.0 -1.0 {-1.0 * (0.010 + EREST_ACT)} -0.01 \
    125.0 0.0 0.0 {0.0 - EREST_ACT} 0.08

pope
disable /library

// ---- network (flat /net tree for single hsolve) ----
create neutral /net

float soma_area  = SOMA_L * PI * SOMA_D
float soma_xarea = PI * (SOMA_D/2) * (SOMA_D/2)
float gbar_Na = GNA_DENS * soma_area
float gbar_K  = GK_DENS  * soma_area

int n
str cell

echo "Building HH1952 squid axons..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}

    create compartment {cell}/soma
    setfield {cell}/soma \
        Em     {ELEAK} \
        initVm {EREST_ACT} \
        Rm     {RM_DENS / soma_area} \
        Cm     {CM_DENS * soma_area} \
        Ra     {RA_DENS * SOMA_L / soma_xarea}

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
