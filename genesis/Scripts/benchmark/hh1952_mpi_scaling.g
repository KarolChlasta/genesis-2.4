// genesis
//
// PGENESIS strong-scaling benchmark: N_TOTAL HH1952 neurons across N_NODES MPI ranks.
// Each rank creates (N_TOTAL / N_NODES) independent HH neurons with hsolve (chanmode 4),
// runs N_STEPS steps.  Total wall time is measured by the calling shell script.
//
// Usage:
//   mpirun -np N nxpgenesis -nosimrc -notty -batch hh1952_mpi_scaling.g N_TOTAL N_NODES N_STEPS
//
// N_TOTAL must be exactly divisible by N_NODES.
// N_NODES must equal the mpirun -np value.

int N_TOTAL = 2400
int N_NODES = 1
int N_STEPS = 5000

if ({argc} > 1)
    N_TOTAL = {argv 1}
end
if ({argc} > 2)
    N_NODES = {argv 2}
end
if ({argc} > 3)
    N_STEPS = {argv 3}
end

// Start PGENESIS parallel section (-silent 1 suppresses per-node startup banners)
paron -parallel -silent 1 -nodes {N_NODES}

int my_node  = {mynode}
int my_count = N_TOTAL / N_NODES

// HH1952 parameters (Hodgkin & Huxley 1952)
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

float soma_area  = SOMA_L * PI * SOMA_D
float soma_xarea = PI * (SOMA_D/2) * (SOMA_D/2)
float gbar_Na    = GNA_DENS * soma_area
float gbar_K     = GK_DENS  * soma_area

include genesis/src/startup/schedule.g

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

int n
str cell
for (n = 0; n < {my_count}; n = n + 1)
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

// Wire recorder for cell0 BEFORE hsolve SETUP (required for chanmode 4 Vm sync)
create table /rec0
call /rec0 TABCREATE {N_STEPS + 20} 0.0 {(N_STEPS + 20) * DT}
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

barrier

reset

// Timed simulation: N_STEPS steps (warmup is done in the calling shell script
// by discarding the first replicate)
step {N_STEPS}

barrier

int i_am_master
i_am_master = {mynode} == 0
if (i_am_master)
    echo "PGENESIS_DONE"
end

paroff
quit
