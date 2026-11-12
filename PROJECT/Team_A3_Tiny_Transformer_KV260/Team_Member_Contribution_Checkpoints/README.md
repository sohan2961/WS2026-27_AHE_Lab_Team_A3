# Team A3 — Start-to-Finish Checkpoint Tracker

**Project:** Tiny Transformer Inference Engine on AMD Kria KV260  
**Team:** Md Mostafizur Rahman, Deepak, Turja  
**Workbook:** [`Team_A3_Final_Start_to_Finish_Checkpoints_FIXED.xlsx`](Team_A3_Final_Start_to_Finish_Checkpoints_FIXED.xlsx)  
**Project source:** See the main [`README.md`](../README.md).

## Purpose

The Excel workbook is a shared, **33-checkpoint project progress tracker**. It follows the project from setting up the repository and preparing reference inputs through building the HLS accelerator, integrating it into the KV260, benchmarking and reporting.

It records **each person's involvement separately**, rather than forcing one status for the whole team. It does not replace the source code, testing evidence, review process or technical reports.

## How to use the workbook

Open the workbook in Microsoft Excel and use its four existing tabs:

| Worksheet | What it contains | What to do |
|---|---|---|
| **Team Checkpoints** | 33 chronological tasks; one status column for each team member | Select your own status from the dropdown in your column (rows 11–43). |
| **Teammate Details** | The same 33 tasks and a partner selector for each member | When you select **I did it with teammate**, identify the partner(s) on the matching task row. |
| **Checkpoint Guide** | Lead person, plain-language acceptance criteria and suggested proof for all 33 tasks | Read the corresponding row before marking a task complete. |
| **Project Roadmap** | Seven stages and their checkpoint ranges | Use this to see what phase comes next. |

### The five exact status options

| Dropdown selection | Meaning |
|---|---|
| **Not started** | You have not begun this checkpoint. |
| **In progress** | You are currently working on it; acceptance criteria are not yet fully met. |
| **I did it** | You completed your own work for the checkpoint and can show evidence. |
| **I did it with teammate** | You completed the work jointly; name your collaborator(s) on **Teammate Details**. |
| **I failed to do it** | Your attempt was unsuccessful or blocked; document what failed, and retry later if appropriate. |

**Important:** Do not mark `I did it` merely because an earlier starter package exists or someone else ran a software test. Use the criteria in **Checkpoint Guide** and preserve the relevant code, output, log, screenshot, report or pull request. The sheet does not automatically verify proof or peer approval.

### Where to enter your status

| Member | Team Checkpoints | Teammate Details |
|---|---|---|
| **Md Mostafizur Rahman** | Column **B**, rows **11–43** | Column **B**, rows **6–38** |
| **Deepak** | Column **C**, rows **11–43** | Column **C**, rows **6–38** |
| **Turja** | Column **D**, rows **11–43** | Column **D**, rows **6–38** |

The same numbered task appears on all relevant tabs; use the **checkpoint number** to match rows, as the row numbers differ between tabs.

For example, if Deepak and Turja jointly complete the attention HLS verification checkpoint (17), they can each choose `I did it with teammate` in their own status cell, then select each other on the corresponding row in **Teammate Details**. Each member should only claim work that they actually performed.

## How progress totals work

At the top of **Team Checkpoints**:

- **Row 7 — Done checkpoints (% of all project tasks):** The percentage of the 33 tasks where an individual marked `I did it` or `I did it with teammate`.
- **Row 8 — Failed checkpoints:** How many tasks that individual marked `I failed to do it`.

These are **per-member involvement figures**, not a verified project completion percentage. If several teammates worked on the same task, it may count toward each person's percentage. Therefore the three percentages **must not be added together**. They also do not prove the corresponding FPGA hardware was tested.

Keep task statuses honest and, if a failed task is later completed, update its status accordingly.

## Work division

| Team member | Main responsibilities | Expected deliverables |
|---|---|---|
| **Md Mostafizur Rahman** | KV260 architecture; top-level Transformer HLS interface and module integration; AXI/Vivado system; ARM deployment; CPU-versus-FPGA benchmarking | Integrated HLS top, Vivado design and bitstream/XSA, KV260 application, benchmark comparison |
| **Deepak** | Q, K and V projections; matrix multiplication; scaled dot-product attention; Softmax; weighted sum and output projection; attention HLS checks | Tested C++/HLS attention accelerator and verification results |
| **Turja** | Python/NumPy model; deterministic inputs and weights; LayerNorm; residuals/FFN support; numerical comparisons | Reference vectors and outputs, tested Transformer layer functions, accuracy comparison |

All members assist with shared interfaces, testing, review and the final submission. The **Checkpoint Guide** names the lead for each specific checkpoint.

## Seven project stages

| Stage | Checkpoints | Expected result |
|---|---|---|
| 1. Setup and architecture | **01–05** | Shared repository, architecture and test inputs |
| 2. Software reference | **06–10** | Working deterministic NumPy Transformer baseline |
| 3. Attention accelerator | **11–17** | HLS attention implementation and verification |
| 4. Transformer layers | **18–21** | LayerNorm, residuals and FFN implementation/tests |
| 5. Top-level HLS | **22–26** | Integrated design, C simulation, synthesis, co-simulation/export |
| 6. FPGA deployment | **27–31** | Vivado/AXI integration, bitstream, KV260 execution and output checks |
| 7. Evaluation and reporting | **32–33** | CPU-versus-FPGA benchmarks and final project submission |

### Suggested evidence for key acceptance gates

- **Checkpoint 10:** Saved per-stage NumPy expected outputs.
- **Checkpoint 17:** Attention testbench and Vitis HLS verification log.
- **Checkpoint 21:** LayerNorm/FFN output comparison with reference and error/tolerance results.
- **Checkpoints 24–26:** Complete-model C simulation, synthesis reports, RTL co-simulation and exported IP evidence.
- **Checkpoints 27–31:** Vivado block design, clock/address map, bitstream/XSA, ARM application run, board output comparison.
- **Checkpoint 32:** Same test configuration for CPU and FPGA, measured latency/throughput and clear methodology.
- **Checkpoint 33:** Final report, source code and presentation.

Store evidence in your project repository (commits, pull requests, `benchmarks/`, reports or a suitably named `results/` folder). Enter the actual proof in your team review records. The provided workbook has **no dedicated evidence input column**, so it should not be treated as proof by itself.

## Technical baseline and boundaries

The starter design uses **one pre-LayerNorm Transformer encoder block**, with **8 tokens**, **16 features**, **one attention head**, **FFN width 32** and **FP32** arithmetic. Inputs/weights are deterministic for testing. This is not a trained LLM and does not yet include a tokenizer, causal inference, or KV cache.

The earlier package may contain passed **host software** checks, but these are different from Vitis HLS C simulation, C synthesis, RTL co-simulation, successful KV260 deployment and measured hardware benchmarking. Each milestone needs its own actual evidence.

## Practical team workflow

1. Open **Project Roadmap** to identify the active stage.
2. Read your checkpoint's **Checkpoint Guide** row.
3. Do the implementation/test on your assigned branch; save evidence.
4. Update **your own** status in **Team Checkpoints**.
5. For shared completion, update **Teammate Details** on the matching task.
6. At the team review, compare statuses against evidence and agree on the next checkpoints.

**Change policy:** Update status cells and partner selections as work progresses. Keep the 33 numbered checkpoint labels and their ordering consistent across all tabs. The fixed workbook is preserved without layout changes in this package.
