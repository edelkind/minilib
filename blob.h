#ifndef _MINILIB_BLOB_H
#define _MINILIB_BLOB_H

typedef struct blobentry {
    ub1_t *name;
    ub2_t  namesize;
    void  *data;
    struct blobentry *next;
} blobentry;

typedef struct {
    blobentry **hash;
    ub1_t  elem;
    void  *dflt;
} blobset;

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
  ssh_blob_destroy
  args:
    blobset *blobset;

  not yet implemented.
 ***************************************************************************/
void  blob_destroy(void *);
int   blob_register(blobset *, ub1_t *, ub2_t, void *);
void  blob_unregister();

/***************************************************************************
  blob_get
  args:
    blobset *set;
    uint8_t *data;
    uint32_t length;
 ***************************************************************************/

void *blob_get(blobset *, ub1_t *, ub2_t);

#endif /* _MINILIB_BLOB_H */
