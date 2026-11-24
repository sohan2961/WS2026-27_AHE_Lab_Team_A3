# Nexys A7-100T Bring-Up Checklist (Team A3)

**Hardware:** Nexys A7-100T, part `xc7a100tcsg324-1`; **Tools:** Vivado/Vitis/Vitis HLS 2025.1. This is a plan; no board build has yet been verified.

## Gate A — software and HLS (begin here)

1. Run `bash scripts/run_host_test.sh` and `bash scripts/run_host_attention.sh` (or the `.ps1` counterparts); save PASS logs.
2. Open a Vitis HLS 2025.1 command prompt in the repo root and run `vitis_hls -f scripts/run_hls.tcl`.
3. Confirm C simulation PASS. Check `csynth_design` report for `attention_top`: LUT, FF, DSP, BRAM, latency and achieved clock estimate; resolve synthesis failures before proceeding.
4. Once synthesis succeeds, uncomment RTL co-simulation and IP export in `scripts/run_hls.tcl` and rerun. Keep the exported IP repository path.
5. **If FP32 synthesis does not fit or meet timing:** record the failing report; try a smaller fixed-point attention kernel next. Do not claim successful hardware inference.

## Gate B — Vivado block design

1. Create an RTL project for part `xc7a100tcsg324-1` (use part selection if board file isn't installed).
2. Add MicroBlaze, MicroBlaze Debug Module, local BRAM/memory controller, AXI UART Lite, Clocking Wizard (if needed), reset, AXI interconnect and AXI BRAM Controller + shared Block Memory Generator.
3. Add the exported HLS IP to the IP repository. Connect `s_axi_control` to MicroBlaze AXI master via an interconnect; HLS `m_axi_gmem` to AXI BRAM Controller AXI slave via an interconnect/SmartConnect that supports **two masters**.
4. Wire same clock/reset consistently. Resolve all validation warnings. Use Vivado Address Editor to assign and record the **actual** AXI BRAM Controller and HLS control base addresses.
5. Reserve at least 16 KiB shared BRAM (data) for test vectors and **separate** local BRAM for MicroBlaze code/stack. The HLS input/weights/output pointers must be passed as **physical AXI addresses** visible to the IP master.
6. Add Nexys A7-100T 100 MHz and UART constraints from Digilent's correct **master XDC for your board revision**; do not invent pin names. Clock pin `E3` is commonly used but confirm the official XDC.
7. Generate bitstream, check timing closure and export XSA (include bitstream).

## Gate C — Vitis standalone MicroBlaze app

1. Create a Vitis 2025.1 platform from your **new** XSA, target standalone MicroBlaze. Do **not** use a KV260 ARM or PetaLinux BSP.
2. Create app that loads 128 normalized floats, 1024 weights, and reserves output buffer at the planned shared BRAM offsets.
3. Verify the generated `xattention_top.h`/`xattention_top_hw.h` driver API or control register addresses. Write **actual AXI memory addresses** to `input`, `weights`, `output` pointer registers via the generated driver; do not guess hard-coded offsets.
4. Start accelerator, poll completion/status, read back 128 output floats, print comparison summary through UART.
5. Compare output to `data/expected_attention.txt` (Turja's golden values). Confirm acceptable numerical tolerance and save console log.

## Gate D — Expand after first board success

1. Try `vitis_hls -f scripts/run_hls_full.tcl` (C simulation only). Only attempt full synthesis after FP32 attention resource analysis.
2. If full design exceeds Artix-7 capacity, experiment with `ap_fixed` precision and update the software reference/test tolerance accordingly.
3. Benchmark MicroBlaze software-only attention against FPGA accelerator on the **same board** where possible, reporting CPU cycles, FPGA cycles and transfer overhead separately.

## Stop points / important caveats

- Host C++ test PASS is not FPGA C simulation PASS, synthesis, bitstream, or board verification.
- AXI4-Lite registers control the accelerator; they cannot hold all weights. Shared BRAM + `m_axi` serves tensor data.
- Avoid starting with DDR2 MIG or AXI DMA for this small first milestone.
- All board connections and register offsets require validation in your generated Vivado/Vitis design.
