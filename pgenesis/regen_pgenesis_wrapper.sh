#!/bin/sh
# Regenerate the PGENESIS launch wrapper (bin/pgenesis) from the distributed
# template src/startup/pgenesis.dist.
#
# Why this exists: the stock PGENESIS install (src/startup/Makefile:install)
# produced a 0-byte bin/pgenesis on this tree, which blocked the `-nodes N`
# launch interface referenced by the benchmark protocol. This script reproduces
# exactly the substitution pipeline that Makefile uses, but:
#   * runs under POSIX sh + sed (no csh needed to GENERATE the wrapper), and
#   * leaves the path placeholders unsubstituted so the wrapper SELF-LOCATES
#     relative to its own directory at run time -> portable across machines
#     (laptop, RunPod, UMCS cluster) with no rebuild.
#
# The generated wrapper is still #!/bin/csh -f, so the RUN host needs csh/tcsh.
# For a csh-free launch, use liquid/start.sh (direct mpirun) instead.
#
# Usage:  sh pgenesis/regen_pgenesis_wrapper.sh
#
# Prepared by Karol Chlasta (karol@chlasta.pl), 2026-07-15.
set -e

HERE=$(cd "$(dirname "$0")" && pwd)
DIST="$HERE/src/startup/pgenesis.dist"
OUT="$HERE/bin/pgenesis"

[ -r "$DIST" ] || { echo "ERROR: template not found: $DIST" >&2; exit 1; }

# Portable MPI launch commands inserted at the # MPI_CMD / # MPI_DEBUG_CMD
# markers. Use `mpirun` from PATH (load the cluster's MPI module first) rather
# than a hardcoded laptop path. csh variables $num_nodes/$exec/$nargv are
# expanded by the wrapper, not by this script -- keep them single-quoted.
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
printf 'mpirun -np $num_nodes $exec $nargv\n'          > "$TMP/mpicmd"
printf 'mpirun -np $num_nodes $exec $nargv\n'          > "$TMP/mpidebugcmd"

# Substitution pipeline (mirrors src/startup/Makefile:install):
#   - insert MPI launch commands after their marker lines
#   - _use_mpi_ -> 01 (0$(USE_MPI) with USE_MPI=1; csh reads 01 as true)
#   - _use_pvm_ -> 0  (PVM disabled)
#   - _pvm_arch_ -> Linux (matches bin/Linux/nxpgenesis)
# Path placeholders (_pgenesis-src_, _pgenesis-inst_, _genesis_, _pvm_default_)
# are intentionally left in place so the wrapper resolves them from $0 at run
# time (see Phase 1 of the template).
sed -e '/MPI_CMD/r '"$TMP/mpicmd" "$DIST" \
  | sed -e '/MPI_DEBUG_CMD/r '"$TMP/mpidebugcmd" \
  | sed -e 's/_use_mpi_/01/g' \
  | sed -e 's/_use_pvm_/0/g' \
  | sed -e 's/_pvm_arch_/Linux/g' \
  > "$OUT"

chmod +x "$OUT"
cp "$OUT" "$HERE/lib/pgenesis.ext"

echo "Regenerated wrapper: $OUT ($(wc -l < "$OUT") lines)"
echo "Also updated:        $HERE/lib/pgenesis.ext"
