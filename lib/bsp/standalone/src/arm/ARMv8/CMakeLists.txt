
add_library(xil_bsp_standalone_armv8_ps INTERFACE)
add_library(xil::bsp::standalone_armv8_ps ALIAS xil_bsp_standalone_armv8_ps)

target_include_directories(xil_bsp_standalone_armv8_ps
  INTERFACE
    $<$<STREQUAL:${XIL_PLATFORM},versal>:include_ps/platform/Versal>
    $<$<STREQUAL:${XIL_PLATFORM},ZynqMP>:include_ps/platform/ZynqMP>

add_subdirectory(32bit)
add_subdirectory(64bit)
