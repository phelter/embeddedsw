add_library(xil_service_timer STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::timer ALIAS xil_service_timer)

set(XIL_SERVICE_TIMER_TYPE "DEFAULT" CACHE STRING "Service Timer type")
set(XIL_SERVICE_TIMER_TYPE_LIST AXI DEFAULT SCU TTCPS)

if (NOT XIL_SERVICE_TIMER_TYPE IN_LIST XIL_SERVICE_TIMER_TYPE_LIST)
    message(FATAL_ERROR "Invalid Service timer type, must be one of ${XIL_SERVICE_TIMER_TYPE_LIST}")
endif()

target_sources(xil_service_timer
  PRIVATE
    $<$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},AXI>:src/core/axi_timer/axi_timer.c>
    # TODO(phelter): Sort out Default for various types of processors.
    # $<$<AND:$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},DEFAULT>,$<STREQUAL:${XIL_PROCESSOR},"cortexr5">>:
    #     src/core/default_timer/cortexr5_sleep.c>
    $<$<AND:$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},DEFAULT>,$<IN_LIST:${XIL_PLATFORM},${XIL_PLATFORM_ZYNQ_LIST}>>:
        src/core/default_timer/globaltimer_sleep_zynq.c>
    $<$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},DEFAULT>:
        src/core/default_timer/globaltimer_sleep.c>
    # $<$<AND:$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},DEFAULT>,$<STREQUAL:${XIL_PROCESSOR},"microblaze">>:
    #     src/core/default_timer/microblaze_sleep.c>
    $<$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},SCU>:src/core/scutimer/scutimer.c>
    $<$<STREQUAL:${XIL_SERVICE_TIMER_TYPE},TTCPS>:src/core/ttcps/ttcps.c>

    src/sleep.h
    src/xiltimer.c
    src/xiltimer.h
)

target_include_directories( xil_service_timer SYSTEM
  PUBLIC
    src
)

target_link_libraries( xil_service_timer
  PUBLIC
    xil::bsp::standalone_common
)
