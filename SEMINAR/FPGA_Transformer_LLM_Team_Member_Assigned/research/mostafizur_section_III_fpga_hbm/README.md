# Mostafizur Rahman — lead for Section III

**Assigned person:** Mostafizur Rahman  
**Paper section:** III. FPGA Accelerator Architectures and HBM  
**Status:** Research assigned; source review and writing not yet marked complete.

## Scope and concrete work

- Processing elements, DSP pipelines, dataflow, tiling and memory reuse
- QKV/attention/FFN accelerator schematic; map transfers through BRAM/URAM/DDR/HBM
- HBM channels and aggregate bandwidth versus actual sustained throughput
- Quantization, sparsity and resource/accuracy trade-offs
- Sources to check: `li2020`, `zeng2024`, `chae2025`, `xiao2023`, `lin2024`, `amdU280`, `amdKV260`
- Figure suggestion: original FPGA decode datapath with labeled memory connections

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
