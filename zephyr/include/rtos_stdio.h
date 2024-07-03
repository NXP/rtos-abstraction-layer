/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTOS_ABSTRACTION_LAYER_STDIO_H_
#define _RTOS_ABSTRACTION_LAYER_STDIO_H_

#include <stdarg.h>

void rtos_printf(const char *fmt_s, ...);
void rtos_vprintf(const char *fmt_s, va_list ap);

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_STDIO_H_ */
