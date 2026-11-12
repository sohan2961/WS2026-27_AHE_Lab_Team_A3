# Team A3: frozen module interface contract (v1)

**Do not change dimensions, weights, tensor layout or function signatures without a three-person review.**

- Tokens `TOKENS = 8`
- Embedding dimensions `DIM = 16`
- Attention heads `HEADS = 1`
- FFN hidden dimension `FF_DIM = 32`
- Floating point `float` (FP32), row-major arrays
- Single **pre-layer-norm** Transformer encoder block
- Matrix multiply uses `output[t][o] = sum_i input[t][i] * weight[i * output_size + o]`
- No projection biases, activation is ReLU, layer norm epsilon is `1e-5`
- Weights are deterministic for tests. This is **not** a trained language model.

## Flat 2,112-element weights array

| Start | Length | Item | Shape |
|---:|---:|---|---|
| 0 | 256 | Wq | 16 x 16 |
| 256 | 256 | Wk | 16 x 16 |
| 512 | 256 | Wv | 16 x 16 |
| 768 | 256 | Wo | 16 x 16 |
| 1024 | 512 | W1 | 16 x 32 |
| 1536 | 512 | W2 | 32 x 16 |
| 2048 | 16 | LN1 gamma | 16 |
| 2064 | 16 | LN1 beta | 16 |
| 2080 | 16 | LN2 gamma | 16 |
| 2096 | 16 | LN2 beta | 16 |

## Module APIs

`void layer_norm(const float x[8][16], const float gamma[16], const float beta[16], float y[8][16]);` (Turja)

`void feed_forward(const float x[8][16], const float weights[2112], float y[8][16]);` (Turja)

`void attention_block(const float x[8][16], const float weights[2112], float y[8][16]);` (Deepak)

`void transformer_top(const float input[128], const float weights[2112], float output[128]);` (Md Mostafizur Rahman)

## Dataflow

`LN1(input) -> attention -> residual with input -> LN2 -> FFN -> residual with previous residual -> output`

**Important:** LayerNorm is PRE attention, and LayerNorm2 is PRE FFN. Neither is applied after the second residual. Attention output projection is included in `attention_block`.

## Team acceptance gates

- **Week 1:** Python generates input/weights/reference outputs. Each member can build and run the host test.
- **Week 2:** C simulation passes all four gates (LayerNorm, attention, FFN, complete top). Vitis HLS C synthesis and RTL co-simulation must be run on a machine with Vitis HLS 2022.2 before claiming FPGA validation.
- **Weeks 3–4:** Integrate exported IP into a separate KV260 design, boot it, and benchmark. No hardware deployment is included in this starter package.
