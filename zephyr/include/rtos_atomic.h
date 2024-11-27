/*
* Copyright 2023-2024 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _RTOS_ABSTRACTION_LAYER_ATOMIC_H_
#define _RTOS_ABSTRACTION_LAYER_ATOMIC_H_

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

static inline void rtos_atomic_clear_bit(unsigned int nr, rtos_atomic_t *addr)
{
    return atomic_clear_bit(addr, nr);
}

static inline void rtos_atomic_set_bit(unsigned int nr, rtos_atomic_t *addr)
{
    return atomic_set_bit(addr, nr);
}

static inline int rtos_atomic_test_and_set_bit(unsigned int nr, rtos_atomic_t *addr)
{
    return atomic_test_and_set_bit(addr, nr);
}

static inline int rtos_atomic_test_and_clear_bit(unsigned int nr, rtos_atomic_t *addr)
{
    return atomic_test_and_clear_bit(addr, nr);
}

static inline int rtos_atomic_test_bit(unsigned int nr, rtos_atomic_t *addr)
{
    return atomic_test_bit(addr, nr);
}

#endif /* _RTOS_ABSTRACTION_LAYER_ATOMIC_H_ */
