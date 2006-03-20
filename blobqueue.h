#ifndef _MINILIB_BLOBQUEUE_H
#define _MINILIB_BLOBQUEUE_H

#define BLOB_FIRST 0
#define BLOB_LAST  1

typedef struct blobqentry {
    void *data;
    void (*destructor)(void *);
    struct blobqentry *next;
    struct blobqentry *prev;
} blobqentry;

typedef struct {
    blobqentry *first;
    blobqentry *last;
    ub4_t elem;
} blobqueue;

/* use bq_size() instead of accessing blobqueue internals */
static inline int bq_size (blobqueue *bq) { return bq->elem; }

/***************************************************************************
  blobqueue_new
  args:
    none.

  creates a new blobqueue structure.
 ***************************************************************************/
void *blobqueue_new(void);

/***************************************************************************
  blobqueue_destroy
  args:
    blobqueue *bq;

  destroys the entire blob queue
  frees all associated memory

  for every entry, if there is a destructor associated with the entry, it will
  be called as described in blobqueue_push().
 ***************************************************************************/
void  blobqueue_destroy(blobqueue *);

/***************************************************************************
  blobqueue_push
  args:
    blobqueue *bq;
    ub1_t qside;
    void *data;
    void (*destructor)(void *);

  pushes [data] onto the blobqueue [bq] stack, as either an appendage
  (BLOB_LAST) or prependage (BLOB_FIRST), depending on the value of [qside].

  If [destructor] is not 0, it will be called with [data] as an argument
  whenever the associated blobqentry is freed.  This may simply be 'free' if
  [data] was allocated using malloc(3) and needs no further action before
  destruction.

  returns 0 on success
  returns 1 on out-of-memory error
 ***************************************************************************/
int   blobqueue_push(blobqueue *, ub1_t, void *, void (*)(void *));

/***************************************************************************
  blobqueue_pop
  args:
    blobqueue *bq;
    ub1_t qside;
    void (**destructor)(void *);
  
  pops the first (BLOB_FIRST) or last (BLOB_LAST) element off the queue
  [bq], depending on the value of [qside].  

  if [destructor] is nonzero, the associated destructor will be placed into
  it (this may be zero itself, so don't dereference the pointer if you're
  unsure).  The associated data will not be freed, so you should free it
  with the associated destructor when you're finished with it.

  returns 0 on success
  returns 1 if the entry could not be found.
 ***************************************************************************/
void *blobqueue_pop (blobqueue *, ub1_t , void (**)(void *));


#endif /* _MINILIB_BLOBQUEUE_H */
