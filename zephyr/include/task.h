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

#ifndef INC_TASK_H
#define INC_TASK_H

#ifndef INC_FREERTOS_H
#error "include FreeRTOS.h must appear in source files before include task.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>
#include "zephyr/sys/util.h"

struct tskTaskControlBlock {
    k_thread_stack_t *stack;
    struct k_thread thread;
    struct k_event notify_event;
    k_tid_t thread_id;
};

typedef struct tskTaskControlBlock *TaskHandle_t;

typedef void (*TaskFunction_t)(void *);
typedef BaseType_t (*TaskHookFunction_t)(void *);

#define xTaskGetTickCount() k_uptime_ticks()
#define NOTIFY_EVENT 1

static inline void taskYIELD() { k_yield(); }

void taskENTER_CRITICAL();

void taskEXIT_CRITICAL();

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName,
                       const configSTACK_DEPTH_TYPE usStackDepth,
                       void *const pvParameters, UBaseType_t uxPriority,
                       TaskHandle_t * pxCreatedTask);

void vTaskDelete(TaskHandle_t xTaskToDelete);

void vTaskDelay(const TickType_t xTicksToDelay);

void vTaskSuspendAll(void);

BaseType_t xTaskResumeAll(void);

static inline uint32_t ulTaskNotifyTake( BaseType_t xClearCountOnExit,
                            TickType_t xTicksToWait )
{
    TaskHandle_t task = CONTAINER_OF(k_current_get(), struct tskTaskControlBlock, thread);
    int ret = pdFALSE;
    uint32_t  events;

    /* FIXME, FreeRTOS vTaskNotifyGiveFromISR/ulTaskNotifyTake have counting semaphore semantics, while here a single bit state is supported */
    events = k_event_wait(&task->notify_event, NOTIFY_EVENT, false, xTicksToWait);
    if (events == NOTIFY_EVENT) {
        ret = pdTRUE;
    }

    k_event_clear(&task->notify_event, NOTIFY_EVENT);

    return ret;
}

static inline void vTaskNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                              BaseType_t *pxHigherPriorityTaskWoken )
{
    (*pxHigherPriorityTaskWoken) = pdFALSE;

    k_event_set(&xTaskToNotify->notify_event, NOTIFY_EVENT);
}

#ifdef __cplusplus
}
#endif

#endif /* INC_TASK_H */