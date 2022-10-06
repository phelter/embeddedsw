add_library(xil_service_skey STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::skey ALIAS xil_service_skey)

target_sources(xil_service_skey
  PRIVATE
    src/include/xilskey_bbram.h
    src/include/xilskey_epl.h
    src/include/xilskey_eps_zynqmp_puf.h
    src/include/xilskey_eps_zynqmp.h
    src/include/xilskey_eps.h
    src/include/xilskey_utils.h
    src/xilskey_bbram.c
    src/xilskey_bbramps_zynqmp_hw.h
    src/xilskey_bbramps_zynqmp.c
    src/xilskey_epl.c
    src/xilskey_eps_zynqmp_hw.h
    src/xilskey_eps_zynqmp_puf.c
    src/xilskey_eps_zynqmp.c
    src/xilskey_eps.c
    src/xilskey_epshw.h
    src/xilskey_js.h
    src/xilskey_jscmd.c
    src/xilskey_jscmd.h
    src/xilskey_jslib.c
    src/xilskey_jslib.h
    src/xilskey_jtag.h
    src/xilskey_utils.c
)

target_include_directories( xil_service_skey SYSTEM
  PUBLIC
    src/include
  PRIVATE
    src
)

target_link_libraries( xil_service_skey
  PUBLIC
    xil::bsp::standalone_common
)
