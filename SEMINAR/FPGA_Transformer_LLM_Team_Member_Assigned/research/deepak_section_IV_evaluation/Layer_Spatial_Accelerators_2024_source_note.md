# [2024] LLM Acceleration on FPGAs: A Comparative Study of Layer and Spatial Accelerators

- **Authors:** L. D. Prieto-Sibaja, L. G. Leon-Vega, I. Leon-Vega, J. Castro-Godinez, and S. Cozzini
- **Published in:** 2024 IEEE 42nd Central America and Panama Convention (CONCAPAN XLII).
- **DOI:** https://doi.org/10.1109/CONCAPAN63470.2024.10933896
- **BibTeX key:** `prietosibaja2024llm` (proposed; check the team's reference file).
- **Reviewed by:** Deepak
- **Status:** Reading / verification in progress.

## Research question connection

This paper is useful for my Section IV because it studies how different FPGA accelerator designs affect the performance of LLM operations.

The researchers compare two types of FPGA accelerators:

1. Layer accelerators
2. Spatial accelerators

They study the resource usage and execution time of these designs using operations from the LLaMA2-7B model.

The paper also includes comparisons involving AMD EPYC CPUs and an NVIDIA V100 GPU.

This helps us understand why the architecture of an FPGA accelerator is important when comparing its performance with GPUs.

However, the experiments mainly focus on individual LLM operations rather than complete token-generation performance.

## 3–5 key ideas (in our own words)

1. FPGA performance depends on how the accelerator architecture is designed.
2. A layer accelerator uses hardware resources to accelerate selected operations or layers.
3. A spatial accelerator uses a different organization of processing resources and can require fewer FPGA resources.
4. Different architectures create trade-offs between execution speed and resource usage.
5. Improving an individual LLM operation does not automatically mean that the complete LLM will generate tokens faster.

## Experimental setup

| Feature | Description |
| --- | --- |
| LLM model studied | LLaMA2-7B |
| FPGA platform | AMD/Xilinx Alveo U250 |
| CPU comparison | Dual AMD EPYC processors |
| GPU comparison | NVIDIA V100 |
| Accelerator designs | Layer and spatial accelerators |
| Main evaluation | Selected LLM operations, resource usage, and execution time |
| Complete LLM decoding benchmark | Not established by this comparison |

The researchers examine accelerator implementations for operations used in LLM inference.

Therefore, the results should not be interpreted as a complete FPGA-versus-GPU inference benchmark.

## Evidence from the IEEE paper

| What was compared | Reported result | Source | Important note |
| --- | --- | --- | --- |
| Layer accelerator resource occupancy | Approximately 33% | Resource comparison in original paper | Verify the exact occupancy definition |
| Spatial accelerator resource occupancy | Approximately 10% | Resource comparison in original paper | Verify the exact occupancy definition |
| Layer accelerator DSP usage | 4036 DSPs | Resource comparison in original paper | Specific accelerator design |
| Spatial accelerator DSP usage | 1277 DSPs | Resource comparison in original paper | Specific accelerator design |
| Layer accelerator LUT usage | 411,098 LUTs | Resource comparison in original paper | Specific accelerator design |
| Spatial accelerator LUT usage | 99,290 LUTs | Resource comparison in original paper | Specific accelerator design |
| Reported FPGA speedup over CPU | 1.37× to 10.98× | IEEE paper, abstract and performance evaluation | Selected operations and configurations |
| GPU performance comparison | V100 approximately 1.66× faster in one reported case | Performance comparison in original paper | Not a complete LLM inference result |

**Important:** The 1.37×–10.98× CPU speedup range is confirmed in the IEEE publication abstract. The detailed hardware-resource values and the 1.66× GPU comparison still need their exact table or figure locations checked in the original PDF.

## Additional data analysis

### 1. FPGA resource usage

The reported DSP usage is:

- Layer accelerator: 4036 DSPs
- Spatial accelerator: 1277 DSPs

DSPs are hardware blocks inside an FPGA that perform mathematical operations such as multiplication and addition.

I calculated the ratio:

4036 / 1277 = **3.16**

This means that the layer accelerator uses approximately 3.16 times as many DSP blocks as the spatial accelerator in the evaluated designs.

The paper also reports the following LUT usage:

- Layer accelerator: 411,098 LUTs
- Spatial accelerator: 99,290 LUTs

LUTs are FPGA resources used to implement digital logic.

The ratio is:

411098 / 99290 = **4.14**

Therefore, the layer accelerator uses approximately 4.14 times as many LUTs as the spatial accelerator.

These comparisons show that the spatial design uses fewer reported hardware resources.

However, lower resource usage does not automatically mean better execution speed.

### 2. Performance compared with CPUs

The researchers report speedups ranging from **1.37× to 10.98×** compared with the evaluated AMD EPYC CPU baseline.

This suggests that specialized FPGA accelerators can execute selected LLM operations faster than the CPU implementation.

However, these speedups depend on the operation and accelerator configuration.

We should not describe them as a 10.98× improvement in complete LLM token-generation throughput.

### 3. Performance compared with a GPU

The paper also includes NVIDIA V100 GPU results.

In one reported comparison, the GPU is approximately **1.66× faster** than the evaluated FPGA configuration.

This is useful because it shows that the FPGA does not always outperform the GPU.

However, the comparison focuses on particular operations and configurations.

It does not provide enough evidence to conclude which platform is faster for complete LLaMA2-7B inference.

### 4. What I learned from the results

This paper helped me understand that FPGA accelerator design involves a trade-off.

Using more processing resources can help accelerate calculations, but it also increases hardware usage.

A smaller design may save resources, but it does not necessarily provide the lowest execution time.

Therefore, performance comparisons should consider both speed and resource utilization.

## Critical analysis

This study is relevant because it demonstrates how FPGA architecture affects performance and resource usage.

The layer and spatial accelerators use different amounts of FPGA resources.

The reported results also show that specialized FPGA implementations can accelerate selected LLM operations compared with CPUs.

However, the study has an important limitation for my Section IV.

It does not establish a complete FPGA-versus-GPU comparison using metrics such as:

- Time to first token.
- Decoding latency per token.
- Complete-model output throughput.
- Energy per generated token.

These metrics are central to our research question.

Therefore, I will mainly use this paper to explain architectural performance trade-offs.

For direct FPGA-versus-GPU latency and energy comparisons, GLITCHES and EdgeLLM provide more suitable evidence.

## Short paragraph we can adapt into the paper

Prieto-Sibaja et al. (2024) compare layer and spatial FPGA accelerators for operations used in LLaMA2-7B. The researchers evaluate the execution time and hardware resource usage of the two accelerator designs. Their results show that the spatial design uses fewer FPGA resources, while performance depends on the operation and implementation. The paper reports speedups ranging from 1.37× to 10.98× compared with the evaluated AMD EPYC CPU baseline. However, these results mainly concern selected operations rather than complete LLM inference. This study therefore helps explain the architectural trade-offs behind FPGA acceleration but does not establish a general FPGA advantage over GPUs.

## Open questions for teammates

- Should we include the DSP and LUT resource comparison in Section IV or leave most of it for Section III?
- Which operation-level performance results are most relevant to our FPGA-versus-GPU discussion?
- Can we verify the exact table and figure numbers for the resource and GPU comparisons?
- Should the final paper explain the difference between operation-level acceleration and complete LLM inference?
- Is this publication already included in the team's BibTeX file?