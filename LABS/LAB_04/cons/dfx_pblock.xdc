create_pblock pblock_u_rm
add_cells_to_pblock [get_pblocks pblock_u_rm] [get_cells -quiet [list u_rm]]
resize_pblock [get_pblocks pblock_u_rm] -add {SLICE_X30Y103:SLICE_X39Y109}
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_u_rm]
set_property SNAPPING_MODE ON [get_pblocks pblock_u_rm]
