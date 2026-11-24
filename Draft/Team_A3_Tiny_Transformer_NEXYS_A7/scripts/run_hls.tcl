# Team A3: Nexys A7-100T first FPGA milestone (attention-only).
# Run from repository root in Vitis HLS 2025.1:
#    vitis_hls -f scripts/run_hls.tcl
# Host tests should pass before this run.
open_project -reset team_a3_nexys_attention_hls
set_top attention_top
add_files hls/attention_top.cpp -cflags "-Ihls"
add_files hls/attention.cpp -cflags "-Ihls"
add_files -tb hls/attention_testbench.cpp -cflags "-Ihls"
open_solution -reset solution1 -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
set data_dir [file normalize "data"]
csim_design -argv $data_dir
csynth_design
# Only after C synthesis passes and resources/timing are reviewed:
# cosim_design -argv $data_dir
# export_design -format ip_catalog
exit
