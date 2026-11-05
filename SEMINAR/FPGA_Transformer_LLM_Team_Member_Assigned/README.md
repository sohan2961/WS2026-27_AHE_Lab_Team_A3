# Transformer and LLM Inference on FPGAs
### Advanced Hardware Engineering · WS 2026/27 · Hochschule Hamm-Lippstadt
**Team:** Mostafizur Rahman · Turja · Deepak · **Supervisor:** Prof. Dr.-Ing. Ali Hayek · **Topic 4**

> **Purpose of this repository:** One shared place for our literature research, new ideas, notes, draft sections, figures, source evidence, meeting decisions, and final IEEE seminar paper.
>
> **Status:** Research and drafting in progress. The included `paper/main.tex` and `paper/draft_v1_reference.pdf` are working drafts, **not a verified final submission**. All authors must independently validate sources, claims, and citations.

## Research question

**How can FPGA accelerator architectures and memory optimizations improve Transformer and LLM inference efficiency, and under which conditions are FPGAs competitive with GPUs in latency and energy per generated token?**

We focus on: (1) attention and KV-cache demands, (2) FPGA dataflow and HBM, (3) FPGA vs. GPU latency and energy per token, (4) edge vs. data-center feasibility.

## Who is responsible for which paper section?

| IEEE paper section | Lead author | Research work | Draft file |
| --- | --- | --- | --- |
| **II. Transformer Workload and Memory Demands** | **Turja** | Attention, prefill/decode, KV-cache formula, MHA/MQA/GQA and bandwidth | [`drafts/turja_section_II.md`](drafts/turja_section_II.md) |
| **III. FPGA Accelerator Architectures and HBM** | **Mostafizur Rahman** | Processing elements, HLS/dataflow, pipelining, quantization, BRAM/URAM, DDR and HBM | [`drafts/mostafizur_section_III.md`](drafts/mostafizur_section_III.md) |
| **IV. Comparative Evaluation** | **Deepak** | Published FPGA-vs-GPU results, latency, throughput, power and energy/token | [`drafts/deepak_section_IV.md`](drafts/deepak_section_IV.md) |
| Abstract, I. Introduction, V. Discussion, VI. Conclusion and References | **All three** | Joint editing, cross-review, presentation | [`paper/main.tex`](paper/main.tex) |

The names are **assigned leads**, not claims that work has been completed. See [`docs/SECTION_OWNERSHIP.md`](docs/SECTION_OWNERSHIP.md) for concrete deliverables and review partners.

## Start here (each teammate)

1. Read [`docs/GETTING_STARTED.md`](docs/GETTING_STARTED.md) and [`docs/TEAM_ROLES.md`](docs/TEAM_ROLES.md).
2. Check the source tracker at [`research/shared/literature_matrix.csv`](research/shared/literature_matrix.csv).
3. Work in your assigned area: [`research/turja_section_II_attention/`](research/turja_section_II_attention/), [`research/mostafizur_section_III_fpga_hbm/`](research/mostafizur_section_III_fpga_hbm/), or [`research/deepak_section_IV_evaluation/`](research/deepak_section_IV_evaluation/).
4. Add a note for each paper using [`templates/source_note.md`](templates/source_note.md). Use an **exact title, stable DOI/URL, and page/table number for numerical claims**.
5. Record new suggestions in [`ideas/idea_board.md`](ideas/idea_board.md) and detailed proposals using [`templates/idea_proposal.md`](templates/idea_proposal.md).
6. Write in your assigned [`drafts/`](drafts/) file first, then propose edits to [`paper/main.tex`](paper/main.tex) through a pull request.
7. Update [`docs/TASK_BOARD.md`](docs/TASK_BOARD.md) and add meeting decisions to [`meetings/`](meetings/).

## Project folders

```text
FPGA_Transformer_LLM_Team_GitHub_Repository_Assigned/
├── README.md                     ← project home and navigation
├── CONTRIBUTING.md               ← branch/PR rules and paper quality rules
├── .gitignore                    ← ignore LaTeX build leftovers
├── .github/                     ← issue and pull-request templates
├── docs/                        ← roles, milestones, plans, source checklist
├── research/
│   ├── turja_section_II_attention/       ← Turja: Transformer, prefill/decode, KV cache
│   ├── mostafizur_section_III_fpga_hbm/  ← Mostafizur: architectures/HBM
│   ├── deepak_section_IV_evaluation/     ← Deepak: GPU comparison/energy
│   ├── shared/                  ← shared source matrix and reading notes
│   └── papers/                  ← paper LINKS; PDFs only if sharing is allowed
├── ideas/                       ← idea board and detailed proposals
├── drafts/                      ← individual section drafts in Markdown
├── figures/                     ← your original diagrams, source SVGs, captions
├── data/                        ← quoted benchmark evidence and assumptions
├── meetings/                    ← agendas, minutes, action items
├── templates/                   ← copy-and-fill research/idea/review templates
└── paper/
    ├── main.tex                 ← existing IEEE-format working draft
    ├── references.bib           ← shared BibTeX database
    └── draft_v1_reference.pdf   ← updated author-name working preview PDF
```

## Deadlines from the seminar slides

| Milestone | Date | What to deliver |
| --- | --- | --- |
| Outline | 2026-11-05 | Research question, structure, at least 10 sources |
| First draft | 2026-11-19 | Main figures and references |
| Peer review | 2026-12-03 | Cross-team review and polishing |
| Final IEEE paper | 2026-12-31 | 6–8 pages, at least 15 references |
| Presentation | 2027-01-07 | 20 minutes + discussion |

**One joint paper:** all three students contribute to the analysis and all three review the complete paper. Each author should keep a truthful contribution record.

## Compile the seminar paper

In **Overleaf**, upload the files inside `paper/`, set **`main.tex`** as the main document, and compile. The `references.bib` file must remain beside `main.tex`. Locally, from the `paper/` directory:

```bash
pdflatex main
bibtex main
pdflatex main
pdflatex main
```

## What counts as evidence?

A copied speedup such as “6× faster” is **not enough**. Record: exact source, model, input/output lengths, batch size, quantization, FPGA type, GPU baseline, power measurement scope, whether results were measured or post-synthesis, and page/figure/table. See [`data/benchmark_evidence_template.csv`](data/benchmark_evidence_template.csv) and [`docs/QUALITY_CHECKLIST.md`](docs/QUALITY_CHECKLIST.md).

## Academic integrity and sharing

Write notes and drafts in your own words. Link to papers rather than uploading publishers' copyrighted PDFs without permission. Clearly separate reported study results from your own measurements. Verify AI-assisted text and follow university guidelines for AI-use declarations. 

**Important:** Upload the *extracted contents* of the ZIP to GitHub, not the ZIP file itself; GitHub does not automatically unpack ZIP archives into repository folders.
