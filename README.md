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
- basic standard output

Using the RTOS Abstraction Layer
--------------------------------
#### FreeRTOS

##### MCUX SDK (version 25.06 onward) - West Build System

When using MCUX SDK NG with the west build system, the RTOS Abstraction Layer is integrated through Kconfig configuration.

#### Configuration

Add the following configuration to your application's `prj.conf` file:

```bash
CONFIG_MCUX_COMPONENT_component.rtos_abstraction_layer_freertos=y
```

In your application's Kconfig, source the rtos-abstraction-layer's Kconfig as follows:

```bash
source /path/to/rtos-abstraction-layer/freertos/Kconfig
```

Include the CMake file as follows:

```cmake
include(/path/to/rtos-abstraction-layer/freertos/mcux_rtos_abstraction_layer.cmake)
```

##### MCUX SDK Legacy (version 2.16 or below) CMake

For legacy MCUX SDK legacy projects using CMake, add the following lines to your application's CMake:

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

And add the following Kconfig options:
```
CONFIG_DYNAMIC_THREAD=y
CONFIG_DYNAMIC_THREAD_ALLOC=y
```

To use the abstraction layer, include the top header file: 'rtos_abstraction_layer.h'
