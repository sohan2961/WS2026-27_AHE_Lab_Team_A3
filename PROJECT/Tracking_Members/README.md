# Team A3 — Four-week checkpoint tracker

**Final workflow:** Vitis HLS C++ + Vivado 2025.1 + Vitis software IDE for MicroBlaze. **Target:** Nexys A7-100T (`xc7a100tcsg324-1`).

The authoritative tracker is [`Weekly_Updates.xlsx`](Weekly_Updates.xlsx), with **18 checkpoints in 4 weeks** and 3 separate member status columns. [`CHECKPOINTS_18.md`](CHECKPOINTS_18.md) expands the same exact 18 titles into named responsibilities and expected results. The titles must never be edited in one file without editing and verifying the other.

## Workbook tabs

| Sheet | Purpose |
|---|---|
| **Weekly Checkpoints** | IDs 1–18, exact checkpoint names, main lead, per-member status, evidence needed, overall status |
| **Weekly Progress** | Automatically calculated summary per week and for the whole team |
| **Teammate Details** | Collaborator names and evidence notes for the same checkpoint ID |
| **Instructions** | Status definitions and responsibilities |

## How to update it

1. Open `Weekly_Updates.xlsx` → **Weekly Checkpoints**.
2. Find the task by **ID**, not by an approximate task description.
3. Change **only your own** status: column E (Mostafizur), F (Deepak) or G (Turja).
4. Choose one of `Not started`, `In progress`, `I did it`, `I did it with teammate`, `I failed to do it`.
5. If you worked together, fill the corresponding collaborator field in **Teammate Details** for that same ID.
6. Add genuine evidence: host test log, HLS C/RTL co-simulation output, synthesis/resource report, exported IP, validated Vivado design, bitstream/XSA, UART output, or benchmark. The *Proof needed to mark done* field specifies what is required; it does **not** mean that proof has been submitted.
7. Put your evidence and short work notes in `weekly_work/week_0N/<member>/`.

## Week and ID map

| Week | IDs | Theme |
|---|---|---|
| Week 1 | 1–5 | Setup, Python reference, attention calculations |
| Week 2 | 6–10 | HLS simulation/synthesis, AXI and MicroBlaze design, FFN verification |
| Week 3 | 11–14 | Bitstream, firmware, FPGA test, full Transformer feasibility |
| Week 4 | 15–18 | Quantization, optimization, benchmarking and final delivery |

**Snapshot preserved from the supplied workbook:** IDs **1 and 2** are marked done by Mostafizur, and ID **4** is in progress. The remaining tasks are open. We did not mark additional hardware accomplishments merely because files or scripts already exist.

## Keep titles synchronized

From the repository root, run:

```bash
python3 scripts/check_checkpoint_sync.py
```

The script checks that the 18 checkpoint titles and IDs in `CHECKPOINTS_18.md`, all weekly overviews and member workspaces exactly match the `.xlsx` file, and that the four weekly groups contain 5, 5, 4 and 4 checkpoints. It requires only Python 3 standard-library modules.

The main system integration is described in [`../docs/NEXYS_A7_BRINGUP.md`](../docs/NEXYS_A7_BRINGUP.md). Team ownership is in [`../TEAM_TASKS.md`](../TEAM_TASKS.md).
