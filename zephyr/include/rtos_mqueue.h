/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _RTOS_ABSTRACTION_LAYER_MQUEUE_H_
#define _RTOS_ABSTRACTION_LAYER_MQUEUE_H_

#include <zephyr/kernel.h>
#include "rtos_time.h"

typedef struct {
    struct k_msgq queue;
    bool is_static;
} rtos_mqueue_t;

/** Send an item to the queue.
 *
 * This function sends an item to the queue. The current thread is blocked until
 * the item is sent or the timeout period expires.
 *
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	item Item to send.
 * \param 	ticks Timeout period.
 */
static inline int rtos_mqueue_send(rtos_mqueue_t *mq, const void *item, rtos_tick_t ticks)
{
    int ret;

    ret = k_msgq_put(&mq->queue, item, ticks);

    return (ret < 0) ? -1 : 0;
}

/** Send an item to the queue from an interrupt.
 *
 * This function sends an item to the queue. The current thread is blocked until
 * the item is sent or the timeout period expires.
 *
 * Can be called from an interrupt and specifies if a context switch is needed.
 *
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	item Item to send.
 * \param 	ticks Timeout period.
 * \param 	yield Value that specifies if a context switch is needed at ISR exit.
 */
static inline int rtos_mqueue_send_from_isr(rtos_mqueue_t *mq, const void *item, rtos_tick_t ticks, bool *yield)
{
    ARG_UNUSED(yield);

    return rtos_mqueue_send(mq, item, ticks);
}

/** Receive items sent to the queue.
 *
 * This function receives and removes items sent to the queue. The current
 * thread is blocked until the queue receives one or more items or the
 * timeout period expires.
 *`
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	item Pointer to the buffer where the items will be copied
 * \param 	ticks Timeout period.
 */
static inline int rtos_mqueue_receive(rtos_mqueue_t *mq, void *item, rtos_tick_t ticks)
{
    int ret;

    ret = k_msgq_get(&mq->queue, item, ticks);

    return (ret < 0) ? -1 : 0;
}

/** Receive items sent to the queue from an interrupt.
 *
 * This function receives and removes items sent to the queue. The current
 * thread is blocked until the queue receives one or more items or the
 * timeout period expires.
 *`
 * Can be called from an interruptand specifies if a context switch is needed.
 *
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	item Pointer to the buffer where the items will be copied
 * \param 	ticks Timeout period.
 * \param 	yield Value that specifies if a context switch is needed at ISR exit.
 */
static inline int rtos_mqueue_receive_from_isr(rtos_mqueue_t *mq, void *item, rtos_tick_t ticks, bool *yield)
{
    ARG_UNUSED(yield);

    return rtos_mqueue_receive(mq, item, ticks);
}

/** Receive items sent to the queue.
 *
 * This function receives items sent to the queue without removing it from the queue.
 * The current thread is blocked until the queue receives one or more items or the
 * timeout period expires.
 *
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	item Pointer to the buffer where the items will be copied
 * \param 	ticks Timeout period.
 */
static inline int rtos_mqueue_peek(rtos_mqueue_t *mq, void *item, rtos_tick_t ticks)
{
    ARG_UNUSED(ticks);

    int ret;

    ret = k_msgq_peek(&mq->queue, item);

    return (ret < 0) ? -1 : 0;
}

/** Allocate and initialize a queue.
 *
 * This function allocates and initializes a queue.
 *
 * \ingroup rtos_mqueue
 * \return 	Pointer to the queue.
 * \param 	nb_items Number of items that the buffer can contain.
 * \param 	item_size Size if the items.
 */
rtos_mqueue_t *rtos_mqueue_alloc_init(uint32_t nb_items, size_t item_size);

/** Initialize a queue.
 *
 * This function initializes a queue.
 *
 * \ingroup rtos_mqueue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 * \param 	nb_items Number of items that the buffer can contain.
 * \param 	item_size Size if the items.
 * \param 	storage Pointer to buffer where the items will be stored.
 */
int rtos_mqueue_init(rtos_mqueue_t *mq, uint32_t nb_items, size_t item_size, uint8_t *storage);

/** Delete a queue.
 *
 * This function deletes a queue.
 *
 * \ingroup rtos_queue
 * \return 	0 if success, -1 otherwise.
 * \param 	mq Pointer to the queue.
 */
int rtos_mqueue_destroy(rtos_mqueue_t *mq);

#endif /* #ifndef _RTOS_ABSTRACTION_LAYER_MQUEUE_H_ */
