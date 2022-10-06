add_library(xil_service_mailbox STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::mailbox ALIAS xil_service_mailbox)

target_sources(xil_service_mailbox
  PRIVATE
    #TODO(phelter): PS? - is that for zynq only?
    src/PS/xilmailbox_ipips.c
    src/PS/xilmailbox_ipips.h
    src/xilmailbox.c
    src/xilmailbox.h
)

target_include_directories( xil_service_mailbox SYSTEM
  PUBLIC
    src
)

target_link_libraries( xil_service_mailbox
  PUBLIC
    xil::bsp::standalone_common
)
