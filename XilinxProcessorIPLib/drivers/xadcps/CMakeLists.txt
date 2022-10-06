add_library(xil_driver_xadcps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::xadcps ALIAS xil_driver_xadcps)

target_sources(xil_driver_xadcps
  PRIVATE
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

target_compile_options( xil_driver_xadcps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-missing-variable-declarations
    -Wno-padded>
)

target_link_libraries( xil_driver_xadcps
  PUBLIC
    xil::bsp::standalone_common
)
