#include <stdlib.h>
#include <string.h>
#include "mltypes.h"
#include "blob.h"

#include <stdio.h>
#include <assert.h>

static inline ub4_t
blob_sum(const void *blob, ub4_t len)
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

void *
blob_new (ub1_t hashsize, void *defaultdata)
{
    blobset *bs = malloc (sizeof(blobset) + sizeof(blobentry *)*hashsize);
    if (!bs) return 0;

    bs->hash = (blobentry **)((ub1_t *)bs + sizeof(blobset));
    bs->elem = hashsize;
    bs->dflt = defaultdata;

    memset (bs->hash, 0, sizeof(blobentry *)*hashsize);
    return bs;
}

int
blob_register (blobset *bs,
               const ub1_t *name,
               ub2_t namesize,
               void *data,
               void (*destructor)(void *))
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

int
blob_unregister (blobset *bs,
                 const ub1_t *name,
                 ub2_t namesize)
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

ub1_t
blob_cursor_unregister (blobcursor *bc)
{
    blobentry *entry = bc->lastentry,
              *last  = bc->lastref;
    ub1_t slice = bc->lastslice;
    blobset *bs = bc->bs;
    ub1_t rv;

    /* remove from list */
    if (last) last->next = entry->next;
    else bs->hash[slice] = entry->next;

    /* then set cursor to next item */
    rv = blob_cursor_next(bc, 0, 0, 0);

    /* now destroy the entry */
    if (entry->destructor) entry->destructor(entry->data);
    free(entry);
    return rv;
}

void blob_empty (blobset *bs)
{
    ub1_t slice = 0;
    blobentry *entry, *next;

    while (slice < bs->elem) {
        next = bs->hash[slice];
        while (next) {
            entry = next;
            next = next->next;
            if (entry->destructor) entry->destructor(entry->data);
            free(entry);
        }
        bs->hash[slice++] = 0;
    }
}

void blob_destroy (blobset *bs)
{
    blob_empty(bs);
    free(bs);
}


/* XXX: optimize for 32-bit integers */
void *blob_get ( blobset *bs,
                 const ub1_t *name,
                 ub2_t namesize )
{
    ub1_t slice = (blob_sum(name,namesize) % bs->elem);
    blobentry *entry = bs->hash[slice];

    while (entry) {
//        printf ("comparing: %lu/%lu, %d/%d\n", *(ub4_t *)entry->name, *(ub4_t *)name, (int)entry->namesize, (int)namesize);
        if (entry->namesize == namesize && !memcmp(entry->name,name,(size_t)namesize))
            return entry->data;
        entry = entry->next;
    }

    return bs->dflt;
}

void blob_cursor_init ( blobcursor *bc,
                        blobset *bs )
{
    assert(bc);
    assert(bs);
    bc->bs = bs;
    bc->lastentry = 0;
    bc->lastref = 0;
    bc->lastslice = -1;
}

static inline ub1_t
_blob_entry_is_equal(blobentry *entry, const ub1_t *name, ub2_t namesize)
{
        if (entry->namesize == namesize && !memcmp(entry->name,name,namesize))
            return 1; /* true */
        return 0;
}

static inline ub1_t
_blob_find( blobset *bs,
            ub1_t *slicep,
            blobentry **entryp,
            blobentry **erefp, /* eref->next == entry (or NULL) */
            const ub1_t *name,
            ub2_t namesize)
{
    ub1_t slice = (blob_sum(name,namesize) % bs->elem);
    blobentry *entry = bs->hash[slice];
    blobentry *eref = 0;

    while (entry) {
        if (_blob_entry_is_equal(entry, name, namesize)) {
            *slicep = slice;
            *entryp = entry;
            if (erefp) *erefp = eref;
            return 0;
        }
        eref  = entry;
        entry = entry->next;
    }
    return 1;

}

void *blob_cursor_get ( blobcursor *bc,
                        const ub1_t *name,
                        ub2_t namesize )
{
    ub1_t slice;
    blobentry *entry, *eref;

    if (!_blob_find(bc->bs, &slice, &entry, &eref, name, namesize)) {
        bc->lastslice = slice;
        bc->lastentry = entry;
        bc->lastref   = eref;
        return entry->data;
    }

    return bc->bs->dflt;
}

ub1_t blob_cursor_find_first (
        blobcursor *bc,
        const ub1_t *name,
        ub2_t namesize,
        void **data_out )
{
    ub1_t slice;
    blobentry *entry, *eref;

    if (!_blob_find(bc->bs, &slice, &entry, &eref, name, namesize)) {
        bc->lastslice = slice;
        bc->lastentry = entry;
        bc->lastref   = eref;
        if (data_out)
            *data_out = bc->lastentry->data;
        return 0;
    }
    return 1;
}

ub1_t blob_cursor_next (
        blobcursor *bc,
        void **data_out,
        ub1_t **name_out,
        ub2_t *namesize_out )
{
    blobset *bs = bc->bs;
    blobentry *entry = bc->lastentry,
              *eref;
    int slice = bc->lastslice;
    int rv = 0;

    if (entry) {
        eref  = entry;
        entry = entry->next;
    }

    if (!entry) {
        eref  = 0;
        do {
            if (slice == ((int)bs->elem)-1) {
                // not found
                rv = 1;
                goto OUT;
            }
            entry = bs->hash[++slice];
            assert(slice < bs->elem);
        } while (!entry);
    }

    // entry != null
    if (data_out)     *data_out     = entry->data;
    if (name_out)     *name_out     = entry->name;
    if (namesize_out) *namesize_out = entry->namesize;

OUT:
    bc->lastslice = slice;
    bc->lastentry = entry;
    bc->lastref   = eref;
    return rv;
}
