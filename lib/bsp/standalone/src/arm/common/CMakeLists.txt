add_library(xil_bsp_standalone_arm_common STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_arm_common ALIAS xil_bsp_standalone_arm_common)

target_sources(xil_bsp_standalone_arm_common
  PRIVATE
    $<$<C_COMPILER_ID:ARMClang>:
      armclang/_sys_close.c
      armclang/_sys_exit.c
      armclang/_sys_iserror.c
      armclang/_sys_istty.c
      armclang/_sys_open.c
      armclang/_sys_read.c
      armclang/_sys_time.c
      armclang/_sys_write.c>
    $<$<OR:$<BOOL:${CMAKE_CROSSCOMPILING}>,$<C_COMPILER_ID:GNU,Clang>>:
      gcc/_exit.c
      gcc/_open.c
      gcc/_sbrk.c
      gcc/abort.c
      gcc/close.c
      gcc/cpputest_time.c
      gcc/fcntl.c
      gcc/fstat.c
      gcc/getpid.c
      gcc/isatty.c
      gcc/kill.c
      gcc/lseek.c
      gcc/open.c
      gcc/read.c
      gcc/sbrk.c
      gcc/time.c
      gcc/unlink.c
      gcc/write.c
      gcc/xpseudo_asm_gcc.h>
    $<$<AND:$<BOOL:${CMAKE_CROSSCOMPILING}>,$<C_COMPILER_ID:GNU,Clang>>:
        gcc/errno.c>
      $<$<AND:$<NOT:$<BOOL:${CMAKE_CROSSCOMPILING}>>,$<C_COMPILER_ID:GNU,Clang>>:
        stubs/errno.c>
    $<$<C_COMPILER_ID:IAR>:
      iccarm/abort.c
      iccarm/clock.c
      iccarm/close.c
      iccarm/exit.c
      iccarm/low_level_init.c
      iccarm/lseek.c
      iccarm/open.c
      iccarm/read.c
      iccarm/remove.c
      iccarm/write.c
      iccarm/xpseudo_asm_iccarm.c
      iccarm/xpseudo_asm_iccarm.h>
    putnum.c
    vectors.c
    vectors.h
    xil_exception.c
    xil_exception.h
    xil_sleeptimer.c
    xil_sleeptimer.h
    xil_spinlock.c
    xil_spinlock.h
)

target_include_directories( xil_bsp_standalone_arm_common SYSTEM
  PUBLIC
    .
    #$<$<C_COMPILER_ID:ARMClang>:${CMAKE_CURRENT_SOURCE_DIR}/armclang> # No Headers
    $<$<C_COMPILER_ID:GNU,Clang>:${CMAKE_CURRENT_SOURCE_DIR}/gcc>
    $<$<C_COMPILER_ID:IAR>:${CMAKE_CURRENT_SOURCE_DIR}/iccarm>
)

target_compile_options( xil_bsp_standalone_arm_common
  PUBLIC
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-extra-semi-stmt>
  PRIVATE
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-extra-semi-stmt>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-missing-noreturn>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-missing-variable-declarations>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-reserved-identifier>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-shadow>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Wno-undef>
)

target_link_libraries( xil_bsp_standalone_arm_common
  PUBLIC
    xil::config
  PRIVATE
    xil::bsp::standalone_common
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_ZYNQ_LIST}>:xil::bsp::standalone_arm_cortexa9>
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_ZYNQMP_LIST}>:xil::bsp::standalone_armv8_64bit>
    $<$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_VERSAL_LIST}>:xil::bsp::standalone_armv8_64bit>
    # TODO: What about 32-bit little in ZynqMP and Versal?
)