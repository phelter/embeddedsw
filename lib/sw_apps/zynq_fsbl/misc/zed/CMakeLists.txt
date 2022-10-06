add_library( xil_config_zed STATIC EXCLUDE_FROM_ALL)

target_sources(xil_config_zed
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

target_include_directories(xil_config_zed
  PUBLIC
    .
)

target_link_libraries(xil_config_zed
  PRIVATE
    xil::bsp::standalone_common
    xil::driver::uartps
)
