#include <stdlib.h>
#include <string.h>
#include "mltypes.h"
#include "blob.h"

#include <stdio.h>

static inline ub4_t blob_sum(blob, len)
    void *blob;
    ub4_t len;
{
    ub4_t sum = 0;

    while (len >= sizeof(sum))
        {
            sum ^= *(ub4_t *)blob;
            len-=sizeof(sum);
            if (!len) return sum;
            blob+=sizeof(sum);
        }

    if (len >= 4) {
        sum ^= *(unsigned int *)blob;
        len -= 4;
        /* if !len, the switch statement below will be a NOP */
        blob += 4;
    }

    switch (len) {
        case 2: sum ^= *(ub2_t *)blob;
                break;
        case 3: sum ^= ((ub4_t)*(ub2_t *)blob) << 8; blob+=2;
        case 1: sum ^= *(ub1_t *)blob;
                break;
    }
    return sum;
}

void *blob_new (hashsize, defaultdata)
    ub1_t hashsize;
    void *defaultdata;
{
    blobset *bs = malloc (sizeof(blobset) + sizeof(blobentry *)*hashsize);
    if (!bs) return 0;

    bs->hash = (blobentry **)((ub1_t *)bs + sizeof(blobset));
    bs->elem = hashsize;
    bs->dflt = defaultdata;

    memset (bs->hash, 0, sizeof(blobentry *)*hashsize);
    return bs;
}

int blob_register (bs, name, namesize, data, destructor)
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;
    void *data;
    void (*destructor)(void *);
{
    ub1_t slice = (blob_sum(name,namesize) % bs->elem);
    blobentry *entry = malloc (sizeof(blobentry)+namesize);
    blobentry **target;

    if (!entry) return 1;

    entry->namesize = namesize;
    entry->name = (ub1_t *)entry + sizeof(blobentry);
                  memcpy(entry->name, name, namesize);
    entry->data = data;
    entry->next = 0;
    entry->destructor = destructor;

    target = &(bs->hash[slice]);
    while (*target)
        target = &((*target)->next);

    *target = entry;

    return 0;
}

int blob_unregister (bs, name, namesize)
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;
{
    ub1_t slice = (blob_sum(name,namesize) % bs->elem);
    blobentry *entry = bs->hash[slice], *last = 0;

    while (entry) {
        if (entry->namesize == namesize && !memcmp(entry->name,name,namesize))
        {
            if (last) last->next = entry->next;
            else bs->hash[slice] = entry->next;
            if (entry->destructor) entry->destructor(entry->data);
            free(entry);
            return 0;
        }
        last  = entry;
        entry = entry->next;
    }

    return 1;
}

void blob_destroy (bs)
    blobset *bs;
{
    ub1_t slice = 0;
    blobentry *entry, *next;

    while (slice < bs->elem) {
        next = bs->hash[slice++];
        while (next) {
            entry = next;
            next = next->next;
            if (entry->destructor) entry->destructor(entry->data);
            free(entry);
        }
    }

    free(bs);
}


/* XXX: optimize for 32-bit integers */
void *blob_get (bs, name, namesize)
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;
{
    ub1_t slice = (blob_sum(name,namesize) % bs->elem);
    blobentry *entry = bs->hash[slice];

    while (entry) {
//        printf ("comparing: %lu/%lu, %d/%d\n", *(ub4_t *)entry->name, *(ub4_t *)name, (int)entry->namesize, (int)namesize);
        if (entry->namesize == namesize && !memcmp(entry->name,name,namesize))
            return entry->data;
        entry = entry->next;
    }

    return bs->dflt;
}

