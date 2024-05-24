/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_
#define _RTOS_ABSTRACTION_LAYER_ASSERT_H_

#include "FreeRTOS.h"

#define rtos_assert(expr, fmt, ...)       \
do { \
    if (!(expr)) { \
        configASSERT(expr); \
        while (1); \
    } \
} while (0)

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_ */
