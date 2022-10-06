add_library(xil_service_ffs STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::ffs ALIAS xil_service_ffs)

target_sources(xil_service_ffs
  PRIVATE
    src/include/diskio.h
    src/include/ff.h
    src/include/ffconf.h
    src/include/integer.h
    src/diskio.c
    src/ff.c
    src/ffsystem.c
    src/ffunicode.c
)

target_include_directories( xil_service_ffs SYSTEM
  PUBLIC
    src/include
)

target_compile_options( xil_service_ffs
  PRIVATE
  $<$<C_COMPILER_ID:Clang,ARMClang>:
    -Wno-implicit-int-conversion
    -Wno-sign-conversion
    -Wno-shorten-64-to-32
    -Wno-unused-macros>
)

target_link_libraries( xil_service_ffs
  PUBLIC
    xil::bsp::standalone_common
  PRIVATE
    xil::driver::sdps
)
