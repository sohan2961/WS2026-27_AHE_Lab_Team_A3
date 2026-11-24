# Hardware interface agreement (draft)

## Dot product (implemented)

- `clk`: rising-edge clock, target 100 MHz after timing closure.
- `rst`: synchronous active-high reset.
- `start`: one-cycle pulse while not busy. The DUT enters its collection state on that edge.
- `input_valid`: presents one pair of `a_data`, `b_data` per accepted rising edge while `busy=1`.
- `busy`: high while collecting pairs.
- `done`: one-cycle pulse on last accepted pair. `result` remains valid until another `start`/reset.
- Data: two's-complement signed INT8; 16-bit products; 32-bit accumulator.
- Overflow: two's-complement wrap for the accumulator. For VECTOR_LENGTH=16, full signed INT8 dot products fit in 32 bits.
- Latency: one start edge + 16 accepted pairs; gaps in input_valid add cycles.

## Integration decisions still open

Before connecting Transformer modules, agree on:

1. Per-layer quantization scales and zero points (or a common signed fixed-point format).
2. Rounding and saturation during layer-to-layer conversions.
3. Softmax approximation method and numerical error tolerance.
4. LayerNorm arithmetic and treatment of epsilon.
5. Shared 8×16 tensor memory layout and AXI register map.
6. Whether the accelerator controls BRAM addresses directly or receives streamed data.

Never silently treat integer dot-product results as normalized attention probabilities.
