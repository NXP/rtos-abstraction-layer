/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_
#define _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_

#if defined(CONFIG_RTOS_NET_HEAP_SIZE) && (CONFIG_RTOS_NET_HEAP_SIZE > 0)
#error "RTOS network heap is not supported on FreeRTOS"
#endif

#include "rtos_heap.h"

#define rtos_net_malloc         rtos_malloc
#define rtos_net_free           rtos_free

#endif /* _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_ */
