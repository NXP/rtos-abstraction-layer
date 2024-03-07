/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "rtos_mqueue.h"

rtos_mqueue_t *rtos_mqueue_alloc_init(uint32_t nb_items, size_t item_size)
{
    rtos_mqueue_t *mq;
    char *storage;

    mq = (rtos_mqueue_t *)k_malloc(sizeof(rtos_mqueue_t) + (nb_items*item_size));
    if (!mq)
        goto err;

    memset(mq, 0, sizeof(rtos_mqueue_t) + (nb_items*item_size));
    storage = (char *)(mq +1);

    k_msgq_init(&mq->queue, storage, item_size, nb_items);

    mq->is_static = false;

    return mq;

err:
    return NULL;
}

int rtos_mqueue_init(rtos_mqueue_t *mq, uint32_t nb_items, size_t item_size, uint8_t *storage)
{
    k_msgq_init(&mq->queue, storage, item_size, nb_items);

    mq->is_static = true;

    return 0;
}

int rtos_mqueue_destroy(rtos_mqueue_t *mq)
{
    if (!mq->is_static) {
        k_free(mq);
    } else {
        k_msgq_purge(&mq->queue);
    }

    return 0;
}
