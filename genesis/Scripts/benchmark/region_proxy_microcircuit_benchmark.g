// genesis

// Region-proxy microcircuit benchmark.
// - simplified cortical-column style E/I layout on a 2-D sheet
// - uses planarconnect to create local recurrent projections

float DT = 50e-6
int N_STEPS = 20000

int EX_NX = 80
int EX_NY = 80
int INH_NX = 40
int INH_NY = 40

float EX_SEP_X = 40e-6
float EX_SEP_Y = 40e-6
float INH_SEP_X = 80e-6
float INH_SEP_Y = 80e-6

float RM = 0.333
float CM = 3.2e-11
float RA = 0.1

float E_EX = 0.0
float E_INH = -0.080
float TAU_EX = 3e-3
float TAU_INH = 10e-3
float GMAX_EX = 2e-9
float GMAX_INH = 2e-9

float EX_BG_RATE = 8.0

if ({argc} > 1)
    N_STEPS = {argv 1}
end

function makecompartment(path, l, d, Erest)
    str path
    float l, d
    float Erest
    float area = l*3.141592653589793*d
    float xarea = 3.141592653589793*d*d/4
    create compartment {path}
    setfield {path} Em {Erest} initVm {Erest} Rm {{RM}/area} Cm {{CM}*area} \
        Ra {{RA}*l/xarea}
end

function make_proto(name)
    str name
    create neutral /library/{name}
    makecompartment /library/{name}/soma 20e-6 10e-6 -0.065

    create spikegen /library/{name}/soma/spike
    setfield /library/{name}/soma/spike thresh 0 abs_refract 0.002 output_amp 1
    addmsg /library/{name}/soma /library/{name}/soma/spike INPUT Vm

    create synchan /library/{name}/soma/Ex_syn
    setfield /library/{name}/soma/Ex_syn Ek {E_EX} tau1 {TAU_EX} tau2 {TAU_EX} gmax {GMAX_EX}
    addmsg /library/{name}/soma/Ex_syn /library/{name}/soma CHANNEL Gk Ek
    addmsg /library/{name}/soma /library/{name}/soma/Ex_syn VOLTAGE Vm

    create synchan /library/{name}/soma/Inh_syn
    setfield /library/{name}/soma/Inh_syn Ek {E_INH} tau1 {TAU_INH} tau2 {TAU_INH} gmax {GMAX_INH}
    addmsg /library/{name}/soma/Inh_syn /library/{name}/soma CHANNEL Gk Ek
    addmsg /library/{name}/soma /library/{name}/soma/Inh_syn VOLTAGE Vm
end

echo "=== Region Proxy Microcircuit Benchmark ==="
echo "Ex grid: " {EX_NX} "x" {EX_NY}
echo "Inh grid: " {INH_NX} "x" {INH_NY}
echo "Steps: " {N_STEPS}
echo "dt: " {DT}

if (!{exists /library})
    create neutral /library
end

make_proto Ex_cell
make_proto Inh_cell

create neutral /Ex_layer
create neutral /Inh_layer

echo "Creating Ex/Inh maps..."
createmap /library/Ex_cell /Ex_layer/Ex_cell {EX_NX} {EX_NY} -delta {EX_SEP_X} {EX_SEP_Y}
createmap /library/Inh_cell /Inh_layer/Inh_cell {INH_NX} {INH_NY} -delta {INH_SEP_X} {INH_SEP_Y}

echo "Creating local recurrent connectivity..."
planarconnect /Ex_layer/Ex_cell[]/soma/spike /Ex_layer/Ex_cell[]/soma/Ex_syn \
    -relative -sourcemask box -1 -1 1 1 -destmask box -1 -1 1 1 -probability 0.02
planarconnect /Ex_layer/Ex_cell[]/soma/spike /Inh_layer/Inh_cell[]/soma/Ex_syn \
    -relative -sourcemask box -1 -1 1 1 -destmask box -1 -1 1 1 -probability 0.02
planarconnect /Inh_layer/Inh_cell[]/soma/spike /Ex_layer/Ex_cell[]/soma/Inh_syn \
    -relative -sourcemask box -1 -1 1 1 -destmask box -1 -1 1 1 -probability 0.02
planarconnect /Inh_layer/Inh_cell[]/soma/spike /Inh_layer/Inh_cell[]/soma/Inh_syn \
    -relative -sourcemask box -1 -1 1 1 -destmask box -1 -1 1 1 -probability 0.02

planarweight /Ex_layer/Ex_cell[]/soma/spike -fixed 1
planarweight /Inh_layer/Inh_cell[]/soma/spike -fixed 1
planardelay /Ex_layer/Ex_cell[]/soma/spike -fixed 0
planardelay /Inh_layer/Inh_cell[]/soma/spike -fixed 0

setclock 0 {DT}
setclock 1 {DT}
useclock /Ex_layer/##[] 0
useclock /Inh_layer/##[] 0

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
