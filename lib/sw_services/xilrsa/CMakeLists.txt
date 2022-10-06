add_library(xil_service_rsa STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::rsa ALIAS xil_service_rsa)

target_sources(xil_service_rsa
  PRIVATE
    src/include/xilrsa.h
)

target_include_directories( xil_service_rsa SYSTEM
  PUBLIC
    src/include
)

target_link_libraries( xil_service_rsa
  PUBLIC
    xil::bsp::standalone_common
    $<$<C_COMPILER_ID:ARMCC>:librsa_armcc.a>
    $<$<NOT:$<C_COMPILER_ID:ARMCC>>:librsa.a>
)
