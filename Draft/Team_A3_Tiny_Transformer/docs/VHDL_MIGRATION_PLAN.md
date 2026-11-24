# Team A3 — VHDL implementation plan

## Why the repository contains both `hls/` and `rtl/`

The original project in the uploaded ZIP implements a functioning *FP32 host-reference* Transformer encoder in C++ and NumPy. Its HLS source was written for an earlier Vitis HLS implementation route. That code and its existing tests are preserved, unchanged, as the numerical contract and a possible comparison baseline.

**The team selected a VHDL RTL hardware route for the Nexys A7.** The new `rtl/` directory is the hardware source of truth. Vitis HLS is *not required*. Vitis IDE is recommended later for the MicroBlaze test application.

## Model behavior we must preserve

- 8 tokens, 16 features per token, 1 head, hidden FFN size 32, 1 encoder block.
- Q/K/V and output projections without biases, row-major weights.
- Attention score scale: `1/sqrt(16) = 1/4`.
- Numerically stable Softmax row by row.
- Pre-LayerNorm and two residual connections.
- FFN activation: ReLU; LayerNorm epsilon `1e-5`.
- Reference files: `config/INTERFACE_CONTRACT.md`, `reference/generate_vectors.py`, `data/expected_*.txt`.

The existing reference is FP32. The supplied VHDL module uses **INT8 integer dot products** as a *starting exercise*; it is not expected to reproduce the FP32 attention output on its own. Define quantization, rescaling, clipping, and acceptable errors before comparing entire layers.

## Implementation sequence

1. **First arithmetic block** — signed 16-element dot product (`rtl/attention/dot_product.vhd`), one MAC per accepted cycle. Run `sim/tb_dot_product.vhd` in Vivado. Pure-Python check: `python3 reference/check_dot_product.py`.
2. **Q×Kᵀ matrix control** — schedule 64 dot products, map Q and K addresses, store an 8×8 result.
3. **Projections and scale** — implement all four 16×16 projection matrices; define fixed-point scales and saturation.
4. **Softmax** — choose and document a feasible approximation (e.g. lookup table with max-subtraction, fixed-point denominator and reciprocal); show error against NumPy.
5. **Weighted sum, output projection** — produce 8×16 attention output.
6. **Transformer block** — integrate two LayerNorms, residual additions, and FFN 16→32→16 with Turja/Deepak's reference vectors.
7. **MicroBlaze** — create AXI-Lite status/control and a BRAM-based input/weight/output mechanism; implement bare-metal Vitis application.
8. **Hardware validation** — obtain real synthesis utilization, timing closure, bitstream, UART results and latency measurements.

## Clear ownership

| Member | Active work | Deliverable |
|---|---|---|
| Mostafizur | VHDL self-attention, arithmetic/memory control, AXI and MicroBlaze system, verification | Integrated RTL and Nexys A7 hardware evidence |
| Turja | Python reference, FFN/LayerNorm/residual arithmetic, documentation | Golden vectors and verified support functions |
| Deepak | Assist Turja, build independent numerical tests, help prepare FFN/LayerNorm RTL or specs | Shared support modules and reproducible tests |

## PR quality gate

Every new VHDL module should have a deterministic testbench. A reviewer should check signal widths, clock/reset, latency, valid handshakes, edge cases and golden-reference comparison before merging.

## Evidence and limitations

- **Verified** on 24 November 2026: original FP32 host full-Transformer test suite and attention-only host test suite passed; new Python dot-product reference passed.
- **Not verified yet**: VHDL behavioral simulation in Vivado/GHDL; FPGA synthesis/fit; AXI system; bitstream; board execution; FPGA performance.
- The existing 33-row Excel tracker is HLS-specific; it has been preserved. The new 18-point VHDL schedule is `docs/VHDL_CHECKPOINTS.md`.
- This is a **tiny Transformer encoder demonstration**, not a trained generative LLM.
