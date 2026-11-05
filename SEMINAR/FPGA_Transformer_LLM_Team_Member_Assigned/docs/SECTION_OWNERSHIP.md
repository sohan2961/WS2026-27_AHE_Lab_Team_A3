# Detailed section ownership and handoff checklist

## Turja — Section II: Transformer inference and memory requirements

**Research goal:** Explain why Transformer inference becomes compute- or memory-constrained in different phases.

Deliverables:
1. Define scaled dot-product attention and Q, K, V; cite the foundational Transformer paper.
2. Explain **prefill** versus **autoregressive decode**, and why the bottleneck can shift with batch size/context length.
3. Derive and explain `M_KV = 2 × layers × batch × sequence_length × kv_heads × head_dim × bytes_per_element`; state assumptions.
4. Compare MHA, GQA and MQA cache footprint with one clearly labeled illustrative calculation.
5. Draft one original attention/KV-cache figure (do not copy a published diagram without attribution).
6. Verify the original articles for Attention Is All You Need, MQA, GQA, FlashAttention and PagedAttention; log page/section numbers.
7. Upload own notes to `research/turja_section_II_attention/` and prose to `drafts/turja_section_II.md`.

**Handoff:** Member reviewer Deepak validates equations and distinctions before integration.

## Mostafizur Rahman — Section III: FPGA accelerator architectures

**Research goal:** Explain the concrete hardware mechanisms for reducing compute and memory costs in attention/LLM inference.

Deliverables:
1. Describe FPGA processing elements, pipelining, tiling, streaming dataflow and on-chip buffering.
2. Map Q/K/V projection, attention, FFN and KV-cache movement to a **conceptual** FPGA architecture.
3. Compare BRAM, URAM, DDR and HBM; distinguish rated throughput from achieved memory bandwidth.
4. Cover quantization (INT8/INT4), sparsity and architecture-specific trade-offs (DSP/LUT/BRAM/power).
5. Check architecture claims against FTRANS, FlightLLM and the ISOCC quantization/MQA design; use original publication figures/tables for factual claims.
6. Draft or revise a **self-made** accelerator block diagram and memory hierarchy table.
7. Upload own notes to `research/mostafizur_section_III_fpga_hbm/` and prose to `drafts/mostafizur_section_III.md`.

**Handoff:** Reviewer Turja checks that architecture claims connect to the Transformer bottlenecks in Section II.

## Deepak — Section IV: Comparative evaluation

**Research goal:** Provide a transparent, fair comparison of published FPGA and GPU inference results.

Deliverables:
1. Define **time to first token (TTFT)**, **time per output token (TPOT)**, tokens/s, power (W) and energy/token (J/token).
2. Extract reported FPGA/GPU numbers from FlightLLM and EdgeLLM, plus other suitable peer-reviewed studies; note publication and exact page/table.
3. Record every baseline: device, model, parameter count, quantization, batch size, sequence lengths and measured/estimated status.
4. Avoid ranking non-matched experiments as if they used identical workloads; write an explicit threats-to-validity paragraph.
5. Use `data/benchmark_evidence_template.csv` for exact reported numbers and definitions.
6. Prepare one comparison table; explain what performance gains do and **do not** establish.
7. Upload own notes to `research/deepak_section_IV_evaluation/` and prose to `drafts/deepak_section_IV.md`.

**Handoff:** Reviewer Mostafizur checks hardware and memory specification claims.

## Joint contributions

| IEEE part | Who contributes | Minimum action |
| --- | --- | --- |
| Abstract | All | Summarize the actual verified findings only |
| I. Introduction | All | Agree on motivation, precise research question, limitations and contributions |
| V. Discussion | All | Integrate memory/architecture/benchmark implications for edge vs data center |
| VI. Conclusion | All | Answer research question, identify evidence limits and future work |
| References | All | Verify minimum 15 bibliographic entries, in-text use and IEEE formatting |
| Final presentation | All | Coordinate a ~20-minute presentation and questions |

**Deadlines (professor's slides):** Outline Nov 5 2026; first draft Nov 19; peer review Dec 3; final paper Dec 31; presentation Jan 7 2027.
