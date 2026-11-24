# Week 02 — Self-attention hardware

**Goal:** Build and verify the attention datapath with a documented fixed-point approach. **Checkpoints:** W2-01 to W2-05 (5 total).

| Member | Assigned work | Deliverable |
|---|---|---|
| [Mostafizur](mostafizur/README.md) | Q/K/V, Q×Kᵀ scale, Softmax approximation, weighted sum with V | Simulated attention RTL |
| [Turja](turja/README.md) | Reference stage outputs and numeric accuracy criteria | FP32-to-fixed-point comparison report |
| [Deepak](deepak/README.md) | Cross-check approximations and edge cases; help Turja verify modules | Independent test vectors and review |

**Week acceptance:** All attention stages simulated and compared against Python with explicitly recorded tolerances, scaling and saturation rules. Do not treat the simple integer dot product as a complete Softmax implementation.
