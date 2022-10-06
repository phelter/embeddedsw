add_library(xil_driver_emacps STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::emacps ALIAS xil_driver_emacps)

target_sources(xil_driver_emacps
  PRIVATE
    src/xemacps_bd.h
    src/xemacps_bdring.c
    src/xemacps_bdring.h
    src/xemacps_control.c
    src/xemacps_g.c
    src/xemacps_hw.c
    src/xemacps_hw.h
    src/xemacps_intr.c
    src/xemacps_sinit.c
    src/xemacps.c
    src/xemacps.h
)

target_include_directories( xil_driver_emacps SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_emacps
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-embedded-directive
    -Wno-implicit-int-conversion
    -Wno-logical-not-parentheses
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-shorten-64-to-32
    -Wno-unreachable-code
    -Wno-unused-but-set-variable
    -Wno-unused-macros>
)

target_link_libraries( xil_driver_emacps
  PUBLIC
    xil::bsp::standalone_common
)
