TITLE Hodgkin-Huxley potassium channel, COBAHH benchmark kinetics

COMMENT
NMODL transcription of the ChannelBuilder channel "khh" defined in
hhchan.ses of the Destexhe benchmark suite (ModelDB 83319). See nahh.mod
for why the compiled form is needed and how the .ses triples map onto
these rate expressions.

  n gate, power 4:
    alpha  type 3  (0.16,  0.2,   -48) -> 0.032*(v+48)/(1-exp(-(v+48)/5))
    beta   type 2  (0.5,  -0.025, -53) -> 0.5*exp(-(v+53)/40)

These are the COBAHH potassium rates of Brette et al., J Comput Neurosci
23:349 (2007), Appendix, with VT = -63 mV. gmax defaults to 0.03 S/cm2
(30 mS/cm2), matching genprop.set_defstr(0.03, 0) in the .ses file.

Prepared by Karol Chlasta (karol@chlasta.pl).
ENDCOMMENT

NEURON {
    SUFFIX khh
    USEION k READ ek WRITE ik
    RANGE gmax, g
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S)  = (siemens)
}

PARAMETER {
    gmax = 0.03 (S/cm2)
}

ASSIGNED {
    v    (mV)
    ek   (mV)
    ik   (mA/cm2)
    g    (S/cm2)
    ninf
    ntau (ms)
}

STATE { n }

BREAKPOINT {
    SOLVE states METHOD cnexp
    g = gmax * n * n * n * n
    ik = g * (v - ek)
}

INITIAL {
    rates(v)
    n = ninf
}

DERIVATIVE states {
    rates(v)
    n' = (ninf - n) / ntau
}

PROCEDURE rates(v (mV)) {
    LOCAL a, b
    UNITSOFF
    a = 0.032 * vtrap(-(v + 48), 5)
    b = 0.5 * exp(-(v + 53) / 40)
    ntau = 1 / (a + b)
    ninf = a * ntau
    UNITSON
}

: x/(exp(x/y)-1), with the removable singularity at x=0 handled by its
: limit y - x/2, so the linoid rate stays finite at its pivot voltage.
FUNCTION vtrap(x, y) {
    UNITSOFF
    if (fabs(x / y) < 1e-6) {
        vtrap = y * (1 - x / y / 2)
    } else {
        vtrap = x / (exp(x / y) - 1)
    }
    UNITSON
}
