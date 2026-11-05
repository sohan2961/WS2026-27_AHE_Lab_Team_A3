# Turja — lead for Section II

**Assigned person:** Turja  
**Paper section:** II. Transformer Workload and Memory Demands  
**Status:** Research assigned; source review and writing not yet marked complete.

## Scope and concrete work

- Self-attention: Q/K/V, scaled dot-product attention and causality
- Prefill vs autoregressive decode and their compute/memory characteristics
- KV-cache formula + numerical assumptions and MHA/MQA/GQA comparison
- Sources to check: `vaswani2017`, `shazeer2019`, `ainslie2023`, `dao2022`, `dao2024`, `kwon2023`, `williams2009`
- Figure suggestion: prefill→decode and growing KV-cache diagram

## Workflow

1. Read the relevant papers, verify precise claims, and write original notes here using `templates/source_note.md`.
2. Update `research/shared/literature_matrix.csv` with your name, source status and exact evidence location.
3. Write the section in your named Markdown draft in `drafts/`.
4. Open a pull request to integrate a reviewed revision into `paper/main.tex`.
5. Record work **actually completed** in `meetings/CONTRIBUTIONS.md`.

## Research checklist

- [ ] Read at least three primary references and note exact page/figure citations
- [ ] Check all quantitative claims and formulas
- [ ] Draft one original figure/table and its caption
- [ ] Write a coherent section with citations in own words
- [ ] Request a teammate review before merging
