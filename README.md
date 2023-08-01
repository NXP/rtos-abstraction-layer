RTOS Abstraction Layer
----------------------
RTOS Abstraction Layer is an abstraction layer for Real-Time Operating systems developped by NXP.
It aims to provide a generic API for RTOS services and selecting between different target RTOS.
It currently implements a generic API for the abstraction and supports Zephyr and FreeRTOS RTOS targets.

Supported RTOS services
-----------------------
- tasks
- locking: mutexes and spinlocks
- event_groups
- timers
- queues
- memory heap
- atomic operations

Using the RTOS Abstraction Layer
------------------------------
On the applications' CMake, add the following lines:

#### FreeRTOS
```cmake
set(RTOS_DIR <FreeRTOS Kernel directory>)
set(FREERTOS_PORT <FreeRTOS Kernel Port Folder>)
set(FREERTOS_CONFIG_INCLUDES <FreeRTOS Configs include directory>)
set(RTOS_ABSTRACTION_LAYER_TARGET <application target name>)
include(${RTOS_ABSTRACTION_LAYER_DIR}/rtos_abstraction_layer.cmake)
```

#### Zephyr

```cmake
set(RTOS_ABSTRACTION_LAYER_TARGET <application target name>)
include(${RTOS_ABSTRACTION_LAYER_DIR}/rtos_abstraction_layer.cmake)
```

Sources will be added to the specified target, as well as required headers.

To use the abstraction layer, include the top header file: 'rtos_abstraction_layer.h'
