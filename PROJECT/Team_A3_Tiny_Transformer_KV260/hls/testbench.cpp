#include "attention.h"
#include "transformer_layers.h"
#include "transformer_top.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

static bool load_file(const std::string& filename, float* values, int count) {
    std::ifstream in(filename.c_str());
    if (!in) { std::cerr << "Missing file: " << filename << "\n"; return false; }
    for (int i = 0; i < count; ++i)
        if (!(in >> values[i])) { std::cerr << "Invalid data in: " << filename << "\n"; return false; }
    float extra;
    if (in >> extra) { std::cerr << "Unexpected extra values in " << filename << "\n"; return false; }
    return true;
}

static bool check(const char* section, const float* actual, const float* expected, int n) {
    float max_error = 0.0f, max_relative_error = 0.0f;
    int failures = 0;
    for (int i = 0; i < n; ++i) {
        const float absolute_error = std::fabs(actual[i] - expected[i]);
        const float threshold = 2.0e-4f + 2.0e-4f * std::fabs(expected[i]);
        if (!std::isfinite(actual[i]) || absolute_error > threshold) ++failures;
        max_error = std::max(max_error, absolute_error);
        const float relative_error = absolute_error / std::max(1.0e-6f, std::fabs(expected[i]));
        max_relative_error = std::max(max_relative_error, relative_error);
    }
    std::cout << (failures ? "FAIL " : "PASS ") << section
              << " | max_abs_error=" << max_error
              << " | failed_elements=" << failures << '/' << n << '\n';
    return failures == 0;
}

int main(int argc, char** argv) {
    const std::string dir = (argc > 1) ? argv[1] : "data";
    float input[INPUT_COUNT], weights[WEIGHT_COUNT];
    float expected_ln1[INPUT_COUNT], expected_a[INPUT_COUNT];
    float expected_ln2[INPUT_COUNT], expected_ffn[INPUT_COUNT];
    float expected_final[INPUT_COUNT];
    if (!load_file(dir + "/input.txt", input, INPUT_COUNT) ||
        !load_file(dir + "/weights.txt", weights, WEIGHT_COUNT) ||
        !load_file(dir + "/expected_ln1.txt", expected_ln1, INPUT_COUNT) ||
        !load_file(dir + "/expected_attention.txt", expected_a, INPUT_COUNT) ||
        !load_file(dir + "/expected_ln2.txt", expected_ln2, INPUT_COUNT) ||
        !load_file(dir + "/expected_ffn.txt", expected_ffn, INPUT_COUNT) ||
        !load_file(dir + "/expected_output.txt", expected_final, INPUT_COUNT))
        return 2;

    float x[TOKENS][DIM];
    for (int i = 0; i < INPUT_COUNT; ++i) x[i / DIM][i % DIM] = input[i];

    float ln1[TOKENS][DIM], attn[TOKENS][DIM], r1[TOKENS][DIM];
    float ln2[TOKENS][DIM], ffn[TOKENS][DIM], result[INPUT_COUNT];
    layer_norm(x, &weights[LN1_GAMMA], &weights[LN1_BETA], ln1);
    bool pass = check("Turja: LayerNorm1", &ln1[0][0], expected_ln1, INPUT_COUNT);

    attention_block(ln1, weights, attn);
    pass &= check("Deepak: QKV/Attention/Softmax/Wo", &attn[0][0], expected_a, INPUT_COUNT);

    for (int t = 0; t < TOKENS; ++t)
        for (int j = 0; j < DIM; ++j)
            r1[t][j] = x[t][j] + attn[t][j];
    layer_norm(r1, &weights[LN2_GAMMA], &weights[LN2_BETA], ln2);
    pass &= check("Turja: LayerNorm2", &ln2[0][0], expected_ln2, INPUT_COUNT);
    feed_forward(ln2, weights, ffn);
    pass &= check("Turja: FFN", &ffn[0][0], expected_ffn, INPUT_COUNT);

    transformer_top(input, weights, result);
    pass &= check("Mostafizur: top-level transformer", result, expected_final, INPUT_COUNT);
    std::cout << (pass ? "\nALL SOFTWARE TESTS PASSED\n" : "\nCHECK FAILURES ABOVE\n");
    return pass ? 0 : 1;
}
