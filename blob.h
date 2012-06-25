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
int   blob_register(blobset *, ub1_t *, ub2_t, void *, void (*)(void *));

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
int   blob_unregister (blobset *, ub1_t *, ub2_t);

/***************************************************************************
  blob_get
  args:
    blobset *set;
    uint8_t *data;
    uint32_t length;
 ***************************************************************************/

void *blob_get(blobset *, ub1_t *, ub2_t);



void blob_cursor_init(blobcursor *bc, blobset *bs);
void *blob_cursor_get(blobcursor *bc, ub1_t *name, ub2_t namesize);
ub1_t blob_cursor_find_first(blobcursor *bc, ub1_t *name, ub2_t namesize, void **data_out);
ub1_t blob_cursor_next(blobcursor *bc, void **data_out, ub1_t **name_out, ub2_t *namesize_out);

#if 0
blob_cursor bc;
blob_cursor_init(&bc);
stuff = blob_cursor_get(&bc, &bs, name, namelen);
stuff = blob_cursor_next(&bc, &name, &namelen);
#endif

#endif /* _MINILIB_BLOB_H */
