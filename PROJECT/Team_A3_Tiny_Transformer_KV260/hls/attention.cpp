#include "attention.h"
#include <cmath>

// Deepak's HLS attention unit: Q,K,V -> scaled score -> stable Softmax -> V -> Wo.
void attention_block(const float x[TOKENS][DIM],
                     const float weights[WEIGHT_COUNT],
                     float y[TOKENS][DIM]) {
#pragma HLS INLINE off
    float q[TOKENS][DIM];
    float k[TOKENS][DIM];
    float v[TOKENS][DIM];
    float probability[TOKENS][TOKENS];
    float context[TOKENS][DIM];

    // 3 independent 16x16 projections, using row-major weights [input][output].
    for (int t = 0; t < TOKENS; ++t) {
        for (int j = 0; j < DIM; ++j) {
            float qsum = 0.0f, ksum = 0.0f, vsum = 0.0f;
            for (int i = 0; i < DIM; ++i) {
                qsum += x[t][i] * weights[WQ + i*DIM + j];
                ksum += x[t][i] * weights[WK + i*DIM + j];
                vsum += x[t][i] * weights[WV + i*DIM + j];
            }
            q[t][j] = qsum;
            k[t][j] = ksum;
            v[t][j] = vsum;
        }
    }

    // Stable Softmax. Single head with d_k = 16, hence 1/sqrt(16) = 1/4.
    for (int t = 0; t < TOKENS; ++t) {
        float score[TOKENS];
        float max_score = -1.0e30f;
        for (int s = 0; s < TOKENS; ++s) {
            float dot = 0.0f;
            for (int i = 0; i < DIM; ++i)
                dot += q[t][i] * k[s][i];
            score[s] = dot * 0.25f;
            if (score[s] > max_score) max_score = score[s];
        }
        float denominator = 0.0f;
        for (int s = 0; s < TOKENS; ++s) {
            float e = std::exp(score[s] - max_score);
            probability[t][s] = e;
            denominator += e;
        }
        for (int s = 0; s < TOKENS; ++s)
            probability[t][s] /= denominator;
    }

    // Weighted sum of values.
    for (int t = 0; t < TOKENS; ++t) {
        for (int i = 0; i < DIM; ++i) {
            float sum = 0.0f;
            for (int s = 0; s < TOKENS; ++s)
                sum += probability[t][s] * v[s][i];
            context[t][i] = sum;
        }
    }

    // Output linear projection Wo.
    for (int t = 0; t < TOKENS; ++t) {
        for (int j = 0; j < DIM; ++j) {
            float sum = 0.0f;
            for (int i = 0; i < DIM; ++i)
                sum += context[t][i] * weights[WO + i*DIM + j];
            y[t][j] = sum;
        }
    }
}
