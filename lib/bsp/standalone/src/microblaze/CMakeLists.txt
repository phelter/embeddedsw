add_library(xil_bsp_standalone_microblaze STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_microblaze ALIAS xil_bsp_standalone_microblaze)

target_sources(xil_bsp_standalone_microblaze
  PRIVATE
    _exit.c
    errno.c
    fcntl.c
    fsl.h
    hw_exception_handler.S
    mb_interface.h
    microblaze_disable_dcache.S
    microblaze_disable_exceptions.S
    microblaze_disable_icache.S
    microblaze_disable_interrupts.S
    microblaze_enable_dcache.S
    microblaze_enable_exceptions.S
    microblaze_enable_icache.S
    microblaze_enable_interrupts.S
    microblaze_exception_handler.c
    microblaze_exceptions_g.h
    microblaze_exceptions_i.h
    microblaze_flush_cache_ext_range.S
    microblaze_flush_cache_ext.S
    microblaze_flush_dcache_range.S
    microblaze_flush_dcache.S
    microblaze_init_dcache_range.S
    microblaze_init_icache_range.S
    microblaze_instructions.h
    microblaze_interrupt_handler.c
    microblaze_interrupts_g.c
    microblaze_interrupts_i.h
    microblaze_invalidate_cache_ext_range.S
    microblaze_invalidate_cache_ext.S
    microblaze_invalidate_dcache_range.S
    microblaze_invalidate_dcache.S
    microblaze_invalidate_icache_range.S
    microblaze_invalidate_icache.S
    microblaze_scrub.S
    microblaze_selftest.S
    microblaze_sleep.c
    microblaze_sleep.h
    microblaze_update_dcache.S
    microblaze_update_icache.S
    pvr.c
    pvr.h
    xil_cache.c
    xil_cache.h
    xil_exception.c
    xil_exception.h
    xil_misc_psreset_api.c
    xil_misc_psreset_api.h

)

target_include_directories( xil_bsp_standalone_microblaze SYSTEM
  PUBLIC
   .
   #$<$<C_COMPILER_ID:ARMCC>:armcc>
)

target_link_libraries( xil_bsp_standalone_microblaze
  PUBLIC
)
