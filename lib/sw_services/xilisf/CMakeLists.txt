add_library(xil_service_isf STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::isf ALIAS xil_service_isf)

target_sources(xil_service_isf
  PRIVATE
    src/include/xilisf_atmel.h
    src/include/xilisf_intelstm.h
    src/include/xilisf.h
    src/xilisf_erase.c
    src/xilisf_read.c
    src/xilisf_spr.c
    src/xilisf_write.c
    src/xilisf.c
)

target_include_directories( xil_service_isf SYSTEM
  PUBLIC
    src/include
)

target_link_libraries( xil_service_isf
  PUBLIC
    xil::bsp::standalone_common
)
