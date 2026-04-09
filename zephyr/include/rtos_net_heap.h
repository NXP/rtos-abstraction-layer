/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_
#define _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_

#if defined(CONFIG_RTOS_NET_HEAP_SIZE) && (CONFIG_RTOS_NET_HEAP_SIZE > 0)

#include <zephyr/kernel.h>

typedef struct {
    struct k_heap *kheap;
} rtos_net_heap_t;

extern rtos_net_heap_t *rtos_net_heap_handle;

static inline void *rtos_net_malloc(size_t size)
{
    return k_heap_alloc(rtos_net_heap_handle->kheap, size, K_NO_WAIT);
}

static inline void rtos_net_free(void *pointer)
{
    k_heap_free(rtos_net_heap_handle->kheap, pointer);
}

#else

#include "rtos_heap.h"

#define rtos_net_malloc         rtos_malloc
#define rtos_net_free           rtos_free

#endif /* CONFIG_RTOS_NET_HEAP_SIZE > 0 */

#endif /* _RTOS_ABSTRACTION_LAYER_NET_HEAP_H_ */
