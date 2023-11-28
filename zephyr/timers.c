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
#include "timers.h"

#include <zephyr/sys/util.h>

TimerHandle_t xTimerCreate(const char *const pcTimerName,
                           const TickType_t xTimerPeriodInTicks,
                           const BaseType_t xAutoReload, void *const pvTimerID,
                           TimerCallbackFunction_t pxCallbackFunction)
{
    StaticTimer_t *timer;

    timer = k_malloc(sizeof(StaticTimer_t));
    if (!timer)
        return NULL;

    xTimerCreateStatic(pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID,
                       pxCallbackFunction, timer);

    timer->is_static = false;

    return timer;
}

static void xTimerCallback(struct k_timer *timer)
{
    StaticTimer_t *pxTimerBuffer = CONTAINER_OF(timer, struct xTIMER, timer);

    pxTimerBuffer->callback(pxTimerBuffer);
}

TimerHandle_t xTimerCreateStatic(const char *const pcTimerName,
                                 const TickType_t xTimerPeriodInTicks,
                                 const BaseType_t xAutoReload,
                                 void *const pvTimerID,
                                 TimerCallbackFunction_t pxCallbackFunction,
                                 StaticTimer_t *pxTimerBuffer)
{
    k_timer_init(&(pxTimerBuffer->timer), xTimerCallback, NULL);

    pxTimerBuffer->name = pcTimerName;
    pxTimerBuffer->autoreload = (xAutoReload == pdTRUE);
    pxTimerBuffer->is_static = true;
    pxTimerBuffer->id = pvTimerID;
    pxTimerBuffer->duration = xTimerPeriodInTicks;
    pxTimerBuffer->callback = pxCallbackFunction;

    if (xAutoReload)
        pxTimerBuffer->period = pxTimerBuffer->duration;
    else
        pxTimerBuffer->period = K_NO_WAIT;

    return pxTimerBuffer;
}

BaseType_t xTimerIsTimerActive(TimerHandle_t xTimer)
{
    return pdFALSE;
}

void *pvTimerGetTimerID(const TimerHandle_t xTimer)
{
    return xTimer->id;
}

BaseType_t xTimerStart(TimerHandle_t xTimer, TickType_t xTicksToWait)
{
    k_timer_start(&xTimer->timer, xTimer->duration, xTimer->period);

    return pdTRUE;
}

BaseType_t xTimerStop(TimerHandle_t xTimer, TickType_t xTicksToWait)
{
    k_timer_stop(&xTimer->timer);

    return pdTRUE;
}

BaseType_t xTimerChangePeriod(TimerHandle_t xTimer, TickType_t xNewPeriod,
                              TickType_t xTicksToWait)
{
    xTimer->duration = xNewPeriod;

    if (xTimer->autoreload)
        xTimer->period = xNewPeriod;

    k_timer_start(&xTimer->timer, xTimer->duration, xTimer->period);

    return pdTRUE;
}

BaseType_t xTimerDelete(TimerHandle_t xTimer, TickType_t xTicksToWait)
{
    k_timer_stop(&xTimer->timer);

    if (!xTimer->is_static)
        k_free(xTimer);

    return pdTRUE;
}
