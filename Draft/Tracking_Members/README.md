# Team A3 — 18 Checkpoints and Member Responsibilities

**Project:** Tiny Transformer Inference Engine on Nexys A7-100T  
**Implementation:** VHDL RTL (Vivado 2025.1) + MicroBlaze (Vitis IDE)  
**Team:** Md Mostafizur Rahman, Turja, Deepak  
**Schedule:** Four weeks · 18 checkpoints

This README explains exactly what each member is responsible for during the four-week implementation. A **lead** owns the checkpoint deliverable; **support** contributes tests, references, reviews or integration help.

> **Progress is not implied by assignment.** All 18 new VHDL checkpoints are initially marked **Not started** in the Excel tracker. The existing FP32 software reference passing does not count as completed VHDL/FPGA hardware work.

## Week 1 — VHDL Foundations and Matrix Multiplication

**Four checkpoints**

| ID | Checkpoint | Lead | Support |
|---|---|---|---|
| W1-01 | Create Vivado Nexys A7-100T RTL project | **Mostafizur** | — |
| W1-02 | Simulate 16-element signed dot-product RTL | **Mostafizur** | Deepak: test vectors |
| W1-03 | Implement and verify Q × Kᵀ score controller | **Mostafizur** | Deepak: numerical verification |
| W1-04 | Create deterministic reference and test vectors | **Turja** | Deepak: independent checks |

**Expected result:** A simulated dot-product and matrix-multiplication foundation plus deterministic Python/NumPy reference data. The supplied dot-product test expects **16**. Matrix controller testing is a separate deliverable.

**Member workspaces:** [Mostafizur](../weekly_work/week_01/mostafizur/README.md) · [Turja](../weekly_work/week_01/turja/README.md) · [Deepak](../weekly_work/week_01/deepak/README.md)

## Week 2 — Self-Attention Accelerator

**Five checkpoints**

| ID | Checkpoint | Lead | Support |
|---|---|---|---|
| W2-01 | Implement Q/K/V projections with fixed weights | **Mostafizur** | — |
| W2-02 | Verify scaled Q × Kᵀ scores | **Mostafizur** | Deepak: calculation tests |
| W2-03 | Implement stable Softmax approximation | **Mostafizur** | Deepak: edge-case tests |
| W2-04 | Implement attention-weighted sum with V | **Mostafizur** | — |
| W2-05 | Verify complete attention against Python | **Turja** | Deepak and Mostafizur |

**Expected result:** Correct simulated self-attention with documented quantization, precision and error tolerance. Softmax approximation must be verified numerically.

**Member workspaces:** [Mostafizur](../weekly_work/week_02/mostafizur/README.md) · [Turja](../weekly_work/week_02/turja/README.md) · [Deepak](../weekly_work/week_02/deepak/README.md)

## Week 3 — Transformer and MicroBlaze Integration

**Five checkpoints**

| ID | Checkpoint | Lead | Support |
|---|---|---|---|
| W3-01 | Implement/validate LayerNorm, residual and FFN | **Turja** | Deepak: support-module verification; Mostafizur: integration |
| W3-02 | Integrate top-level Transformer VHDL | **Mostafizur** | Turja |
| W3-03 | Connect MicroBlaze to custom IP with AXI/BRAM | **Mostafizur** | — |
| W3-04 | Write Vitis MicroBlaze test application | **Mostafizur** | — |
| W3-05 | Run integrated simulation and interface tests | **Deepak** | Mostafizur and Turja |

**Expected result:** Simulated full Transformer RTL and a documented MicroBlaze/AXI/BRAM interface. Hardware implementation is not automatically verified by successful RTL simulation.

**Responsibility note:** The Excel tracker currently makes Deepak the lead of W3-05, integrated verification. In the team's shorter responsibility table, Deepak is described as the support-module verification contributor, which is captured under W3-01. If the team wants exact one-to-one ownership, it may reassign W3-05 to Mostafizur in a future approved update. This README matches the current tracker.

**Member workspaces:** [Mostafizur](../weekly_work/week_03/mostafizur/README.md) · [Turja](../weekly_work/week_03/turja/README.md) · [Deepak](../weekly_work/week_03/deepak/README.md)

## Week 4 — FPGA Implementation and Benchmarking

**Four checkpoints**

| ID | Checkpoint | Lead | Support |
|---|---|---|---|
| W4-01 | Complete synthesis, implementation and timing | **Mostafizur** | — |
| W4-02 | Run Nexys A7 hardware test | **Mostafizur** | — |
| W4-03 | Measure latency and numerical correctness | **Mostafizur** | Deepak: independent check; Turja: reference comparison |
| W4-04 | Finalize README, results and technical report | **Turja** | Deepak and Mostafizur |

**Expected result:** Real Nexys A7 bitstream and board test evidence, utilization/timing report, reproducible benchmarks and final documentation. Do not report a speedup without measured and clearly described baselines.

**Member workspaces:** [Mostafizur](../weekly_work/week_04/mostafizur/README.md) · [Turja](../weekly_work/week_04/turja/README.md) · [Deepak](../weekly_work/week_04/deepak/README.md)

## Primary checkpoint ownership summary

| Member | Lead checkpoints | Total | Additional contributions |
|---|---|---:|---|
| **Mostafizur Rahman** | W1-01–03, W2-01–04, W3-02–04, W4-01–03 | **13** | Hardware integration and support for reference comparison |
| **Turja** | W1-04, W2-05, W3-01, W4-04 | **4** | Python reference, LayerNorm/FFN, output comparison, documentation |
| **Deepak** | W3-05 | **1** | Verification and test-vector contributions in every week |
| **Total** | | **18** | Lead counts do not measure the full workload |

The ownership distribution is hardware-heavy for Mostafizur because both self-attention and FPGA integration are assigned to him. Deepak and Turja should link their own verification and support pull requests so their contributions remain visible.

## Where to update progress

1. Open the **[active Excel tracker](../tracking/Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx)**.
2. Select the correct **Week 1, 2, 3 or 4** worksheet.
3. Each teammate updates only their own status column, choosing one of: `Not started`, `In progress`, `I did it`, `I did it with teammate`, `I failed to do it`.
4. The checkpoint lead adds a GitHub pull request, simulation log or measurement reference in **Evidence / PR**.
5. A checkpoint counts **Complete** only when the lead selects a completed status and evidence is entered. Otherwise the tracker displays **Needs evidence** or the current progress state.
6. Keep each member's detailed weekly deliverables and notes in `weekly_work/week_0N/<member>/README.md`.

## Repository map

| Location | Purpose |
|---|---|
| [`weekly_work/`](../weekly_work/README.md) | Four week folders and individual work assignments |
| [`tracking/`](../tracking/README.md) | Main VHDL Excel tracker and archived HLS tracker |
| [`rtl/attention/`](../rtl/attention/) | VHDL arithmetic and attention hardware |
| [`rtl/transformer/`](../rtl/transformer/) | Transformer support modules |
| [`reference/`](../reference/) | Python/NumPy reference and numerical checks |
| [`sim/`](../sim/) | VHDL simulation testbenches |
| [`integration/`](../integration/) | Vivado AXI/BRAM and MicroBlaze integration |
| [`docs/`](../docs/) | Architecture, instructions, results and documentation |

The original HLS/FP32 C++ sources remain available in `hls/` as a tested software baseline. The active FPGA implementation path is VHDL with Vivado, followed by Vitis IDE for the MicroBlaze application.
