add_library(xil_driver_emacps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::emacps ALIAS xil_driver_emacps)

target_sources(xil_driver_emacps
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xemacps_bd.h
    src/xemacps_bdring.c
    src/xemacps_bdring.h
    src/xemacps_control.c
    src/xemacps_g.c
    src/xemacps_hw.c
    src/xemacps_hw.h
    src/xemacps_intr.c
    src/xemacps_sinit.c
    src/xemacps.c
    src/xemacps.h
)

target_include_directories( xil_driver_emacps SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_emacps
  PUBLIC
    xil::bsp::standalone_common
)
