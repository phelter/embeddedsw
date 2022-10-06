add_library(xil_bsp_standalone_arm_cortexr5 STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_arm_cortexr5 ALIAS xil_bsp_standalone_arm_cortexr5)

target_sources(xil_bsp_standalone_arm_cortexr5 
  PRIVATE
  $<$<C_COMPILER_ID:ARMClang>:
    armclang/ARM_argv_veneer.c
    armclang/asm_vectors.S
    armclang/boot.S
    armclang/cpu_init.S
    armclang/xil-crt0.S
    armclang/xpseudo_asm_armclang.h>
  $<$<C_COMPILER_ID:GNU>:
    gcc/asm_vectors.S
    gcc/boot.S
    gcc/cpu_init.S
    gcc/xil-crt0.S>
  $<$<C_COMPILER_ID:IAR>:
    iccarm/asm_vectors.s
    iccarm/boot.s>
  $<$<STREQUAL:${XIL_PLATFORM},versal>:
    platform/versal/mpu.c
    platform/versal/xparameters_ps.h>
    $<$<STREQUAL:${XIL_PLATFORM},ZynqMP>:
    platform/ZynqMP/mpu.c
    platform/ZynqMP/xparameters_ps.h>

    sleep.c
    usleep.c
    xil_cache.c
    xil_cache.h
    xil_mmu.h
    xil_mpu.c
    xil_mpu.h
    xpm_counter.c
    xpm_counter.h
    xpseudo_asm.h
    xreg_cortexr5.h
    xtime_l.c
    xtime_l.h
)

target_include_directories( xil_bsp_standalone_arm_cortexr5 SYSTEM
  PUBLIC
   .
   $<$<BOOL:${XIL_PLATFORM}>:${CMAKE_CURRENT_SOURCE_DIR}/platform/${XIL_PLATFORM}>
)

target_link_libraries( xil_bsp_standalone_arm_cortexr5
  PUBLIC
    xil_bsp_standalone_arm_common
)
