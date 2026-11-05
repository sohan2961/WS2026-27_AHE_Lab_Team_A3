# Mostafizur Rahman — Section III: FPGA Accelerator Architectures and HBM

**Owner:** Mostafizur Rahman  
**IEEE section:** III  
**Reviewer:** Turja  
**Status:** Outline and prompts for research; not a completed verified section.

## A. FPGA compute and attention dataflow

Explain processing elements, DSP multiplication, pipelining, systolic or streaming dataflows, tiling and on-chip buffers. Show where linear layers, attention/softmax and feed-forward operations are computed.

**Notes / draft:**

[Add verified explanation]

## B. Memory hierarchy and HBM

Describe BRAM, URAM, DDR, and HBM. Why is HBM useful for streaming weights/KV-cache? Distinguish vendor peak bandwidth from achieved application bandwidth and identify platform specifics.

| Memory | Capacity evidence | Bandwidth evidence | Implication for LLM inference | Exact source page |
| --- | --- | --- | --- | --- |
| BRAM/URAM | | | | |
| DDR | | | | |
| HBM | | | | |

## C. Optimization and FPGA design trade-offs

Discuss INT8/INT4, accuracy, logic/DSP usage, sparsity and workload-dependent benefits. Do not imply an individual optimization always improves end-to-end performance.

## D. Literature architecture case studies

Review FTRANS, FlightLLM, and small-device quantized Transformer architectures, then design an original conceptual accelerator block diagram.

**Sources to check:** `li2020`, `zeng2024`, `chae2025`, `xiao2023`, `lin2024`, `amdU280`, `amdKV260`.

**Questions for teammates:**
- From Turja: Which attention/decoder paths most need bandwidth?
- From Deepak: What part of the measured latency/power does each hardware design cover?
