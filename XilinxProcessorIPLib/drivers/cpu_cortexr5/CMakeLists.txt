add_library(xil_driver_cpu_cortexr5 INTERFACE)
add_library(xil::driver::cpu_cortexr5 ALIAS xil_driver_cpu_cortexr5)

target_sources(xil_driver_cpu_cortexr5
  INTERFACE
    src/xcpu_cortexr5.h
)

target_include_directories( xil_driver_cpu_cortexr5 SYSTEM
  INTERFACE
    src
)

target_link_libraries( xil_driver_cpu_cortexr5
  INTERFACE
    xil::bsp::standalone_armv8_64bit
)
