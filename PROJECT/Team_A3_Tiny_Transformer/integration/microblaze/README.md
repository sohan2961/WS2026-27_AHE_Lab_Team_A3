# MicroBlaze software — Vitis IDE 2025.1

Owner: **Md Mostafizur Rahman**. Build the application only after exporting a validated Vivado hardware XSA and checking the generated HLS control-register driver.

## Minimal first-board test

1. Create a standalone MicroBlaze platform from the Vivado XSA.
2. Create a C application and include the actual generated `xparameters.h` and the HLS IP driver, using the names present in the platform rather than guessing them.
3. Copy the **128 FP32 input samples** and **1,024 FP32 attention weights** into the correct shared-BRAM physical address ranges, with enough space for the **128 FP32 outputs**.
4. Program the HLS AXI4-Lite control registers with the physical addresses for input, weights, and output. Flush/invalidate caches as necessary for this MicroBlaze configuration.
5. Start the accelerator, poll its completion status, read the output buffer, and print selected results over UART.
6. Compare output values to `data/expected_attention.txt` and the host attention C test. Record numerical error and test conditions.
7. When correct, time repeated inference (including/excluding transfer separately) and report exact board clock and build settings.

**Do not invent register offsets:** the final `xattention_top` driver API, base addresses and BRAM layout depend on HLS export and Vivado implementation.

### Evidence checklist

- [ ] XSA/platform name and Vivado build ID
- [ ] UART log showing start/finish and real output values
- [ ] Numerical comparison with Python golden output
- [ ] Repeated latency measurements and methodology

**Not yet supplied:** firmware source, validated platform and real board output. The first project milestone is correct attention output, not full LLM text generation.
