# Team roles and responsibilities (agreed section allocation)

This team produces **one** IEEE-format research paper, with all three authors contributing to shared sections and reviewing the finished draft. Assignment of a section **does not imply it has been written or verified yet**.

| Person | Lead IEEE section | Scope | Research location | Individual draft |
| --- | --- | --- | --- | --- |
| **Turja** | **II. Transformer Workload and Memory Demands** | Self-attention, Q/K/V, prefill vs decode, MHA/MQA/GQA, KV-cache size and bandwidth limits | `research/turja_section_II_attention/` | `drafts/turja_section_II.md` |
| **Mostafizur Rahman** | **III. FPGA Accelerator Architectures and HBM** | Compute/dataflow design, PE/systolic arrays, BRAM/URAM, DDR and HBM, quantization, sparsity, FPGA constraints | `research/mostafizur_section_III_fpga_hbm/` | `drafts/mostafizur_section_III.md` |
| **Deepak** | **IV. Comparative Evaluation** | FPGA/GPU measurements from literature, TTFT, TPOT, tokens/s, power, energy/token, comparability, limits | `research/deepak_section_IV_evaluation/` | `drafts/deepak_section_IV.md` |

## Shared writing and quality control

- **All three:** Abstract, Section I (Introduction), Section V (Discussion), Section VI (Conclusion), and References.
- **Cross-review sequence:** Turja reviews Mostafizur's Section III; Mostafizur reviews Deepak's Section IV; Deepak reviews Turja's Section II. All review the final complete PDF.
- **Figures:** Turja owns attention/KV-cache diagram; Mostafizur owns architecture/memory hierarchy; Deepak owns benchmark methodology/comparison table. These are proposed deliverables, not completed artifacts.
- **Integration:** Add draft sections via GitHub pull requests, ask another teammate to review, then merge into `paper/main.tex`.
- **Audit:** For each numerical result, record the publication, benchmark model, hardware, precision, batch size and exact page/figure/table. Distinguish estimated, simulated and measured results.
- **Contribution history:** Use `meetings/CONTRIBUTIONS.md` for truthful entries **after** work is done; track pending actions in `docs/TASK_BOARD.md`.
- **Author name spellings:** Mostafizur Rahman, Turja, Deepak. Add full legal surnames/affiliations if needed at submission; do not invent emails or GitHub handles.
