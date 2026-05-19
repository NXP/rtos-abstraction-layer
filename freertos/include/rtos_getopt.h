/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTOS_ABSTRACTION_LAYER_GETOPT_H_
#define _RTOS_ABSTRACTION_LAYER_GETOPT_H_

#include <getopt.h>

/**
 @file
 @brief Getopt abstraction.
 @details
*/

/** Initialize getopt parsing state.
 *
 * This function initializes getopt parsing state from the provided values.
 *
 * \ingroup rtos_getopt
 * \param _optind Argument index to use as parsing start position.
 * \param _opterr Control whether getopt prints error messages.
 *
 * \note On FreeRTOS builds using the standard C library getopt
 * implementation, this function updates the global getopt state.
 */
static inline void rtos_getopt_init(int _optind, int _opterr)
{
    optind = _optind;
    opterr = _opterr;
}

/** Parse command line options.
 *
 * This function parses command line options using the underlying RTOS
 * getopt implementation.
 *
 * \ingroup rtos_getopt
 * \return Option character on success, -1 when parsing is complete.
 * \param argc Argument count.
 * \param argv Argument vector.
 * \param optstring String containing the legitimate option characters.
 */
static inline int rtos_getopt(int argc, char *const argv[], const char *optstring)
{
    return getopt(argc, argv, optstring);
}

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_GETOPT_H_ */
