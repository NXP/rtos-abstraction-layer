/*
 * FreeRTOS Kernel V10.5.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include "FreeRTOS.h"
#include "task.h"

#ifdef CONFIG_SMP
static K_MUTEX_DEFINE(global_mutex);
#endif

static k_spinlock_key_t key;
static struct k_spinlock lock;
static unsigned int count = 0;

void taskENTER_CRITICAL()
{
    __ASSERT(count == 0, "Spinlock: non zero count");

    key = k_spin_lock(&lock);
    count++;
}

void taskEXIT_CRITICAL()
{
    count--;
    if (!count)
        k_spin_unlock(&lock, key);
}

static void vTaskCallback(void * p1, void * p2, void * p3)
{
    TaskFunction_t function = p1;
    function(p2);
}

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName,
                       const configSTACK_DEPTH_TYPE usStackDepth,
                       void *const pvParameters, UBaseType_t uxPriority,
                       TaskHandle_t * pxCreatedTask)
{
    TaskHandle_t task;
    k_tid_t thread_id;
    size_t stack_depth;

    stack_depth = Z_KERNEL_STACK_SIZE_ADJUST(usStackDepth * sizeof(configSTACK_DEPTH_TYPE));

    task = k_malloc(sizeof(struct tskTaskControlBlock));
    if (!task)
        goto err_task_alloc;

    task->stack = k_aligned_alloc(Z_KERNEL_STACK_OBJ_ALIGN, stack_depth);
    if (!task->stack)
        goto err_stack_alloc;

    thread_id = k_thread_create(
        &task->thread, task->stack, stack_depth,
        vTaskCallback, pxTaskCode, pvParameters, NULL,
        ((CONFIG_NUM_PREEMPT_PRIORITIES - 1) - uxPriority), 0, K_NO_WAIT);

    if (!thread_id)
        goto err_thread_create;

    task->thread_id = thread_id;
    k_thread_name_set(task->thread_id, pcName);

    k_event_init(&task->notify_event);

    if (pxCreatedTask)
        *pxCreatedTask = task;

    return pdPASS;

err_thread_create:
    k_free(task->stack);

err_stack_alloc:
    k_free(task);

err_task_alloc:
    return pdFAIL;
}

void vTaskDelete(TaskHandle_t xTaskToDelete)
{
    __ASSERT(xTaskToDelete, "xTaskToDelete == NULL not supported");

    k_thread_abort(xTaskToDelete->thread_id);
    k_free(xTaskToDelete->stack);
    k_free(xTaskToDelete);
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    k_sleep(xTicksToDelay);
}

void vTaskSuspendAll(void)
{
#ifdef CONFIG_SMP
    k_mutex_lock(&global_mutex, K_FOREVER);
#else
    k_sched_lock();
#endif
}

BaseType_t xTaskResumeAll(void)
{
#ifdef CONFIG_SMP
    k_mutex_unlock(&global_mutex);
#else
    k_sched_unlock();
#endif

    return pdTRUE;
}
