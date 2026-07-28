// ocl_test.g — minimalny test hsolve chanmode 4 z tabchannel
float DT = 50e-6
float EREST = -0.065
float ENA   =  0.050
float EK    = -0.077

// --- prosty kanal Na (tabchannel z bramkami m,h) ---
function make_Na(path)
    str path
    create tabchannel {path}/Na
    setfield {path}/Na Ek {ENA} Gbar 1200.0 Ik 0 Gk 0
    setupalpha {path}/Na X \
        3.2e5 0 -1 -0.0651 -0.004 \
        -2.8e5 0 1  0.0178  5e-3 \
        -size 30 -range -0.1 0.05
    setfield {path}/Na Xpower 3
    setupalpha {path}/Na Y \
        128.0 0 0 -0.0170 0.018 \
        4.0e3 0 1  0.040  5e-3 \
        -size 30 -range -0.1 0.05
    setfield {path}/Na Ypower 1
end

// --- prosty kanal K (tabchannel z bramka n) ---
function make_K(path)
    str path
    create tabchannel {path}/K
    setfield {path}/K Ek {EK} Gbar 360.0 Ik 0 Gk 0
    setupalpha {path}/K X \
        3.2e4 0 -1 -0.0549 -0.005 \
        500.0 0 0   0.0549  0.04 \
        -size 30 -range -0.1 0.05
    setfield {path}/K Xpower 4
end

// --- budowa komorki ---
create neutral /cell
create compartment /cell/soma
setfield /cell/soma Cm 1.0e-10 Rm 0.1 Ra 0.1 Em {EREST} initVm {EREST}
make_Na /cell/soma
addmsg /cell/soma /cell/soma/Na VOLTAGE Vm
addmsg /cell/soma/Na /cell/soma CHANNEL Gk Ek
make_K /cell/soma
addmsg /cell/soma /cell/soma/K VOLTAGE Vm
addmsg /cell/soma/K /cell/soma CHANNEL Gk Ek

create compartment /cell/dend
setfield /cell/dend Cm 5.0e-11 Rm 0.2 Ra 0.2 Em {EREST} initVm {EREST}
addmsg /cell/soma /cell/dend RAXIAL Ra Vm
addmsg /cell/dend /cell/soma AXIAL Vm
make_Na /cell/dend
addmsg /cell/dend /cell/dend/Na VOLTAGE Vm
addmsg /cell/dend/Na /cell/dend CHANNEL Gk Ek
make_K /cell/dend
addmsg /cell/dend /cell/dend/K VOLTAGE Vm
addmsg /cell/dend/K /cell/dend CHANNEL Gk Ek

// --- hsolve ---
create hsolve /cell/solver
setfield /cell/solver \
    path "/cell/##[][TYPE=compartment]" \
    chanmode 4 \
    calcmode 1

setclock 0 {DT}
useclock /cell/solver 0

call /cell/solver SETUP
reset

echo "chanmode po reset: " {getfield /cell/solver chanmode}
echo "ncompts: "           {getfield /cell/solver ncompts}
echo "nchips: "            {getfield /cell/solver nchips}

step 10

echo "Vm soma: " {getfield /cell/soma Vm}
quit
