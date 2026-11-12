#include "transformer_top.h"
#include "attention.h"
#include "transformer_layers.h"

// Minimal ARM-controllable Vivado HLS IP with direct AXI memory-mapped masters.
// No AXI DMA is required for this m_axi version; software must provide valid
// physically addressable buffers and perform appropriate cache maintenance.
void transformer_top(const float input[INPUT_COUNT],
                     const float weights[WEIGHT_COUNT],
                     float output[INPUT_COUNT]) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem depth=128
#pragma HLS INTERFACE m_axi port=weights offset=slave bundle=gmem depth=2112
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem depth=128
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=weights bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    float x[TOKENS][DIM];
    float local_weights[WEIGHT_COUNT];
    float n1[TOKENS][DIM], a[TOKENS][DIM];
    float r1[TOKENS][DIM], n2[TOKENS][DIM];
    float f[TOKENS][DIM];

    // AXI loads: sequential bursts can be inferred from flat accesses.
    for (int index = 0; index < INPUT_COUNT; ++index)
        x[index / DIM][index % DIM] = input[index];
    for (int index = 0; index < WEIGHT_COUNT; ++index)
        local_weights[index] = weights[index];

    layer_norm(x, &local_weights[LN1_GAMMA], &local_weights[LN1_BETA], n1);
    attention_block(n1, local_weights, a);

    // Attention residual: r1 = x + attention(LN1(x)).
    for (int t = 0; t < TOKENS; ++t)
        for (int j = 0; j < DIM; ++j)
            r1[t][j] = x[t][j] + a[t][j];

    layer_norm(r1, &local_weights[LN2_GAMMA], &local_weights[LN2_BETA], n2);
    feed_forward(n2, local_weights, f);

    // FFN residual: out = r1 + FFN(LN2(r1)).
    for (int index = 0; index < INPUT_COUNT; ++index) {
        int t = index / DIM, j = index % DIM;
        output[index] = r1[t][j] + f[t][j];
    }
}
