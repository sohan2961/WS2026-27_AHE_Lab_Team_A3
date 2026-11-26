# [2025] Hummingbird: A Smaller and Faster Large Language Model Accelerator on Embedded FPGA

- **Authors:** J. Li et al.
- **Published in:** 2025 IEEE/ACM International Conference on Computer-Aided Design (ICCAD).
- **DOI:** https://doi.org/10.1109/ICCAD66269.2025.11241002
- **BibTeX key:** `li2025hummingbird` (proposed; check the team's reference file).
- **Reviewed by:** Deepak
- **Status:** Reading / verification in progress.

## Research question connection

This paper is useful for my Section IV because it studies how large language models can run on smaller FPGA devices.

The researchers developed an accelerator called Hummingbird and tested it using the LLaMA3-8B model.

The paper mainly focuses on decoding speed, memory bandwidth, power consumption, and hardware resource usage.

This is related to our research question because we want to understand how FPGA memory systems affect LLM inference performance.

The paper also helps us understand the performance limitations of embedded FPGAs compared with larger computing platforms.

## 3–5 key ideas (in our own words)

1. Hummingbird is an FPGA accelerator designed to run LLMs on smaller FPGA boards.
2. The researchers use quantization and memory optimizations to reduce the memory needed for inference.
3. The accelerator moves the embedding table to external storage to make better use of the limited memory available on embedded devices.
4. Memory bandwidth is important because the FPGA must repeatedly read model data during token generation.
5. Smaller FPGA devices can run LLM inference, but their decoding speed is limited by the available hardware and memory bandwidth.

## Experimental setup

| LLM model | FPGA platform | Decoding throughput | Reported power |
| --- | --- | --- | --- |
| LLaMA3-8B | KV260 | 4.8 tokens/s | 3.81 W |
| LLaMA3-8B | ZCU104 | 8.6 tokens/s | 7.09 W |
| LLaMA3-8B | Alveo U250 | 19.4 tokens/s | 14.61 W |

The researchers tested the same LLM on different FPGA platforms.

The platforms have different memory bandwidths and hardware resources.

These are FPGA platform measurements, not a direct controlled FPGA-versus-GPU experiment.

## Evidence from the IEEE paper

| What was measured | Result | Source | Important note |
| --- | --- | --- | --- |
| KV260 decoding throughput | 4.8 tokens/s | Hummingbird, Table V | Embedded FPGA |
| ZCU104 decoding throughput | 8.6 tokens/s | Hummingbird, Table V | Embedded FPGA |
| U250 decoding throughput | 19.4 tokens/s | Hummingbird, Table V | Larger FPGA platform |
| KV260 reported power | 3.81 W | Hummingbird, Table V | Not necessarily complete system power |
| ZCU104 reported power | 7.09 W | Hummingbird, Table V | Not necessarily complete system power |
| U250 reported power | 14.61 W | Hummingbird, Table V | Not necessarily complete system power |
| KV260 memory bandwidth | 19.2 GB/s | Hummingbird, Table V | Reported platform bandwidth |
| ZCU104 memory bandwidth | 34.1 GB/s | Hummingbird, Table V | Reported platform bandwidth |
| U250 memory bandwidth | 76.8 GB/s | Hummingbird, Table V | Reported platform bandwidth |
| KV260 bandwidth utilization | 94% | Hummingbird, Table V | Reported utilization |
| ZCU104 bandwidth utilization | 93% | Hummingbird, Table V | Reported utilization |

**Note:** Table V refers to Table V in the original Hummingbird paper, not a table in our Section IV. These values should be checked against the final IEEE PDF before changing the note's status to Verified.

## Additional data analysis

### 1. Memory bandwidth versus decoding speed

The researchers report the following results:

| FPGA | Memory bandwidth | Decoding speed |
| --- | --- | --- |
| KV260 | 19.2 GB/s | 4.8 tokens/s |
| ZCU104 | 34.1 GB/s | 8.6 tokens/s |
| U250 | 76.8 GB/s | 19.4 tokens/s |

From these results, I noticed that the FPGA platform with higher memory bandwidth also achieved higher decoding throughput.

For example:

- KV260 generates 4.8 tokens/s.
- ZCU104 generates 8.6 tokens/s.
- U250 generates 19.4 tokens/s.

The U250 achieves approximately:

19.4 / 4.8 = **4.04 times**

the decoding throughput of the KV260.

This suggests that memory bandwidth is an important factor in LLM decoding performance.

However, the FPGA boards also differ in processing resources and implementation details. Therefore, we cannot say that memory bandwidth alone caused the complete performance difference.

### 2. Power and energy efficiency

The paper reports power consumption of:

- KV260: 3.81 W
- ZCU104: 7.09 W
- U250: 14.61 W

Power tells us how quickly electrical energy is consumed.

For decoding, we can estimate energy per generated token using:

Energy per token = Power / Throughput

For KV260:

3.81 / 4.8 = **0.79 J/token**

For ZCU104:

7.09 / 8.6 = **0.82 J/token**

For U250:

14.61 / 19.4 = **0.75 J/token**

These are calculated estimates based on the reported power and throughput values.

They should not be described as measured complete-system energy per token.

This calculation helps us see that a device with higher total power can still have favorable energy per token if it generates tokens faster.

### 3. Memory optimization

The researchers use memory optimizations to support LLaMA3-8B on embedded FPGA platforms.

One important technique is moving the embedding table to external storage.

The accelerator also benefits from grouped-query attention, which reduces the memory needed for the key-value cache.

These techniques help overcome the memory-capacity limitations of small FPGA devices.

The architecture supports longer contexts of up to 4096 tokens. This is a supported context-length capability, not necessarily the sequence length used for the reported throughput measurements.

## Critical analysis

From this paper, I understood that memory bandwidth is one of the important factors affecting LLM inference performance on FPGAs.

The results show that the U250 achieves higher decoding throughput than the smaller KV260 and ZCU104 platforms.

However, the smaller platforms use less reported power.

This creates a trade-off between performance, power consumption, and hardware resources.

One important limitation is that Hummingbird does not provide the same type of controlled FPGA-versus-GPU comparison as GLITCHES.

Therefore, I will mainly use this paper to explain the relationship between memory bandwidth and decoding throughput.

The Jetson performance results mentioned in the paper come from other published benchmarks and should not be presented as a directly matched GPU experiment.

Also, differences between FPGA devices mean that the graph shows an association between bandwidth and throughput, not proof that bandwidth is the only reason for the performance difference.

## Short paragraph we can adapt into the paper

Hummingbird [Li et al., 2025] investigates LLM inference on embedded FPGA platforms. The researchers tested LLaMA3-8B on the KV260, ZCU104, and Alveo U250, achieving decoding throughput of 4.8, 8.6, and 19.4 tokens/s, respectively. The study also reports device power consumption of 3.81 W, 7.09 W, and 14.61 W for these platforms. These results show that FPGA memory bandwidth and hardware resources play an important role in decoding performance. The paper also demonstrates how memory optimization can make larger models possible on smaller FPGA devices. However, these measurements should not be treated as a direct FPGA-versus-GPU comparison.

## Open questions for teammates

- Should our Section IV include all three FPGA platforms or focus only on KV260 and ZCU104?
- How can we connect the memory-bandwidth results to the HBM discussion in Section III?
- Should we include calculated energy per token for Hummingbird, clearly stating the measurement limitations?
- Are the Jetson comparisons suitable for our final evaluation table, considering their different experimental conditions?
- Is the Hummingbird BibTeX reference already included in our shared bibliography?