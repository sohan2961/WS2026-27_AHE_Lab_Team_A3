#pragma once

// Shared by ALL three team members. Row-major, fixed dimensions.
static const int TOKENS = 8;
static const int DIM = 16;
static const int FF_DIM = 32;
static const int INPUT_COUNT = TOKENS * DIM;
static const int WEIGHT_COUNT = 2112;
static const int WQ = 0;
static const int WK = WQ + DIM*DIM;
static const int WV = WK + DIM*DIM;
static const int WO = WV + DIM*DIM;
static const int W1 = WO + DIM*DIM;
static const int W2 = W1 + DIM*FF_DIM;
static const int LN1_GAMMA = W2 + FF_DIM*DIM;
static const int LN1_BETA = LN1_GAMMA + DIM;
static const int LN2_GAMMA = LN1_BETA + DIM;
static const int LN2_BETA = LN2_GAMMA + DIM;
static const float LAYER_NORM_EPS = 1.0e-5f;
