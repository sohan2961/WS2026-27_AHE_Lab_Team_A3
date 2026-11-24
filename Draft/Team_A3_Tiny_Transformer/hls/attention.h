#pragma once
#include "transformer_config.h"

// Owner: Deepak. Computes projected multi-head (single-head here) attention.
void attention_block(const float x[TOKENS][DIM],
                     const float weights[WEIGHT_COUNT],
                     float y[TOKENS][DIM]);
