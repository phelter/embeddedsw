add_library(xil_service_puf STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::puf ALIAS xil_service_puf)

target_sources(xil_service_puf
  PRIVATE
    src/client/xpuf_client.c
    src/client/xpuf_client.h
    src/client/xpuf_mailbox.c
    src/client/xpuf_mailbox.h
    src/common/xpuf_defs.h
    src/server/xpuf_cmd.c
    src/server/xpuf_cmd.h
    src/server/xpuf_hw.h
    src/server/xpuf_init.c
    src/server/xpuf_init.h
    src/server/xpuf_ipihandler.c
    src/server/xpuf_ipihandler.h
    src/server/xpuf.c
    src/server/xpuf.h
)

target_include_directories( xil_service_puf SYSTEM
  PUBLIC
    src/client
    src/common
    src/server
)

target_link_libraries( xil_service_puf
  PUBLIC
    xil::bsp::standalone_common
)
