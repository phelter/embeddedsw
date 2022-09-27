add_library(xil_driver_scugic STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::scugic ALIAS xil_driver_scugic)

target_sources(xil_driver_scugic
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xscugic_g.c
    src/xscugic_hw.c
    src/xscugic_hw.h
    src/xscugic_intr.c
    src/xscugic_selftest.c
    src/xscugic_sinit.c
    src/xscugic.c
    src/xscugic.h
)

target_include_directories( xil_driver_scugic SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_scugic
  PUBLIC
    xil::bsp::standalone_common
)
