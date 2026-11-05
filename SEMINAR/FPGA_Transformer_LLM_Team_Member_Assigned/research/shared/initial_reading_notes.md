# Relevance notes for seminar bibliography

These short notes satisfy the instructor's request to document how each source is relevant; cross-check them against `references.bib`.

1. **Vaswani et al. (2017), Attention Is All You Need.** Primary explanation of attention and Transformer structure; source for attention equation.
2. **Shazeer (2019), Fast Transformer Decoding.** Introduces MQA, showing why sharing K/V heads can reduce decode memory traffic.
3. **Ainslie et al. (2023), GQA.** Describes compromise between multi-head attention and MQA via grouped KV heads.
4. **Dao et al. (2022), FlashAttention.** Establishes IO-aware tiled attention; important GPU algorithm comparison.
5. **Dao (2024), FlashAttention-2.** Illustrates optimized GPU parallelization; prevent weak baseline assumptions.
6. **Kwon et al. (2023), PagedAttention.** KV-cache management and batching effects beyond arithmetic considerations.
7. **Williams et al. (2009), Roofline.** Conceptual basis of bandwidth-limited versus compute-limited reasoning.
8. **Xiao et al. (2023), SmoothQuant.** Quantization scheme for activations and weights, relevance to custom arithmetic.
9. **Lin et al. (2024), AWQ.** Weight-only quantization and quality preservation in constrained devices.
10. **Li et al. (2020), FTRANS.** Early architecture co-design and compression; comparison requires workload caution.
11. **Zeng et al. (2024), FlightLLM.** FPGA LLM accelerator and reported U280 energy and VHK158 throughput comparisons.
12. **Huang et al. (2025), EdgeLLM.** CPU--FPGA mixed-precision architecture and selected A100 comparison.
13. **Chae and Kang (2025), ISOCC.** Small Artix-7 quantized/MQA streaming design with post-synthesis numbers; avoid misrepresenting as general 7B hardware result.
14. **Blankestijn et al. (2026), Survey.** Recent broad survey reinforcing need for reproducible and like-for-like comparison.
15. **AMD U280 data sheet.** Hardware capacity and rated bandwidth figures for HBM and DDR; not a runtime benchmark.
16. **AMD KV260 data sheet.** Grounding for realistic edge feasibility and 4GB DDR capacity.
17. **NVIDIA A100 data sheet.** GPU HBM bandwidth reference, explicitly distinguished from achieved inference performance.

## Claims to validate before final submission

- **FlightLLM:** Confirm the exact model, bit width, batch, GPU software stack and energy-measurement boundary in the experimental tables. U280 versus V100S and VHK158 versus A100 are separate cases.
- **EdgeLLM:** The final IEEE TCSI abstract reports 1.91x throughput and 7.55x energy efficiency; the earlier arXiv version gave different values for a named workload. Prefer final published version.
- **Chae/Kang:** The 4.4k tokens/s figure is described as *post-synthesis*. Do not interpret it as physical end-to-end throughput or compare directly with 7B-model GPU studies.
- **HBM:** Card-rated HBM and DDR bandwidth numbers do not equal achieved application bandwidth, and the A100 example is also a published hardware specification.
- **Source age:** At least one source (2026 survey) covers a specific literature window, not necessarily all papers published through November 2026.
