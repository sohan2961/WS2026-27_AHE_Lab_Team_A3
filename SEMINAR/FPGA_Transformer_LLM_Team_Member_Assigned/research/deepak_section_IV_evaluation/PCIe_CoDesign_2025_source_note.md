# [2025] Hardware-Software Co-Design for Efficient LLM Inference on PCIe-Based FPGAs Using Coarse-Grained Systolic Arrays

- **Author:** Yun-Nan Chang
- **Published in:** 2025 IEEE 38th International System-on-Chip Conference (SOCC).
- **DOI:** https://doi.org/10.1109/SOCC66126.2025.11235351
- **BibTeX key:** `chang2025pcie` (proposed; check the team's reference file).
- **Reviewed by:** Deepak
- **Status:** Reading / verification in progress.

## Research question connection

This paper is useful for my Section IV because it studies how an FPGA accelerator can improve LLM inference performance.

The researchers use an FPGA connected to a computer through PCIe.

They compare the FPGA-accelerated system with a CPU-only implementation.

The paper studies two important inference stages:

1. **Prefill:** Processing the input prompt.
2. **Decoding:** Generating output tokens.

This helps us understand why an FPGA can improve one stage of LLM inference but may not improve another.

**Important:** This paper compares an FPGA-based system with a CPU. It does not provide a direct FPGA-versus-GPU benchmark.

## 3–5 key ideas (in our own words)

1. LLM inference requires many matrix multiplication operations.
2. The researchers designed larger processing elements called Big PEs to perform matrix calculations efficiently.
3. The accelerator uses a systolic array, where several processing elements work together.
4. PCIe connects the FPGA accelerator to the host computer.
5. The results show that FPGA acceleration improves prompt processing in the tested configurations, but decoding performance remains a challenge.

## Experimental setup

| Feature | Description |
| --- | --- |
| LLM model | TinyStories-15M |
| FPGA platform | AMD/Xilinx Alveo U55 |
| CPU baseline | AMD Ryzen 7 |
| Numerical precision | INT8 |
| Accelerator architecture | Coarse-grained systolic array |
| Connection | PCIe |
| GPU comparison | Not included |

The researchers used a relatively small language model.

Therefore, the results should not be directly generalized to much larger models such as LLaMA2-7B or LLaMA3-8B.

## Evidence from the IEEE paper

The following prompt-processing and decoding results are from the paper's performance evaluation. The exact table number should be checked against the original PDF before marking this note as Verified.

| What was measured | Result | Source | Important note |
| --- | --- | --- | --- |
| CPU prompt throughput | 33.29 tokens/s | Performance evaluation, prompt/decode results | CPU-only baseline |
| FPGA HW-1 prompt throughput | 71.58 tokens/s | Performance evaluation, prompt/decode results | FPGA configuration 1 |
| FPGA HW-2 prompt throughput | 124.00 tokens/s | Performance evaluation, prompt/decode results | FPGA configuration 2 |
| CPU decoding throughput | 10.90 tokens/s | Performance evaluation, prompt/decode results | CPU-only baseline |
| FPGA HW-1 decoding throughput | 3.64 tokens/s | Performance evaluation, prompt/decode results | FPGA configuration 1 |
| FPGA HW-2 decoding throughput | 5.15 tokens/s | Performance evaluation, prompt/decode results | FPGA configuration 2 |

The paper also discusses improvements in the systolic-array design.

Its IEEE abstract reports that the proposed design reduces the cycle count of a 64 × 64 matrix multiplication from approximately 190 to 120 cycles under a fixed DSP budget.

This is an architecture-level comparison, not a measurement of complete LLM inference latency.

## Additional data analysis

### 1. Prompt-processing performance

The reported prompt throughput is:

- CPU: 33.29 tokens/s
- FPGA HW-1: 71.58 tokens/s
- FPGA HW-2: 124.00 tokens/s

I calculated the throughput improvement of HW-2 over the CPU:

124.00 / 33.29 = **3.72 times**

This means that FPGA HW-2 processes prompt tokens approximately **3.72 times faster** than the CPU-only baseline for this reported measurement.

This result shows that FPGA acceleration can be useful during prefill.

### 2. Decoding performance

The reported decoding throughput is:

- CPU: 10.90 tokens/s
- FPGA HW-1: 3.64 tokens/s
- FPGA HW-2: 5.15 tokens/s

In this case, the CPU achieves higher decoding throughput.

For example:

10.90 / 5.15 = **2.12 times**

Therefore, the CPU generates tokens approximately **2.12 times faster** than the FPGA HW-2 configuration.

This shows that improving matrix multiplication performance does not automatically improve token-by-token decoding.

### 3. Why are the results different?

Prefill and decoding have different computational requirements.

During prefill, the accelerator can process many input tokens using parallel matrix operations.

During decoding, the model generates tokens one after another.

Memory transfers, communication overhead, and hardware utilization can affect decoding performance.

This helps explain why the tested FPGA configurations perform better during prompt processing but worse during decoding.

## Critical analysis

From this paper, I understood that FPGA acceleration does not always improve every stage of LLM inference.

The researchers developed an optimized systolic-array architecture that performs matrix calculations efficiently.

The results show a clear improvement in prompt-processing throughput.

However, decoding throughput is lower than the CPU baseline in the evaluated configurations.

One possible reason is that decoding offers less parallel work and can be affected by data-transfer and communication overhead.

The paper does not provide a GPU baseline, so its results cannot answer whether the FPGA is faster or more energy-efficient than an NVIDIA GPU.

The experiment also uses TinyStories-15M, which is much smaller than the multi-billion-parameter models considered in other studies.

Therefore, I will use this paper as supporting evidence for FPGA architectural trade-offs rather than as a direct FPGA-versus-GPU comparison.

## Short paragraph we can adapt into the paper

Chang (2025) studies FPGA acceleration for LLM inference using a PCIe-connected Alveo U55 and a coarse-grained systolic-array architecture. The researchers evaluate an INT8 TinyStories-15M model and compare the results with a CPU-only implementation. The FPGA configurations improve prompt-processing throughput, with HW-2 reaching 124.00 tokens/s compared with 33.29 tokens/s for the CPU. However, the CPU achieves higher decoding throughput, reaching 10.90 tokens/s compared with 5.15 tokens/s for HW-2. These findings show that FPGA acceleration can improve prefill performance while still facing limitations during decoding. Since the paper does not include a GPU comparison, its results are supporting evidence rather than a direct FPGA-versus-GPU benchmark.

## Open questions for teammates

- Should we include this CPU–FPGA comparison in our final Section IV table?
- Can we confirm the exact table number and benchmark conditions in the original IEEE PDF?
- How can we connect these results to the systolic-array discussion in Section III?
- Should we discuss PCIe communication overhead as a possible limitation?
- Is this paper already included in the team's BibTeX reference file?