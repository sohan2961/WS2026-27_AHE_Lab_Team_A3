# Mostafizur — Week 02

**Owner:** Md Mostafizur Rahman · **Branch:** `mostafizur/attention-rtl`

- [ ] W2-01 — Implement 16×16 fixed-weight Q/K/V projections and test them.
- [ ] W2-02 — Scale 8×8 attention scores by `1/sqrt(16) = 1/4` in a documented numeric format.
- [ ] W2-03 — Design numerically stable, hardware-friendly row-wise Softmax approximation; test its error.
- [ ] W2-04 — Implement weighted sum with V, plus output projection if included in this RTL stage.
- [ ] W2-05 — Compare full attention RTL results against Turja's Python reference.

**Canonical files:** `rtl/attention/`, `sim/`, `config/`, `docs/`.

**Acceptance:** Simulation tests pass with stated precision, clock latency and valid handshakes; no FPGA resource/timing claims yet.

**Evidence / PR:** Not started. Add stage test results and numeric error here as work completes.
