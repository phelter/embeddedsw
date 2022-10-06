add_library(xil_driver_coresightps_ddc STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::coresightps_ddc ALIAS xil_driver_coresightps_ddc)

target_sources(xil_driver_coresightps_ddc
  PRIVATE
    src/xcoresightpsdcc.c
    src/xcoresightpsdcc.h
)

target_include_directories( xil_driver_coresightps_ddc SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_coresightps_ddc
  PUBLIC
    xil::bsp::standalone_common
)
