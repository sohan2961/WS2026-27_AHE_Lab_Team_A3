#pragma once
#include "transformer_config.h"

// Owner: Md Mostafizur Rahman.
// m_axi input/weights/output are separate 32-bit float DDR buffers.
void transformer_top(const float input[INPUT_COUNT],
                     const float weights[WEIGHT_COUNT],
                     float output[INPUT_COUNT]);
