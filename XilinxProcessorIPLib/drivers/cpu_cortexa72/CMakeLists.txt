add_library(xil_driver_cpu_cortexa72 STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::cpu_cortexa72 ALIAS xil_driver_cpu_cortexa72)

target_sources(xil_driver_cpu_cortexa72
  PRIVATE
    src/xcpu_cortexa72.h
)

target_include_directories( xil_driver_cpu_cortexa72 SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_cpu_cortexa72
  PUBLIC
    xil::bsp::standalone_armv8_64bit
)
