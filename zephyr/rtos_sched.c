/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "rtos_sched.h"

rtos_spinlock_key_t rtos_global_key;
rtos_spinlock_t rtos_global_spinlock;

#ifdef CONFIG_SMP
K_MUTEX_DEFINE(rtos_global_mutex);
#endif
