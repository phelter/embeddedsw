add_library(xil_bsp_standalone_arm_cortexa9 STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_arm_cortexa9 ALIAS xil_bsp_standalone_arm_cortexa9)

target_sources(xil_bsp_standalone_arm_cortexa9 
  PRIVATE
    sleep.c
    smc.h
    usleep.c
    xil_cache_l.h
    $<$<BOOL:${CMAKE_CROSSCOMPILING}>:
        xil_cache.c
        xil_mmu.c
        xpm_counter.c>
    $<$<NOT:$<BOOL:${CMAKE_CROSSCOMPILING}>>:
        stubs/xil_cache.c
        stubs/xil_mmu.c
        stubs/xpm_counter.c>
    xil_cache.h
    xil_errata.h
    xil_misc_psreset_api.c
    xil_misc_psreset_api.h
    xil_mmu.h
    xl2cc_counter.c
    xl2cc_counter.h
    xl2cc.h
    xparameters_ps.h
    xpm_counter.h
    xpseudo_asm.h
    xreg_cortexa9.h
    xtime_l.c
    xtime_l.h
  $<$<C_COMPILER_ID:ARMCC>:
    armcc/_sys_close.c
    armcc/_sys_exit.c
    armcc/_sys_iserror.c
    armcc/_sys_istty.c
    armcc/_sys_open.c
    armcc/_sys_read.c
    armcc/_sys_time.c
    armcc/_sys_write.c
    armcc/ARM_argv_veneer.c
    armcc/asm_vectors.s
    armcc/boot.S
    armcc/translation_table.s
    armcc/xpseudo_asm_rvct.c
    armcc/xpseudo_asm_rvct.h>
  $<$<C_COMPILER_ID:GNU>:
    gcc/asm_vectors.S
    gcc/boot.S
    gcc/cpu_init.S
    gcc/translation_table.S
    gcc/xil-crt0.S>
  $<$<C_COMPILER_ID:IAR>:
    iccarm/asm_vectors.s
    iccarm/boot.s
    iccarm/translation_table.s>
)

target_include_directories( xil_bsp_standalone_arm_cortexa9 SYSTEM
  PUBLIC
   .
   #$<$<C_COMPILER_ID:ARMCC>:${CMAKE_CURRENT_SOURCE_DIR}/armcc>
)

target_compile_options( xil_bsp_standalone_arm_cortexa9 
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang,Clang>:
    -Wno-gnu-statement-expression
    -Wno-pointer-to-int-cast
    -Wno-reserved-identifier
    -Wno-shorten-64-to-32>
)

target_link_libraries( xil_bsp_standalone_arm_cortexa9
  PUBLIC
    xil::bsp::standalone_arm_common
    xil::bsp::standalone_common
)
