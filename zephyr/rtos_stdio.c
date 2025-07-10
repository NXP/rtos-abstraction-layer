/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <zephyr/sys/printk.h>
#include "rtos_stdio.h"

void rtos_printf(const char *fmt_s, ...)
{
    va_list ap;

    va_start(ap, fmt_s);
    vprintk(fmt_s, ap);
    va_end(ap);
}

void rtos_vprintf(const char *fmt_s, va_list ap)
{
    vprintk(fmt_s, ap);
}