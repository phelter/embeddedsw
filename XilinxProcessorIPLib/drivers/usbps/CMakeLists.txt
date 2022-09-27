add_library(xil_driver_usbps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::usbps ALIAS xil_driver_usbps)

target_sources(xil_driver_usbps
  PUBLIC # Using PUBLIC since relies on xparameters.h
    src/xusbps_endpoint.c
    src/xusbps_endpoint.h
    src/xusbps_g.c
    src/xusbps_hw.c
    src/xusbps_hw.h
    src/xusbps_intr.c
    src/xusbps_sinit.c
    src/xusbps.c
    src/xusbps.h
)

target_include_directories( xil_driver_usbps SYSTEM
  PUBLIC
   src
)

target_link_libraries( xil_driver_usbps
  PUBLIC
    xil::bsp::standalone_common
)
