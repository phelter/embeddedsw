add_library( xil_config_zc706 STATIC EXCLUDE_FROM_ALL)

target_sources(xil_config_zc706
  PRIVATE
    bspconfig.h
    drivers.txt
    inbyte.c
    outbyte.c
    ps7_init_gpl.c
    ps7_init_gpl.h
    ps7_init.c
    ps7_init.h
    xparameters.h
)

target_compile_options( xil_config_zc706
  PRIVATE
  $<$<C_COMPILER_ID:Clang,ARMClang>:
    -Wno-missing-prototypes
    -Wno-missing-variable-declarations
    -Wno-shorten-64-to-32
    -Wno-sign-compare
    -Wno-sign-conversion
    -Wno-strict-prototypes>
)

target_include_directories(xil_config_zc706
  PUBLIC
    .
)

target_link_libraries(xil_config_zc706
  PRIVATE
    xil::bsp::standalone_common
    xil::driver::uartps
)