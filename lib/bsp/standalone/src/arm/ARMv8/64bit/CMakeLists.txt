add_library(xil_bsp_standalone_armv8_64bit STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_armv8_64bit ALIAS xil_bsp_standalone_armv8_64bit)

target_sources(xil_bsp_standalone_armv8_64bit
  PRIVATE
    sleep.c
    xil_cache.c
    xil_cache.h
    xil_errata.h
    xil_mmu.c
    xil_mmu.h
    xil_smc.c
    xil_smc.h
    xpseudo_asm.h
    xreg_cortexa53.h
    xtime_l.c
    xtime_l.h
  $<$<C_COMPILER_ID:ARMClang>:
    armclang/ARM_argv_veneer.c
    armclang/asm_vectors.S
    armclang/boot.S
    armclang/xpseudo_asm_armclang.h>
  $<$<AND:$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_LIST}>,$<C_COMPILER_ID:ARMClang>>:
    platform/${XIL_PLATFORM}/armclang/translation_table.S>
  $<$<C_COMPILER_ID:GNU>:
    gcc/asm_vectors.S
    gcc/boot.S
    gcc/initialise_monitor_handles.c
    gcc/xil-crt0.S>
  $<$<AND:$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_LIST}>,$<C_COMPILER_ID:ARMClang>>:
    platform/${XIL_PLATFORM}/gcc/translation_table.S>
    xpvxenconsole/arm64_ops.h
    xpvxenconsole/hypercall.h
    xpvxenconsole/hypercall.S
    xpvxenconsole/xen_console.c
    xpvxenconsole/xen_console.h
    xpvxenconsole/xen_events.c
    xpvxenconsole/xen_events.h
    xpvxenconsole/xen.h
)

# TODO: Add target_compiler_options to allow both 32 and 64bit to compile at same time

target_include_directories( xil_bsp_standalone_armv8_64bit SYSTEM
  PUBLIC
   .
   xpvxenconsole
  PRIVATE
  $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_LIST}:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/${XIL_PLATFORM}>
)

target_compile_options (xil_bsp_standalone_armv8_64bit
  PRIVATE
  $<$<C_COMPILER_ID:GNU>:
    -nostartfiles
    -march=armv8-a>
)

target_link_libraries(xil_bsp_standalone_armv8_64bit
  PUBLIC
    xil_bsp_standalone_armv8_ps
    xil_bsp_standalone_arm_commonS
)
