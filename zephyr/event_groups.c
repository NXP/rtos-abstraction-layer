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
#include "event_groups.h"

EventGroupHandle_t
xEventGroupCreateStatic(StaticEventGroup_t *pxEventGroupBuffer)
{
    k_event_init(pxEventGroupBuffer);

    return pxEventGroupBuffer;
}

EventBits_t xEventGroupWaitBits(EventGroupHandle_t xEventGroup,
                                const EventBits_t uxBitsToWaitFor,
                                const BaseType_t xClearOnExit,
                                const BaseType_t xWaitForAllBits,
                                TickType_t xTicksToWait)
{
    __ASSERT(!xWaitForAllBits, "xWaitForAllBits == pdTRUE not supported");

    EventBits_t uxReturn = 0;

    /* Zephyr and FreeRTOS have different semantics, reset flag for FreeRTOS is to clear after wait,
     * as Zephyr's flag is to clear before waiting. */
    uxReturn = k_event_wait(xEventGroup, uxBitsToWaitFor, pdFALSE, xTicksToWait);

    if (xClearOnExit)
        k_event_clear(xEventGroup, uxBitsToWaitFor);

    return uxReturn;
}

EventBits_t xEventGroupSetBits(EventGroupHandle_t xEventGroup,
                               const EventBits_t uxBitsToSet)
{
    k_event_post(xEventGroup, uxBitsToSet);

    return xEventGroup->events;
}
