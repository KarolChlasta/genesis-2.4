# Archive

Superseded material from earlier iterations of the GENESIS 2.5 benchmarking
and manuscript work, kept for provenance rather than deleted. Nothing here is
referenced by the current manuscript (`paper/manuscript_softwarex_draft.tex`)
or by `paper/docs/REPLICATION.md` — for reproducing the paper's results,
start there instead.

Contents, roughly:

- `manuscript_genesis_2_5_proposal.{md,tex,pdf}` — the original GENESIS 2.5
  proposal document, superseded by the SoftwareX manuscript.
- `genesis25_*.csv`, `plot_genesis25_*.py`, `run_genesis25_ocl_multiloop_scaling.py`,
  `run_genesis25_cpu_scaling_dense_10rep.sh`, `ocl_benchmark_*.csv` — earlier,
  per-dispatch benchmark campaigns and their plotting scripts, superseded by
  the unified `experiments/run_overnight_campaign.py` driver and the
  multi-replicate cluster campaigns in `cluster_bringup/`.
- `run_overnight_pipeline.sh`, `run_hh1952_ap_verify.sh` — earlier, standalone
  versions of what `experiments/run_overnight_campaign.py` now does in one
  driver.
- `figures/` — figures generated from the superseded data above.
- `archive_confounded_runs/`, `reference_legacy/`, `profiling_runs/` —
  measurements later found to be confounded (see
  `paper/docs/x11_binary_confound_investigation.md`) or replaced by higher-replicate
  reruns; kept as the historical trail, not as evidence for any claim in the
  paper.
- `PLAN_gpu_rewrite.md`, `WEEKEND_PLAN.md`, `PUBLISH_CHECKLIST.md`,
  `STATUS.html`, `gpu_acceleration_attempt.md`, `reviewer_reproduction_longrun.md`,
  `benchmark_run_protocol.md` — planning and status notes from earlier phases
  of the project.
- `opencl_probe`/`opencl_probe.c`, `nxgenesis_opencl_benchmark_*` — one-off
  diagnostic tooling used while bringing up the OpenCL backend.
