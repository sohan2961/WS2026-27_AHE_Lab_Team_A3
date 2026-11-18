# Week 3 hardware integration notes — not yet performed

This starter is **working host C++ + NumPy**, not a running FPGA design.

1. Complete HLS C simulation, synthesis and optionally RTL cosim using Vitis HLS **2022.2**.
2. Export `transformer_top` as Vivado IP (IP Catalog).
3. Create a **separate** KV260 Vivado project (do not overwrite the existing working Sobel+DPU bitstream or device tree).
4. Instantiate Zynq MPSoC processing system, check PS DDR and enable suitable high-performance AXI slave port(s) for PL masters.
5. Wire AXI-Lite registers from PS AXI master through SmartConnect to HLS `s_axi_control`.
6. Connect HLS AXI **master** `m_axi_gmem` to the PS DDR memory route (PS slave HP/HPC port via SmartConnect), and connect clocks/resets correctly.
7. Validate design, synthesize, implement, generate bitstream, export XSA.
8. For PetaLinux: deploy a matching bitstream, device tree node, a suitable DMA-capable or physically contiguous buffer allocation mechanism, address translation and cache maintenance. `malloc()` user virtual addresses cannot be passed directly as HLS AXI physical addresses. Add a proper driver/userspace mechanism; do not use `/dev/mem` as an unreviewed shortcut.
9. On ARM, compare FPGA output with the same FP32 reference within tolerance and measure end-to-end and compute-only latency separately.
10. For performance optimization, add pipelining, data reuse and fixed-point carefully, then rerun validation.

**Important:** Direct `m_axi` masters in this version mean no separate AXI DMA IP is needed; using AXI-Stream would require a different HLS interface and DMA architecture.
