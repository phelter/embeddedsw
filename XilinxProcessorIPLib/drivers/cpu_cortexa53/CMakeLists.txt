add_library(xil_driver_cpu_cortexa53 STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::cpu_cortexa53 ALIAS xil_driver_cpu_cortexa53)

target_sources(xil_driver_cpu_cortexa53
  PRIVATE
    src/xcpu_cortexa53.h
)

target_include_directories( xil_driver_cpu_cortexa53 SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_cpu_cortexa53
  PUBLIC
    xil::bsp::standalone_armv8_32bit
)
