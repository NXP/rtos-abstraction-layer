/*
* Copyright 2024 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 @file
 @brief Time abstraction.
 @details
*/

#ifndef _RTOS_ABSTRACTION_LAYER_TIME_H_
#define _RTOS_ABSTRACTION_LAYER_TIME_H_

#include <zephyr/kernel.h>

typedef k_timeout_t rtos_tick_t;

#define RTOS_WAIT_FOREVER K_FOREVER
#define RTOS_NO_WAIT K_NO_WAIT

static inline rtos_tick_t RTOS_MS_TO_TICKS(unsigned int msec)
{
    return K_MSEC(msec);
}

static inline rtos_tick_t RTOS_UINT_TO_TICKS(unsigned int ticks)
{
    return K_TICKS(ticks);
}

static inline unsigned int RTOS_TICKS_TO_UINT(rtos_tick_t ticks)
{
    return ticks.ticks;
}

static inline rtos_tick_t RTOS_MS_TO_TICKS_AT_LEAST(unsigned int uMsec, unsigned int xMinTicks)
{
    rtos_tick_t min = { .ticks = xMinTicks };
    rtos_tick_t timeout = K_MSEC(uMsec);

    return (timeout.ticks < min.ticks) ? min : timeout;
}

static inline uint64_t rtos_get_current_time(void)
{
    return k_uptime_ticks();
}

#endif /* _RTOS_ABSTRACTION_LAYER_TIME_H_ */
