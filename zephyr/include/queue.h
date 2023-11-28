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

#ifndef QUEUE_H
#define QUEUE_H

#ifndef INC_FREERTOS_H
#error "include FreeRTOS.h" must appear in source files before "include queue.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>

typedef struct k_msgq StaticQueue_t;
typedef struct k_msgq *QueueHandle_t;

QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength,
                           const UBaseType_t uxItemSize);

QueueHandle_t xQueueCreateStatic(const UBaseType_t uxQueueLength,
                                 const UBaseType_t uxItemSize,
                                 uint8_t *pucQueueStorage,
                                 StaticQueue_t *pxStaticQueue);

void vQueueDelete(QueueHandle_t xQueue);

static inline BaseType_t xQueueReceive(QueueHandle_t xQueue,
                                       void *pvBuffer,
                                       TickType_t xTicksToWait)
{
    int ret;

    ret = k_msgq_get(xQueue, pvBuffer, xTicksToWait);

    return (ret < 0) ? pdFALSE : pdTRUE;
}

static inline BaseType_t
xQueueReceiveFromISR(QueueHandle_t xQueue, void *pvBuffer,
                     BaseType_t * pxHigherPriorityTaskWoken)
{
    if (pxHigherPriorityTaskWoken)
        (*pxHigherPriorityTaskWoken) = pdFALSE;

    return xQueueReceive(xQueue, pvBuffer, K_NO_WAIT);
}

static inline BaseType_t xQueuePeek(QueueHandle_t xQueue, void *pvBuffer,
                                    TickType_t xTicksToWait)
{
    int ret;

    ret = k_msgq_peek(xQueue, pvBuffer);

    return (ret < 0) ? pdFALSE : pdTRUE;
}

static inline BaseType_t xQueueSendToBack(QueueHandle_t xQueue,
                                          const void *const pvItemToQueue,
                                          TickType_t xTicksToWait)
{
    int ret;

    ret = k_msgq_put(xQueue, pvItemToQueue, xTicksToWait);

    return (ret < 0) ? pdFALSE : pdTRUE;
}

static inline BaseType_t
xQueueSendToBackFromISR(QueueHandle_t xQueue, const void *const pvItemToQueue,
                        BaseType_t * pxHigherPriorityTaskWoken)
{
    if (pxHigherPriorityTaskWoken)
        (*pxHigherPriorityTaskWoken) = pdFALSE;

    return xQueueSendToBack(xQueue, pvItemToQueue, K_NO_WAIT);
}

static inline BaseType_t xQueueSend(QueueHandle_t xQueue,
                                    const void *const pvItemToQueue,
                                    TickType_t xTicksToWait)
{
    return xQueueSendToBack(xQueue, pvItemToQueue, xTicksToWait);
}

static inline BaseType_t
xQueueSendFromISR(QueueHandle_t xQueue, const void *const pvItemToQueue,
                  BaseType_t * pxHigherPriorityTaskWoken)
{
    if (pxHigherPriorityTaskWoken)
        (*pxHigherPriorityTaskWoken) = pdFALSE;

    return xQueueSendToBack(xQueue, pvItemToQueue, K_NO_WAIT);
}

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */
