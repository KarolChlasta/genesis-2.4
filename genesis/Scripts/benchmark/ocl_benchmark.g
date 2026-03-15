// ocl_benchmark.g
//
// Benchmark porownujacy czas symulacji CPU vs GPU (OpenCL) w GENESIS 2.4.
//
// Buduje siec N neuronow typu Traub (wielokompartmentowych) z kanalami
// jonowymi Na, K, Ca. Mierzy czas 1000 krokow czasowych.
//
// Uzycie:
//   genesis -nox ocl_benchmark.g [N_neurons]
//   domyslnie N_neurons = 100

int N_NEURONS = 100
int N_COMPTS  = 19    // kompartmenty na neuron (model Traub91)
float DT      = 50e-6 // krok czasowy 50 us
int   N_STEPS = 1000  // liczba krokow do zmierzenia

if ({argc} > 1)
    N_NEURONS = {argv 1}
end

echo "=== GENESIS OpenCL Benchmark ==="
echo "Neurony:       " {N_NEURONS}
echo "Kompartmenty:  " {N_NEURONS * N_COMPTS} " lacznie"
echo "Kroki:         " {N_STEPS}
echo "dt:            " {DT} " s"
echo ""

// --- budowa pojedynczego neuronu jako prototypu ---
include traub91proto.g   // standardowy plik z kanalami Na/K/Ca

function make_neuron(path)
    str path
    int i
    str prev, curr

    // soma
    create compartment {path}/soma
    setfield {path}/soma Cm 3.2e-11 Rm 0.333 Ra 0.1 Em -0.065 initVm -0.065

    // dodaj kanaly jonowe do somy
    make_Na_channel  {path}/soma
    make_K_channel   {path}/soma
    make_Ca_channel  {path}/soma

    // dendryty — lancuch kompartmentow
    prev = {path}/soma
    for i = 1 to {N_COMPTS - 1}
        curr = {path}/dend{i}
        create compartment {curr}
        setfield {curr} Cm 1.2e-11 Rm 1.0 Ra 0.2 Em -0.065 initVm -0.065
        addmsg {prev} {curr} RAXIAL Ra Vm
        addmsg {curr} {prev} AXIAL Vm
        make_Na_channel {curr}
        make_K_channel  {curr}
        prev = {curr}
    end
end

// --- budowa sieci ---
echo "Budowanie sieci..."
int n
for n = 0 to {N_NEURONS - 1}
    make_neuron /net/cell{n}
end

// --- konfiguracja hsolve ---
// chanmode 4: najszybszy tryb, uzywa chip array
// calcmode 1: interpolacja tabel (wymagana dla OpenCL)
echo "Konfiguracja hsolve (chanmode=4)..."
for n = 0 to {N_NEURONS - 1}
    create hsolve /net/cell{n}/solver
    setfield /net/cell{n}/solver \
        path "../##[][TYPE=compartment]" \
        chanmode 4 \
        calcmode 1
    setclock 0 {DT}
    useclock /net/cell{n}/solver 0
end

// --- reset i rozgrzewka (10 krokow zeby GPU sie zainicjalizowal) ---
reset
step 10

// --- pomiar CPU (bez OpenCL) lub GPU (z OpenCL) ---
// Czas mierzony przez GENESIS cpu() — zwraca czas CPU w sekundach
float t_start = {cpu}
step {N_STEPS}
float t_end   = {cpu}

float t_total   = {t_end - t_start}
float t_per_step = {t_total / N_STEPS}
float t_per_compt = {t_per_step / (N_NEURONS * N_COMPTS) * 1e6}

echo ""
echo "=== Wyniki ==="
echo "Czas lacznie:        " {t_total}       " s"
echo "Czas na krok:        " {t_per_step}    " s"
echo "Czas na kompartment: " {t_per_compt}   " us"
echo ""

// zapisz wynik do pliku CSV (do porownania CPU vs GPU)
str outfile = "benchmark_result.csv"
if (!{exists /output})
    openfile {outfile} a
    writefile {outfile} "mode,neurons,compts_total,steps,t_total,t_per_step,t_per_compt_us"
    closefile {outfile}
end

openfile {outfile} a
str mode = "CPU"
#ifdef USE_OPENCL
mode = "GPU"
#endif
writefile {outfile} \
    {mode} "," \
    {N_NEURONS} "," \
    {N_NEURONS * N_COMPTS} "," \
    {N_STEPS} "," \
    {t_total} "," \
    {t_per_step} "," \
    {t_per_compt}
closefile {outfile}

echo "Wynik zapisany do: " {outfile}
quit
