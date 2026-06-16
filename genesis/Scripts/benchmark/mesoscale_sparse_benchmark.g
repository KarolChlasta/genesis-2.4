// genesis

// Mesoscale sparse network benchmark.
// - 10^4 to 10^5 neurons (recommended), sparse recurrent synapses
// - two cell populations: excitatory/inhibitory
// - randomspike-driven presynaptic generators and synchan targets

float PI = 3.141592653589793

int N_NEURONS = 10000
float EXC_FRACTION = 0.8
int FANIN_EXC = 40
int FANIN_INH = 10
int N_STEPS = 20000
float DT = 50e-6

float RM = 0.333
float CM = 3.2e-11
float RA = 0.1

float EX_RATE_HZ = 5.0
float INH_RATE_HZ = 12.0

float E_EX = 0.0
float E_INH = -0.080
float TAU_EX = 3e-3
float TAU_INH = 10e-3

float GMAX_EX = 2e-9
float GMAX_INH = 2e-9

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

function make_syn_pair(cellpath)
    str cellpath
    create synchan {cellpath}/soma/Ex_syn
    setfield {cellpath}/soma/Ex_syn Ek {E_EX} tau1 {TAU_EX} tau2 {TAU_EX} gmax {GMAX_EX}
    addmsg {cellpath}/soma/Ex_syn {cellpath}/soma CHANNEL Gk Ek
    addmsg {cellpath}/soma {cellpath}/soma/Ex_syn VOLTAGE Vm

    create synchan {cellpath}/soma/Inh_syn
    setfield {cellpath}/soma/Inh_syn Ek {E_INH} tau1 {TAU_INH} tau2 {TAU_INH} gmax {GMAX_INH}
    addmsg {cellpath}/soma/Inh_syn {cellpath}/soma CHANNEL Gk Ek
    addmsg {cellpath}/soma {cellpath}/soma/Inh_syn VOLTAGE Vm
end

function make_source(path, rate_hz)
    str path
    float rate_hz
    create randomspike {path}/src
    setfield {path}/src min_amp 1.0 max_amp 1.0 reset 1 reset_value 0 rate {rate_hz}

    create spikegen {path}/spk
    setfield {path}/spk thresh 0.5 abs_refract 0.001 output_amp 1
    addmsg {path}/src {path}/spk INPUT state
end

if ({argc} > 1)
    N_NEURONS = {argv 1}
end

if ({argc} > 2)
    N_STEPS = {argv 2}
end

int N_EXC = {round {N_NEURONS * EXC_FRACTION}}
if ({N_EXC < 1})
    N_EXC = 1
end
int N_INH = {N_NEURONS - N_EXC}
if ({N_INH < 1})
    N_INH = 1
end

echo "=== Mesoscale Sparse Benchmark ==="
echo "Neurons: " {N_NEURONS} " (E=" {N_EXC} ", I=" {N_INH} ")"
echo "Fan-in: E=" {FANIN_EXC} " I=" {FANIN_INH}
echo "Steps: " {N_STEPS}
echo "dt: " {DT}

create neutral /net
create neutral /sources

int i
str cellpath
str srcpath
echo "Building cells and synaptic targets..."
for (i = 0; i < {N_NEURONS}; i = i + 1)
    cellpath = "/net/cell" @ {i}
    create neutral {cellpath}
    makecompartment {cellpath}/soma 20e-6 10e-6 -0.065
    make_syn_pair {cellpath}
end

echo "Building spike sources..."
for (i = 0; i < {N_EXC}; i = i + 1)
    srcpath = "/sources/exc" @ {i}
    create neutral {srcpath}
    make_source {srcpath} {EX_RATE_HZ}
end
for (i = 0; i < {N_INH}; i = i + 1)
    srcpath = "/sources/inh" @ {i}
    create neutral {srcpath}
    make_source {srcpath} {INH_RATE_HZ}
end

echo "Connecting sparse synapses..."
int j
int pre
int msgnum
str tgt
str src
for (i = 0; i < {N_NEURONS}; i = i + 1)
    tgt = "/net/cell" @ {i} @ "/soma"

    for (j = 0; j < {FANIN_EXC}; j = j + 1)
        pre = {{i + j} % {N_EXC}}
        src = "/sources/exc" @ {pre} @ "/spk"
        addmsg {src} {tgt}/Ex_syn SPIKE
        msgnum = {{getfield {tgt}/Ex_syn nsynapses} - 1}
        setfield {tgt}/Ex_syn synapse[{msgnum}].weight 1 synapse[{msgnum}].delay 0
    end

    for (j = 0; j < {FANIN_INH}; j = j + 1)
        pre = {{i + 3*j} % {N_INH}}
        src = "/sources/inh" @ {pre} @ "/spk"
        addmsg {src} {tgt}/Inh_syn SPIKE
        msgnum = {{getfield {tgt}/Inh_syn nsynapses} - 1}
        setfield {tgt}/Inh_syn synapse[{msgnum}].weight 1 synapse[{msgnum}].delay 0
    end
end

setclock 0 {DT}
setclock 1 {DT}
useclock /net/##[] 0
useclock /sources/##[] 1

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
