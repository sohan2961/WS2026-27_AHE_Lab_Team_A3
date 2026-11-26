# [2025] EdgeLLM: A Highly Efficient CPU-FPGA Heterogeneous Edge Accelerator for Large Language Models

- **Authors:** M. Huang et al.
- **Published in:** IEEE Transactions on Circuits and Systems I: Regular Papers, 2025.
- **DOI:** https://doi.org/10.1109/TCSI.2025.3546256
- **BibTeX key:** `huang2025edgellm` (proposed; check the team's reference file).
- **Reviewed by:** Deepak
- **Status:** Reading / verification in progress.

## Research question connection

This paper is useful for my Section IV because it compares the performance of an FPGA-based LLM accelerator with an NVIDIA A100 GPU.

The researchers developed a system called EdgeLLM, where the CPU and FPGA work together to run large language models.

The paper mainly focuses on improving inference speed and energy efficiency.

It also studies how different memory types, such as HBM and DDR, affect the speed of generating tokens.

This connects to our research question about when FPGAs can perform efficiently compared with GPUs.

## 3–5 key ideas (in our own words)

1. FPGAs can be designed to perform specific AI calculations more efficiently.
2. EdgeLLM uses both a CPU and an FPGA to run LLM inference.
3. The researchers use lower-bit numbers and sparsity to reduce the amount of computation and memory needed.
4. HBM can help improve decoding speed because it transfers data faster than DDR in the tested configuration.
5. The results show that FPGAs can be efficient, but their performance depends on the model and hardware setup.

## Experimental setup

| LLM model | FPGA used | GPU compared | Numerical precision | Batch size |
| --- | --- | --- | --- | --- |
| GLM-6B and Qwen-7B | Xilinx VCU128 | NVIDIA A100 | Mixed precision and low-bit weights | Depends on the reported experiment; check source |

## Evidence from the IEEE paper

| What was measured | Result | Source | Important note |
| --- | --- | --- | --- |
| GLM-6B decoding speed | 85.8 tokens/s | EdgeLLM, Section V | Peak reported result |
| Qwen-7B decoding speed | 69.4 tokens/s | EdgeLLM, Section V | Evaluated model configuration |
| Average FPGA power | 56.86 W | EdgeLLM, Section V | Not complete system power |
| Throughput compared with A100 | 1.91× higher | EdgeLLM, Section V | Specific GPU comparison |
| Energy efficiency compared with A100 | 7.55× higher | EdgeLLM, Section V | Specific GPU comparison |
| HBM decoding speed | 51.42 tokens/s | EdgeLLM, memory comparison | Specific tested workload |
| DDR decoding speed | 14.11 tokens/s | EdgeLLM, memory comparison | Specific tested workload |

**Note:** The exact page, table, or figure number for each result should be added after checking the original paper. The general Section V reference is not sufficient for the team's final evidence requirements.

## Additional data analysis

### HBM versus DDR

The researchers compared decoding speed using HBM and DDR memory.

- HBM: 51.42 tokens/s
- DDR: 14.11 tokens/s

To compare the speeds, I calculated:

51.42 / 14.11 = **3.64**

This means the HBM configuration generated tokens approximately **3.64 times faster** than the DDR configuration in this particular experiment.

This result helps explain why memory bandwidth is important for LLM decoding.

However, it does not mean HBM will always be 3.64 times faster than DDR.

### FPGA versus GPU

EdgeLLM reports **1.91× higher throughput** and **7.55× higher energy efficiency** than the GPU baseline used in the paper.

This suggests that an optimized FPGA accelerator can perform well for certain LLM workloads.

However, the comparison depends on the model, precision, hardware, and experimental conditions.

## Critical analysis

From this paper, I understood that FPGA performance depends not only on computing power but also on how efficiently data moves between memory and the processing units.

HBM is useful because the FPGA needs to read model weights repeatedly during decoding.

The researchers also use mixed precision and sparsity to reduce computation.

One important limitation is that the results are measured using particular LLMs and hardware configurations.

Therefore, we cannot conclude that every FPGA will always be faster or more energy-efficient than every GPU.

Also, the reported FPGA power does not represent the complete power consumption of the CPU–FPGA system.

## Short paragraph we can adapt into the paper

EdgeLLM [Huang et al., 2025] studies how an FPGA-based accelerator can improve LLM inference performance. The researchers tested GLM-6B and Qwen-7B using a VCU128 FPGA and compared the results with an NVIDIA A100 GPU baseline. They report up to 85.8 tokens/s for GLM-6B and 69.4 tokens/s for Qwen-7B. The study also reports improvements in throughput and energy efficiency under its tested conditions. Another important finding is that HBM can improve decoding speed by providing higher memory bandwidth. Overall, this paper shows that FPGA acceleration can be effective when the hardware and memory system are designed for the workload.

## Open questions for teammates

- Should we include the HBM-versus-DDR results in Section IV, or leave most of that discussion to Section III?
- Are the FPGA and GPU power measurements based on the same measurement scope?
- Which EdgeLLM results are most important for our final comparison table?
- Is the EdgeLLM reference already included in our team's BibTeX file?