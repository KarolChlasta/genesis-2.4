// genesis

// OpenCL-oriented benchmark script with valid GENESIS 2.x syntax.
// It builds N neurons, each with N_COMPTS passive compartments,
// configures one hsolve per neuron with chanmode 4, and times N_STEPS.

int N_NEURONS = 100
int N_COMPTS  = 19
float DT      = 50e-6
int N_STEPS   = 50000
float RM = 0.333
float CM = 3.2e-11
float RA = 0.1

function makecompartment(path, l, d, Erest)
    str path
    float l, d
    float Erest
    float area = l*3.141592653589793*d
    float xarea = 3.141592653589793*d*d/4
    create compartment {path}
    setfield {path} Em {Erest} Rm {{RM}/area} Cm {{CM}*area} \
        Ra {{RA}*l/xarea}
end

if ({argc} > 1)
    N_NEURONS = {argv 1}
end

if ({argc} > 2)
    N_STEPS = {argv 2}
end

function make_neuron(path)
    str path
    int i
    str prev

    create neutral {path}
    makecompartment {path}/comp[0] 20e-6 10e-6 -0.065

    prev = {path} @ "/comp[0]"
    for (i = 1; i < {N_COMPTS}; i = i + 1)
        makecompartment {path}/comp[{i}] 20e-6 10e-6 -0.065
        addmsg {prev} {path}/comp[{i}] AXIAL previous_state
        addmsg {path}/comp[{i}] {prev} RAXIAL Ra previous_state
        prev = {path} @ "/comp[" @ {i} @ "]"
    end
end

echo "=== GENESIS OpenCL Benchmark ==="
echo "Neurons:       " {N_NEURONS}
echo "Compartments:  " {N_NEURONS * N_COMPTS} " total"
echo "Steps:         " {N_STEPS}
echo "dt:            " {DT} " s"
echo ""

create neutral /net

int n
str cellpath
echo "Building network..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cellpath = "/net/cell" @ {n}
    make_neuron {cellpath}
end

setclock 0 {DT}

echo "Configuring hsolve (chanmode=4, calcmode=1)..."
for (n = 0; n < {N_NEURONS}; n = n + 1)
    cellpath = "/net/cell" @ {n}
    create hsolve {cellpath}/solver
    setfield {cellpath}/solver \
        path "../##[][TYPE=compartment]" \
        chanmode 4 \
        calcmode 1
    useclock {cellpath}/solver 0
    call {cellpath}/solver SETUP
end

reset
step 10

float t_start = {cpu}
step {N_STEPS}
float t_end = {cpu}

float t_total = {t_end - t_start}
float t_per_step = {t_total / N_STEPS}
float t_per_compt_us = {t_per_step / (N_NEURONS * N_COMPTS) * 1e6}

echo ""
echo "=== Results ==="
echo "Total time:            " {t_total} " s"
echo "Time per step:         " {t_per_step} " s"
echo "Time per compartment:  " {t_per_compt_us} " us"
echo ""

quit
