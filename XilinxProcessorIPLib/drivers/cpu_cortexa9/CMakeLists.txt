add_library(xil_driver_cpu_cortexa9 STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::cpu_cortexa9 ALIAS xil_driver_cpu_cortexa9)

target_sources(xil_driver_cpu_cortexa9
  PRIVATE
    src/xcpu_cortexa9.h
)

target_include_directories( xil_driver_cpu_cortexa9 SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_cpu_cortexa9
  PUBLIC
    xil::bsp::standalone_cortexa9
)
