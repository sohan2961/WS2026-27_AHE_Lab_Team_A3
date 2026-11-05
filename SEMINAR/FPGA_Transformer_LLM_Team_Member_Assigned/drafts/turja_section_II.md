# Turja — Section II: Transformer Workload and Memory Demands

**Owner:** Turja  
**IEEE section:** II  
**Reviewer:** Deepak  
**Status:** Outline and prompts for research; not a completed verified section.

## A. Attention and compute pattern

Explain $Q=XW_Q$, $K=XW_K$, $V=XW_V$ and scaled dot-product attention. Clarify dimensions, softmax, and causal masking. Cite original Transformer sources; avoid copying their wording.

**Notes / draft:**

[Add verified explanation]

## B. Prefill versus decode

Compare dense prompt processing (greater parallelism) with sequential token generation (memory/weight reuse). Specify when KV-cache reads dominate and how batch size matters.

**Notes / draft:**

[Add verified explanation]

## C. KV cache, MHA/MQA/GQA

Derive $M_{KV}=2 L B S H_{KV} d_h b$ with variables defined. Calculate examples for the same L, B, S, d_h and precision; **state derived rather than measured**.

| Configuration | KV heads | Assumptions | Derived cache size | Source for architecture |
| --- | --- | --- | --- | --- |
| MHA | | | | |
| GQA | | | | |
| MQA | | | | |

## D. Bottlenecks, figures and handoff

Explain compute-bound vs bandwidth-bound operation, and propose an original attention/KV-cache figure.

**Sources to check:** `vaswani2017`, `shazeer2019`, `ainslie2023`, `dao2022`, `dao2024`, `kwon2023`, `williams2009`.

**Questions to ask Mostafizur / Deepak:**
- Which KV-cache storage strategy will Section III describe?
- Which benchmark contexts/batch sizes are reported in Section IV?
