add_library(xil_driver_gpiops STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::gpiops ALIAS xil_driver_gpiops)

target_sources(xil_driver_gpiops
  PRIVATE
    src/xgpiops_g.c
    src/xgpiops_hw.c
    src/xgpiops_hw.h
    src/xgpiops_intr.c
    src/xgpiops_selftest.c
    src/xgpiops_sinit.c
    src/xgpiops.c
    src/xgpiops.h
)

target_include_directories( xil_driver_gpiops SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_gpiops
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-padded>
)

target_link_libraries( xil_driver_gpiops
  PUBLIC
    xil::bsp::standalone_common
)
