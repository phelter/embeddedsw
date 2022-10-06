#######################################################################
# @copyright 2020 Retlek Systems Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# CMake Script for module level

cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0048 NEW) # project version
cmake_policy(SET CMP0076 NEW) # full paths

########################################################################
#
# Project-wide settings
project(xilinx-embeddedsw VERSION 0.1.0 LANGUAGES C)

########################################################################
# Requirements
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(XIL_PROCESSOR "" CACHE STRING "Xilinx FPGA SoC Processor type")
set(XIL_PROCESSOR_ARM_LIST
  ARMV8 # Arm ARMv8 32-bit processor
  CORTEXA9 # Arm CortexA9 processr
  CORTEXR5 # Arm CortexR5 processor
)
list(APPEND XIL_PROCESSOR_LIST 
    ${XIL_PROCESSOR_ARM_LIST}
    MICROBLAZE # Microblaze processor
)


set(XIL_PLATFORM "zc706" CACHE STRING "Xilinx FPGA SoC Platform type")
set(XIL_PLATFORM_ZYNQ_LIST zc702 zc706 zed)
set(XIL_PLATFORM_ZYNQMP_LIST ZynqMP zc102 zc102-es2)
set(XIL_PLATFORM_VERSAL_LIST versal)
set(XIL_PLATFORM_LIST
  versal # Versal platform - ARMV8 - assuming 64-bit
  ZynqMP # ZynqMP Platform - ARMV8 - assuming 64-bit
  zc702  # Zynq 702
  zc706  # Zynq 706
  zed    # Zynq Zed platform
  som    # TBD
)

if(XIL_PLATFORM AND NOT ( XIL_PLATFORM IN_LIST XIL_PLATFORM_LIST ) )
  message(FATAL_ERROR "XIL_PLATFORM value '${XIL_PLATFORM} must be either empty or one of '${XIL_PLATFORM_LIST}'")
endif()

########################################################################
# Compile Options
# Note the compile option strategy is to error on everything and then
# Per library opt-out of things that are warnings/errors.
# This ensures that no matter what strategy for compilation you take, the
# builds will still occur.
#
# Only tested with GNU and Clang.
# Other options are https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Naming of compilers translation map:
#
#  GNU : arm-non-eabi
#  ARMClang : TBD
#  IAR : TBD

add_compile_options(
    ### C Based Language and ID.
    $<$<C_COMPILER_ID:GNU>:-fdiagnostics-color=always>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-fcolor-diagnostics>

    $<$<C_COMPILER_ID:ARMClang,Clang,GNU>:-Wall>
    $<$<C_COMPILER_ID:ARMClang,Clang,GNU>:-Wextra>
    $<$<C_COMPILER_ID:ARMClang,Clang,GNU>:-Wpedantic>
    $<$<C_COMPILER_ID:ARMClang,Clang,GNU>:-Werror>
    $<$<C_COMPILER_ID:ARMClang,Clang>:-Weverything>

    # Documentation types
    # $<$<C_COMPILER_ID:Clang>:-fcomment-block-commands=retval> # Doesn't recongize doxygen retval
    # $<$<C_COMPILER_ID:Clang>:-fcomment-block-commands=copydetails> # Doesn't recongize doxygen copydetails

    # For cross compiling - adding in their respective bsp directories.
)

# -----------------------------------------------------------------------------
add_subdirectory(lib/bsp/standalone/src)
add_subdirectory(lib/sw_apps)
add_subdirectory(lib/sw_services)
add_subdirectory(XilinxProcessorIPLib/drivers)

########################################################################
# Install rules
# Not intended for installation but for inclusion with a pre-existing
# cmake build environment.

#install(TARGETS ${PROJECT_NAME}
#  DESTINATION lib)

# add_library(xil_bsp_api INTERFACE)
# add_library(xil_bsp::api ALIAS xil_bsp_api)

# target_include_directories( xil_bsp_api SYSTEM
#   INTERFACE
#   ${xil_bsp_dir}/include
# )

# # -----------------------------------------------------------------------------
# add_library(xil_bsp STATIC)

# target_sources(xil_bsp
#   PRIVATE
#     ${xil_bsp_dir}/include/_profile_timer_hw.h
#     ${xil_bsp_dir}/include/bspconfig.h
#     ${xil_bsp_dir}/include/mblaze_nt_types.h
#     ${xil_bsp_dir}/include/profile.h
#     ${xil_bsp_dir}/include/sleep.h
#     ${xil_bsp_dir}/include/smc.h
#     ${xil_bsp_dir}/include/vectors.h

#     ${xil_bsp_dir}/include/xbasic_types.h
#     ${xil_bsp_dir}/include/xddrps.h
#     ${xil_bsp_dir}/include/xdebug.h
#     ${xil_bsp_dir}/include/xdevcfg.h
#     ${xil_bsp_dir}/include/xdevcfg_hw.h
#     ${xil_bsp_dir}/include/xdmaps.h
#     ${xil_bsp_dir}/include/xdmaps_hw.h
#     ${xil_bsp_dir}/include/xemacps.h
#     ${xil_bsp_dir}/include/xemacps_bd.h
#     ${xil_bsp_dir}/include/xemacps_bdring.h
#     ${xil_bsp_dir}/include/xemacps_hw.h
#     ${xil_bsp_dir}/include/xenv.h
#     ${xil_bsp_dir}/include/xenv_standalone.h
#     ${xil_bsp_dir}/include/xgpiops.h
#     ${xil_bsp_dir}/include/xgpiops_hw.h
#     ${xil_bsp_dir}/include/xiicps.h
#     ${xil_bsp_dir}/include/xiicps_hw.h
#     ${xil_bsp_dir}/include/xiicps_xfer.h
#     ${xil_bsp_dir}/include/xil_assert.h
#     ${xil_bsp_dir}/include/xil_cache.h
#     ${xil_bsp_dir}/include/xil_cache_l.h
#     ${xil_bsp_dir}/include/xil_cache_vxworks.h
#     ${xil_bsp_dir}/include/xil_clocking.h
#     ${xil_bsp_dir}/include/xil_errata.h
#     ${xil_bsp_dir}/include/xil_exception.h
#     ${xil_bsp_dir}/include/xil_hal.h
#     ${xil_bsp_dir}/include/xil_io.h
#     ${xil_bsp_dir}/include/xil_macroback.h
#     ${xil_bsp_dir}/include/xil_mem.h
#     ${xil_bsp_dir}/include/xil_misc_psreset_api.h
#     ${xil_bsp_dir}/include/xil_mmu.h
#     ${xil_bsp_dir}/include/xil_printf.h
#     ${xil_bsp_dir}/include/xil_sleeptimer.h
#     ${xil_bsp_dir}/include/xil_spinlock.h
#     ${xil_bsp_dir}/include/xil_testcache.h
#     ${xil_bsp_dir}/include/xil_testio.h
#     ${xil_bsp_dir}/include/xil_testmem.h
#     ${xil_bsp_dir}/include/xil_types.h
#     ${xil_bsp_dir}/include/xil_util.h
#     ${xil_bsp_dir}/include/xl2cc.h
#     ${xil_bsp_dir}/include/xl2cc_counter.h
#     ${xil_bsp_dir}/include/xparameters.h
#     ${xil_bsp_dir}/include/xparameters_ps.h
#     ${xil_bsp_dir}/include/xplatform_info.h
#     ${xil_bsp_dir}/include/xpm_counter.h
#     ${xil_bsp_dir}/include/xpseudo_asm.h
#     ${xil_bsp_dir}/include/xpseudo_asm_gcc.h
#     ${xil_bsp_dir}/include/xqspips.h
#     ${xil_bsp_dir}/include/xqspips_hw.h
#     ${xil_bsp_dir}/include/xreg_cortexa9.h
#     ${xil_bsp_dir}/include/xscugic.h
#     ${xil_bsp_dir}/include/xscugic_hw.h
#     ${xil_bsp_dir}/include/xscutimer.h
#     ${xil_bsp_dir}/include/xscutimer_hw.h
#     ${xil_bsp_dir}/include/xscuwdt.h
#     ${xil_bsp_dir}/include/xscuwdt_hw.h
#     ${xil_bsp_dir}/include/xsdps.h
#     ${xil_bsp_dir}/include/xsdps_core.h
#     ${xil_bsp_dir}/include/xsdps_hw.h
#     ${xil_bsp_dir}/include/xspips.h
#     ${xil_bsp_dir}/include/xspips_hw.h
#     ${xil_bsp_dir}/include/xstatus.h
#     ${xil_bsp_dir}/include/xtime_l.h
#     ${xil_bsp_dir}/include/xttcps.h
#     ${xil_bsp_dir}/include/xttcps_hw.h
#     ${xil_bsp_dir}/include/xuartps.h
#     ${xil_bsp_dir}/include/xuartps_hw.h
    
#     ${xil_bsp_dir}/libsrc/ddrps_v1_2/src/xddrps.h
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps.h
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps_sinit.c
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps.c
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps_options.c
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps_selftest.c
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps_g.c
#     ${xil_bsp_dir}/libsrc/ttcps_v3_14/src/xttcps_hw.h
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt_sinit.c
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt_hw.h
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt_g.c
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt.h
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt_selftest.c
#     ${xil_bsp_dir}/libsrc/scuwdt_v2_4/src/xscuwdt.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_g.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_options.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_hw.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_sinit.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_hw.h
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips.h
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips.c
#     ${xil_bsp_dir}/libsrc/qspips_v3_9/src/xqspips_selftest.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips.h
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_selftest.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_g.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_sinit.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_hw.c
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_hw.h
#     ${xil_bsp_dir}/libsrc/spips_v3_6/src/xspips_options.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_intr.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_g.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_slave.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps.h
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_options.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_hw.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_master.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_selftest.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_hw.h
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_sinit.c
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_xfer.h
#     ${xil_bsp_dir}/libsrc/iicps_v3_13/src/xiicps_xfer.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_selftest.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic.h
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_sinit.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_hw.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_hw.h
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_g.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic.c
#     ${xil_bsp_dir}/libsrc/scugic_v4_5/src/xscugic_intr.c
#     ${xil_bsp_dir}/libsrc/cpu_cortexa9_v2_11/src/xcpu_cortexa9.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_misc_psreset_api.c
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/cpu_init.S>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_clocking.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/fcntl.c
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/errno.c>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xl2cc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_printf.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xparameters_ps.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xpm_counter.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_macroback.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/xpm_counter.c>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_exception.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testcache.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_mem.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/isatty.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_spinlock.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xpseudo_asm.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xtime_l.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/putnum.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_mmu.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_cache.c>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xbasic_types.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xstatus.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/smc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testmem.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/read.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/sbrk.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_misc_psreset_api.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_sleepcommon.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/lseek.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xl2cc_counter.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/_open.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/_exit.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_cache_l.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xenv.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_mem.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xdebug.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_printf.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/abort.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xtime_l.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil-crt0.S
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_io.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xreg_cortexa9.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/changelog.txt
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/asm_vectors.S
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_cache_vxworks.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/config.make
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/_sbrk.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/sleep.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/print.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testcache.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xplatform_info.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_clocking.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xl2cc_counter.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/kill.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/outbyte.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/time.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/sleep.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xenv_standalone.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/translation_table.S>
    
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_mcount_mb.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/_profile_timer_hw.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_config.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/mblaze_nt_types.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/_profile_clean.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_mcount_arm.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_cg.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_hist.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/dummy.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/profile_mcount_ppc.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/_profile_init.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/profile/_profile_timer_hw.c
    
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_util.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_misc_psreset_api.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/fcntl.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/errno.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_exceptions_i.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_exception.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_disable_exceptions.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_sleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_instructions.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_dcache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_cache.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_misc_psreset_api.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_enable_interrupts.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_icache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_interrupts_i.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/_exit.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/pvr.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_disable_dcache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/fsl.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_sleep.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_init_icache_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_icache_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_selftest.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_cache_ext_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_flush_cache_ext_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_exception_handler.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_init_dcache_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_enable_dcache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_exceptions_g.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/hw_exception_handler.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_dcache_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_update_dcache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_enable_icache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/pvr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_exception.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_invalidate_cache_ext.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_interrupt_handler.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/xil_cache.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_flush_dcache_range.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_flush_cache_ext.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_scrub.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_interrupts_g.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/mb_interface.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_flush_dcache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_enable_exceptions.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_disable_icache.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_disable_interrupts.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/microblaze/microblaze_update_icache.S
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/write.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_types.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_errata.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/clocking
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/clocking/xil_clocking.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/clocking/xil_clocking.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xpseudo_asm_gcc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/unlink.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testio.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xplatform_info.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_printf.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_macroback.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testcache.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_mem.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xbasic_types.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xstatus.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testmem.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_sleepcommon.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xenv.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_mem.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xdebug.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_printf.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_io.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_cache_vxworks.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/sleep.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/print.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testcache.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xplatform_info.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xenv_standalone.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_util.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_types.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/clocking
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/clocking/xil_clocking.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/clocking/xil_clocking.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testio.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xplatform_info.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_hal.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testio.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_util.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_assert.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_testmem.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/common/xil_assert.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/fstat.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_exception.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_hal.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_cache.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/boot.S>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/getpid.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testio.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/usleep.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/vectors.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_spinlock.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_sleeptimer.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_util.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_assert.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_testmem.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/vectors.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_assert.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/cpputest_time.c
#     # One of:
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xreg_cortexr5.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/platform/ZynqMP/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/platform/ZynqMP/mpu.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/platform/versal
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/platform/versal/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/platform/versal/mpu.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xpm_counter.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xpm_counter.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xpseudo_asm.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xtime_l.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xil_mmu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xil_cache.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/iccarm/asm_vectors.s
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/iccarm/boot.s
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xtime_l.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/gcc/cpu_init.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/gcc/xil-crt0.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/gcc/asm_vectors.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/gcc/boot.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/sleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xil_mpu.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/cpu_init.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/xpseudo_asm_armclang.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/xil-crt0.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/asm_vectors.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/boot.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/armclang/ARM_argv_veneer.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xil_cache.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/usleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexr5/xil_mpu.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_exception.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_spinlock.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/putnum.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/read.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/lseek.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/abort.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/exit.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/clock.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/write.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/remove.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/xpseudo_asm_iccarm.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/xpseudo_asm_iccarm.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/low_level_init.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/open.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/iccarm/close.c

#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/fcntl.c>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/errno.c>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/isatty.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/read.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/sbrk.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/lseek.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/_open.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/_exit.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/abort.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/_sbrk.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/kill.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/time.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/write.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/xpseudo_asm_gcc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/unlink.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/fstat.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/getpid.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/cpputest_time.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/open.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/gcc/close.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_open.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_time.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_exit.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_iserror.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_write.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_read.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_istty.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/armclang/_sys_close.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_exception.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/vectors.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_spinlock.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_sleeptimer.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/vectors.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/common/xil_sleeptimer.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_misc_psreset_api.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xl2cc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xparameters_ps.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xpm_counter.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xpm_counter.c>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xpseudo_asm.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xtime_l.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_mmu.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_cache.c>
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/iccarm/translation_table.s
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/iccarm/asm_vectors.s
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/iccarm/boot.s
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/smc.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_misc_psreset_api.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xl2cc_counter.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_cache_l.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xtime_l.h
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/gcc/cpu_init.S>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/gcc/xil-crt0.S>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/gcc/asm_vectors.S>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/gcc/translation_table.S>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/gcc/boot.S>
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xreg_cortexa9.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xl2cc_counter.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/sleep.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_errata.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_cache.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/usleep.c
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/xpseudo_asm_rvct.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_open.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_time.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_exit.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_iserror.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/translation_table.s>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_write.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/boot.S>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/asm_vectors.s>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_read.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/ARM_argv_veneer.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/xpseudo_asm_rvct.h>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_istty.c>
#     # $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/armcc/_sys_close.c>
#     $<$<BOOL:${CMAKE_CROSSCOMPILING}>:${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/cortexa9/xil_mmu.c>
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/ZynqMP/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/ZynqMP/CMakeLists.txt
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/ZynqMP/translation_table.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/versal
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/versal/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/platform/versal/CMakeLists.txt
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xpseudo_asm.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xtime_l.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xil_mmu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xil_cache.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xil_cache_l.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xtime_l.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/gcc/cpu_init.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/gcc/xil-crt0.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/gcc/asm_vectors.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/gcc/boot.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xreg_cortexa53.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/sleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xil_cache.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/usleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/32bit/xil_mmu.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP/gcc
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP/gcc/translation_table.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP/armclang
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/ZynqMP/armclang/translation_table.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal/xparameters_ps.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal/gcc
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal/gcc/translation_table.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal/armclang
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/platform/versal/armclang/translation_table.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpseudo_asm.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xtime_l.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_mmu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_cache.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xtime_l.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/gcc/xil-crt0.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/gcc/asm_vectors.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/gcc/boot.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/gcc/initialise_monitor_handles.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xreg_cortexa53.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/sleep.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_smc.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_errata.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/armclang/xpseudo_asm_armclang.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/armclang/asm_vectors.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/armclang/boot.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/armclang/ARM_argv_veneer.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/xen_console.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/xen_console.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/xen.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/xen_events.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/xen_events.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/arm64_ops.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/hypercall.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xpvxenconsole/hypercall.S
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_cache.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_smc.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/64bit/xil_mmu.c
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xlpd_slcr_secure.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xlpd_xppu_sink.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xfpd_slcr_secure.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xfpd_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu2_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu1_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xiou_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xocm_xmpu_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu5_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xlpd_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xlpd_xppu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu4_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xfpd_xmpu_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xfpd_xmpu_sink.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu3_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xiou_secure_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/ZynqMP/xddr_xmpu0_cfg.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xlpd_slcr_secure.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xlpd_iou_secure_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xfpd_slcr_secure.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xfpd_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xpmc_iou_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xlpd_iou_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xocm_xmpu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xpmc_xppu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xlpd_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xfpd_slave_xmpu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xlpd_xppu.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xpmc_iou_secure_slcr.h
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/arm/ARMv8/includes_ps/platform/Versal/xpmc_xmpu.h
    
#     # ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_mmu.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/bspconfig.h
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/inbyte.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/open.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/close.c
#     ${xil_bsp_dir}/libsrc/standalone_v7_5/src/xil_sleeptimer.h
#     #${xil_bsp_dir}/libsrc/coresightps_dcc_v1_8/src/xcoresightpsdcc.c
#     ${xil_bsp_dir}/libsrc/coresightps_dcc_v1_8/src/xcoresightpsdcc.h
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_intr.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_hw.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_options.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_g.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_sinit.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_selftest.c
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps_hw.h
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps.h
#     ${xil_bsp_dir}/libsrc/uartps_v3_11/src/xuartps.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_host.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_g.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps.h
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_hw.h
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_options.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_core.h
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_card.c
#     ${xil_bsp_dir}/libsrc/sdps_v3_12/src/xsdps_sinit.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg.h
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_hw.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_sinit.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_intr.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_g.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_hw.h
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg.c
#     ${xil_bsp_dir}/libsrc/devcfg_v3_7/src/xdevcfg_selftest.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_bdring.h
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps.h
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_control.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_bd.h
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_g.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_hw.h
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_sinit.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_intr.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_hw.c
#     ${xil_bsp_dir}/libsrc/emacps_v3_14/src/xemacps_bdring.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps_g.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps_sinit.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps_intr.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps_selftest.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps.c
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps.h
#     ${xil_bsp_dir}/libsrc/xadcps_v2_6/src/xadcps_hw.h
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps_sinit.c
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps_g.c
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps_hw.h
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps.c
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps.h
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps_hw.c
#     ${xil_bsp_dir}/libsrc/dmaps_v2_8/src/xdmaps_selftest.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_hw.h
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_sinit.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops.h
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_g.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_selftest.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_hw.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops.c
#     ${xil_bsp_dir}/libsrc/gpiops_v3_9/src/xgpiops_intr.c
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer.h
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer_sinit.c
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer.c
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer_hw.h
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer_selftest.c
#     ${xil_bsp_dir}/libsrc/scutimer_v2_3/src/xscutimer_g.c
# )

# target_compile_options( xil_bsp
#   PRIVATE
#     $<$<C_COMPILER_ID:Clang>: "-Wno-#pragma-messages" >
#     $<$<C_COMPILER_ID:Clang>:-Wno-cast-align>
#     $<$<C_COMPILER_ID:Clang>:-Wno-cast-qual>
#     $<$<C_COMPILER_ID:Clang>:-Wno-conditional-uninitialized>
#     $<$<C_COMPILER_ID:Clang>:-Wno-documentation-unknown-command>
#     $<$<C_COMPILER_ID:Clang>:-Wno-documentation>
#     $<$<C_COMPILER_ID:Clang>:-Wno-embedded-directive>
#     $<$<C_COMPILER_ID:Clang>:-Wno-empty-translation-unit>
#     $<$<C_COMPILER_ID:Clang>:-Wno-extra-semi-stmt>
#     $<$<C_COMPILER_ID:Clang>:-Wno-float-conversion>
#     $<$<C_COMPILER_ID:Clang>:-Wno-gnu-statement-expression>
#     $<$<C_COMPILER_ID:Clang>:-Wno-implicit-fallthrough>
#     $<$<C_COMPILER_ID:Clang>:-Wno-implicit-int-conversion>
#     $<$<C_COMPILER_ID:Clang>:-Wno-implicit-int-float-conversion>
#     $<$<C_COMPILER_ID:GNU>:-Wno-int-to-pointer-cast>
#     $<$<C_COMPILER_ID:Clang>:-Wno-int-to-void-pointer-cast>
#     $<$<C_COMPILER_ID:Clang>:-Wno-logical-not-parentheses>
#     $<$<C_COMPILER_ID:Clang>:-Wno-missing-noreturn>
#     $<$<C_COMPILER_ID:Clang>:-Wno-missing-prototypes>
#     $<$<C_COMPILER_ID:Clang>:-Wno-missing-variable-declarations>
#     $<$<C_COMPILER_ID:Clang>:-Wno-newline-eof>
#     $<$<C_COMPILER_ID:Clang>:-Wno-padded>
#     $<$<C_COMPILER_ID:Clang>:-Wno-parentheses-equality>
#     $<$<C_COMPILER_ID:Clang,GNU>:-Wno-pointer-to-int-cast>
#     $<$<C_COMPILER_ID:Clang>:-Wno-reserved-identifier>
#     $<$<C_COMPILER_ID:Clang>:-Wno-reserved-macro-identifier>
#     $<$<C_COMPILER_ID:Clang>:-Wno-shadow>
#     $<$<C_COMPILER_ID:Clang>:-Wno-shorten-64-to-32>
#     $<$<C_COMPILER_ID:Clang>:-Wno-sign-conversion>
#     $<$<C_COMPILER_ID:Clang>:-Wno-undef>
#     $<$<C_COMPILER_ID:Clang>:-Wno-unreachable-code>
#     $<$<C_COMPILER_ID:Clang>:-Wno-unreachable-code-return>
#     $<$<C_COMPILER_ID:Clang>:-Wno-unused-but-set-variable>
#     $<$<C_COMPILER_ID:Clang>:-Wno-unused-macros>
#     $<$<C_COMPILER_ID:Clang>:-Wno-used-but-marked-unused>
#     $<$<C_COMPILER_ID:Clang>:-Wno-void-pointer-to-int-cast>
# )

# target_link_libraries( xil_bsp
#   PUBLIC
#     xil_bsp::api
# )
