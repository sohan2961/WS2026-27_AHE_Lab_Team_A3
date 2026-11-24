# Team A3 — 18 Weekly Checkpoints and Member Responsibilities

**Project:** Tiny Transformer Inference Engine on Nexys A7-100T  
**Implementation:** Vitis HLS C++ + Vivado FPGA integration + MicroBlaze software (Vitis IDE)  
**Team:** Md Mostafizur Rahman, Deepak, Turja  
**Schedule:** Four weeks · 18 checkpoints

This README follows the **Weekly Checkpoints** worksheet in `Weekly_Updates.xlsx`. The 18 checkpoint titles below reproduce the Excel **Checkpoint: what exactly to do** column **exactly**, including capitalization, symbols, and punctuation. The numeric IDs and weekly groupings also match the workbook.

The **Main lead** reproduces the Excel owner exactly. The **Named work assignment** makes it clear which teammate will produce each part of the deliverable. These named contributions are a proposed team work split; the Excel remains the source of truth for checkpoint status and formal leads.

## Week 1 — Setup, Python Reference and Attention Calculations

**Five checkpoints**

| ID | Checkpoint | Main lead | Named work assignment |
|---:|---|---|---|
| 1 | Set up GitHub and confirm Nexys A7 / Vivado / Vitis tools | Mostafizur | **Mostafizur:** create repository, branches, and tool/board setup instructions. **Deepak and Turja:** confirm their local tool access. |
| 2 | Agree on the 8-token, 16-feature, one-head model and test data | All | **Mostafizur:** fix hardware configuration. **Turja:** prepare shared input/weight data. **Deepak:** review attention dimensions. |
| 3 | Run the full Python/NumPy reference model and tests | Mostafizur | **Turja:** execute and maintain Python reference tests. **Mostafizur:** review results and capture evidence. |
| 4 | Verify Q, K, V projections and Q × K transpose scores | Mostafizur | **Deepak:** calculate and check Q/K/V projections and score matrices. **Mostafizur:** verify the results. |
| 5 | Verify Softmax and weighted-sum attention results | Mostafizur | **Deepak:** check Softmax and attention-weighted sum. **Turja:** provide golden outputs. **Mostafizur:** sign off on comparisons. |

**Expected result:** A shared repository and toolchain, a fixed 8-token × 16-feature one-head model configuration, and reference test data that checks Q/K/V projections, attention scores, Softmax and the attention-weighted sum.

**Suggested contributions:** Turja maintains the Python/NumPy golden reference and verification data; Deepak cross-checks attention arithmetic and results; Mostafizur coordinates repository setup and baseline tests.

**Member workspaces:** [Mostafizur](../weekly_work/week_01/mostafizur/README.md) · [Turja](../weekly_work/week_01/turja/README.md) · [Deepak](../weekly_work/week_01/deepak/README.md)

## Week 2 — Vitis HLS and Vivado Architecture

**Five checkpoints**

| ID | Checkpoint | Main lead | Named work assignment |
|---:|---|---|---|
| 6 | Run attention C simulation in Vitis HLS | Mostafizur | **Mostafizur:** run HLS C simulation. **Deepak:** prepare attention test cases. **Turja:** supply expected outputs. |
| 7 | Synthesize attention hardware and export the HLS IP | Mostafizur | **Mostafizur:** run HLS synthesis, inspect reports, and export IP. **Deepak:** review attention logic and verification logs. |
| 8 | Build MicroBlaze, AXI BRAM, clock, reset and UART in Vivado | Mostafizur | **Mostafizur:** create and validate the complete MicroBlaze block design. |
| 9 | Connect Transformer IP to AXI and validate the complete design | Mostafizur | **Mostafizur:** connect AXI/BRAM interfaces and address map. **Deepak:** check accelerator interface behavior. |
| 10 | Verify LayerNorm, residual connections and the 16–32–16 FFN | Mostafizur | **Turja:** implement/test the reference support functions. **Deepak:** check corner cases. **Mostafizur:** review HLS integration requirements. |

**Expected result:** Attention C simulation compared to golden outputs, an HLS synthesis/resource report and exported hardware IP (or documented blocker), a validated MicroBlaze/AXI BRAM block design, and software verification of Transformer support functions.

**Suggested contributions:** Deepak checks attention and HLS behavior. Turja supplies numerical results for LayerNorm, residual connections and the feed-forward network. Mostafizur owns HLS/Vivado integration.

**Member workspaces:** [Mostafizur](../weekly_work/week_02/mostafizur/README.md) · [Turja](../weekly_work/week_02/turja/README.md) · [Deepak](../weekly_work/week_02/deepak/README.md)

## Week 3 — Nexys A7 Testing and Transformer Integration

**Four checkpoints**

| ID | Checkpoint | Main lead | Named work assignment |
|---:|---|---|---|
| 11 | Generate the Vivado bitstream and matching Vitis platform | Mostafizur | **Mostafizur:** implement the design, meet timing where feasible, export XSA, and create the Vitis platform. |
| 12 | Write MicroBlaze code to load data, start IP and read output | Mostafizur | **Mostafizur:** write the MicroBlaze application and capture UART output. |
| 13 | Test attention on the Nexys A7 and compare against Python | Mostafizur | **Mostafizur:** run FPGA board tests. **Deepak:** debug attention discrepancies. **Turja:** compute the numerical error table. |
| 14 | Integrate the full Transformer in C++ and test HLS feasibility | Mostafizur | **Mostafizur:** integrate and test the full HLS top level. **Deepak:** supply attention core. **Turja:** supply LayerNorm/FFN reference behavior. |

**Expected result:** Implemented bitstream and matching XSA, a working MicroBlaze application, real-board attention results compared against Python, and a documented feasibility result for the full Transformer HLS design.

**Suggested contributions:** Turja checks Python-reference comparisons and full-model functions; Deepak performs independent attention validation; Mostafizur integrates the board design and firmware.

**Member workspaces:** [Mostafizur](../weekly_work/week_03/mostafizur/README.md) · [Turja](../weekly_work/week_03/turja/README.md) · [Deepak](../weekly_work/week_03/deepak/README.md)

## Week 4 — Optimization, Benchmarks and Final Delivery

**Four checkpoints**

| ID | Checkpoint | Main lead | Named work assignment |
|---:|---|---|---|
| 15 | Evaluate INT8/fixed-point attention with Python golden outputs | Mostafizur | **Deepak:** test quantized attention calculations. **Turja:** generate golden comparisons. **Mostafizur:** evaluate accelerator compatibility and accuracy. |
| 16 | Synthesize optimized hardware or document resource limits | Mostafizur | **Mostafizur:** run optimized synthesis and record resources/timing or blockers. **Deepak:** check attention correctness after optimization. |
| 17 | Measure CPU and FPGA latency and compare the results | Mostafizur | **Mostafizur:** run and report CPU/FPGA timing. **Turja:** compare numerical accuracy. **Deepak:** independently review test repeatability. |
| 18 | Finish GitHub README, report, slides and board demonstration | All | **Turja:** README, report, and slides. **Mostafizur:** Nexys A7 demonstration and benchmark evidence. **Deepak:** attention verification evidence and results. |

**Expected result:** Quantization accuracy evaluation, optimized synthesis or a clear resource limitation, repeatable CPU-versus-FPGA latency measurements, and final project documentation with real board evidence. If a hardware milestone fails, record the blocker instead of describing it as complete.

**Suggested contributions:** Deepak independently verifies optimized attention; Turja prepares accuracy comparisons and documentation; Mostafizur leads hardware benchmarking and the board demonstration. All members contribute to the final report.

**Member workspaces:** [Mostafizur](../weekly_work/week_04/mostafizur/README.md) · [Turja](../weekly_work/week_04/turja/README.md) · [Deepak](../weekly_work/week_04/deepak/README.md)

## Team Responsibilities

The following are the main responsibilities stated in the Excel **Instructions** worksheet. They describe technical areas of contribution; the **Main lead** assignments above reproduce the Excel task rows.

| Member | Main responsibility |
|---|---|
| **Md Mostafizur Rahman** | MicroBlaze, AXI BRAM, Vitis HLS top-level, Vivado, board demo and benchmarks |
| **Deepak** | Q/K/V projections, attention score calculation, Softmax, weighted sum and HLS verification |
| **Turja** | Python/NumPy reference, LayerNorm, FFN, residual connections and output verification |

Main lead assignment in Excel: Mostafizur for **16** checkpoints; **All** for checkpoints **2** and **18**. Individual contribution and completion credit are tracked separately in each member's status column.

## How to Update Weekly Progress

1. Open the shared [Weekly_Updates.xlsx](../tracking/Weekly_Updates.xlsx) workbook.
2. In **Weekly Checkpoints**, find the correct checkpoint **ID (1–18)**. Each person edits only their own status column.
3. Choose exactly one status: `Not started`, `In progress`, `I did it`, `I did it with teammate`, or `I failed to do it`.
4. If you select `I did it with teammate`, enter the collaborator in **Teammate Details**, using the matching checkpoint ID.
5. Add a repository link, simulation log, report or board-test evidence in **Proof needed to mark done** or the appropriate evidence notes/location. **Proof needed to mark done** specifies the evidence expected; it is not itself a submitted evidence record.
6. Review **Weekly Progress** for weekly completion counts. The tracker counts a checkpoint as finished when at least one member records a completed status; record real evidence for any claimed hardware success.
7. Keep detailed task evidence in the corresponding `weekly_work/week_0N/<member>/README.md` folder, where those folders are present.

**Status at the supplied workbook snapshot:** 2 of 18 checkpoints finished (IDs **1** and **2**), both in Week 1. The remaining 16 are open. This is a snapshot, not a live value embedded in the README.

## Repository Map

| Location | Purpose |
|---|---|
| [`weekly_work/`](../weekly_work/README.md) | Four weekly folders and member assignments |
| [`tracking/`](../tracking/README.md) | Weekly checkpoint workbook and progress records |
| [`hls/`](../hls/) | C++ attention and Transformer hardware source for Vitis HLS |
| [`reference/`](../reference/) | Python/NumPy golden model, input vectors and expected outputs |
| [`sim/`](../sim/) | C simulation and RTL co-simulation tests/results |
| [`integration/`](../integration/) | Vivado IP/AXI BRAM integration and MicroBlaze firmware |
| [`docs/`](../docs/) | Architecture, verification, hardware reports and final documentation |

**Implementation reminder:** The active tracker is for a Vitis HLS C++ FPGA accelerator integrated through Vivado and controlled using MicroBlaze/Vitis IDE. This is distinct from a pure VHDL RTL development plan. A successful Python or HLS C simulation does not by itself prove FPGA synthesis, timing closure or successful Nexys A7 board execution.
