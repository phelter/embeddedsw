add_library(xil_driver_dmaps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::dmaps ALIAS xil_driver_dmaps)

target_sources(xil_driver_dmaps
  PRIVATE
    src/xdmaps_g.c
    src/xdmaps_hw.c
    src/xdmaps_hw.h
    src/xdmaps_selftest.c
    src/xdmaps_sinit.c
    src/xdmaps.c
    src/xdmaps.h
)

target_include_directories( xil_driver_dmaps SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_dmaps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-implicit-int-conversion
    -Wno-missing-prototypes
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-pointer-to-int-cast
    -Wno-shorten-64-to-32
    -Wno-sign-conversion
    -Wno-unused-macros
    -Wno-void-pointer-to-int-cast>
)

target_link_libraries( xil_driver_dmaps
  PUBLIC
    xil::bsp::standalone_common
)
