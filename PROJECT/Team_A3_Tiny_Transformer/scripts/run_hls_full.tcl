# Experimental full FP32 encoder for Nexys A7-100T.
# Full synthesis is OFF by default because fit/timing are not established.
# Run: vitis_hls -f scripts/run_hls_full.tcl
open_project -reset team_a3_nexys_full_hls
set_top transformer_top
add_files hls/transformer_top.cpp -cflags "-Ihls"
add_files hls/attention.cpp -cflags "-Ihls"
add_files hls/transformer_layers.cpp -cflags "-Ihls"
add_files -tb hls/testbench.cpp -cflags "-Ihls"
open_solution -reset solution1 -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
set data_dir [file normalize "data"]
csim_design -argv $data_dir
if {[info exists ::env(TEAM_A3_FULL_SYNTH)] && $::env(TEAM_A3_FULL_SYNTH) eq "1"} {
    csynth_design
    # Review DSP / LUT / BRAM and achieved clock before RTL cosimulation.
    # cosim_design -argv $data_dir
    # export_design -format ip_catalog
}
exit
