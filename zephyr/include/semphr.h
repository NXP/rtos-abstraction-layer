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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#ifndef INC_FREERTOS_H
#error "include FreeRTOS.h" must appear in source files before "include semphr.h"
#endif

#include <zephyr/kernel.h>

typedef struct k_mutex StaticSemaphore_t;
typedef struct k_mutex *SemaphoreHandle_t;

static inline BaseType_t xSemaphoreTake(SemaphoreHandle_t xQueue,
                                        TickType_t xTicksToWait)
{
    int ret;

    ret = k_mutex_lock(xQueue, xTicksToWait);

    return (ret < 0) ? pdFALSE : pdTRUE;
}

static inline BaseType_t xSemaphoreGive(SemaphoreHandle_t xQueue)
{
    int ret;

    ret = k_mutex_unlock(xQueue);

    return (ret < 0) ? pdFALSE : pdTRUE;
}

static inline SemaphoreHandle_t
xSemaphoreCreateMutexStatic(StaticSemaphore_t *pxStaticQueue)
{
    k_mutex_init(pxStaticQueue);

    return pxStaticQueue;
}

#endif /* SEMAPHORE_H */