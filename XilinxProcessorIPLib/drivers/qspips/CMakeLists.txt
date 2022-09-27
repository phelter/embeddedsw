add_library(xil_driver_qspips STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::qspips ALIAS xil_driver_qspips)

target_sources(xil_driver_qspips
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xqspips_g.c
    src/xqspips_hw.c
    src/xqspips_hw.h
    src/xqspips_options.c
    src/xqspips_selftest.c
    src/xqspips_sinit.c
    src/xqspips.c
    src/xqspips.h
)

target_include_directories( xil_driver_qspips SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_qspips
  PUBLIC
    xil::bsp::standalone_common
)
