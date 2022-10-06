add_library(xil_service_sem_server STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::sem_server ALIAS xil_service_sem_server)

target_sources(xil_service_sem_server
  PRIVATE
    xilsem.h
)

target_include_directories( xil_service_sem_server SYSTEM
  PUBLIC
    .
)

target_link_libraries( xil_service_sem_server
  PRIVATE
    xilsem.a
)
