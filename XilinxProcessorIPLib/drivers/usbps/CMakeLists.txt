add_library(xil_driver_usbps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::usbps ALIAS xil_driver_usbps)

target_sources(xil_driver_usbps
  PRIVATE
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

target_compile_options( xil_driver_usbps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-implicit-int-conversion
    -Wno-int-to-pointer-cast
    -Wno-int-to-void-pointer-cast
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-pointer-to-int-cast
    -Wno-sign-conversion
    -Wno-unused-but-set-variable>
)

target_link_libraries( xil_driver_usbps
  PUBLIC
    xil::bsp::standalone_common
)
