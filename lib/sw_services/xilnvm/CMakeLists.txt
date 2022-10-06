add_library(xil_service_nvm STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::nvm ALIAS xil_service_nvm)

target_sources(xil_service_nvm
  PRIVATE
    src/client/xnvm_bbramclient.c
    src/client/xnvm_bbramclient.h
    src/client/xnvm_efuseclient.c
    src/client/xnvm_efuseclient.h
    src/client/xnvm_mailbox.c
    src/client/xnvm_mailbox.h
    src/common/xnvm_defs.h
    src/server/xnvm_bbram_hw.h
    src/server/xnvm_bbram_ipihandler.c
    src/server/xnvm_bbram_ipihandler.h
    src/server/xnvm_bbram.c
    src/server/xnvm_bbram.h
    src/server/xnvm_cmd.c
    src/server/xnvm_cmd.h
    src/server/xnvm_efuse_hw.h
    src/server/xnvm_efuse_ipihandler.c
    src/server/xnvm_efuse_ipihandler.h
    src/server/xnvm_efuse.c
    src/server/xnvm_efuse.h
    src/server/xnvm_init.c
    src/server/xnvm_init.h
    src/server/xnvm_utils.c
    src/server/xnvm_utils.h
)

target_include_directories( xil_service_nvm SYSTEM
  PUBLIC
    src/client
    src/common
    src/server
)

target_link_libraries( xil_service_nvm
  PUBLIC
    xil::bsp::standalone_common
)
