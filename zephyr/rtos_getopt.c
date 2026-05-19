/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <zephyr/posix/unistd.h>
#include <getopt.h>
#include "rtos_getopt.h"

#include <zephyr/version.h>

#if ZEPHYR_VERSION_CODE < ZEPHYR_VERSION(4, 4, 0)
#define sys_getopt_state_get getopt_state_get
#define sys_getopt_init getopt_init
#define sys_getopt_state getopt_state
#define sys_getopt getopt
#endif

void rtos_getopt_init(int optind)
{
    struct sys_getopt_state *state;

    sys_getopt_init();

    state = sys_getopt_state_get();

    state->optind = optind;
}

int rtos_getopt(int argc, char *const argv[], const char *optstring)
{
    return sys_getopt(argc, argv, optstring);
}
