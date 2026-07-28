// Branching 2-neuron test to empirically inspect SIBARRAY_ELIM/COPY_ARRAY
// (via GENESIS_DUMP_FUNCS=1 debug dump in hines_init.c). Each neuron is a
// Y-shaped branch: one root compartment with TWO children (a real branch
// point), electrically disconnected from the other neuron. Karol Chlasta,
// 2026-07-25.

include genesis/src/startup/schedule.g

float EREST_ACT = -0.070
float ELEAK = -0.0594

int n
str cell, root, kidA, kidB

create neutral /net
for (n = 0; n < 2; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}
    root = {cell} @ "/root"
    kidA = {cell} @ "/kidA"
    kidB = {cell} @ "/kidB"
    str kidC = {cell} @ "/kidC"
    create compartment {root}
    create compartment {kidA}
    create compartment {kidB}
    create compartment {kidC}
    setfield {root} Em {ELEAK} initVm {EREST_ACT} Rm 1e7 Cm 1e-9 Ra 1e6
    setfield {kidA} Em {ELEAK} initVm {EREST_ACT} Rm 1e7 Cm 1e-9 Ra 1e6
    setfield {kidB} Em {ELEAK} initVm {EREST_ACT} Rm 1e7 Cm 1e-9 Ra 1e6
    setfield {kidC} Em {ELEAK} initVm {EREST_ACT} Rm 1e7 Cm 1e-9 Ra 1e6
    // branch point: root has TWO children (kidA, kidB)
    addmsg {root} {kidA} AXIAL Vm
    addmsg {kidA} {root} RAXIAL Ra Vm
    addmsg {root} {kidB} AXIAL Vm
    addmsg {kidB} {root} RAXIAL Ra Vm
    addmsg {root} {kidC} AXIAL Vm
    addmsg {kidC} {root} RAXIAL Ra Vm
end

setclock 0 1e-5
useclock /net/##[] 0

create hsolve /net/solver
setfield /net/solver path "/net/##[][TYPE=compartment]" chanmode 4
call /net/solver SETUP

echo "ncompts: " {getfield /net/solver ncompts}
reset
quit
