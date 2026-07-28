# GENESIS 2.5 — UMCS Lunar compute environment (reproducibility record)

Full provenance of the hardware and software used for the GENESIS 2.5 CUDA/MPI
benchmarks, for the Methods/Reproducibility section and reviewer questions.
Captured **2026-07-23** from a laptop via the login node, by Karol Chlasta.
Raw probe logs are alongside this file (`*_recon_*.txt`, `*_probe_*.txt`).

## Access path
- Host `lunar.umcs.eu` (212.182.1.72). Per the miranda MOTD (LubMAN network
  reorg, 2023-11-14), each node is reachable **directly from outside** on its own
  port, or internally on 22:

  | node | port from outside | internal |
  |------|-------------------|----------|
  | miranda | **55500** | 22 |
  | inf01 | 55001 | 22 |
  | inf02 (A40) | **55002** | 22 |
  | inf03 (A100) | **55003** | 22 |

- We use `lunar.umcs.eu:55500` → **miranda** (user `kchlasta`), then passwordless
  `ssh inf02` / `ssh inf03` (port 22). **Home is shared**; site tools in
  **`/storage/opt`**. Probes ran non-interactively as
  `ssh miranda 'ssh inf0X bash -ls' < script`. (Direct `lunar.umcs.eu:5500X` also
  works and skips the hop.)

## Compute nodes

| | **inf02** | **inf03** |
|---|---|---|
| CPU | 2× Intel Xeon **Gold 6342** @ 2.80 GHz | 2× Intel Xeon **Platinum 8358** @ 2.60 GHz |
| Cores / threads | 48 / **96** (2 sockets, SMT2) | 64 / **128** (2 sockets, SMT2) |
| RAM | 250 GiB | 250 GiB |
| GPU | **NVIDIA A40** | **NVIDIA A100-PCIE-40GB** |
| GPU memory | 46068 MiB (~45 GB) | 40960 MiB (40 GB) |
| Compute capability | **8.6** → `-arch=sm_86` | **8.0** → `-arch=sm_80` |
| NVIDIA driver | 595.71.05 | 595.71.05 |

(These are the modern GPU nodes; the 2015 "Lunar" Haswell/K40 machine in the UMCS
press article is a different, older resource — do not cite it for this work.)

## Software environment (shared)
- OS compiler: **gcc/g++ 8.5.0** (Red Hat 8.5.0-28), `/usr/bin`. `make`, `flex`,
  `bison`, `git` all present in `/usr/bin`.
- `nvcc` is **not** on the default PATH; CUDA is provided as versioned trees under
  `/storage/opt/cuda/cuda-<ver>` (point `CUDA_HOME` at one; there is no CUDA module).
- CUDA toolkits available (nvcc verified): **13.0** (V13.0.88), **12.8** (V12.8.61),
  **12.1** (V12.1.66), **11.7** (V11.7.64), plus 11.6, 11.2, 10.2, 9.2, 9.0, 8.0.
- MPI (Environment Modules):
  - `mpi/mpich-x86_64` → **MPICH** (HYDRA), `MPI_HOME=/usr/lib64/mpich`, `mpicc`
    wraps gcc.
  - `mpi/openmpi-x86_64` → **Open MPI 4.1.1**, `/usr/lib64/openmpi`.
  - `pmi/pmix-x86_64` (PMIx) also available.

## Pinned toolchain for this study (justification)
For reproducibility we pin one toolchain; rationale recorded for reviewers.

- **CUDA 12.8** (`/storage/opt/cuda/cuda-12.8`, nvcc V12.8.61). Modern, supports
  both target archs (sm_80 A100, sm_86 A40), and is compatible with the system
  host compiler gcc 8.5. (CUDA 13.0 is present but pairs less safely with gcc 8.5;
  12.8 is the conservative choice. If 12.8 is unavailable, 12.1 is the fallback.)
- **Host compiler gcc 8.5.0** via `-ccbin gcc`.
- **MPICH** (`module load mpi/mpich-x86_64`) for PGENESIS — matches the MPICH used
  elsewhere in this project; Open MPI 4.1.1 is the documented alternative.
- Per-node GPU arch: **inf03/A100 → sm_80**, **inf02/A40 → sm_86**.

## Exact build & run (pinned)
```sh
# CUDA build of the headless binary (run on the target node)
export CUDA_HOME=/storage/opt/cuda/cuda-12.8
export PATH="$CUDA_HOME/bin:$PATH"          # nvcc is not on PATH by default
cd genesis/src
# inf03 (A100): -arch=sm_80   |   inf02 (A40): -arch=sm_86
make USE_CUDA=1 CUDA_HOME="$CUDA_HOME" \
     NVCCFLAGS="-arch=sm_80 -ccbin gcc" \
     EXTRALIBS="-L$CUDA_HOME/lib64 -lcudart" nxgenesis

# MPI (PGENESIS LSM)
module load mpi/mpich-x86_64                 # provides mpirun/mpicc (HYDRA)
```

## Raw provenance logs (this directory)
- `inf02_recon_2026-07-23.txt` — inf02 (A40) hardware/modules/deps
- `inf03_recon_2026-07-23.txt` — inf03 (A100) hardware/modules/deps
- `cuda_probe_inf03_2026-07-23.txt` — full module list, `/storage/opt/cuda` tree, nvcc paths
- `toolchain_probe_inf03_2026-07-23.txt` — exact nvcc/MPI/gcc versions

## Open items (to record once done)
- Confirmed `nvcc --version` used for the actual build (paste the exact string).
- Exact MPICH version string (`mpirun --version` full) and PGENESIS launch config.
- Whether the CUDA build links `libcudart` cleanly (`ldd nxgenesis`).
