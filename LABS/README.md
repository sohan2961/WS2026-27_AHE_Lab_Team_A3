# Advanced Hardware Engineering (AHE) — Laboratory Work

**Hochschule Hamm-Lippstadt (HSHL)**  
**Course:** Advanced Hardware Engineering (AHE)  
**FPGA board:** Digilent Nexys A7-100T (`xc7a100tcsg324-1`)  
**Development tools:** AMD Vivado and Vitis 2025.1

## Overview

This repository documents five laboratory exercises in FPGA-based hardware and embedded-system development. The labs progress from a custom hardware IP core to MicroBlaze-based systems, peripheral control, partial reconfiguration, and a FreeRTOS application.

## Labs and Contributions

| Lab | Topic | Main work | Responsible student |
|:---:|---|---|---|
| **01** | Your First Own IP Core | VHDL design, PWM generation, simulation, and a reusable AXI4-Lite RGB PWM IP core | **Turja** |
| **02** | MicroBlaze System | Build a MicroBlaze-based embedded system and integrate essential FPGA peripherals | **Md Mostafizur Rahman** |
| **03** | GPIO, 7-Segment Display and PWM IP | Integrate AXI GPIO, switches, LEDs, 7-segment display, and custom PWM IP with MicroBlaze | **Md Mostafizur Rahman** |
| **04** | Partial Reconfiguration with MicroBlaze | Develop a static MicroBlaze system and interchangeable hardware modules (pass-through, inversion, and byte swap) | **Md Mostafizur Rahman** |
| **05** | FreeRTOS I/O Controller | Develop a task-based MicroBlaze application using FreeRTOS, interrupts, UART, GPIO, and DDR2 memory | **Md Mostafizur Rahman** |

## Lab Summaries

### Lab 01 — Your First Own IP Core

**Contributor: Turja**

- Design basic FPGA input/output logic in VHDL.
- Implement and simulate PWM functionality.
- Package a custom RGB PWM controller as an AXI4-Lite peripheral for reuse in later labs.

### Lab 02 — MicroBlaze System

**Contributor: Md Mostafizur Rahman**

- Create an embedded hardware system around the MicroBlaze soft processor.
- Connect processor, memory, and AXI-based peripherals in Vivado.
- Prepare the hardware platform for software development in Vitis.

### Lab 03 — GPIO, 7-Segment Display and PWM IP

**Contributor: Md Mostafizur Rahman**

- Control LEDs and read switches through AXI GPIO.
- Work with the 7-segment display and a custom AXI4-Lite PWM peripheral.
- Integrate the Lab 01 PWM IP into the MicroBlaze system.
- Generate the FPGA bitstream and build a Vitis software platform.

### Lab 04 — Partial Reconfiguration with MicroBlaze

**Contributor: Md Mostafizur Rahman**

- Separate the design into a static MicroBlaze subsystem and a reconfigurable hardware partition.
- Develop alternative hardware functions: pass-through, bitwise inversion, and byte swapping.
- Simulate, synthesize, and prepare the design for partial-reconfiguration experiments.

### Lab 05 — FreeRTOS I/O Controller

**Contributor: Md Mostafizur Rahman**

- Build a MicroBlaze-based system with AXI GPIO, AXI Timer, interrupt controller, UART Lite, and DDR2 memory.
- Develop FreeRTOS tasks for concurrent I/O activities.
- Implement task scheduling, timing, and UART-driven interaction.
- Validate the hardware design and timing before completing software integration and board-level testing.

## Software and Hardware

- **FPGA:** Digilent Nexys A7-100T (Artix-7)
- **Hardware design:** Verilog/VHDL, Vivado IP Integrator, custom AXI4-Lite IP
- **Processor and software:** MicroBlaze, C, Vitis, FreeRTOS (Lab 05)
- **Interfaces:** AXI GPIO, AXI Timer, UART, switches, LEDs, 7-segment display, RGB LED

## How to Use This Repository

1. Open the desired lab folder and read any lab-specific instructions.
2. Open the Vivado project or recreate it using the included design sources and constraints.
3. Select the **Nexys A7-100T** board / `xc7a100tcsg324-1` device as appropriate.
4. Generate the bitstream where required, then use **Vitis 2025.1** for MicroBlaze software.
5. Validate simulations, build logs, and hardware output for the individual lab before treating it as fully tested.

> **Status note:** The repository documents laboratory development; not every lab or subtask should be interpreted as fully verified on the physical board. Check the individual lab material for the latest test results.

## Acknowledgment and Authorship

The work is organized as five AHE laboratory exercises. **Lab 01 was carried out by Turja. Labs 02, 03, 04, and 05 were carried out by Md Mostafizur Rahman.** The custom PWM IP from Lab 01 is reused in subsequent MicroBlaze integration work.

## Academic Use

This repository is intended for learning, technical documentation, and demonstration of FPGA and embedded-systems development at Hochschule Hamm-Lippstadt.
