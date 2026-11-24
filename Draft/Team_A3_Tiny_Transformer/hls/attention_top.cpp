#include "attention_top.h"
#include "attention.h"

// One AXI4 memory-mapped master (gmem) for input/weights/output;
// one AXI4-Lite control port. Intended to access SHARED AXI BRAM, not DDR2.
// AXI BRAM controller and MicroBlaze are wired in Vivado, not in this file.
void attention_top(const float input[INPUT_COUNT],
                   const float weights[4 * DIM * DIM],
                   float output[INPUT_COUNT]) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem depth=128
#pragma HLS INTERFACE m_axi port=weights offset=slave bundle=gmem depth=1024
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem depth=128
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=weights bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    float x[TOKENS][DIM];
    // The attention function only addresses WQ,WK,WV,WO (first 1024 values).
    float w[4 * DIM * DIM];
    float y[TOKENS][DIM];
    for (int i = 0; i < INPUT_COUNT; ++i)
        x[i / DIM][i % DIM] = input[i];
    for (int i = 0; i < 4 * DIM * DIM; ++i)
        w[i] = weights[i];
    attention_block(x, w, y);
    for (int i = 0; i < INPUT_COUNT; ++i)
        output[i] = y[i / DIM][i % DIM];
}
