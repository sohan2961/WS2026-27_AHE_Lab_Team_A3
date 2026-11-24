# Team A3 — Checkpoint Tracker README

> **Route notice (24 Nov 2026):** The included repaired 33-checkpoint spreadsheet was originally written for the **Vitis HLS** plan. It is retained unchanged to preserve your historical tracking and formulas. Do not treat HLS-specific tasks as completed VHDL tasks. Use `docs/VHDL_CHECKPOINTS.md` for the current VHDL schedule until the spreadsheet is intentionally revised with the whole team's agreement.

## Current VHDL tracker (new)

The primary workbook is now [`Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx`](Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx). It has:

- An **Overview** of 4 weeks and 18 checkpoints (4 + 5 + 5 + 4).
- **Week 1–4** sheets with each task's ID, lead, acceptance requirement, status dropdowns for all three members and an evidence/PR field.
- A **Checkpoint status** calculated from the lead's status and the evidence field. A lead marking `I did it` or `I did it with teammate` without evidence displays **Needs evidence**, not Complete.
- Team-member statuses initially `Not started`, since the new VHDL implementation tasks have not yet been verified.

Each member updates only their own status column. The checkpoint lead is responsible for an evidence link or reproducible test log. Keep one shared master copy or coordinate commits to avoid conflicts with this binary Excel file.

The instructions below describe the **older 33-checkpoint HLS workbook** and remain for reference.

**Project:** Tiny Transformer Inference Engine on Digilent Nexys A7-100T  
**Team:** Md Mostafizur Rahman · Deepak · Turja  
**Tracker file:** `Team_A3_Nexys_A7_Checkpoints.xlsx`  
**Version:** 16 November 2026 · repaired Excel workbook, simplified member tracking

## Purpose

This workbook is Team A3's shared progress record from project setup to the final Nexys A7 demonstration. It is **not** the implementation code. Each project checkpoint has **three separate dropdown cells**, one for each member, so each person records **their own contribution** to that checkpoint.

## Workbook sheets

| Sheet | What it contains | How to use it |
|---|---|---|
| **Team Checkpoints** | All **33** checkpoints in chronological order, three member dropdowns, and completion/failure counts | This is the main sheet to update |
| **Teammate Details** | Optional teammate name for each member and checkpoint | Fill this when selecting **I did it with teammate** |
| **Checkpoint Guide** | Lead person, what to do, and evidence / deliverable for every checkpoint | Read before selecting a completed status |
| **Project Roadmap** | Seven phases, checkpoint ranges, and the five status definitions | Use to understand the overall project sequence |

## Main sheet layout

- **Column A**, rows **11–43**: numbered project checkpoints **01–33**.
- **Column B**, rows **11–43**: **Md Mostafizur Rahman**.
- **Column C**, rows **11–43**: **Deepak**.
- **Column D**, rows **11–43**: **Turja**.
- **Row 7**: completion percentage for each member, calculated from their chosen completed statuses out of **all 33 checkpoints**.
- **Row 8**: count of checkpoints marked **I failed to do it**.

The percentage is a **participation count over all 33 checkpoints**, **not** a completion percentage of only a person's assigned tasks. For responsibility/ownership, see the **Checkpoint Guide** sheet.

## Exactly five dropdown options

| Dropdown text | Choose it when... |
|---|---|
| `Not started` | You have not begun that checkpoint. |
| `In progress` | You are currently working on it. |
| `I did it` | **You** completed the checkpoint yourself and can show its result. |
| `I did it with teammate` | You contributed to completing it together with another Team A3 member. Also complete **Teammate Details**. |
| `I failed to do it` | You attempted the checkpoint, but the attempt did not succeed. Record the blocker and retry as needed. |

**Important:** An existing code file or earlier baseline test does **not** mean you personally completed the task. Choose `I did it` only after you can demonstrate the result. Leaving a checkpoint as `Not started` is correct if you did not participate in it.

## How to update your checkpoint (example)

1. Open the repaired `.xlsx` file in Microsoft Excel and choose **Team Checkpoints**.
2. Find the checkpoint in column A (for example **14. Implement numerically stable Softmax in Vitis HLS**).
3. Choose **your own column**: B for Mostafizur, C for Deepak, D for Turja.
4. Select one of the five dropdown statuses in your cell.
5. If the status is `I did it with teammate`, open **Teammate Details** and select who helped on the **same checkpoint**. On this sheet, checkpoint 01 starts in **row 6**, not row 11.
6. Open **Checkpoint Guide** to check what the deliverable should look like. Save any test logs, screenshots, source commits, Vivado reports, or benchmark outputs in the project repository.
7. Revisit your status if a test fails or you make progress. One shared master workbook is preferable to multiple conflicting copies.

### Example of a shared task

For **23. Integrate the full Transformer in HLS C++ for software testing**, if Mostafizur and Deepak complete the work together:

- Mostafizur's cell: `I did it with teammate`.
- Deepak's cell: `I did it with teammate`.
- Turja's cell: their **actual** status, not automatically marked as completed.
- On **Teammate Details**, Mostafizur selects Deepak and Deepak selects Mostafizur for checkpoint 23.

## Project phases and leads

| Phase | Checkpoints | Primary lead | Expected outcome |
|---|---|---|---|
| 1. Project setup and architecture | **01–05** | Mostafizur / all | Shared repository, agreed configuration, architecture, tools and fixed inputs |
| 2. Python/NumPy reference | **06–10** | Turja | Numerical reference and expected stage outputs |
| 3. Self-attention hardware | **11–17** | Deepak | HLS Q/K/V, matrix operations, Softmax and tests |
| 4. Transformer support layers | **18–21** | Turja | HLS LayerNorm, FFN, residual logic and numerical checks |
| 5. HLS attention IP and optional full-encoder C tests | **22–26** | Mostafizur + team | Integrated HLS top, C simulation, synthesis, co-simulation / IP export |
| 6. Vivado and Nexys A7 | **27–31** | Mostafizur; Turja verifies outputs | MicroBlaze, AXI/shared BRAM, bitstream and verified on-board attention |
| 7. Results and presentation | **32–33** | Mostafizur + all | MicroBlaze vs FPGA measurements and final report/demo |

### Member roles

**Md Mostafizur Rahman — FPGA System Design & Integration**  
Design the Nexys A7 architecture; implement the top-level HLS interface; integrate IP with Vivado and AXI; deploy through MicroBlaze software; benchmark MicroBlaze against FPGA.  
**Deliverable:** Running Nexys A7 system and performance results.

**Deepak — Self-Attention Hardware Accelerator**  
Implement Q/K/V projections, matrix multiplication, scaled dot-product attention and Softmax; validate the attention block with Vitis HLS.  
**Deliverable:** Tested attention accelerator.

**Turja — Transformer Model & FFN Implementation**  
Build the Python/NumPy reference; implement HLS LayerNorm, FFN and residual operations; check numerical results.  
**Deliverable:** Reference model and tested Transformer support functions.

*Integration detail:* Turja develops/tests residual computations, while Mostafizur connects their skip paths in the top-level design.

## Technical baseline and quality gates

- Model: **1 pre-normalized Transformer encoder block**, **8 tokens**, **16 embedding dimensions**, **1 attention head**, **FFN 16→32→16**, **FP32 baseline**.
- The supplied starter project has recorded host-side software tests; **team-member reruns have not been verified**, and actual FPGA synthesis, RTL co-simulation, bitstream creation, hardware execution, and hardware benchmarking **are not yet verified**.
- A checked-off hardware checkpoint should have real proof such as a synthesis report, co-simulation log, Vivado design/bitstream, on-device output, or reproducible measurement.
- Compare FPGA output against the same fixed input and weights as the CPU/NumPy reference. Distinguish **compute-only** from **end-to-end** timing, including transfer overhead.

### Four-week suggested sequence

| Week | Shared milestone |
|---|---|
| **Week 1** | All three members can build and explain their own module; host software tests pass on team machines |
| **Week 2** | Nexys-targeted attention_top HLS C simulation and synthesis, review Artix-7 resource fit |
| **Week 3** | Vivado/AXI integration, Nexys A7 bitstream and one verified on-board inference |
| **Week 4** | MicroBlaze–FPGA comparison, evidence, final report and presentation |

These are targets, not automatic deadlines stored in the repaired workbook.

## Handling errors or failed checkpoints

- If a test fails, select `I failed to do it` for your own cell and tell the team what failed and which command/report shows the failure.
- Once work resumes, change to `In progress`; use `I did it` / `I did it with teammate` after you demonstrate a passing result.
- Do not overwrite another member's status without their agreement.
- Save evidence in version-controlled files or a shared team folder, since the tracker does not include an evidence-link column.
- If Excel offers to **repair** this workbook, avoid saving the repaired copy over the master; use the supplied `Team_A3_Nexys_A7_Checkpoints.xlsx`, and report the warning.

## Related documents

- `README.md` — the **main project README**, including setup, software testing, Vitis HLS commands and responsibilities.
- `TEAM_TASKS.md` — parallel development assignments and acceptance gates.
- `config/INTERFACE_CONTRACT.md` — shared dimensions, weights and function APIs. Review before changing any HLS interface.

**Team rule:** Each person updates only their own contribution, and a completed checkpoint means the member can demonstrate the result.

## GitHub teamwork

The project repository includes [`../CONTRIBUTING.md`](../CONTRIBUTING.md), the shared [GitHub publishing guide](../docs/GITHUB_SETUP.md), and an automatic host test workflow. Excel files are binary, so coordinate tracker edits to avoid merge conflicts.

## Nexys A7 implementation note

The **first physical FPGA milestone** is the standalone `attention_top` IP, using `m_axi` for arrays in shared on-chip BRAM and AXI4-Lite for MicroBlaze control. The full 8×16 FP32 Transformer is kept as a verified host-software reference and may require reduced-precision arithmetic before it fits the Artix-7. Do not mark the full Transformer as hardware-complete when only attention has run on the board.
