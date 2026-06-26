// genesis
//
// HH1952 AP Verification — checks that N independent HH1952 neurons
// all produce identical action potentials after N_STEPS steps under
// a 2 nA depolarizing current.
//
// Designed to be run with both nxgenesis_nocl (CPU) and nxgenesis with
// GENESIS_OCL_MULTILOOP set to (N_STEPS+10) to verify that all three
// execution paths (CPU, GPU per-step, GPU multiloop) agree.
//
// Usage:
//   nxgenesis_nocl -nosimrc -notty -batch hh1952_ap_verify.g [N_NEURONS] [N_STEPS]
//   GENESIS_OCL_MULTILOOP=$((N_STEPS+10)) \
//     nxgenesis -nosimrc -notty -batch hh1952_ap_verify.g [N_NEURONS] [N_STEPS]

int   N_NEURONS = 2
int   N_STEPS   = 200
float DT        = 10e-6
float INJECT    = 2e-9

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
float SOMA_L    = 20e-6
float SOMA_D    = 20e-6

if ({argc} > 1)
    N_NEURONS = {argv 1}
end
if ({argc} > 2)
    N_STEPS = {argv 2}
end

echo "=== HH1952 AP Verify N=" {N_NEURONS} " steps=" {N_STEPS} " ==="

include /datadisk/od-kchlasta/5.Dev/GitHub/genesis-2.4/genesis/startup/schedule.g

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

create neutral /net

float soma_area  = SOMA_L * PI * SOMA_D
float soma_xarea = PI * (SOMA_D/2) * (SOMA_D/2)
float gbar_Na = GNA_DENS * soma_area
float gbar_K  = GK_DENS  * soma_area

int n
str cell

for (n = 0; n < {N_NEURONS}; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}
    create compartment {cell}/soma
    setfield {cell}/soma \
        Em     {ELEAK} \
        initVm {EREST_ACT} \
        inject {INJECT} \
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

// Wire a recording message for cell0 BEFORE SETUP — required for chanmode 4
// to enable h_out_msgs Vm sync after stepping.
create table /rec0
call /rec0 TABCREATE {N_STEPS + 10} 0.0 {(N_STEPS + 10) * DT}
setfield /rec0 step_mode 3
addmsg /net/cell0/soma /rec0 INPUT Vm
useclock /rec0 0

create hsolve /net/solver
setfield /net/solver \
    path "/net/##[][TYPE=compartment]" \
    chanmode 4 \
    calcmode 1
call /net/solver SETUP
useclock /net/solver 0

reset
step 10
step {N_STEPS}

// Sync all neurons' Vm to element fields via HGET, then scan min/max
str spath
float vm0 = 0.0
float vm_min = 0.0
float vm_max = 0.0
float vm_cur = 0.0
int   first  = 1

for (n = 0; n < {N_NEURONS}; n = n + 1)
    spath = "/net/cell" @ {n} @ "/soma"
    call /net/solver HGET {spath}
    vm_cur = {getfield {spath} Vm}
    if ({first})
        vm_min = {vm_cur}
        vm_max = {vm_cur}
        first  = 0
    end
    if ({vm_cur} < {vm_min})
        vm_min = {vm_cur}
    end
    if ({vm_cur} > {vm_max})
        vm_max = {vm_cur}
    end
    if ({n} == 0)
        vm0 = {vm_cur}
    end
end

float spread = {{vm_max} - {vm_min}}

echo ""
echo "--- Vm after " {N_STEPS} " steps (+ 10 warmup) ---"
echo "cell0 Vm      = " {vm0}
echo "min   Vm      = " {vm_min}
echo "max   Vm      = " {vm_max}
echo "spread(max-min)= " {spread}
if ({spread} < 1e-6)
    echo "NEURONS_AGREE: YES (spread < 1e-6 V)"
else
    echo "NEURONS_AGREE: NO  (spread " {spread} " V)"
end
echo "RESULT_VM=" {vm0}

quit
