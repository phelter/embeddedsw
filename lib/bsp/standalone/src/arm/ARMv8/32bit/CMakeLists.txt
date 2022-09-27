# Only supported for GNU.
# if(NOT CMAKE_C_COMPILER_ID IN_LIST GNU)
#     return()
# endif()

add_library(xil_bsp_standalone_armv8_32bit STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_armv8_32bit ALIAS xil_bsp_standalone_armv8_32bit)

# TODO(Add check if compiler is only GCC for this.)
target_sources(xil_bsp_standalone_armv8_32bit
  PRIVATE
    sleep.c
    usleep.c
    xil_cache_l.h
    xil_cache.c
    xil_cache.h
    xil_mmu.c
    xil_mmu.h
    xparameters_ps.h
    xpseudo_asm.h
    xreg_cortexa53.h
    xtime_l.c
    xtime_l.h  
    $<$<C_COMPILER_ID:GNU>:
      gcc/asm_vectors.S
      gcc/boot.S
      gcc/cpu_init.S
      gcc/xil-crt0.S>
    $<$<STREQUAL:${XIL_PLATFORM}:versal>:
      platform/${XIL_PLATFORM}/xparameters_ps.h>
    $<$<STREQUAL:${XIL_PLATFORM}:ZynqMP>:
      platform/${XIL_PLATFORM}/xparameters_ps.h
      platform/${XIL_PLATFORM}/translation_table.S>
)

# TODO: Add target_compiler_options to allow both 32 and 64bit to compile at same time

target_include_directories( xil_bsp_standalone_armv8_32bit SYSTEM
  PUBLIC
   .
   $<$<IN_LIST:${XIL_PLATFORM}:${XIL_PLATFORM_LIST}>:
   platform/${XIL_PLATFORM}>
)

target_compile_options (xil_bsp_standalone_armv8_32bit
  PUBLIC
    -nostartfiles
    -mcpu=armv7-a
)

target_link_libraries(xil_bsp_standalone_armv8_32bit
  PUBLIC
    xil_bsp_standalone_armv8_ps
    xil_bsp_standalone_arm_common
)
