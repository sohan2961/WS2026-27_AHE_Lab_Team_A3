# Week 01 — Foundation and reference

**Goal:** Get a first VHDL arithmetic module simulated and establish the correct mathematical reference. **Checkpoints:** W1-01 to W1-04 (4 total).

| Member | Assigned work | Deliverable |
|---|---|---|
| [Mostafizur](mostafizur/README.md) | Nexys A7 Vivado project, dot-product RTL test, begin 8×8 score matrix controller | Simulation pass and RTL source |
| [Turja](turja/README.md) | Run full Python/NumPy reference; record shapes and deterministic expected outputs | Verified golden vectors and description |
| [Deepak](deepak/README.md) | Independent dot-product and attention arithmetic test vectors; support Turja | Test cases and independent checks |

**Week acceptance:** W1-02 testbench produces `PASS: dot product = 16`; Q×Kᵀ controller has its own numerical test before W1-03 is marked complete; NumPy baseline results reproducible. This is simulation only, not a bitstream.
