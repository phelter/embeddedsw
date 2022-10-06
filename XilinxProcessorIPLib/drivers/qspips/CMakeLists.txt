add_library(xil_driver_qspips STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::qspips ALIAS xil_driver_qspips)

target_sources(xil_driver_qspips
  PRIVATE
    src/xqspips_g.c
    src/xqspips_hw.c
    src/xqspips_hw.h
    src/xqspips_options.c
    src/xqspips_selftest.c
    src/xqspips_sinit.c
    src/xqspips.c
    src/xqspips.h
)

target_include_directories( xil_driver_qspips SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_qspips
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-implicit-int-conversion
    -Wno-int-to-void-pointer-cast
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-shadow
    -Wno-sign-conversion>
)

target_link_libraries( xil_driver_qspips
  PUBLIC
    xil::bsp::standalone_common
)
