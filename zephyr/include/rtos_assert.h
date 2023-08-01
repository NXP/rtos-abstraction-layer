/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_
#define _RTOS_ABSTRACTION_LAYER_ASSERT_H_

#include <zephyr/kernel.h>

static inline void rtos_assert(int expr)
{
    __ASSERT(expr, "");
}

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_ASSERT_H_ */
