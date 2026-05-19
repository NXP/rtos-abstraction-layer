/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTOS_ABSTRACTION_LAYER_GETOPT_H_
#define _RTOS_ABSTRACTION_LAYER_GETOPT_H_

/**
 @file
 @brief Getopt abstraction.
 @details
*/

/** Initialize getopt parsing state.
 *
 * This function resets getopt parsing state and then applies the requested
 * optind value to initialize parsing from the specified argument index.
 *
 * \ingroup rtos_getopt
 * \param optind Argument index to use as parsing start position.
 *
 */
void rtos_getopt_init(int optind);

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_GETOPT_H_ */
