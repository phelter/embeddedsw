add_library(xil_driver_cpu_cortexa9 INTERFACE)
add_library(xil::driver::cpu_cortexa9 ALIAS xil_driver_cpu_cortexa9)

target_sources(xil_driver_cpu_cortexa9
  INTERFACE
    src/xcpu_cortexa9.h
)

target_include_directories( xil_driver_cpu_cortexa9 SYSTEM
  INTERFACE
    src
)

target_link_libraries( xil_driver_cpu_cortexa9
  INTERFACE
    xil::bsp::standalone_arm_cortexa9
)
