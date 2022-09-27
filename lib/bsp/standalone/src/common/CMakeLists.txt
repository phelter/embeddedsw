add_library(xil_bsp_standalone_common STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_common ALIAS xil_bsp_standalone_common)

target_sources(xil_bsp_standalone_common
  PRIVATE
    clocking/xil_clocking.c
    clocking/xil_clocking.h
    intr/xinterrupt_wrap.c
    intr/xinterrupt_wrap.h
  $<$<STREQUAL:${XIL_PLATFORM},versal>:
    versal/xil_error_node.h
    versal/xil_hw.h>

    print.c
    sleep.h
    xbasic_types.h
    xdebug.h
    xenv_standalone.h
    xenv.h
    xil_assert.c
    xil_assert.h
    xil_cache_vxworks.h
    xil_hal.h
    xil_io.h
    xil_macroback.h
    xil_mem.c
    xil_mem.h
    xil_printf.c
    xil_printf.h
    xil_sleepcommon.c
    xil_testcache.c
    xil_testcache.h
    xil_testio.c
    xil_testio.h
    xil_testmem.c
    xil_testmem.h
    xil_types.h
    xil_util.c
    xil_util.h
    xplatform_info.c
    xplatform_info.h
    xstatus.h
)

target_include_directories( xil_bsp_standalone_common SYSTEM
  PUBLIC
   .
   clocking
   intr

   $<$<STREQUAL:${XIL_PLATFORM},versal>:versal>
)

# target_link_libraries( xil_bsp_standalone_common
#   PUBLIC
#     xil_bsp_standalone_arm_common
# )
