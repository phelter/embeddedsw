add_library(xil_service_loader STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::loader ALIAS xil_service_loader)

target_sources(xil_service_loader
  PRIVATE
    src/xloader_auth_enc.c
    src/xloader_auth_enc.h
    src/xloader_cfi.c
    src/xloader_cmd.c
    src/xloader_ddr.c
    src/xloader_ddr.h
    src/xloader_dfu_util.c
    src/xloader_dfu_util.h
    src/xloader_intr.c
    src/xloader_ospi.c
    src/xloader_ospi.h
    src/xloader_prtn_load.c
    src/xloader_qspi.c
    src/xloader_qspi.h
    src/xloader_sbi.c
    src/xloader_sbi.h
    src/xloader_sd.c
    src/xloader_sd.h
    src/xloader_secure.c
    src/xloader_secure.h
    src/xloader_usb.c
    src/xloader_usb.h
    src/xloader.c
    src/xloader.h
)

target_include_directories( xil_service_loader SYSTEM
  PUBLIC
    src
)

target_link_libraries( xil_service_loader
  PUBLIC
    xil::bsp::standalone_common
)
