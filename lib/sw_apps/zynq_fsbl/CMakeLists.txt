set(ZYNQ_FSBL_PLATFORM_LIST zc702 zc706 zed)
if (NOT XIL_PLATFORM IN_LIST ZYNQ_FSBL_PLATFORM_LIST)
    # Not a supported platform for the zynq_fsbl
    return()
endif()

# -------------------------------------------------------------------
add_subdirectory(misc/zc702)
add_subdirectory(misc/zc706)
add_subdirectory(misc/zed)

if( TARGET xil::config )
    #TODO(phelter): Support for external config?
    message(FATAL_ERROR "xil::config already defined - XIL_PLATFORM=${XIL_PLATFORM}")
elseif (XIL_PLATFORM STREQUAL "zc702")
    add_library( xil::config ALIAS xil_config_zc702 )
elseif (XIL_PLATFORM STREQUAL "zc706")
    add_library( xil::config ALIAS xil_config_zc706 )
elseif (XIL_PLATFORM STREQUAL "zed")
    add_library( xil::config ALIAS xil_config_zed )
endif()


# -------------------------------------------------------------------
add_executable(zynq_fsbl)

target_sources( zynq_fsbl
  PRIVATE
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
    src
)

target_compile_options( zynq_fsbl
  PRIVATE
  $<$<C_COMPILER_ID:Clang,ARMClang>:
    -Wno-date-time
    -Wno-gnu-statement-expression
    -Wno-implicit-int-conversion
    -Wno-int-to-pointer-cast
    -Wno-int-to-void-pointer-cast
    -Wno-missing-noreturn
    -Wno-missing-prototypes
    -Wno-missing-variable-declarations
    -Wno-parentheses-equality
    -Wno-pointer-to-int-cast
    -Wno-shadow
    -Wno-sign-conversion
    -Wno-strict-prototypes
    -Wno-unused-macros>
)
# TODO Link options for Xilinx.spec
#target_link_options()
target_link_libraries( zynq_fsbl
  PRIVATE
    xil::config
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

    xil::service::ffs
)
