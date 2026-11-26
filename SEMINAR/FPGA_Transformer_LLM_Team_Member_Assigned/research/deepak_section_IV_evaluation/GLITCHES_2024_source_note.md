# [2024] GLITCHES: GPU-FPGA LLM Inference Through a Collaborative Heterogeneous System

- **Who wrote it:** F. Yang et al.
- **Publication / venue / year:** IEEE High Performance Extreme Computing Conference (HPEC), 2024
- **DOI or stable URL:** https://doi.org/10.1109/HPEC62836.2024.10938498
- **BibTeX key in `paper/references.bib`:** `yang2024glitches` (proposed; confirm against the shared bibliography)
- **Team reviewer:** Deepak
- **Status:** Reading / verification in progress

## Research question connection

This paper directly supports Section IV because it compares FPGA and GPU performance during two different LLM inference stages: prefill and decoding. It provides latency and power measurements and investigates a hybrid GPU–FPGA system.

## 3–5 key ideas (in our own words)

1. GPU and FPGA accelerators can have different performance advantages during prefill and decoding.
2. GPUs are particularly effective at processing long input prompts.
3. The evaluated FPGA achieves competitive token-by-token decoding performance with lower reported power.
4. A hybrid system can assign prefill to GPUs and decoding to FPGAs.
5. Numerical precision and measurement conditions must be considered when interpreting comparisons.

## Experimental setup

| Model / parameters | FPGA | GPU baseline | Precision | Batch | Input / output length |
| --- | --- | --- | --- | --- | --- |
| LLaMA2-7B | AMD Alveo U280 | NVIDIA A100 and V100S | FPGA approx. W4A8; GPUs FP16 | Verify against source | 1536 prefill / 512 decode tokens |

## Evidence (exact table, figure, or page)

| Claim | Exact number | Units | Page/figure | Measured or estimated? | Caveat |
| --- | --- | --- | --- | --- | --- |
| A100 prefill latency | 175.85 | ms | Table I (GLITCHES, 2024) | Reported measurement | GPU FP16 |
| V100S prefill latency | 398.80 | ms | Table I (GLITCHES, 2024) | Reported measurement | GPU FP16 |
| U280 prefill latency | 5001.20 | ms | Table I (GLITCHES, 2024) | Reported measurement | FPGA approximately W4A8 |
| A100 decode latency | 24.26 | ms/token | Table I (GLITCHES, 2024) | Reported measurement | Decode phase |
| V100S decode latency | 29.52 | ms/token | Table I (GLITCHES, 2024) | Reported measurement | Decode phase |
| U280 decode latency | 21.50 | ms/token | Table I (GLITCHES, 2024) | Reported measurement | Decode phase |
| A100 decode power | 167.3 | W | Table I (GLITCHES, 2024) | Reported measurement | Reported device power |
| V100S decode power | 222.5 | W | Table I (GLITCHES, 2024) | Reported measurement | Reported device power |
| U280 decode power | 46.0 | W | Table I (GLITCHES, 2024) | Reported measurement | Reported device power |
| A100 decode energy/token | 4.06 | J/token | Derived from Table I (GLITCHES, 2024) | Calculated | Excludes prefill energy |
| U280 decode energy/token | 0.99 | J/token | Derived from Table I (GLITCHES, 2024) | Calculated | Excludes prefill energy |

## Critical analysis

The results show that the A100 GPU processes the evaluated prompt much faster than the U280 FPGA. However, the FPGA achieves slightly lower decoding latency and considerably lower reported decoding power.

The comparison is not fully controlled for numerical precision: the GPU uses FP16, whereas the FPGA uses approximately 4-bit weights and 8-bit activations. The calculated energy-per-token values apply only to decoding and should not be interpreted as complete system energy.

The paper also evaluates heterogeneous multi-accelerator configurations through simulation. Those results should not be described as direct measurements showing that one FPGA outperforms one GPU.

## Short paragraph we can adapt into the paper

GLITCHES [2] provides phase-specific performance measurements for LLaMA2-7B inference using NVIDIA A100 and V100S GPUs and an Alveo U280 FPGA. The A100 achieves a prefill latency of 175.85 ms, compared with 5001.20 ms for the U280. During decoding, however, the U280 records 21.50 ms per generated token at 46.0 W, while the A100 records 24.26 ms per token at 167.3 W. These findings suggest that FPGA acceleration can be competitive during low-batch decoding, although the implementations use different numerical precisions and the comparison does not establish a general advantage across all inference workloads.

## Open questions for teammates

- Can we confirm the batch size and exact measurement boundary from the original paper?
- Are the reported device power values directly comparable across all platforms?
- Which GLITCHES results should be included in our final combined seminar paper?