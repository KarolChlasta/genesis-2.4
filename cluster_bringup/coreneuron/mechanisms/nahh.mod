TITLE Hodgkin-Huxley sodium channel, COBAHH benchmark kinetics

COMMENT
NMODL transcription of the ChannelBuilder channel "nahh" defined in
hhchan.ses of the Destexhe benchmark suite (ModelDB 83319).

CoreNEURON cannot use ChannelBuilder mechanisms: they are constructed at
run time inside the NEURON interpreter and have no compiled NMODL
representation, so nrn_setup aborts with "nahh mechanism does not exist".
This file supplies the identical channel as a compiled mechanism.

The ChannelBuilder rate functions are stored as (A, k, vh) triples with a
type code. Transcribing them:

  type 3 (linoid)  f(v) = A*k*(v-vh) / (1 - exp(-k*(v-vh)))
  type 2 (exp)     f(v) = A*exp(k*(v-vh))
  type 4 (sigmoid) f(v) = A / (1 + exp(-k*(v-vh)))

  m gate, power 3:
    alpha  type 3  (1.28,  0.25, -50)  -> 0.32*(v+50)/(1-exp(-(v+50)/4))
    beta   type 3  (1.4,  -0.2,  -23)  -> 0.28*(v+23)/(exp((v+23)/5)-1)
  h gate, power 1:
    alpha  type 2  (0.128, -0.055556, -46) -> 0.128*exp(-(v+46)/18)
    beta   type 4  (4,     -0.2,      -23) -> 4/(1+exp(-(v+23)/5))

These are exactly the COBAHH rates of Brette et al., J Comput Neurosci
23:349 (2007), Appendix, with VT = -63 mV. gmax defaults to 0.1 S/cm2
(100 mS/cm2), matching genprop.set_defstr(0.1, 0) in the .ses file.

Prepared by Karol Chlasta (karol@chlasta.pl).
ENDCOMMENT

NEURON {
    SUFFIX nahh
    USEION na READ ena WRITE ina
    RANGE gmax, g
}

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
    (S)  = (siemens)
}

PARAMETER {
    gmax = 0.1 (S/cm2)
}

ASSIGNED {
    v    (mV)
    ena  (mV)
    ina  (mA/cm2)
    g    (S/cm2)
    minf
    hinf
    mtau (ms)
    htau (ms)
}

STATE { m h }

BREAKPOINT {
    SOLVE states METHOD cnexp
    g = gmax * m * m * m * h
    ina = g * (v - ena)
}

INITIAL {
    rates(v)
    m = minf
    h = hinf
}

DERIVATIVE states {
    rates(v)
    m' = (minf - m) / mtau
    h' = (hinf - h) / htau
}

PROCEDURE rates(v (mV)) {
    LOCAL a, b
    UNITSOFF
    a = 0.32 * vtrap(-(v + 50), 4)
    b = 0.28 * vtrap(v + 23, 5)
    mtau = 1 / (a + b)
    minf = a * mtau

    a = 0.128 * exp(-(v + 46) / 18)
    b = 4 / (1 + exp(-(v + 23) / 5))
    htau = 1 / (a + b)
    hinf = a * htau
    UNITSON
}

: x/(exp(x/y)-1), with the removable singularity at x=0 handled by its
: limit y - x/2, so the linoid rates stay finite at their pivot voltage.
FUNCTION vtrap(x, y) {
    UNITSOFF
    if (fabs(x / y) < 1e-6) {
        vtrap = y * (1 - x / y / 2)
    } else {
        vtrap = x / (exp(x / y) - 1)
    }
    UNITSON
}
