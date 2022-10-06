add_library(xil_driver_scuwdt STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::scuwdt ALIAS xil_driver_scuwdt)

target_sources(xil_driver_scuwdt
  PRIVATE
    src/xscuwdt_g.c
    src/xscuwdt_hw.h
    src/xscuwdt_selftest.c
    src/xscuwdt_sinit.c
    src/xscuwdt.c
    src/xscuwdt.h
)

target_include_directories( xil_driver_scuwdt SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_scuwdt
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-padded>
)

target_link_libraries( xil_driver_scuwdt
  PUBLIC
    xil::bsp::standalone_common
)
