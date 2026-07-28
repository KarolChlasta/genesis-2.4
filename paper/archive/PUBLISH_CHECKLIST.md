# GENESIS 2.5 — publish checklist (SoftwareX submission)

Manual, one-time steps to take `WarsawIQ/genesis-2.5` from private to a
citable, archived public release. None of these can be done from this
environment (no `gh` / GitHub API access here) — do them in the GitHub /
Zenodo web UI, in this order. Check items off as you go.

## 0. Pre-flight review (do this first)
- [ ] Review `cluster/GENESIS25_wymagania_klaster_UMCS_v2.pdf` (+ `.tex`) —
      it names Karol Karpowicz and Prof. Przemysław Stpiczyński in the context
      of cluster resource provisioning. Decide if that's fine to publish as-is
      (it's in the same spirit as the paper's Acknowledgements, but confirm).
      If not: `git rm` it from `cluster_bringup`... no — it lives under
      `cluster/`, which is otherwise gitignored; this PDF was force-added
      (`git add -f`). To remove it from history if needed, say so and it will
      be handled deliberately (do not just `git rm` — check git log first).
- [ ] Skim `cluster_bringup/logs/` once more for anything unexpected (should
      be clean: build logs, benchmark CSVs, hardware specs — no secrets, per
      the audit on 2026-07-24).

## 1. Make the repository public
- [ ] GitHub → `WarsawIQ/genesis-2.5` → **Settings** → **Danger Zone** →
      **Change repository visibility** → **Public**. Confirm by typing the
      repo name.
- [ ] Verify: open the repo in a private/incognito browser window (logged
      out) and confirm it loads.

## 2. Link Zenodo (do this BEFORE tagging a release)
- [ ] Log in to <https://zenodo.org> with your GitHub account (or link GitHub
      under Zenodo account settings: **Settings → GitHub**).
- [ ] Find `WarsawIQ/genesis-2.5` in the repository list and **toggle it ON**.
      This must happen before step 3, or the release won't be archived.

## 3. Tag a GitHub release (this triggers the Zenodo DOI mint)
- [ ] GitHub → genesis-2.5 → **Releases** → **Draft a new release**.
- [ ] Tag: `v2.5` (matches C1 in the paper's metadata table).
- [ ] Title: `GENESIS 2.5.0 — OpenCL + CUDA acceleration`.
- [ ] Description: short summary (can reuse the manuscript abstract or
      `paper/manuscript_softwarex_highlights.txt`).
- [ ] Publish the release.
- [ ] Wait a minute, then check Zenodo → **Uploads** for the newly minted
      record; copy its **DOI** (format `10.5281/zenodo.XXXXXXX`).

## 4. Wire the DOI back into the paper
- [ ] Edit `paper/manuscript_softwarex_draft.tex`, table row **C2**: replace
      `Zenodo DOI \emph{to be inserted upon release}` with the real DOI (as a
      link: `\url{https://doi.org/10.5281/zenodo.XXXXXXX}`).
- [ ] Recompile: `tectonic paper/manuscript_softwarex_draft.tex`.
- [ ] Also add the DOI badge to `README.md` if desired (Zenodo provides a
      Markdown snippet on the record page).
- [ ] Commit + push the DOI update to genesis-2.5.

## 5. Final sanity pass before submitting to SoftwareX
- [ ] All 4 figures render in the compiled PDF (already verified 2026-07-24).
- [ ] All 6 referenced CSVs exist under `experiments/data/` (verified).
- [ ] `paper/REPLICATION.md` steps still match the current repo layout.
- [ ] `LICENSE` file present and matches C3 in the metadata table (GPLv2+/LGPL).
- [ ] Submit via the SoftwareX Editorial Manager, attaching the compiled PDF,
      `manuscript_softwarex_highlights.txt`, and the .tex source.

---
Prepared 2026-07-24. Update this file's checkboxes in place as steps complete
(or note "N/A — done differently" rather than deleting a line, so the record
of what happened stays intact).
