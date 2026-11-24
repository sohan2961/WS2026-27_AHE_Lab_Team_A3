#include "attention_top.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
static bool read_floats(const std::string &name, float *a, int count) {
    std::ifstream f(name.c_str());
    if (!f) { std::cerr << "Cannot open " << name << "\n"; return false; }
    for (int i = 0; i < count; i++)
        if (!(f >> a[i])) { std::cerr << "Bad data " << name << "\n"; return false; }
    return true;
}
int main(int argc, char** argv) {
    const std::string dir = argc > 1 ? argv[1] : "data";
    float ln1[INPUT_COUNT], weights[4 * DIM * DIM], expected[INPUT_COUNT], actual[INPUT_COUNT];
    if (!read_floats(dir+"/expected_ln1.txt", ln1, INPUT_COUNT) ||
        !read_floats(dir+"/weights.txt", weights, 4 * DIM * DIM) ||
        !read_floats(dir+"/expected_attention.txt", expected, INPUT_COUNT)) return 2;
    attention_top(ln1, weights, actual);
    int failed=0; float max_error=0;
    for (int i=0;i<INPUT_COUNT;i++) {
        float e=std::fabs(actual[i]-expected[i]);
        if (!std::isfinite(actual[i]) || e>2.0e-4f+2.0e-4f*std::fabs(expected[i])) failed++;
        max_error=std::max(e,max_error);
    }
    std::cout << (failed ? "FAIL" : "PASS")
              << " Nexys attention_top (8x16); failed=" << failed
              << "; max_abs_error=" << max_error << "\n";
    return failed ? 1 : 0;
}
