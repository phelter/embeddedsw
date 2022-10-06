add_library(xil_driver_scutimer STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::scutimer ALIAS xil_driver_scutimer)

target_sources(xil_driver_scutimer
  PRIVATE
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

target_compile_options( xil_driver_scutimer
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-missing-variable-declarations
    -Wno-padded>
)

target_link_libraries( xil_driver_scutimer
  PUBLIC
    xil::bsp::standalone_common
)
