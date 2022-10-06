add_library(xil_driver_sdps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::sdps ALIAS xil_driver_sdps)

target_sources(xil_driver_sdps
  PRIVATE
    src/xsdps_card.c
    src/xsdps_core.h
    src/xsdps_g.c
    src/xsdps_host.c
    src/xsdps_hw.h
    src/xsdps_options.c
    src/xsdps_sinit.c
    src/xsdps.c
    src/xsdps.h
)

target_include_directories( xil_driver_sdps SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_sdps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-shorten-64-to-32
    -Wno-sign-conversion>
)

target_link_libraries( xil_driver_sdps
  PUBLIC
    xil::bsp::standalone_common
)
