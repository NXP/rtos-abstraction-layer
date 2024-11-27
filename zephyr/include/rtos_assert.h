/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_
#define _RTOS_ABSTRACTION_LAYER_ASSERT_H_

#include <zephyr/kernel.h>

#define rtos_assert(expr, msg, ...)       \
do { \
    if (unlikely(!(expr))) {    \
        __ASSERT(expr, msg, ##__VA_ARGS__);  \
        while (1);   \
    }   \
} while (0)

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_ */
