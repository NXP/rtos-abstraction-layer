/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_SCHEDULING_H_
#define _RTOS_ABSTRACTION_LAYER_SCHEDULING_H_

#include <stdbool.h>
#include <zephyr/kernel.h>
#include "rtos_time.h"

typedef struct k_spinlock rtos_spinlock_t;
typedef k_spinlock_key_t rtos_spinlock_key_t;

static inline void rtos_sleep(rtos_tick_t ticks)
{
    k_sleep(ticks);
}

static inline void rtos_yield_from_isr(bool yield) {}

static inline void rtos_yield(void)
{
    k_yield();
}

static inline void rtos_spin_lock(rtos_spinlock_t *lock, rtos_spinlock_key_t *key)
{
    (*key) = k_spin_lock(lock);
}

static inline void rtos_spin_unlock(rtos_spinlock_t *lock, rtos_spinlock_key_t key)
{
    k_spin_unlock(lock, key);
}

#ifdef CONFIG_SMP
extern struct k_mutex rtos_global_mutex;
#endif

static inline void rtos_mutex_global_lock(void)
{
#ifdef CONFIG_SMP
    k_mutex_lock(&rtos_global_mutex, K_FOREVER);
#else
    k_sched_lock();
#endif
}

static inline void rtos_mutex_global_unlock(void)
{
#ifdef CONFIG_SMP
    k_mutex_unlock(&rtos_global_mutex);
#else
    k_sched_unlock();
#endif
}

extern rtos_spinlock_key_t rtos_global_key;
extern rtos_spinlock_t rtos_global_spinlock;

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_SCHEDULING_H_ */
