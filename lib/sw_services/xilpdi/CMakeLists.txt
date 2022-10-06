add_library(xil_service_pdi STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::pdi ALIAS xil_service_pdi)

target_sources(xil_service_pdi
  PRIVATE
    src/xilpdi.c
    src/xilpdi.h
)

target_include_directories( xil_service_pdi SYSTEM
  PUBLIC
    src
)

target_link_libraries( xil_service_pdi
  PUBLIC
    xil::bsp::standalone_common
)
