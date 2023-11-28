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

#ifndef TIMERS_H
#define TIMERS_H

#ifndef INC_FREERTOS_H
#error "include FreeRTOS.h must appear in source files before include timers.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>

typedef struct xTIMER {
    /* must be first member */
    struct k_timer timer;
    k_timeout_t duration;
    k_timeout_t period;
    void (*callback)(struct xTIMER * xTimer);
    bool autoreload;
    bool is_static;
    void *id;
    const char *name;
} StaticTimer_t;
typedef StaticTimer_t *TimerHandle_t;

typedef void (*TimerCallbackFunction_t)(TimerHandle_t xTimer);

TimerHandle_t xTimerCreate(const char *const pcTimerName,
                           const TickType_t xTimerPeriodInTicks,
                           const BaseType_t xAutoReload, void *const pvTimerID,
                           TimerCallbackFunction_t pxCallbackFunction);

TimerHandle_t xTimerCreateStatic(const char *const pcTimerName,
                                 const TickType_t xTimerPeriodInTicks,
                                 const BaseType_t xAutoReload,
                                 void *const pvTimerID,
                                 TimerCallbackFunction_t pxCallbackFunction,
                                 StaticTimer_t *pxTimerBuffer);

void *pvTimerGetTimerID(const TimerHandle_t xTimer);

BaseType_t xTimerIsTimerActive(TimerHandle_t xTimer);

BaseType_t xTimerStart(TimerHandle_t xTimer, TickType_t xTicksToWait);

BaseType_t xTimerStop(TimerHandle_t xTimer, TickType_t xTicksToWait);

BaseType_t xTimerChangePeriod(TimerHandle_t xTimer, TickType_t xNewPeriod,
                              TickType_t xTicksToWait);

BaseType_t xTimerDelete(TimerHandle_t xTimer, TickType_t xTicksToWait);

#ifdef __cplusplus
}
#endif

#endif /* TIMERS_H */