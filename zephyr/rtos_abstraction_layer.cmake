#Description: RTOS Abstraction layer for zephyr; user_visible: True
message("rtos_abstraction_layer_zephyr headers are included for target ${RTOS_ABSTRACTION_LAYER_TARGET}")
target_include_directories(${RTOS_ABSTRACTION_LAYER_TARGET} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${RTOS_ABSTRACTION_LAYER_TARGET} PUBLIC zephyr_interface)

include_guard(GLOBAL)
message("rtos_abstraction_layer_zephyr sources are included for target ${RTOS_ABSTRACTION_LAYER_TARGET}")

target_sources(${RTOS_ABSTRACTION_LAYER_TARGET} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/rtos_mqueue.c
    ${CMAKE_CURRENT_LIST_DIR}/rtos_sched.c
    ${CMAKE_CURRENT_LIST_DIR}/rtos_thread.c
    ${CMAKE_CURRENT_LIST_DIR}/rtos_timer.c
)
