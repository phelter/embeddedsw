add_library(xil_driver_cpu_cortexa53 INTERFACE)
add_library(xil::driver::cpu_cortexa53 ALIAS xil_driver_cpu_cortexa53)

target_sources(xil_driver_cpu_cortexa53
  INTERFACE
    src/xcpu_cortexa53.h
)

target_include_directories( xil_driver_cpu_cortexa53 SYSTEM
  INTERFACE
    src
)

target_link_libraries( xil_driver_cpu_cortexa53
  INTERFACE
    xil::bsp::standalone_armv8_32bit
)
