#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
ghdl -a --std=08 rtl/attention/dot_product.vhd
ghdl -a --std=08 sim/tb_dot_product.vhd
ghdl -e --std=08 tb_dot_product
ghdl -r --std=08 tb_dot_product --stop-time=250ns
