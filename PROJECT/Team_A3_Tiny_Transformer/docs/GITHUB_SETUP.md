# Share Team A3 through GitHub

The ZIP is **GitHub-ready** but has not created an online repository.

1. Create an empty GitHub repository named `team-a3-tiny-transformer-nexys-a7` (private while developing if desired).
2. Extract the ZIP and open a terminal **inside** `Team_A3_Tiny_Transformer_NEXYS_A7/`.
3. Add source files without generated Vivado/HLS build directories or outputs. Review `.gitignore` and commit in small stages.
4. Add the new remote URL given by GitHub and push the `main` branch.
5. Create feature branches: `mostafizur/integration`, `deepak/attention`, `turja/reference-layers`.
6. Update only your own status in `tracking/Weekly_Updates.xlsx`; add results under the matching `weekly_work/week_0N/<member>/` directory. Avoid concurrent edits to the shared Excel file; one person should merge it each week.

Example commands after replacing `<YOUR_REPOSITORY_URL>` with the URL GitHub gives you:

```bash
git init
git branch -M main
git add .
git commit -m "Initialize Team A3 HLS and Vivado project"
git remote add origin "<YOUR_REPOSITORY_URL>"
git push -u origin main
```

Run `python3 scripts/check_checkpoint_sync.py` and host tests before pushing. GitHub Actions checks the same exact-title synchronization in CI.
