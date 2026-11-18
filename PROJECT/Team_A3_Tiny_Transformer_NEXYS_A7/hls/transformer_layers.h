#pragma once
#include "transformer_config.h"

// Owner: Turja.
void layer_norm(const float x[TOKENS][DIM],
                const float gamma[DIM], const float beta[DIM],
                float y[TOKENS][DIM]);

void feed_forward(const float x[TOKENS][DIM],
                  const float weights[WEIGHT_COUNT],
                  float y[TOKENS][DIM]);
