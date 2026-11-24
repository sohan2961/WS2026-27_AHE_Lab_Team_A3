# Team A3 — Nexys A7-100T Work Assignment

Project: 8-token / 16-dimensional Tiny Transformer on **Artix-7**, via **Vitis HLS and MicroBlaze**.
Baseline FP32 software exists and has passed host tests; **FPGA tests are still pending**.

## Md Mostafizur Rahman — FPGA System Design & Integration
**Owns:** `hls/attention_top.*`, `hls/transformer_top.*`, `scripts/run_hls*.tcl`, Vivado block design, Vitis MicroBlaze app and benchmarks.

1. Verify `xc7a100tcsg324-1`, 100 MHz clock and exact Nexys A7-100T board.
2. Run host tests and HLS attention-only simulation/synthesis with Vitis HLS 2025.1.
3. Record LUT, FF, DSP, BRAM and clock estimate; optimize if needed.
4. Export attention HLS IP (after synthesis and RTL co-simulation if possible).
5. Add MicroBlaze, AXI interconnect, AXI UART Lite, dedicated program BRAM and shared data BRAM (AXI BRAM Controller).
6. Connect the HLS AXI-Lite control and `m_axi` master to the shared BRAM address space.
7. Validate design, constrain board clock/UART, generate bitstream and XSA.
8. Write the standalone MicroBlaze application after checking generated driver and address map; verify output; benchmark.

**Deliverable:** Board demo, reported real resource/timing and MicroBlaze/FPGA measurements.

## Deepak — Self-Attention Hardware Accelerator
**Owns:** `hls/attention.*` and help with `hls/attention_testbench.cpp`.

1. Check Q/K/V matrix multiplication and row-major weights.
2. Validate scaled attention `QK^T / 4`, stable Softmax, weighted V and Wo.
3. Run `bash scripts/run_host_attention.sh` or the PowerShell equivalent.
4. Run/assist attention-only HLS C simulation and synthesis. Review resource-heavy FP32 operations.
5. Only after a correct baseline, propose fixed-point or pipelining changes and revalidate outputs.

**Deliverable:** Numerically verified, HLS-synthesized attention accelerator.

## Turja — Transformer Model & FFN Implementation
**Owns:** `reference/generate_vectors.py`, `hls/transformer_layers.*`, `data/` reference vectors.

1. Maintain fixed NumPy reference outputs for 8×16 input and 2,112 weights.
2. Verify the attention-only input is **LayerNorm1(X)** and matches `data/expected_ln1.txt`.
3. Implement and test LayerNorm1, LayerNorm2, both residual paths, FFN 16→32→16.
4. Compare all intermediate and final outputs with NumPy.
5. Help check actual UART output from Nexys A7 after the MicroBlaze app is built.

**Deliverable:** Golden reference and numerically validated Transformer layers.

## Shared milestone gates

| Stage | Test | Evidence |
|---|---|---|
| 1 — Host | Both scripts pass on a PC | Terminal logs |
| 2 — Attention HLS | Nexys `attention_top` C simulation, then C synthesis | Vitis HLS reports |
| 3 — Attention hardware | Vivado implementation with MicroBlaze + shared BRAM; real output | Bitstream/XSA, UART log |
| 4 — Full encoder | FP32 full synthesis attempted; fixed-point if needed | Fit/timing/error report |
| 5 — Results | Same-board software/accelerator latency where feasible | Benchmark CSV + methods |

**Branches:** `mostafizur/integration`, `deepak/attention`, `turja/reference-layers`.
**Tracker:** `tracking/Team_A3_Nexys_A7_Checkpoints.xlsx`, 33 shared checkpoints, personal dropdowns.
