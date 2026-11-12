# Team A3 — Tiny Transformer Inference Engine on AMD Kria KV260

**Owners:** Md Mostafizur Rahman (integration); Deepak (attention); Turja (reference/LayerNorm/FFN).

This package contains a **complete deterministic FP32 software implementation** of one pre-normalized Transformer encoder block, with Vitis HLS-compatible C++ function boundaries. The baseline is intentionally unoptimized. FPGA synthesis, RTL simulation and actual KV260 deployment have **not** been run in this package.

## Architecture

```text
Input embeddings X[8][16]  (128 floats)
          |
       LayerNorm 1                 Turja
          |
  Q/K/V projections               Deepak
          |
 scaled self-attention + Softmax  Deepak
          |
     Wo output projection         Deepak
          |
    Add residual with X           Mostafizur
          |
       LayerNorm 2                Turja
          |
    FFN 16 -> 32 -> 16            Turja
          |
   Add second residual            Mostafizur
          |
Output embeddings Y[8][16]
          |
 AXI m_axi + AXI-Lite top        Mostafizur
```

LayerNorm2 acts on the first residual output; it is a **pre-norm** design. Residual skip connections are present in code.

## Run host validation (no FPGA required)

Prerequisites: Python 3 with NumPy and a C++11 compiler such as GCC/g++.

### Linux / WSL

```bash
cd Team_A3_Tiny_Transformer_KV260
bash scripts/run_host_test.sh
```

### Windows PowerShell

```powershell
cd Team_A3_Tiny_Transformer_KV260
.\scripts\run_host_test.ps1
```

Expected: five PASS lines for Turja's two LayerNorm checks + FFN, Deepak's attention and Mostafizur's integrated top, ending `ALL SOFTWARE TESTS PASSED`.

## Vitis HLS 2022.2 (Week 2)

**Use a Windows/Linux machine where Vitis HLS 2022.2 is installed and on PATH.** Run the above reference generator first, then:

```bash
vitis_hls -f scripts/run_hls.tcl
```

The script selects the K26 commercial FPGA part `xck26-sfvc784-2LV-c`, a 10 ns target and a Vivado IP flow. It attempts **C simulation followed by C synthesis**. It does NOT automatically claim the synthesis will pass and does NOT automatically run RTL cosimulation. Uncomment cosim/export only after verifying results. If your installed KV260 board file expects a different compatible part suffix, check your exact board/package.

Vitis HLS runs test vectors from a normalized absolute path derived from the repository `data/` folder.

## Files

- `config/INTERFACE_CONTRACT.md`: agreed dimensions, weight offsets and C++ APIs.
- `reference/generate_vectors.py`: Turja's independent NumPy reference and test vector generator.
- `hls/attention.*`: Deepak's HLS attention block.
- `hls/transformer_layers.*`: Turja's LayerNorm and FFN HLS code.
- `hls/transformer_top.*`: Mostafizur's AXI-enabled wrapper + residuals.
- `hls/testbench.cpp`: component and system level verification.
- `TEAM_TASKS.md`: day-by-day parallel team plan.
- `docs/KV260_INTEGRATION_NOT_YET_DONE.md`: Weeks 3–4 board integration caveats.

## Team checkpoint tracker — start to finish

The project also has a shared **33-checkpoint Excel tracker** for Md Mostafizur Rahman, Deepak and Turja:

- **Workbook:** [`tracking/Team_A3_Final_Start_to_Finish_Checkpoints_FIXED.xlsx`](tracking/Team_A3_Final_Start_to_Finish_Checkpoints_FIXED.xlsx)
- **Tracker instructions:** [`tracking/README.md`](tracking/README.md)

The workbook keeps the original four worksheets: **Team Checkpoints**, **Teammate Details**, **Checkpoint Guide** and **Project Roadmap**. Its five dropdown statuses are **Not started**, **In progress**, **I did it**, **I did it with teammate** and **I failed to do it**.

Each person updates their own status column. If two or more people completed a checkpoint together, select `I did it with teammate` and name the partner(s) on **Teammate Details**. Use **Checkpoint Guide** to check the lead, completion criteria and expected proof.

The seven stages run from setup (01–05), reference modeling (06–10), attention HLS (11–17), Transformer layers (18–21), full-system HLS (22–26), KV260 deployment (27–31), to benchmarking and reporting (32–33).

**Progress interpretation:** The percentages on the tracker are per-person counts of tasks marked done, **not** a validated end-to-end hardware completion metric. Host software test success does not imply HLS synthesis, RTL simulation or a working KV260 deployment. Preserve actual testing evidence for each completed milestone.

## Limits of this milestone

- This is a mathematical/inference kernel with fixed random test weights, **not** a trained language model or token predictor.
- No training, tokenizer, causal mask or KV cache is implemented.
- Direct `m_axi` buffers are not the same as AXI-Stream + DMA. A correct driver and physically suitable memory buffers are needed on PetaLinux.
- FP32 exponential/division/square-root operations can be expensive on FPGA. Optimization comes after synthesis and correctness.
- Hardware is NOT claimed to outperform CPU; benchmark after real KV260 execution.
