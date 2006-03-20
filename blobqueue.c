#include <stdlib.h>
#include "mltypes.h"
#include "blobqueue.h"

void *blobqueue_new(void) {
    blobqueue *bq = malloc(sizeof(blobqueue));
    if (!bq) return 0;

    bq->first = bq->last = 0;
    bq->elem = 0;
    return bq;
}

void blobqueue_destroy(bq)
    blobqueue *bq;
{
    void (*destructor)(void *);
    void *entry;

    while ((entry = blobqueue_pop(bq, BLOB_LAST, &destructor))) {
        if (destructor)
            destructor(entry);
    }
    free(bq);
}

int blobqueue_push(bq, qside, data, destructor)
    blobqueue *bq;
    ub1_t qside;
    void *data;
    void (*destructor)(void *);
{
    blobqentry *entry = malloc(sizeof(blobqentry));
    if (!entry) return 1;

    entry->data = data;
    entry->destructor = destructor;

    if (!bq->last) {
        entry->next = entry->prev = 0;
        bq->first = bq->last = entry;
    } else if (qside == BLOB_FIRST) {
        entry->prev = 0;
        entry->next = bq->first;
        bq->first->prev = entry;
        bq->first       = entry;
    } else /* BLOB_LAST */ {
        entry->next = 0;
        entry->prev = bq->last;
        bq->last->next = entry;
        bq->last = entry;
    }

    bq->elem++;
    return 0;
}

void *blobqueue_pop (bq, qside, destructor)
    blobqueue *bq;
    ub1_t qside;
    void (**destructor)(void *);
{
    blobqentry *entry;
    void *data;

    if (!bq->last) return 0;

    if (qside == BLOB_LAST) {
        entry = bq->last;
        if ((bq->last = entry->prev))
            bq->last->next = 0;
    } else {
        entry = bq->first;
        if ((bq->first = entry->next))
            bq->first->prev = 0;
    }
    bq->elem--;

    data = entry->data;
    if (destructor) *destructor = entry->destructor;

    free(entry);
    return data;
}
