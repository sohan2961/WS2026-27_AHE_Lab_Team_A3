# Vivado 2025.1 system design — Nexys A7-100T

Owner: **Md Mostafizur Rahman**. Target part: `xc7a100tcsg324-1`.

## After successful HLS synthesis

1. In Vitis HLS, confirm resource use and synthesize/export `attention_top` as **Vivado IP**, not an XRT/Vitis accelerator kernel. Use `-flow_target vivado` in the HLS script.
2. Create a Vivado RTL project for the Nexys A7-100T, set the correct board/part and constraints.
3. Build MicroBlaze, processor/program BRAM, UART Lite, AXI interconnect, 100 MHz clock and reset, and a **separate shared data BRAM** with AXI BRAM Controller.
4. Add the generated HLS IP to IP Catalog. Connect its `s_axi_control` to the MicroBlaze AXI address space, and its AXI `m_axi_gmem` master to the shared data BRAM via suitable AXI interconnect/SmartConnect.
5. Verify that MicroBlaze can access the shared data BRAM too. Check BRAM controller port arbitration, address widths, offsets, interrupt/handshake requirements, and the complete address map.
6. Validate the block design, run synthesis and implementation, inspect constraints and timing, and only then export **bitstream + XSA** for Vitis IDE.
7. Record Vivado utilization (LUT, FF, BRAM, DSP), achieved timing, a block-design screenshot, and hardware addresses here. Never enter values from estimates as measured results.

The HLS `gmem` master uses physical addresses in the MicroBlaze/AXI system, while `s_axi_control` sets those addresses. The *planned* shared-BRAM offsets in the top-level README are **not verified base addresses**.

## Needed outputs (not yet generated)

- Vivado project sources or a reproducible Tcl block-design script
- Packaged `attention_top` IP and synthesis report
- Validated address map and constraints
- Bitstream, XSA, and resource/timing reports

Reference: [AMD UG1399 — Vitis HLS](https://docs.amd.com/r/2025.1-English/ug1399-vitis-hls) and [AMD UG1579 — MicroBlaze Embedded Design](https://docs.amd.com/r/2025.1-English/ug1579-microblaze-embedded-design).
