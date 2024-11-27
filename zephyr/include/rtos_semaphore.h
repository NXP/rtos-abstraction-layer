/*
 * Copyright 2022, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_SEMAPHORE_H_
#define _RTOS_ABSTRACTION_LAYER_SEMAPHORE_H_

#include <zephyr/kernel.h>
#include "rtos_time.h"

typedef struct k_sem rtos_sem_t;

/** Initialize a semaphore.
 *
 * This function initializes a semaphore before it can be used.
 *
 * \ingroup rtos_semaphore
 * \return 	0 if success, -1 otherwise.
 * \param	sem Pointer to the semaphore.
 * \param	init_count Initial value for the semaphore
 */
static inline int rtos_sem_init(rtos_sem_t *sem, uint32_t init_count)
{
    int ret;

    ret = k_sem_init(sem, init_count, UINT_MAX);

    return (ret < 0) ? -1 : 0;
}

/** Release a semaphore.
 *
 * This function releases a semaphore.
 *
 * \ingroup rtos_semaphore
 * \return 	0 if success, -1 otherwise.
 * \param	sem Pointer to the semaphore.
 */
static inline int rtos_sem_give(rtos_sem_t *sem)
{
    k_sem_give(sem);

    return 0;
}

/** Release a semaphore from an interrupt.
 *
 * This function releases a semaphore.
 *
 * Can be called from an interrupt and specifies if a context switch is needed.
 *
 * \ingroup rtos_semaphore
 * \return 	0 if success, -1 otherwise.
 * \param	sem Pointer to the semaphore.
 * \param 	yield Value that specifies if a context switch is needed at ISR exit.
 */
static inline int rtos_sem_give_from_isr(rtos_sem_t *sem, bool *yield)
{
    ARG_UNUSED(yield);

    rtos_sem_give(sem);

    return 0;
}

/** Take a semaphore.
 *
 * This function takes a semaphore.
 * The current thread is blocked until a semaphore become available or the
 * timeout period expires.
 *
 * \ingroup rtos_semaphore
 * \return 	0 if success, -1 otherwise.
 * \param	sem Pointer to the semaphore.
 * \param 	ticks Timeout period.
 */
static inline int rtos_sem_take(rtos_sem_t *sem, rtos_tick_t ticks)
{
    int ret;
    
    ret = k_sem_take(sem, ticks);
    
    return (ret < 0) ? -1 : 0;
}

/** Take a semaphore from an interrupt.
 *
 * This function takes a semaphore.
 *
 * Can be called from an interrupt and specifies if a context switch is needed.
 *
 * \ingroup rtos_semaphore
 * \return 	0 if success, -1 otherwise.
 * \param	sem Pointer to the semaphore.
 * \param 	yield Value that specifies if a context switch is needed at ISR exit.
 */ 
static inline int rtos_sem_take_from_isr(rtos_sem_t *sem, bool *yield)
{
    ARG_UNUSED(yield);
    int ret;

    ret = k_sem_take(sem, RTOS_NO_WAIT);

    return (ret < 0) ? -1 : 0;
}

/** Delete a semaphore.
 *
 * This function deletes a semaphore.
 *
 * \ingroup rtos_semaphore
 * \param 	sem Pointer to the semaphore.
 */
static inline void rtos_sem_destroy(rtos_sem_t *sem)
{
    k_sem_reset(sem);
}

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_SEMAPHORE_H_ */