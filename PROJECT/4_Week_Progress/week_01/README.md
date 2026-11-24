# Week 1 — Setup, Python Reference and Attention Calculations

**Checkpoint IDs:** 1–5. **Final toolchain:** Vitis HLS C++ + Vivado 2025.1.

| ID | Exact checkpoint title | Main lead |
|---:|---|---|
| 1 | Set up GitHub and confirm Nexys A7 / Vivado / Vitis tools | Mostafizur |
| 2 | Agree on the 8-token, 16-feature, one-head model and test data | All |
| 3 | Run the full Python/NumPy reference model and tests | Mostafizur |
| 4 | Verify Q, K, V projections and Q × K transpose scores | Mostafizur |
| 5 | Verify Softmax and weighted-sum attention results | Mostafizur |

## Member workspaces

- [Mostafizur](mostafizur/README.md) — HLS hardware, Vivado/MicroBlaze integration and measurements.
- [Deepak](deepak/README.md) — attention calculations and independent verification.
- [Turja](turja/README.md) — Python reference, LayerNorm/FFN and numerical comparisons.

Use the [shared workbook](../../tracking/Weekly_Updates.xlsx) for statuses. A task is complete only with evidence.
