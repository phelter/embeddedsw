add_library(xil_service_flash STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::flash ALIAS xil_service_flash)

target_sources(xil_service_flash
  PRIVATE
    src/include/xilflash_amd.h
    src/include/xilflash_cfi.h
    src/include/xilflash_intel.h
    src/include/xilflash_properties.h
    src/include/xilflash.h
    src/xilflash_amd.c
    src/xilflash_cfi.c
    src/xilflash_intel.c
    src/xilflash.c
)

target_include_directories( xil_service_flash SYSTEM
  PUBLIC
    src/include
)

target_link_libraries( xil_service_flash
  PUBLIC
    xil::bsp::standalone_common
)
