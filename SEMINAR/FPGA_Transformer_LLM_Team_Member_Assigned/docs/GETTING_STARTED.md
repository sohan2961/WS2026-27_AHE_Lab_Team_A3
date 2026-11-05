# Getting started: upload and collaborate on GitHub

## A. Create the GitHub repository (team leader)

1. Unzip `FPGA_Transformer_LLM_Team_GitHub_Repository.zip` on your PC.
2. Sign in at [github.com](https://github.com), choose **New repository**.
3. Example name: `fpga-transformer-llm-seminar-2026`.
4. Choose **Private** initially (you can change visibility later, after checking source and team privacy).
5. **Do not initialize** with another README, .gitignore or license, because this starter already includes the first two.
6. Create the empty repository.

### Upload with Git (recommended for the complete folder)

Open PowerShell or Git Bash in the **unpacked project folder**, then replace `YOUR_USERNAME_OR_ORG` with your GitHub owner:

```bash
git init -b main
git add .
git commit -m "Initialize three-person FPGA LLM seminar workspace"
git remote add origin https://github.com/YOUR_USERNAME_OR_ORG/fpga-transformer-llm-seminar-2026.git
git push -u origin main
```

If `git init -b main` is not supported in your older Git version, run `git init`, then `git branch -M main` before pushing.

### Alternative: upload in browser

Inside your empty repo choose **uploading an existing file** (or **Add file → Upload files**). Drag in the files and folders from the **unpacked** directory, not the ZIP. Commit the upload. For larger projects Git on your computer is more reliable.

## B. Invite both teammates

**Repository → Settings → Collaborators and teams → Add people**. Invite the two teammates by their GitHub usernames. They must accept the invitations. On an organization repo, permissions and menu names can differ.

## C. Daily collaboration workflow

1. Pick an item from [`TASK_BOARD.md`](TASK_BOARD.md) or make a GitHub Issue from the templates.
2. Create a new branch per task; avoid three people changing the same file on `main` at the same time.
3. Add your research notes and update the literature matrix.
4. Open a Pull Request (PR) back to `main` and ask one teammate to check facts and formatting.
5. Merge after review. Edit the draft PDF only by recompiling the LaTeX source; do not manually change the PDF.

Example for **Turja**:

```bash
git clone https://github.com/YOUR_USERNAME_OR_ORG/fpga-transformer-llm-seminar-2026.git
cd fpga-transformer-llm-seminar-2026
git checkout -b turja/kv-cache-notes
# edit research/turja_section_II_attention/ or drafts/turja_section_II.md
git add .
git commit -m "Add KV-cache literature notes"
git push -u origin turja/kv-cache-notes
```

Then visit GitHub, click **Compare & pull request**, ask a teammate to review, and merge when ready.

## D. Working from Overleaf

- Best starting option: all teammates write Markdown notes here, and one person integrates reviewed content into `paper/main.tex`.
- Optional: connect Overleaf with GitHub if your account/workflow supports it. Do **not** assume automatic two-way synchronization.
- Keep `paper/references.bib` the shared citation file. Use unique BibTeX keys and check the rendered bibliography.

## E. What to upload where

| You have... | Put it in... |
| --- | --- |
| Paper link, DOI, paper notes | your named `research/` folder and `research/shared/literature_matrix.csv` |
| New suggestion or optional experiment | `ideas/` or a GitHub Issue |
| Your writing for the paper | your named `drafts/` file |
| Original block diagram or plot | `figures/` with source and caption |
| Reported benchmarking numbers | `data/benchmark_evidence_template.csv` copy or new CSV |
| Team decision and task assignment | `meetings/` and `docs/TASK_BOARD.md` |
| Integrated paper section | `paper/main.tex` via reviewed PR |

**Do not:** put passwords, personal credentials, private email threads, copied paywalled PDFs, or unverified invented performance numbers into the repository.
