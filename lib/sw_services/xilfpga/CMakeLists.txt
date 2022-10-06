add_library(xil_service_fpga STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::fpga ALIAS xil_service_fpga)

target_sources(xil_service_fpga
  PRIVATE
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_VERSAL_LIST}>:
        src/interface/versal/xilfpga_versal.c
        src/interface/versal/xilfpga_versal.h>
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_ZYNQMP_LIST}>:    
        src/interface/zynqmp/xilfpga_ipi_pcap.c
        src/interface/zynqmp/xilfpga_pcap_common.h
        src/interface/zynqmp/xilfpga_pcap.c
        src/interface/zynqmp/xilfpga_pcap.h>
    src/xilfpga.c
    src/xilfpga.h
)

target_include_directories( xil_service_fpga SYSTEM
  PUBLIC
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_VERSAL_LIST}>:src/interface/versal>
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_ZYNQMP_LIST}>:src/interface/zynqmp> 
    src
)

target_link_libraries( xil_service_fpga
  PUBLIC
    xil::bsp::standalone_common
)
