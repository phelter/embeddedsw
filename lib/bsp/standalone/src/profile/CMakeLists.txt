add_library(xil_bsp_standalone_profile STATIC EXCLUDE_FROM_ALL)
add_library(xil::bsp::standalone_profile ALIAS xil_bsp_standalone_profile)

target_sources(xil_bsp_standalone_profile
  PRIVATE
    _profile_clean.c
    _profile_init.c
    _profile_timer_hw.c
    _profile_timer_hw.h
    dummy.S
    mblaze_nt_types.h
    profile_cg.c
    profile_config.h
    profile_hist.c
    profile_mcount_arm.S
    #profile_mcount_mb.S
    #profile_mcount_ppc.S
    profile.h
)

target_include_directories( xil_bsp_standalone_profile SYSTEM
  PUBLIC
   .
)

target_link_libraries( xil_bsp_standalone_profile
  PUBLIC
    xil_bsp_standalone_common
)
