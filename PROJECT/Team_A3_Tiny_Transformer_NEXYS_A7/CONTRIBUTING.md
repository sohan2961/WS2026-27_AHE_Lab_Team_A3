# Contributing — Team A3

Three people work in parallel on **one common interface contract**. Please do not change array sizes, function signatures or weight layout without discussing the change with the others first. See [`config/INTERFACE_CONTRACT.md`](config/INTERFACE_CONTRACT.md).

## File ownership

| Member | Branch | Primary files |
|---|---|---|
| Md Mostafizur Rahman | `mostafizur/integration` | `hls/transformer_top.*`, `hls/testbench.cpp`, `scripts/run_hls.tcl`, `hls/attention_top.*`, MicroBlaze/AXI integration and benchmarks |
| Deepak | `deepak/attention` | `hls/attention.cpp`, `hls/attention.h` |
| Turja | `turja/reference-layers` | `reference/generate_vectors.py`, `hls/transformer_layers.*`, reference data |

## Start work

1. Clone the repository and open its root folder.
2. Install dependencies (`python -m pip install -r requirements.txt`; also install `g++` for host testing).
3. Run `bash scripts/run_host_test.sh` on Linux/WSL or `./scripts/run_host_test.ps1` in Windows PowerShell.
4. Create your own branch from `main`. For example: `git switch -c deepak/attention`.
5. Change your assigned files, then rerun the full host tests.
6. Commit with a meaningful message, push your branch and open a pull request against `main`.
7. Ask another team member to review before merging.

## Weekly verification

- **Week 1:** host-level unit tests pass on members' machines.
- **Week 2:** synthesize attention_top for Nexys A7-100T, review fit/timing, and attempt RTL co-simulation. Host tests alone do not meet this milestone.
- **Week 3:** record real Nexys A7 bitstream, MicroBlaze integration and numerical outputs.
- **Week 4:** collect measurements and produce the final report.

## Tracker rules

Each member updates only their own dropdown in `tracking/Team_A3_Nexys_A7_Checkpoints.xlsx`. The five options are `Not started`, `In progress`, `I did it`, `I did it with teammate`, `I failed to do it`. If collaborating, also select the helper in the **Teammate Details** worksheet. Do not mark hardware checkpoints done based on host tests.

Because an `.xlsx` file is binary, GitHub cannot merge conflicting edits made to separate copies. **Coordinate who edits the tracker and when**, or share one centrally editable master. Save Excel and close it before committing the workbook. Do not resolve binary merge conflicts by selecting one person's entire copy without reconciling their changes.

## Evidence

Commit or link small reproducible evidence files (for example, `.txt` summaries, resource figures, test results). Avoid committing generated Vivado/HLS project directories, giant binaries or personal credentials. Hardware reports and benchmarks must state their measurement environment.

## No performance claims without measurements

The starter code implements an **FP32 mathematical Transformer encoder block with fixed test weights**. We have validated host software only. Do not claim FPGA acceleration, a trained LLM or CPU/GPU speedups before performing the corresponding real tests.
