#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
python3 reference/generate_vectors.py
mkdir -p build
g++ -std=c++11 -O2 -Wall -Wextra -Wno-unknown-pragmas \
    -Ihls hls/transformer_top.cpp hls/attention.cpp \
    hls/transformer_layers.cpp hls/testbench.cpp \
    -o build/team_a3_testbench
./build/team_a3_testbench data
