# Team A3 — Parallel assignments and acceptance gates

## Md Mostafizur Rahman: HLS system integration

**Owns:** `hls/transformer_top.*`, `hls/testbench.cpp`, `scripts/run_hls.tcl`, future Vivado block design and KV260 app.

**Days 1–2:** Freeze interface contract; set up repository; agree on one format of input/weights; install/run host test.

**Days 3–5:** Ensure top-level works with Turja and Deepak functions. Validate both residual paths, HLS top signature and AXI pragmas; review HLS script.

**Week 2:** Perform full `csim_design`, then `csynth_design` with Vitis HLS 2022.2. Record timing/resources; attempt `cosim_design`, resolve tool issues. Merge passing changes after review.

**Acceptance:** Top-level passes host test; after real Vitis run, C simulation passes and synthesis report is saved. The KV260 itself is not required until Week 3.

## Deepak: self-attention accelerator

**Owns:** `hls/attention.h`, `hls/attention.cpp`.

**Days 1–2:** Understand and verify Wq/Wk/Wv layout and Q/K/V projections.

**Days 3–5:** Test 8x8 scaled attention scores, stable row-wise Softmax, weighted V and Wo output. Check against `data/expected_attention.txt`.

**Week 2:** Run HLS C simulation and assist RTL cosim. Explore pipeline/partition pragmas only AFTER baseline passes; report any resource/latency effect.

**Acceptance:** `PASS Deepak: QKV/Attention/Softmax/Wo` on shared testbench and HLS simulation.

## Turja: reference model, LayerNorm, FFN

**Owns:** `reference/generate_vectors.py`, `hls/transformer_layers.h`, `hls/transformer_layers.cpp`.

**Days 1–2:** Generate 8x16 inputs, random-but-fixed FP32 weights and intermediate reference output files.

**Days 3–5:** Confirm LayerNorm uses variance over feature dimension and epsilon 1e-5; check FFN 16->32->16 ReLU; verify residual order.

**Week 2:** Run HLS C simulation of entire design and cross-check any output discrepancies; maintain numerical test vectors.

**Acceptance:** `PASS Turja: LayerNorm1`, `PASS Turja: LayerNorm2` and `PASS Turja: FFN`.

## Shared finish criteria

1. Everyone runs `scripts/run_host_test.sh` (or `.ps1` on Windows) and gets five PASS lines.
2. Every change keeps the interface contract stable and passes the common testbench.
3. Actual Vitis HLS `csim_design` is green on the team's tool machine.
4. Vitis HLS `csynth_design` completes and hardware utilization + timing are recorded.
5. RTL co-simulation is attempted and failures are documented; it is not equivalent to host simulation.
6. KV260 deployment/benchmark are Weeks 3–4, after this starter milestone.

## Suggested Git branches

- `mostafizur/integration`
- `deepak/attention`
- `turja/reference-layers`

Use pull requests; do not directly modify each other's owner files without coordination. Keep `data` test vectors under version control until every member is validated.
