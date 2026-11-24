# Team A3 — Nexys A7 Hardware and Transformer Architecture

## First hardware milestone: attention-only

```text
    PC reference/test vectors
             |
         USB-UART
             |
+-------------- Nexys A7-100T (Artix-7) ----------------+
| MicroBlaze soft CPU -------- AXI UART Lite            |
|     |                                                   |
|     +--- AXI4-Lite ----> attention_top HLS IP          |
|     |                         | AXI4 m_axi             |
|     |                         v                         |
|     +-----> AXI interconnect / AXI BRAM Controller      |
|                               |                         |
|                      Shared data BRAM                   |
|                   input / weights / output              |
|     (Separate MicroBlaze local instruction/data BRAM)  |
+---------------------------------------------------------+
```

The first HLS IP computes `attention(LN1(X), Wq,Wk,Wv,Wo)`. It does **not** include LayerNorm, FFN or residuals in the hardware milestone. The NumPy reference supplies the normalized input to test the attention IP in isolation.

**Important:** Drawn as a design target, **not a verified completed Vivado block design**. Use a 100 MHz clock target and check tool timing reports. The FPGA has no ARM processor; MicroBlaze is implemented in its fabric.

## Later full Transformer milestone

```text
  X[8][16] ----> LN1 ------> Q / K / V ------> Q*K^T/4
      |                                         |
      |                                      Softmax
      |                                         |
      |                                      weights * V
      |                                         |
      |                                      Wo output
      |                                         |
      +-------------------------------> residual add R1
                                                |
                                               LN2
                                                |
                                          FFN 16-32-16
                                                |
            R1 ------------------------------> residual add
                                                |
                                           Y[8][16]
```

In this **pre-norm encoder**, the first residual is `R1 = X + Attention(LN1(X))` and the output is `Y = R1 + FFN(LN2(R1))`. The exact software calculation is in `hls/transformer_top.cpp` and `reference/generate_vectors.py`.

## BRAM memory map proposal

- Controller base address assigned in Vivado: **TBD**, no assumed absolute address
- `+0x0000`: 128 floats input, 512 B
- `+0x1000`: 1024 floats attention weights, 4 KiB
- `+0x3000`: 128 floats output, 512 B
- Allocate at least 16 KiB shared data BRAM; MicroBlaze executable memory separate

FPGA resource fit, clock closure, AXI connectivity and on-board output are **not yet verified**. Use [the editable Word architecture](architecture/Team_A3_Nexys_A7_Editable_Architecture.docx) for your report.
