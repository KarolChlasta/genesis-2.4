// Minimal 2-neuron test to empirically inspect the combined funcs[] program
// (via GENESIS_DUMP_FUNCS=1 debug dump in hines_init.c). Each neuron is a
// simple 3-compartment linear chain, electrically disconnected from the
// other. Karol Chlasta, 2026-07-25.

include genesis/src/startup/schedule.g

float SOMA_L = 20e-6
float SOMA_D = 20e-6
float EREST_ACT = -0.070
float ELEAK = -0.0594

int n, c
str cell, comp, prev
create neutral /net
for (n = 0; n < 2; n = n + 1)
    cell = "/net/cell" @ {n}
    create neutral {cell}
    for (c = 0; c < 3; c = c + 1)
        comp = {cell} @ "/c" @ {c}
        create compartment {comp}
        setfield {comp} Em {ELEAK} initVm {EREST_ACT} Rm 1e7 Cm 1e-9 Ra 1e6
        if ({c} > 0)
            prev = {cell} @ "/c" @ {c - 1}
            addmsg {prev} {comp} AXIAL Vm
            addmsg {comp} {prev} RAXIAL Ra Vm
        end
    end
end

setclock 0 1e-5
useclock /net/##[] 0

create hsolve /net/solver
setfield /net/solver path "/net/##[][TYPE=compartment]" chanmode 4
call /net/solver SETUP

echo "ncompts: " {getfield /net/solver ncompts}
reset
quit
