add_library(xil_service_sem_client STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::sem_client ALIAS xil_service_sem_client)

target_sources(xil_service_sem_client
  PRIVATE
    xsem_client_api.c
    xsem_client_api.h
    xsem_ipi_interface.c
    xsem_ipi_interface.h
)

target_include_directories( xil_service_sem_client SYSTEM
  PUBLIC
    .
)

target_link_libraries( xil_service_sem_client
  PUBLIC
    xil::bsp::standalone_common
)
