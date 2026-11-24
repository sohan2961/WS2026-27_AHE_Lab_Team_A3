#include "transformer_layers.h"
#include <cmath>

// Turja's per-token layer normalization, with learned gamma and beta.
void layer_norm(const float x[TOKENS][DIM],
                const float gamma[DIM], const float beta[DIM],
                float y[TOKENS][DIM]) {
#pragma HLS INLINE off
    for (int t = 0; t < TOKENS; ++t) {
        float mean = 0.0f;
        for (int i = 0; i < DIM; ++i) mean += x[t][i];
        mean /= static_cast<float>(DIM);
        float variance = 0.0f;
        for (int i = 0; i < DIM; ++i) {
            const float difference = x[t][i] - mean;
            variance += difference * difference;
        }
        variance /= static_cast<float>(DIM);
        const float inv_std = 1.0f / std::sqrt(variance + LAYER_NORM_EPS);
        for (int i = 0; i < DIM; ++i)
            y[t][i] = ((x[t][i] - mean) * inv_std) * gamma[i] + beta[i];
    }
}

// Turja's 2-layer feed forward network: 16 -> 32 (ReLU) -> 16.
void feed_forward(const float x[TOKENS][DIM],
                  const float weights[WEIGHT_COUNT],
                  float y[TOKENS][DIM]) {
#pragma HLS INLINE off
    float hidden[TOKENS][FF_DIM];
    for (int t = 0; t < TOKENS; ++t) {
        for (int h = 0; h < FF_DIM; ++h) {
            float sum = 0.0f;
            for (int i = 0; i < DIM; ++i)
                sum += x[t][i] * weights[W1 + i*FF_DIM + h];
            hidden[t][h] = (sum > 0.0f) ? sum : 0.0f;
        }
    }
    for (int t = 0; t < TOKENS; ++t) {
        for (int j = 0; j < DIM; ++j) {
            float sum = 0.0f;
            for (int h = 0; h < FF_DIM; ++h)
                sum += hidden[t][h] * weights[W2 + h*DIM + j];
            y[t][j] = sum;
        }
    }
}
