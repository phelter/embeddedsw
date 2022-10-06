add_library(xil_service_plmi STATIC EXCLUDE_FROM_ALL)
add_library(xil::service::plmi ALIAS xil_service_plmi)

target_sources(xil_service_plmi
  PRIVATE
    src/list.h
    src/xplmi_cdo.c
    src/xplmi_cdo.h
    src/xplmi_cmd.c
    src/xplmi_cmd.h
    src/xplmi_config.h
    src/xplmi_debug.c
    src/xplmi_debug.h
    src/xplmi_dma.c
    src/xplmi_dma.h
    src/xplmi_err_cmd.c
    src/xplmi_err.c
    src/xplmi_err.h
    src/xplmi_error_node.h
    src/xplmi_event_logging.c
    src/xplmi_event_logging.h
    src/xplmi_generic.c
    src/xplmi_generic.h
    src/xplmi_gic_interrupts.c
    src/xplmi_gic_interrupts.h
    src/xplmi_hw.h
    src/xplmi_ipi.c
    src/xplmi_ipi.h
    src/xplmi_modules.c
    src/xplmi_modules.h
    src/xplmi_proc.c
    src/xplmi_proc.h
    src/xplmi_scheduler.c
    src/xplmi_scheduler.h
    src/xplmi_ssit.c
    src/xplmi_ssit.h
    src/xplmi_status.h
    src/xplmi_sysmon.c
    src/xplmi_sysmon.h
    src/xplmi_task.c
    src/xplmi_task.h
    src/xplmi_util.c
    src/xplmi_util.h
    src/xplmi_wdt.c
    src/xplmi_wdt.h
    src/xplmi.c
    src/xplmi.h
)

target_include_directories( xil_service_plmi SYSTEM
  PUBLIC
    src
)

target_link_libraries( xil_service_plmi
  PUBLIC
    xil::bsp::standalone_common
)
