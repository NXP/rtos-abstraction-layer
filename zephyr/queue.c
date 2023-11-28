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
#include "queue.h"

void vQueueDelete(QueueHandle_t xQueue)
{
    __ASSERT(xQueue, "vQueueDelete: Invalid queue handle");

    k_msgq_cleanup((struct k_msgq *)xQueue);
    k_free(xQueue);
}

QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength,
                           const UBaseType_t uxItemSize)
{
    struct k_msgq *mq;

    mq = k_malloc(sizeof(struct k_msgq));
    if (!mq)
        return NULL;

    k_msgq_alloc_init(mq, uxItemSize, uxQueueLength);

    return mq;
}

QueueHandle_t xQueueCreateStatic(const UBaseType_t uxQueueLength,
                                 const UBaseType_t uxItemSize,
                                 uint8_t *pucQueueStorage,
                                 StaticQueue_t *pxStaticQueue)
{
    k_msgq_init(pxStaticQueue, pucQueueStorage, uxItemSize, uxQueueLength);

    return pxStaticQueue;
}
