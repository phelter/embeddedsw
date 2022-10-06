add_library(xil_driver_devcfg STATIC EXCLUDE_FROM_ALL)
add_library(xil::driver::devcfg ALIAS xil_driver_devcfg)

# TODO(phelter): Investigate for copying headers if install required.
# target_sources(xil_driver_devcfg INTERFACE
#   FILE_SET HEADERS
#   TYPE HEADERS
#   BASE_DIRS src
#   FILES 
#     src/xdevcfg_hw.h
#     src/xdevcfg.h
# )

target_sources(xil_driver_devcfg
  PRIVATE
    src/xdevcfg_g.c
    src/xdevcfg_hw.c
    src/xdevcfg_hw.h
    src/xdevcfg_intr.c
    src/xdevcfg_selftest.c
    src/xdevcfg_sinit.c
    src/xdevcfg.c
    src/xdevcfg.h
)

target_include_directories( xil_driver_devcfg SYSTEM
  PUBLIC
   src
)

target_compile_options( xil_driver_devcfg
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-sign-conversion
    -Wno-void-pointer-to-int-cast>
)

target_link_libraries( xil_driver_devcfg
  PUBLIC
    xil::bsp::standalone_common
)
