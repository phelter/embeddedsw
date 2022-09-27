add_library(xil_driver_dmaps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::dmaps ALIAS xil_driver_dmaps)

target_sources(xil_driver_dmaps
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xdmaps_g.c
    src/xdmaps_hw.c
    src/xdmaps_hw.h
    src/xdmaps_selftest.c
    src/xdmaps_sinit.c
    src/xdmaps.c
    src/xdmaps.h
)

target_include_directories( xil_driver_dmaps SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_dmaps
  PUBLIC
    xil::bsp::standalone_common
)
