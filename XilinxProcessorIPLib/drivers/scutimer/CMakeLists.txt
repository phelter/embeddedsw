add_library(xil_driver_scutimer STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::scutimer ALIAS xil_driver_scutimer)

target_sources(xil_driver_scutimer
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xscutimer_g.c
    src/xscutimer_hw.h
    src/xscutimer_selftest.c
    src/xscutimer_sinit.c
    src/xscutimer.c
    src/xscutimer.h
)

target_include_directories( xil_driver_scutimer SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_scutimer
  PUBLIC
    xil::bsp::standalone_common
)
