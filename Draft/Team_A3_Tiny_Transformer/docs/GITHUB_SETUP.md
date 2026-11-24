# Upload and collaborate with GitHub

## First upload (repository not created yet)

1. Download the Team A3 ZIP and **extract** it.
2. Open https://github.com/new and create a **private** repository called `team-a3-tiny-transformer-nexys-a7`.
3. Do not generate another README, `.gitignore`, or license because this folder already includes project files.
4. Upload **all contents inside the extracted project folder**, including `.github/`, `.gitattributes` and `.gitignore`. The repository root should display `README.md`, `rtl/`, `hls/`, `reference/`, and `docs/` directly.
5. Invite Turja and Deepak as collaborators in GitHub Settings. Share the repository URL with the team.

## Preferred Git workflow (terminal)

From the extracted project root:

```bash
git init
git branch -M main
git add .
git commit -m "Team A3 baseline and VHDL project kickoff"
git remote add origin https://github.com/YOUR_USERNAME/team-a3-tiny-transformer-nexys-a7.git
git push -u origin main
```

Replace `YOUR_USERNAME` with the actual owner. This is an example URL, not a repository that has been created.

## Team branches

- Mostafizur: `mostafizur/attention-rtl`
- Turja: `turja/reference-ffn`
- Deepak: `deepak/verification`

Each member creates their branch, commits small changes, pushes and opens a pull request to `main`. A different member reviews before merge.

```bash
git switch -c mostafizur/attention-rtl
# change or add code, then run relevant tests
git add .
git commit -m "Add attention RTL milestone"
git push -u origin mostafizur/attention-rtl
```

## Do not accidentally upload

Vivado project caches, synthesis runs, `.bit`, `.xsa`, GHDL generated files, local `build/` and personal credentials. These are ignored by `.gitignore`. For reproducibility, store reusable RTL, Vivado Tcl scripts, tests, test logs and documents.

## Checks

GitHub Actions runs the FP32 host baselines and new dot-product simulation on supported Linux runners. A green Actions result **does not** mean the full Transformer has been built on FPGA.
