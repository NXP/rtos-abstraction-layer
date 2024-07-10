/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <zephyr/kernel.h>
#include "rtos_thread.h"

#define WORD uint16_t

static void rtos_thread_callback(void * p1, void * p2, void * p3)
{
    void (*function)(void *) = p1;
    function(p2);
}

int rtos_thread_create(rtos_thread_t *thread, unsigned int priority, unsigned int affinity,
                       size_t stack_size, const char *name,
                       void (*start_routine)(void *), void *arg)
{
    int thread_priority;
    size_t stack_depth;
    k_tid_t thread_id;
    int ret;

    stack_depth = Z_KERNEL_STACK_SIZE_ADJUST(stack_size * sizeof(WORD));
    thread_priority = ((CONFIG_NUM_PREEMPT_PRIORITIES - 1) - priority);
    thread_priority = (thread_priority < 0)? 0: thread_priority;

    thread->stack = k_aligned_alloc(Z_KERNEL_STACK_OBJ_ALIGN, stack_depth);
    if (!thread->stack)
       goto err_alloc;

    thread_id = k_thread_create(&thread->thread, thread->stack, stack_depth,
                                 rtos_thread_callback, start_routine, arg, NULL,
                                 thread_priority, 0, K_FOREVER);
    if (!thread_id)
       goto err;

    if (name)
        k_thread_name_set(thread_id, name);

    ret = k_thread_cpu_pin(thread_id, affinity);
    if (ret < 0)
        goto err;

    k_thread_start(thread_id);

    return 0;

err:
    k_free(thread->stack);

err_alloc:
    return -1;
}

void rtos_thread_abort(rtos_thread_t *thread)
{
    __ASSERT(thread, "thread == NULL not supported");

    k_free(thread->stack);
    k_thread_abort(&thread->thread);
}
