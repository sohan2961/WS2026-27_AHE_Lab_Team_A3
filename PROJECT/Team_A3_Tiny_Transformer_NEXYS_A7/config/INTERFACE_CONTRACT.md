# Team A3 — Interface Contract v2 (Nexys A7-100T)

**Frozen model parameters:** 8 tokens, dimension 16, 1 attention head, FFN width 32, one pre-norm encoder block. FP32 host baseline, fixed deterministic weights, row-major layout. No tokenizer or language generation.

- Input: `float input[128]` (8 × 16)
- Full weights: `float weights[2112]`, offsets unchanged from the original baseline
- Attention-only weights: **first 1024 floats** = Wq (0), Wk (256), Wv (512), Wo (768)
- Output: `float output[128]`
- Input for `attention_top` = `LayerNorm1(X)`, NOT raw X
- `attention_top` expected output = `data/expected_attention.txt`
- Attention dimensions: `Q,K,V ∈ R^{8×16}`, scores `8×8`, scaling `/4`
- Full encoder: `LN1(X) -> attention -> X+attention -> LN2 -> FFN -> residual`
- Epsilon = `1e-5`, activation = ReLU, no projection biases

## Hardware interface (first attention IP)

```cpp
void attention_top(const float input[128],
                   const float weights[1024],
                   float output[128]);
```

Vitis HLS creates AXI4-Lite `control` interface and AXI4 memory mapped `gmem` master. The host MicroBlaze and the HLS IP must share an AXI BRAM memory region via an interconnect. Do not assume the master sees a C pointer from a software virtual address.

BRAM region offsets (relative to controller base chosen in Vivado): `input = 0x0000`, `weights = 0x1000`, `output = 0x3000`. Allocate at least 16 KiB for shared data BRAM. Record actual base addresses and HLS-generated register map before writing drivers.

## Full encoder API (optional advanced milestone)

```cpp
void transformer_top(const float input[128],
                     const float weights[2112],
                     float output[128]);
```

All three members must approve changes to dimensions, weight offsets or interfaces. FPGA fit and timing are not yet verified.
