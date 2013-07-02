#ifndef _MINILIB_BLOB_H
#define _MINILIB_BLOB_H

typedef struct blobentry {
    ub1_t *name;
    ub2_t  namesize;
    void  *data;
    void (*destructor)(void *);
    struct blobentry *next;
} blobentry;

typedef struct {
    blobentry **hash;
    ub1_t  elem;
    void  *dflt;
} blobset;

typedef struct {
    blobset *bs;
    blobentry *lastentry;
    int lastslice;
    blobentry *lastref; /*< lastref->next == lastentry || 0 if first entry */
} blobcursor;

/***************************************************************************
  blob_new
  args:
    ub1_t hashsize;
    void *default;


  creates a new blob with a hash of [hashsize] elements.  [default] will be
  registered as the default data to be returned upon no match.  The pointer
  is taken as-is -- if 0 (or NULL) is passed, then 0 (or NULL) will be
  returned.
 ***************************************************************************/
void *blob_new(ub1_t, void *);

/***************************************************************************
  blob_destroy
  args:
    blobset *bs;
    void (*freefunc)(void *)

  destroys the entire blob set
  frees all associated memory

  Note that bs->dflt is never freed, and may be reused by the caller.

  for every entry, if there is a destructor associated with the entry, it will
  be called as described in blob_register().
 ***************************************************************************/
void  blob_destroy(blobset *);

/***************************************************************************
  blob_register
  args:
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;
    void *data;
    void (*destructor)(void *);

  registers the [data] in blobset [bs], with the associated [name] (of size
  [namesize]) as the key.

  If [destructor] is not 0, it will be called with [data] as an argument
  whenever the associated blob entry is freed.  This may simply be 'free' if
  [data] was allocated using malloc(3) and needs no further action before
  destruction.

  returns 0 on success
  returns 1 on out-of-memory error
 ***************************************************************************/
int   blob_register(blobset *, const ub1_t *, ub2_t, void *, void (*)(void *));

/***************************************************************************
  blob_unregister
  args:
    blobset *bs;
    ub1_t *name;
    ub2_t namesize;

  finds the blob entry in [bs] associated with [name]/[namesize], removes it
  from the hash, and frees the allocated memory.

  if there is a destructor associated with the entry, it will be called as
  described in blob_register().

  returns 0 on success
  returns 1 if the entry could not be found.
 ***************************************************************************/
int   blob_unregister (blobset *, const ub1_t *, ub2_t);

/***************************************************************************
  blob_get
  args:
    blobset *set;
    uint8_t *data;
    uint32_t length;
 ***************************************************************************/

void *blob_get(blobset* bs, const ub1_t* name, ub2_t namesize);



/****************************************************************************
  blob_cursor_init
  args:
    blobcursor *bc;
    blobset    *bs;

  Initialize a cursor, and associate it with [bs].
 ****************************************************************************/
void blob_cursor_init(blobcursor *bc, blobset *bs);
void *blob_cursor_get(blobcursor *bc, const ub1_t *name, ub2_t namesize);
ub1_t blob_cursor_find_first(blobcursor *bc, const ub1_t *name, ub2_t namesize, void **data_out);

/****************************************************************************
  blob_cursor_next
  args:
    blobcursor *bc;
    void      **data_out;
    ub1_t     **name_out;
    ub2_t      *namesize_out;

  Position the cursor at the next entry.  If not null, the *_out variables
  will be set to the new entry's data, name, and namesize, respectively.

  returns 0 on success
  returns 1 if there was no next entry (*_out variables remain unchanged).
 ****************************************************************************/
ub1_t blob_cursor_next(blobcursor *bc, void **data_out, ub1_t **name_out, ub2_t *namesize_out);

/***************************************************************************
  blob_cursor_unregister
  args:
    blobcursor *bc;

  Unregister and destroy the entry currently referenced by the cursor, and if
  possible, advance the cursor to the next entry in the blobset.

  If bc is not currently set to a valid item, the behavior is undefined.

  returns 0 if there is at least one more entry in the blobset
  returns 1 if there are no more entries in the blobset
 ***************************************************************************/
ub1_t blob_cursor_unregister(blobcursor *bc);

/****************************************************************************
  blob_cursor_switcheroo
  args:
    blobcursor *bc;
    void *data;

  Switch out the data at the current cursor entry with [data].
 ****************************************************************************/
static inline void
blob_cursor_switcheroo(blobcursor *bc, void *data)
{ bc->lastentry->data = data; }

/****************************************************************************
  blob_cursor_value
  args:
    blobcursor *bc;

  Return the data for the entry currently referenced by the cursor.
 ****************************************************************************/
static inline void *
blob_cursor_value(blobcursor *bc)
{ return bc->lastentry->data; }

#if 0
blob_cursor bc;
blob_cursor_init(&bc, &bs);
stuff = blob_cursor_get(&bc, name, namelen);
assert (stuff == blob_cursor_value(&bc));
while (!blob_cursor_next(&bc, &stuff, &name, &namelen))
    ...
#endif

#endif /* _MINILIB_BLOB_H */
