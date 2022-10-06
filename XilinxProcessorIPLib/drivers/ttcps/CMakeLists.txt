add_library(xil_driver_ttcps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::ttcps ALIAS xil_driver_ttcps)

target_sources(xil_driver_ttcps
  PRIVATE
    src/xttcps_g.c
    src/xttcps_hw.h
    src/xttcps_options.c
    src/xttcps_selftest.c
    src/xttcps_sinit.c
    src/xttcps.c
    src/xttcps.h
)

target_include_directories( xil_driver_ttcps SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_ttcps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-missing-variable-declarations
    -Wno-padded>
)

target_link_libraries( xil_driver_ttcps
  PUBLIC
    xil::bsp::standalone_common
)
