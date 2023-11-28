/*
* Copyright 2023 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 @file
 @brief atomic access interface
 @details
*/

#ifndef _ZEPHYR_ATOMIC_H_
#define _ZEPHYR_ATOMIC_H_

#include <zephyr/sys/atomic.h>

typedef atomic_t rtos_atomic_t;

static inline void rtos_atomic_set(rtos_atomic_t *addr, unsigned int val)
{
    atomic_set(addr, val);
}

static inline rtos_atomic_t rtos_atomic_read(rtos_atomic_t *addr)
{
    return atomic_get(addr);
}

static inline void rtos_atomic_add(unsigned int val, rtos_atomic_t *addr)
{
    atomic_add(addr, val);
}

static inline void rtos_atomic_sub(unsigned int val, rtos_atomic_t *addr)
{
    atomic_sub(addr, val);
}

static inline void rtos_atomic_inc(rtos_atomic_t *addr)
{
    atomic_inc(addr);
}

static inline void rtos_atomic_dec(rtos_atomic_t *addr)
{
    atomic_dec(addr);
}

static inline rtos_atomic_t rtos_atomic_xchg(rtos_atomic_t *addr, unsigned int new)
{
    return atomic_set(addr, new);
}

#endif /* _ZEPHYR_ATOMIC_H_ */
