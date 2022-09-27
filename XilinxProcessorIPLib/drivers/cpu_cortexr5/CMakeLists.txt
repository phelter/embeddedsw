add_library(xil_driver_cpu_cortexr5 STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::cpu_cortexr5 ALIAS xil_driver_cpu_cortexr5)

target_sources(xil_driver_cpu_cortexr5
  PRIVATE
    src/xcpu_cortexr5.h
)

target_include_directories( xil_driver_cpu_cortexr5 SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_cpu_cortexr5
  PUBLIC
    xil::bsp::standalone_armv8_64bit
)
