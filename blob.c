#include <stdlib.h>
#include <string.h>
#include "mltypes.h"
#include "blob.h"

static inline ub4_t blob_sum(blob, len)
    void *blob;
    ub4_t len;
{
    ub4_t sum = 0;

    while (len >= 4)
        { sum ^= *(ub4_t *)blob; len-=4; if (!len) return sum; blob+=4; }

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

int blob_register (bs, name, namesize, data)
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;
    void *data;
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

    target = &(bs->hash[slice]);
    while (*target)
        target = &((*target)->next);

    *target = entry;

    return 0;
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

