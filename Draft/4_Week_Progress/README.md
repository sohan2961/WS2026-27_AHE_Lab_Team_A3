# Team A3 — Four-week GitHub workspaces

This folder provides **one week folder and three member folders per week**, following the active **VHDL / Nexys A7** plan. All weeks are initially **not started**; check tasks only after evidence exists.

| Week | Main goal | Workspaces |
|---|---|---|
| [Week 01](week_01/README.md) | Dot product, Q×Kᵀ foundations and reference | [Mostafizur](week_01/mostafizur/README.md) · [Turja](week_01/turja/README.md) · [Deepak](week_01/deepak/README.md) |
| [Week 02](week_02/README.md) | Q/K/V, scaled attention, Softmax, output verification | [Mostafizur](week_02/mostafizur/README.md) · [Turja](week_02/turja/README.md) · [Deepak](week_02/deepak/README.md) |
| [Week 03](week_03/README.md) | Transformer block, MicroBlaze, AXI/BRAM | [Mostafizur](week_03/mostafizur/README.md) · [Turja](week_03/turja/README.md) · [Deepak](week_03/deepak/README.md) |
| [Week 04](week_04/README.md) | Bitstream, board test, benchmark, documentation | [Mostafizur](week_04/mostafizur/README.md) · [Turja](week_04/turja/README.md) · [Deepak](week_04/deepak/README.md) |

## How to collaborate

1. Each member creates their own Git branch: `mostafizur/attention-rtl`, `turja/reference-ffn`, or `deepak/verification`.
2. Read your weekly `README.md`. Work in the **canonical** `rtl/`, `sim/`, `reference/`, `integration/`, and `docs/` directories listed there; **do not make duplicate working copies** in weekly folders.
3. Update only your own weekly `README.md` checkboxes and notes. Put reproducible small logs, figures or test summaries in your member folder if useful; link to real implementation files or a PR.
4. Open a pull request against `main`; have a teammate review it. Merge only when the week's acceptance criteria are met.
5. Use [`docs/VHDL_CHECKPOINTS.md`](../docs/VHDL_CHECKPOINTS.md) as the canonical **18-checkpoint** project tracker. Member tasks below describe contributions to those checkpoints; they are **not extra checkpoints**.

The active Excel tracker is [`tracking/Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx`](../tracking/Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx). It has an **Overview** plus **Week 1, Week 2, Week 3 and Week 4** worksheets. Each member changes only their own dropdown status; the checkpoint lead adds evidence before the tracker counts it complete. Coordinate Excel edits to avoid binary Git merge conflicts.

## Evidence convention

For each finished item record: commit/PR, test command, observed result, expected result, and any remaining limitation. Do not check boxes for work that only exists as a plan. An HLS host test passing is not evidence that VHDL is verified on the FPGA.

**Original project preserved:** `hls/`, `data/`, `tracking/` and original architecture documents remain in the repository. The 33-item Excel tracker is the earlier HLS plan and is not silently rewritten.
