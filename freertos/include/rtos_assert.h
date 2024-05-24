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
    configASSERT(expr); \
} while(0)

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_ */
