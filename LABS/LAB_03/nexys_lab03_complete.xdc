# Advanced Hardware Engineering - Lab 03
# Nexys A7-100T (xc7a100tcsg324-1)
# Vivado 2025.1
# Top-level ports from design_microblaze_wrapper.vhd
# Pin map: Digilent Nexys-A7-100T-Master.xdc
# Replace existing nexys_lab02.xdc content; do not add duplicate constraints.

# ============================================================
# CLOCK, RESET AND UART
# ============================================================
set_property -dict { PACKAGE_PIN E3 IOSTANDARD LVCMOS33 } [get_ports {clk100}]
create_clock -period 10.000 -name sys_clk_pin [get_ports {clk100}]
set_property -dict { PACKAGE_PIN C12 IOSTANDARD LVCMOS33 } [get_ports {reset_rtl_0}]
set_property -dict { PACKAGE_PIN C4 IOSTANDARD LVCMOS33 } [get_ports {uart_rtl_0_rxd}]
set_property -dict { PACKAGE_PIN D4 IOSTANDARD LVCMOS33 } [get_ports {uart_rtl_0_txd}]

# ============================================================
# SWITCHES (AXI GPIO 0, CHANNEL 1)
# ============================================================
set_property -dict { PACKAGE_PIN J15 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[0]}]
set_property -dict { PACKAGE_PIN L16 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[1]}]
set_property -dict { PACKAGE_PIN M13 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[2]}]
set_property -dict { PACKAGE_PIN R15 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[3]}]
set_property -dict { PACKAGE_PIN R17 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[4]}]
set_property -dict { PACKAGE_PIN T18 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[5]}]
set_property -dict { PACKAGE_PIN U18 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[6]}]
set_property -dict { PACKAGE_PIN R13 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[7]}]
set_property -dict { PACKAGE_PIN T8 IOSTANDARD LVCMOS18 } [get_ports {sw_tri_i[8]}]
set_property -dict { PACKAGE_PIN U8 IOSTANDARD LVCMOS18 } [get_ports {sw_tri_i[9]}]
set_property -dict { PACKAGE_PIN R16 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[10]}]
set_property -dict { PACKAGE_PIN T13 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[11]}]
set_property -dict { PACKAGE_PIN H6 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[12]}]
set_property -dict { PACKAGE_PIN U12 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[13]}]
set_property -dict { PACKAGE_PIN U11 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[14]}]
set_property -dict { PACKAGE_PIN V10 IOSTANDARD LVCMOS33 } [get_ports {sw_tri_i[15]}]

# ============================================================
# LEDS (AXI GPIO 0, CHANNEL 2)
# ============================================================
set_property -dict { PACKAGE_PIN H17 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[0]}]
set_property -dict { PACKAGE_PIN K15 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[1]}]
set_property -dict { PACKAGE_PIN J13 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[2]}]
set_property -dict { PACKAGE_PIN N14 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[3]}]
set_property -dict { PACKAGE_PIN R18 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[4]}]
set_property -dict { PACKAGE_PIN V17 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[5]}]
set_property -dict { PACKAGE_PIN U17 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[6]}]
set_property -dict { PACKAGE_PIN U16 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[7]}]
set_property -dict { PACKAGE_PIN V16 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[8]}]
set_property -dict { PACKAGE_PIN T15 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[9]}]
set_property -dict { PACKAGE_PIN U14 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[10]}]
set_property -dict { PACKAGE_PIN T16 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[11]}]
set_property -dict { PACKAGE_PIN V15 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[12]}]
set_property -dict { PACKAGE_PIN V14 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[13]}]
set_property -dict { PACKAGE_PIN V12 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[14]}]
set_property -dict { PACKAGE_PIN V11 IOSTANDARD LVCMOS33 } [get_ports {led_tri_o[15]}]

# ============================================================
# 7-SEGMENT LINES (AXI GPIO 1, CHANNEL 1, BIT 7=DP)
# ============================================================
set_property -dict { PACKAGE_PIN T10 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[0]}]
set_property -dict { PACKAGE_PIN R10 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[1]}]
set_property -dict { PACKAGE_PIN K16 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[2]}]
set_property -dict { PACKAGE_PIN K13 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[3]}]
set_property -dict { PACKAGE_PIN P15 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[4]}]
set_property -dict { PACKAGE_PIN T11 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[5]}]
set_property -dict { PACKAGE_PIN L18 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[6]}]
set_property -dict { PACKAGE_PIN H15 IOSTANDARD LVCMOS33 } [get_ports {seg_tri_o[7]}]

# ============================================================
# 7-SEGMENT DIGIT ENABLES (AXI GPIO 1, CHANNEL 2)
# ============================================================
set_property -dict { PACKAGE_PIN J17 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[0]}]
set_property -dict { PACKAGE_PIN J18 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[1]}]
set_property -dict { PACKAGE_PIN T9 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[2]}]
set_property -dict { PACKAGE_PIN J14 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[3]}]
set_property -dict { PACKAGE_PIN P14 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[4]}]
set_property -dict { PACKAGE_PIN T14 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[5]}]
set_property -dict { PACKAGE_PIN K2 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[6]}]
set_property -dict { PACKAGE_PIN U13 IOSTANDARD LVCMOS33 } [get_ports {an_tri_o[7]}]

# ============================================================
# CUSTOM PWM RGB LED 16
# ============================================================
set_property -dict { PACKAGE_PIN N15 IOSTANDARD LVCMOS33 } [get_ports {pwm_r}]
set_property -dict { PACKAGE_PIN M16 IOSTANDARD LVCMOS33 } [get_ports {pwm_g}]
set_property -dict { PACKAGE_PIN R12 IOSTANDARD LVCMOS33 } [get_ports {pwm_b}]

