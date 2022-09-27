add_library(xil_driver_sdps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::sdps ALIAS xil_driver_sdps)

target_sources(xil_driver_sdps
  PUBLIC # Using PUBLIC since relies on xparameters.h
    sdps/src/xsdps_card.c
    sdps/src/xsdps_core.h
    sdps/src/xsdps_g.c
    sdps/src/xsdps_host.c
    sdps/src/xsdps_hw.h
    sdps/src/xsdps_options.c
    sdps/src/xsdps_sinit.c
    sdps/src/xsdps.c
    sdps/src/xsdps.h
)

target_include_directories( xil_driver_sdps SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_sdps
  PUBLIC
    xil::bsp::standalone_common
)
