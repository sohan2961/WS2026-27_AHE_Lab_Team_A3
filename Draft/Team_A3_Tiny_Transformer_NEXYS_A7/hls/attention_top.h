#pragma once
#include "transformer_config.h"
// Nexys A7 first hardware milestone: attention sublayer only.
// The input is LN1(X), not the raw embedding X; reference is data/expected_attention.txt.
void attention_top(const float input[INPUT_COUNT],
                   const float weights[4 * DIM * DIM],
                   float output[INPUT_COUNT]);
