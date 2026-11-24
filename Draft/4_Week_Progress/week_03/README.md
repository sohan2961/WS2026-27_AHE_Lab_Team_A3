# Week 03 — Transformer and MicroBlaze integration

**Goal:** Connect attention, residual, LayerNorm and FFN and develop the AXI/BRAM MicroBlaze interface. **Checkpoints:** W3-01 to W3-05 (5 total).

| Member | Assigned work | Deliverable |
|---|---|---|
| [Mostafizur](mostafizur/README.md) | Top-level VHDL, MicroBlaze block design, AXI/BRAM and Vitis test app | Simulated hardware/software integration |
| [Turja](turja/README.md) | LayerNorm/FFN/residual reference arithmetic and docs | Verified support functions / stage outputs |
| [Deepak](deepak/README.md) | Work with Turja on support modules and integration tests | Additional VHDL/testbench support |

**Week acceptance:** Top-level interface and memory map documented; integrated test compares stage outputs against reference. A generated IP wrapper or AXI block design is not automatically a working bitstream.
