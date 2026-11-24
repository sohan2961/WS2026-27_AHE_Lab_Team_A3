# Team A3 — Tiny Transformer Inference Engine on Nexys A7-100T

> **Project direction updated 24 November 2026:** The active FPGA implementation is now **VHDL RTL in Vivado 2025.1**, with MicroBlaze software later built in Vitis IDE. All existing `hls/` C++ sources, scripts, test vectors, and host test results are preserved as a **software/HLS reference baseline**, not the required hardware implementation route. Start with [`docs/VHDL_MIGRATION_PLAN.md`](docs/VHDL_MIGRATION_PLAN.md) and [`docs/VHDL_CHECKPOINTS.md`](docs/VHDL_CHECKPOINTS.md). The sections below document the original HLS-based plan and should not be mistaken for the active route.

## Current team kickoff — VHDL route

**[Open the four weekly GitHub workspaces](weekly_work/README.md)** — Every week has individual folders for Mostafizur, Turja and Deepak, with responsibilities, deliverables and evidence instructions.

**[Active VHDL Excel checkpoint tracker](tracking/Team_A3_VHDL_4_Week_18_Checkpoint_Tracker.xlsx)** — 18 checkpoints organized in four weekly worksheets, with status dropdowns for each member, lead-based completion, evidence and an automatically updating Overview. The previous 33-checkpoint HLS workbook remains available for historical reference.

| Member | Active assignment | First contribution |
|---|---|---|
| **Md Mostafizur Rahman** | VHDL self-attention accelerator, top-level Vivado/AXI/MicroBlaze integration and testing | Run `sim/tb_dot_product.vhd`, then build Q×Kᵀ matrix control |
| **Turja** | Python/NumPy reference, LayerNorm/FFN/residual support, documentation | Define golden vectors and staged output tests |
| **Deepak** | Work alongside Turja on LayerNorm/FFN support and independent verification | Add boundary/negative-number test cases and layer test vectors |

The existing FP32 host tests were run successfully on 24 November 2026. The first VHDL RTL testbench is supplied but **has not yet been run in Vivado or GHDL** in this version. The FPGA system is not built yet.

### Start now

1. Create a Vivado 2025.1 RTL project targeting `xc7a100tcsg324-1`.
2. Add `rtl/attention/dot_product.vhd` and set `sim/tb_dot_product.vhd` as the simulation top.
3. Run Behavioral Simulation and look for `PASS: dot product = 16`.
4. Run `python3 reference/check_dot_product.py` to verify the same short vector in software.
5. Keep the established FP32 baseline: `bash scripts/run_host_test.sh && bash scripts/run_host_attention.sh`.

This version keeps `config/INTERFACE_CONTRACT.md` for **FP32 reference semantics**, and `config/VHDL_DOT_PRODUCT_INTERFACE.md` for the **new INT8 RTL prototype**. These two numeric formats are not interchangeable without explicit quantization.

---

**Target:** Digilent Nexys A7-100T, `xc7a100tcsg324-1`, Vivado / Vitis HLS / Vitis **2025.1**.  
**Members:** Md Mostafizur Rahman (FPGA and MicroBlaze integration); Deepak (attention); Turja (Transformer reference, LayerNorm, FFN).

> **Status (16 November 2026):** Deterministic NumPy/C++ host tests pass for the full FP32 encoder and new attention-only wrapper. No Nexys A7 HLS synthesis report, Vivado bitstream, MicroBlaze runtime or hardware measurement has been obtained yet.

## Start here

Run from this repository root in a terminal with Python 3 + NumPy + g++:

```bash
python3 -m pip install -r requirements.txt
bash scripts/run_host_test.sh           # full software Transformer, 5 component checks
bash scripts/run_host_attention.sh      # Nexys attention-only top
```

Windows PowerShell (with Python, NumPy and g++ on PATH):

```powershell
python -m pip install -r requirements.txt
.\scripts\run_host_test.ps1
.\scripts\run_host_attention.ps1
```

**First FPGA task:** Launch Vitis HLS 2025.1 from the project root and run:

```bash
vitis_hls -f scripts/run_hls.tcl
```

This targets **attention_top**, part `xc7a100tcsg324-1`, requested clock **10 ns (100 MHz)**, and attempts **C simulation plus C synthesis**. The target clock is a constraint, not an achieved timing measurement. Open the generated HLS reports to verify DSP, LUT, BRAM and timing estimates.

**Later full encoder C simulation:**

```bash
vitis_hls -f scripts/run_hls_full.tcl
```

The full FP32 engine **does not automatically synthesize**. To attempt it after checking attention resource use, set `TEAM_A3_FULL_SYNTH=1` in the environment before launching the full Tcl script. If it does not fit, move to fixed-point or reduce workload.

## Two milestones: do not confuse them

| Milestone | Algorithm | Current status |
|---|---|---|
| **A — first FPGA bring-up** | Q/K/V → scaled attention → stable Softmax → weighted V → Wo (8×16) | Host verified; **HLS/board unverified** |
| **B — full Tiny Transformer encoder** | LN1 → attention → residual → LN2 → FFN (16→32→16) → residual | Host verified; **FP32 HLS/board unverified** |

Both use one attention head, sequence length 8 and embedding dimension 16. These are fixed test-vector inference kernels, **not a trained LLM**.

## Nexys A7 hardware design

```text
                  Windows PC
         Python reference / serial terminal
                          |
                       USB-UART
                          |
+----------------- Nexys A7-100T -----------------------+
|        MicroBlaze (processor in FPGA fabric)         |
|               | AXI4-Lite (control)                 |
|               v                                      |
|       HLS attention_top control registers            |
|               | AXI4 m_axi (data)                    |
|               v                                      |
|    AXI interconnect -> AXI BRAM Controller           |
|                         |                             |
|            Shared Block RAM:                         |
|          input + weights + output                    |
+-------------------------------------------------------+
```

No ARM CPU, PetaLinux, DPU, DDR2 controller, AXI DMA or external RAM is required for the **first attention-only demonstration**. Shared BRAM is **a design proposal, not a verified Vivado block design**. The MicroBlaze application will write the arrays, program HLS AXI-Lite pointer offsets, start the IP, read output, and send results over UART.

**Planned BRAM layout** (offsets relative to the AXI BRAM controller base address; check the actual address map in Vivado):

| Area | Offset | Floats | Bytes |
|---|---:|---:|---:|
| Normalized input LN1(X) | `0x0000` | 128 | 512 |
| Attention weights Wq/Wk/Wv/Wo | `0x1000` | 1,024 | 4,096 |
| Attention output | `0x3000` | 128 | 512 |

Allocate **at least 16 KiB** of shared data BRAM and check actual available space; the above regions do not overlap. Keep MicroBlaze program/instruction memory separate during first bring-up. A shared AXI4 BRAM controller should permit both MicroBlaze and the HLS `m_axi` master to access the same data region through interconnect arbitration.

See [`docs/NEXYS_A7_BRINGUP.md`](docs/NEXYS_A7_BRINGUP.md) and [`docs/architecture.md`](docs/architecture.md).

## Team ownership

| Member | Responsibility | Deliverable |
|---|---|---|
| **Md Mostafizur Rahman** | Top-level HLS IP, Nexys A7 Vivado system, MicroBlaze and AXI/BRAM, board deployment, MicroBlaze vs FPGA benchmarking | Tested board demo and measured performance |
| **Deepak** | Q/K/V projections, matrix multiplication, scaled dot-product attention, Softmax, value weighting, output projection | Synthesizable attention block + numerical checks |
| **Turja** | NumPy reference, two LayerNorms, FFN, residuals, expected test vectors, board output validation | Correct reference and Transformer layer functions |

See [`TEAM_TASKS.md`](TEAM_TASKS.md), [`CONTRIBUTING.md`](CONTRIBUTING.md), and the original HLS [Excel checkpoints](tracking/Team_A3_Nexys_A7_4_Week_Checkpoint_Tracker_REPAIRED.xlsx) ([instructions](tracking/README.md)). The active VHDL schedule is in [`docs/VHDL_CHECKPOINTS.md`](docs/VHDL_CHECKPOINTS.md).

## Important files

- `hls/attention_top.{h,cpp}` — **first FPGA IP**, AXI memory master + AXI-Lite controls (Mostafizur)
- `hls/attention.{h,cpp}` — Q/K/V, Softmax, weighted sum and Wo (Deepak)
- `hls/transformer_layers.{h,cpp}` — LayerNorm and FFN (Turja)
- `hls/transformer_top.{h,cpp}` — optional full FP32 encoder (Mostafizur)
- `hls/attention_testbench.cpp` — attention-only host / HLS test
- `hls/testbench.cpp` — 5-stage full encoder validation
- `reference/generate_vectors.py`, `data/` — deterministic NumPy golden outputs (Turja)
- `scripts/run_hls.tcl` — first FPGA synthesis flow, Nexys Artix-7 part
- `scripts/run_hls_full.tcl` — full encoder C simulation; synthesis opt-in
- `docs/architecture.md` — diagrams and residual skip-path explanation
- `docs/NEXYS_A7_BRINGUP.md` — numbered Vivado and MicroBlaze integration checklist
- `tracking/Team_A3_Nexys_A7_4_Week_Checkpoint_Tracker_REPAIRED.xlsx` — original HLS-era member tracker, preserved

## Constraints and honest scope

- FP32 `exp`, `sqrt` and divide operations may be expensive; no FPGA resource fit or timing closure is claimed.
- The `m_axi` and `s_axilite` buses must actually be connected in Vivado. C tests **do not** check interconnect wiring.
- This first design uses BRAM rather than board DDR2; DDR2 can be considered after the small demonstration works.
- Compare **MicroBlaze software-only computation vs accelerated computation on the same board** if practical. Otherwise label any PC vs FPGA comparison as cross-platform and do not call it a fair speedup.
- The HLS-generated AXI-Lite driver/register offsets and Vivado address map must be checked before writing the MicroBlaze runtime.
- GitHub Actions runs host software tests only; it does not run licensed FPGA tools or access the board.

## Publish

See [`docs/GITHUB_SETUP.md`](docs/GITHUB_SETUP.md) for creating a **new** repository named `team-a3-tiny-transformer-nexys-a7`, or use Git to update an existing team repository after review. No online repository is created by this ZIP.
