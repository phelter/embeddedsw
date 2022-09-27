add_library(xil_driver_xadcps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::xadcps ALIAS xil_driver_xadcps)

target_sources(xil_driver_xadcps
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xadcps_g.c
    src/xadcps_hw.h
    src/xadcps_intr.c
    src/xadcps_selftest.c
    src/xadcps_sinit.c
    src/xadcps.c
    src/xadcps.h
)

target_include_directories( xil_driver_xadcps SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_xadcps
  PUBLIC
    xil::bsp::standalone_common
)
