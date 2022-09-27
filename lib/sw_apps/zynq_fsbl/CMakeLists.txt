add_executable(zynq_fsbl EXCLUDE_FROM_ALL)
add_library(xil::apps::zynq_fsbl ALIAS zynq_fsbl)

target_sources(zynq_fsbl
  PRIVATE
  $<$<STREQUAL:${XIL_PLATFORM},zc702>:
    misc/zc702/bspconfig.h
    misc/zc702/CMakeLists.txt
    misc/zc702/drivers.txt
    misc/zc702/inbyte.c
    misc/zc702/outbyte.c
    misc/zc702/ps7_init_gpl.c
    misc/zc702/ps7_init_gpl.h
    misc/zc702/ps7_init.c
    misc/zc702/ps7_init.h
    misc/zc702/xparameters.h>
  $<$<STREQUAL:${XIL_PLATFORM},zc706>:
    misc/zc706/bspconfig.h
    misc/zc706/drivers.txt
    misc/zc706/inbyte.c
    misc/zc706/outbyte.c
    misc/zc706/ps7_init_gpl.c
    misc/zc706/ps7_init_gpl.h
    misc/zc706/ps7_init.c
    misc/zc706/ps7_init.h
    misc/zc706/xparameters.h>
  $<$<STREQUAL:${XIL_PLATFORM},zed>:
    misc/zed/bspconfig.h
    misc/zed/drivers.txt
    misc/zed/inbyte.c
    misc/zed/outbyte.c
    misc/zed/ps7_init_gpl.c
    misc/zed/ps7_init_gpl.h
    misc/zed/ps7_init.c
    misc/zed/ps7_init.h
    misc/zed/xparameters.h>
 
    src/fsbl_debug.h
    src/fsbl_handoff.S
    src/fsbl_hooks.c
    src/fsbl_hooks.h
    src/fsbl.h
    src/image_mover.c
    src/image_mover.h
    src/lscript.ld
    src/main.c
    src/Makefile
    src/md5.c
    src/md5.h
    src/nand.c
    src/nand.h
    src/nor.c
    src/nor.h
    src/pcap.c
    src/pcap.h
    src/qspi.c
    src/qspi.h
    src/rsa.c
    src/rsa.h
    src/scatter.scat
    src/sd.c
    src/sd.h
)

target_include_directories( zynq_fsbl SYSTEM
  PRIVATE
    $<$<STREQUAL:${XIL_PLATFORM},zc702>:misc/zc702>
    $<$<STREQUAL:${XIL_PLATFORM},zc706>:misc/zc706>
    $<$<STREQUAL:${XIL_PLATFORM},zed>:misc/zed>
    
   
)

# TODO Link options for Xilinx.spec
#target_link_options()
target_link_libraries( zynq_fsbl
  PRIVATE
    xil::driver::cpu_cortexa9
    xil::driver::devcfg
    xil::driver::dmaps
    xil::driver::emacps
    xil::driver::gpiops
    xil::driver::qspips
    xil::driver::scugic
    xil::driver::scutimer
    xil::driver::scuwdt
    xil::driver::sdps
    xil::driver::ttcps
    xil::driver::uartps
    xil::driver::usbps
    xil::driver::xadcps
)
