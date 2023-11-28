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

#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include <stddef.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "portable.h"
#include "portmacro.h"
#include <zephyr/kernel.h>

#define configASSERT(x) __ASSERT(x, "");
#define configSTACK_DEPTH_TYPE uint16_t
#define PRIVILEGED_FUNCTION " "
#define pdMS_TO_TICKS(xTimeInMs) K_MSEC(xTimeInMs)

static inline unsigned int pdTICKS_TO_UINT(TickType_t ticks)
{
	return ticks.ticks;
}

static inline TickType_t pdUINT_TO_TICKS(unsigned int ticks)
{
	return K_TICKS(ticks);
}

static inline TickType_t pdMS_TO_TICKS_AT_LEAST(unsigned int uMsec, unsigned int xMinTicks)
{
    TickType_t min = { .ticks = xMinTicks };
    TickType_t timeout = K_MSEC(uMsec);

    return (timeout.ticks < min.ticks) ? min : timeout;
}

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)

#define pdPASS (pdTRUE)
#define pdFAIL (pdFALSE)

#define configMINIMAL_STACK_SIZE ((unsigned short)2048)
#define configMAX_PRIORITIES (CONFIG_NUM_PREEMPT_PRIORITIES - 1)

#ifdef __cplusplus
}
#endif

#endif /* INC_FREERTOS_H */
