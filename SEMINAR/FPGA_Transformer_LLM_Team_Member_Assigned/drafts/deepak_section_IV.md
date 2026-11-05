# Deepak — Section IV: Comparative Evaluation

**Owner:** Deepak  
**IEEE section:** IV  
**Reviewer:** Mostafizur Rahman  
**Status:** Outline and prompts for research; not a completed verified section.

## A. Define fair comparisons

Define tokens/s, time to first token (TTFT), time per output token (TPOT), total-system power (W), and energy per generated token (J/token). Explain measurement boundaries, batching and context length.

**Notes / draft:**

[Add verified definitions]

## B. Evidence table

Use `data/benchmark_evidence_template.csv` or copy it and populate from papers. Every numerical claim must have an exact source page/table/figure.

| Study | FPGA | GPU baseline | Model/precision/batch | Reported metric | Evidence location | Measurement type |
| --- | --- | --- | --- | --- | --- | --- |
| FlightLLM | | | | | | |
| EdgeLLM | | | | | | |

Do not treat the table rows as one directly matched benchmark unless the studies actually use equivalent conditions.

## C. Interpretation and limitations

Analyze differences in models, token lengths, batch size, quantization, hardware capacity, power measurement and runtime support. Tie results to the hardware choices in Section III and memory limits in Section II.

## D. Edge vs. data-center implications

Provide conditions under which low-latency small-device inference might be feasible; contrast with batch throughput, capacity and scalability requirements.

**Sources to check:** `zeng2024`, `huang2025`, `blankestijn2026`, `nvidiaA100`.

**Questions for teammates:**
- Can Turja supply a transparent KV-cache calculation for the compared context lengths?
- Can Mostafizur verify FPGA memory type/capacity and whether figures are theoretical or measured?
