add_library(xil_driver_uartps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::uartps ALIAS xil_driver_uartps)

target_sources(xil_driver_uartps
  PRIVATE
    src/xuartps_g.c
    src/xuartps_hw.c
    src/xuartps_hw.h
    src/xuartps_intr.c
    src/xuartps_options.c
    src/xuartps_selftest.c
    src/xuartps_sinit.c
    src/xuartps.c
    src/xuartps.h
)

target_include_directories( xil_driver_uartps SYSTEM
  PUBLIC
   src
)

target_compile_options(xil_driver_uartps
  PRIVATE
  $<$<C_COMPILER_ID:Clang,ARMClang>:
    -Wno-implicit-int-conversion
    -Wno-missing-variable-declarations
    -Wno-padded>
)

target_link_libraries( xil_driver_uartps
  PUBLIC
    xil::bsp::standalone_common
)
