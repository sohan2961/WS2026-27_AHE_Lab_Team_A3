# Contributing to the team seminar repository

## Simple rules

1. Choose your member folder for individual notes. Use shared folders for items that the team has reviewed.
2. Name research files `year_shorttitle.md` and ideas `idea_YYYY-MM-DD_topic.md`.
3. Prefer GitHub branches and pull requests (PRs) over editing `main` directly.
4. Explain what changed, provide the source URL/DOI, and ask one teammate to review.
5. Research notes are **your own summaries**. Do not commit copyrighted full-text articles unless redistribution is permitted.
6. For numerical results, state *where the number came from* and what was compared.
7. A pull request is ready when another teammate can reproduce the source trail.

## Named team ownership

- **Turja:** `research/turja_section_II_attention/`, `drafts/turja_section_II.md`.
- **Mostafizur Rahman:** `research/mostafizur_section_III_fpga_hbm/`, `drafts/mostafizur_section_III.md`.
- **Deepak:** `research/deepak_section_IV_evaluation/`, `drafts/deepak_section_IV.md`.
- **All:** abstract, introduction, discussion, conclusion, bibliography and final review.

## Branch names

- `turja/attention-background`
- `mostafizur/hbm-architecture`
- `deepak/benchmark-comparison`
- `team/final-editing`

## Commit examples

- `Add notes on grouped-query attention`
- `Verify U280 HBM specs against datasheet`
- `Revise GPU comparison after source review`

## Review before merging

- Is every assertion supported by a reliable source?
- Are quotations marked and referenced?
- Are model, sequence length, precision, and devices distinguished?
- Does this change introduce contradictions or duplicates in `paper/main.tex`?
- Has new material been integrated consistently with the research question?

**Files needing extra care:** `paper/main.tex`, `paper/references.bib`, `research/shared/literature_matrix.csv`. Coordinate large changes to these shared files first.
