# FPGA system integration

**Final workflow:** build the attention accelerator in Vitis HLS C++, package the resulting AXI IP, integrate in Vivado 2025.1, then write MicroBlaze software in Vitis IDE.

- [`vivado/`](vivado/) contains the planned hardware block design, BRAM address-space checklist and bitstream/XSA evidence list.
- [`microblaze/`](microblaze/) explains the firmware interface and test procedure. Firmware cannot be compiled until the Vivado hardware address map and generated HLS driver names are known.

**State:** The archive includes source code and a bring-up plan, not a validated Vivado project or synthesized bitstream. Keep the tracker accurate.
