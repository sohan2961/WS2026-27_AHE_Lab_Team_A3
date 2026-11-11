
# ============================================
# Advanced Hardware Engineering
# MicroBlaze Lab 02 + Lab 03
# Board: Nexys A7-100T
# Vivado 2025.1
# ============================================

# ============================================
# LAB 02 - CLOCK, RESET, UART
# ============================================

# 100 MHz input clock
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports {clk100}]
create_clock -period 10.000 -name sys_clk_pin [get_ports {clk100}]

# Active-low CPU reset
set_property -dict {PACKAGE_PIN C12 IOSTANDARD LVCMOS33} [get_ports {reset_rtl_0}]

# UART RX - PC to FPGA
set_property -dict {PACKAGE_PIN C4 IOSTANDARD LVCMOS33} [get_ports {uart_rtl_0_rxd}]

# UART TX - FPGA to PC
set_property -dict {PACKAGE_PIN D4 IOSTANDARD LVCMOS33} [get_ports {uart_rtl_0_txd}]


# ============================================
# LAB 03 - PART 1: AXI GPIO
# ============================================

# SWITCHES - GPIO Channel 1 (Inputs)

# SW0
set_property -dict {PACKAGE_PIN J15 IOSTANDARD LVCMOS33} [get_ports {sw_tri_i[0]}]

# SW1
set_property -dict {PACKAGE_PIN L16 IOSTANDARD LVCMOS33} [get_ports {sw_tri_i[1]}]

# SW2
set_property -dict {PACKAGE_PIN M13 IOSTANDARD LVCMOS33} [get_ports {sw_tri_i[2]}]

# SW3
set_property -dict {PACKAGE_PIN R15 IOSTANDARD LVCMOS33} [get_ports {sw_tri_i[3]}]


# LEDs - GPIO Channel 2 (Outputs)

# LED0
set_property -dict {PACKAGE_PIN H17 IOSTANDARD LVCMOS33} [get_ports {led_tri_o[0]}]

# LED1
set_property -dict {PACKAGE_PIN K15 IOSTANDARD LVCMOS33} [get_ports {led_tri_o[1]}]

# LED2
set_property -dict {PACKAGE_PIN J13 IOSTANDARD LVCMOS33} [get_ports {led_tri_o[2]}]

# LED3
set_property -dict {PACKAGE_PIN N14 IOSTANDARD LVCMOS33} [get_ports {led_tri_o[3]}]
