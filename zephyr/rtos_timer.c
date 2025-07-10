/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "rtos_timer.h"

static void rtos_timer_callback(struct k_timer *timer)
{
    rtos_timer_t *tmr = CONTAINER_OF(timer, struct _rtos_timer_t, timer);

    tmr->callback(tmr, tmr->data);
}

int rtos_timer_init(rtos_timer_t *timer, const char *name, bool periodic, rtos_timer_callback_t callback, void *data)
{
    k_timer_init(&(timer->timer), rtos_timer_callback, NULL);

    timer->name = name;
    timer->data = data;
    timer->callback = callback;
    timer->status = 0;

    if (periodic)
        timer->status |= RTOS_TIMER_STATUS_PERIODIC;

    return 0;
}

rtos_timer_t *rtos_timer_alloc_init(const char *name, bool periodic, rtos_timer_callback_t callback, void *data)
{
    rtos_timer_t *timer;
    int ret;

    timer = (rtos_timer_t *)k_malloc(sizeof(rtos_timer_t));
    if (!timer)
        goto err_alloc;

    ret = rtos_timer_init(timer, name, periodic, callback, data);
    if (ret < 0)
        goto err_init;

    timer->status |= RTOS_TIMER_STATUS_DYNAMIC;

    return timer;

err_init:
    k_free(timer);

err_alloc:
    return NULL;
}

int rtos_timer_destroy(rtos_timer_t *timer, rtos_tick_t expiry_time)
{
    k_timer_stop(&timer->timer);

    if (timer->status & RTOS_TIMER_STATUS_DYNAMIC)
        k_free(timer);

    return 0;
}
