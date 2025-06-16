
if(CONFIG_MCUX_COMPONENT_component.rtos_abstraction_layer_freertos)
message("rtos_abstraction_layer (freertos) headers are included for target ${RTOS_ABSTRACTION_LAYER_TARGET}")

mcux_add_include(
    INCLUDES
    include
)

include_guard(GLOBAL)
message("rtos_abstraction_layer (freertos) sources are included for target ${RTOS_ABSTRACTION_LAYER_TARGET}")

mcux_add_source(
    SOURCES
    rtos_atomic.c
    rtos_mqueue.c
    rtos_sched.c
    rtos_stdio.c
    rtos_timer.c
    rtos_thread.c
    include/*.h
)
endif()
