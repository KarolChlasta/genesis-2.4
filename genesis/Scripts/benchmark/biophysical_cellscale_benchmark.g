// genesis

// Biophysical cell-scale benchmark.
// - fewer neurons, richer per-cell dynamics (HH channels + synaptic drive)
// - intended to stress channel computations and solver setup

include ./genesis/Scripts/tutorials/hhchan.g

float PI = 3.141592653589793

int N_NEURONS = 256
int N_STEPS = 20000
float DT = 50e-6

float RM = 0.333
float CM = 0.01
float RA = 0.3
float EREST_ACT = -0.070
float ELEAK = EREST_ACT + 0.0106

float EX_RATE_HZ = 80.0
float EX_TAU = 3e-3
float GMAX_EX = 5e-10

function makecompartment(path, l, d, Erest)
    str path
    float l, d
    float Erest
    float area = l*PI*d
    float xarea = PI*d*d/4
    create compartment {path}
    setfield {path} Em {Erest} initVm {Erest} Rm {{RM}/area} Cm {{CM}*area} \
        Ra {{RA}*l/xarea}
end

function make_hh_cell(path)
    str path

    create neutral {path}
    makecompartment {path}/soma 30e-6 30e-6 {ELEAK}
    makecompartment {path}/dend 100e-6 2e-6 {EREST_ACT}

    addmsg {path}/dend {path}/soma RAXIAL Ra previous_state
    addmsg {path}/soma {path}/dend AXIAL previous_state

    // Reuse canonical squid HH channels shipped with GENESIS tutorials.
    pushe {path}/soma
    make_Na_squid_hh
    make_K_squid_hh
    pope

    addmsg {path}/soma/Na_squid_hh {path}/soma CHANNEL Gk Ek
    addmsg {path}/soma {path}/soma/Na_squid_hh VOLTAGE Vm
    addmsg {path}/soma/K_squid_hh {path}/soma CHANNEL Gk Ek
    addmsg {path}/soma {path}/soma/K_squid_hh VOLTAGE Vm

    create synchan {path}/dend/Ex_syn
    setfield {path}/dend/Ex_syn Ek {ENA} tau1 {EX_TAU} tau2 {EX_TAU} gmax {GMAX_EX}
    addmsg {path}/dend/Ex_syn {path}/dend CHANNEL Gk Ek
    addmsg {path}/dend {path}/dend/Ex_syn VOLTAGE Vm

    create spikegen {path}/soma/spike
    setfield {path}/soma/spike thresh 0 abs_refract 0.010 output_amp 1
    addmsg {path}/soma {path}/soma/spike INPUT Vm
end

if ({argc} > 1)
    N_NEURONS = {argv 1}
end

if ({argc} > 2)
    N_STEPS = {argv 2}
end

echo "=== Biophysical Cell-Scale Benchmark ==="
echo "Neurons: " {N_NEURONS}
echo "Steps: " {N_STEPS}
echo "dt: " {DT}

create neutral /net
create neutral /drive

int i
str cellpath
str drvpath

echo "Building HH cells..."
for (i = 0; i < {N_NEURONS}; i = i + 1)
    cellpath = "/net/cell" @ {i}
    make_hh_cell {cellpath}
end

echo "Adding random synaptic drive..."
for (i = 0; i < {N_NEURONS}; i = i + 1)
    drvpath = "/drive/cell" @ {i}
    create neutral {drvpath}
    create randomspike {drvpath}/src
    setfield {drvpath}/src min_amp 1.0 max_amp 1.0 reset 1 reset_value 0 rate {EX_RATE_HZ}
    create spikegen {drvpath}/spk
    setfield {drvpath}/spk thresh 0.5 abs_refract 0.001 output_amp 1
    addmsg {drvpath}/src {drvpath}/spk INPUT state

    cellpath = "/net/cell" @ {i}
    addmsg {drvpath}/spk {cellpath}/dend/Ex_syn SPIKE
    setfield {cellpath}/dend/Ex_syn synapse[0].weight 1 synapse[0].delay 0
end

setclock 0 {DT}
setclock 1 {DT}
useclock /net/##[] 0
useclock /drive/##[] 1

reset
step 10

float t0 = {cpu}
step {N_STEPS}
float t1 = {cpu}

echo ""
echo "=== Results ==="
echo "CPU delta: " {t1 - t0}
echo ""

quit
