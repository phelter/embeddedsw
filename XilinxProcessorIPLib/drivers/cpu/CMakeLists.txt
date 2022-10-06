add_library(xil_driver_cpu STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::cpu ALIAS xil_driver_cpu)

target_sources(xil_driver_cpu
  PRIVATE
    src/xio.c
    src/xio.h
)

target_include_directories( xil_driver_cpu SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_cpu
  PUBLIC
    xil::bsp::standalone_common
)
