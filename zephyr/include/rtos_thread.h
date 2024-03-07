/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_TASK_H_
#define _RTOS_ABSTRACTION_LAYER_TASK_H_

#include <zephyr/kernel.h>

#define RTOS_MAX_PRIORITY CONFIG_NUM_PREEMPT_PRIORITIES
#define RTOS_MINIMAL_STACK_SIZE 2048

typedef struct {
    struct k_thread thread;
    k_thread_stack_t *stack;
} rtos_thread_t;

int rtos_thread_create(rtos_thread_t *thread, unsigned int priority, unsigned int affinity,
                        size_t stack_size, const char *name,
                       void (*start_routine)(void *), void *arg);
void rtos_thread_abort(rtos_thread_t *thread);

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_TASK_H_ */
