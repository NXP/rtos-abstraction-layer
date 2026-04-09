/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <zephyr/kernel.h>
#include "rtos_net_heap.h"

#if defined(CONFIG_RTOS_NET_HEAP_SIZE) && (CONFIG_RTOS_NET_HEAP_SIZE > 0)

static Z_HEAP_DEFINE_IN_SECT(_rtos_network_buf_heap, CONFIG_RTOS_NET_HEAP_SIZE,
                            __in_section(noinit, rtos_net_heap, kheap__rtos_network_buf));


rtos_net_heap_t __rtos_net_heap_buf = { .kheap = &_rtos_network_buf_heap };

rtos_net_heap_t *rtos_net_heap_handle = &__rtos_net_heap_buf;

#endif /* CONFIG_RTOS_NET_HEAP_SIZE > 0 */
