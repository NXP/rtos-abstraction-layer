/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "rtos_stdio.h"

/*
 * Duplicated declaration of function found in MCUX SDK:
 * - devices/<device>/utilities/debug_console/fsl_debug_console.h
 */
extern int DbgConsole_Vprintf(const char *fmt, va_list ap);

void rtos_printf(const char *fmt_s, ...)
{
    va_list ap;

    va_start(ap, fmt_s);
    DbgConsole_Vprintf(fmt_s, ap);
    va_end(ap);
}

void rtos_vprintf(const char *fmt_s, va_list ap)
{
    DbgConsole_Vprintf(fmt_s, ap);
}
