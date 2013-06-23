#ifndef _MINILIB_BLOB_HPP
# define _MINILIB_BLOB_HPP

extern "C" {
#include "mltypes.h"
#include "blob.h"
}

#include <stdexcept>

namespace ml {
template <class T>
struct BlobSet
{
    blobset *bs;
    BlobSet(ub1_t hashsize, T defaultdata)
    {
        bs = (blobset *)blob_new(hashsize, defaultdata);
        if (!bs) {
            throw std::bad_alloc();
        }
    }

    ~BlobSet() {
        blob_destroy(bs);
    }

    inline void add(ub1_t *s, ub2_t len, T dat, void (*destruct)(void*)) {
        if (blob_register(bs, s, len, dat, destruct))
            throw std::bad_alloc();
    }

    inline void add(ub1_t *s, ub2_t len, T dat)
    { add((ub1_t*)s, len, dat, 0); }

    inline void add(char *s, ub2_t len, T dat)
    { add((ub1_t*)s, len, dat); }

    inline int add_nothrow(ub1_t *s, ub2_t len, T dat, void (*destruct)(void*)) {
        return blob_register(bs, s, len, dat, destruct);
    }
    inline int add_nothrow(ub1_t *s, ub2_t len, T dat)
    { return add_nothrow((ub1_t*)s, len, dat, 0); }

    inline int add_nothrow(char *s, ub2_t len, T dat)
    { return add_nothrow((ub1_t*)s, len, dat); }

    inline int remove(ub1_t *s, ub2_t len)
    { return blob_unregister(bs, s, len); }

    inline int remove(char *s, ub2_t len)
    { return remove((ub1_t *)s, len); }

    inline T pop(ub1_t *s, ub2_t len)
    {
        T dat;
        blobcursor bc;
        blob_cursor_init(&bc, bs);
        if ( !(dat = (T)blob_cursor_get(&bc, s, len)) )
            return (T)0;

        blob_cursor_unregister(&bc);
        return dat;
    }

    inline T pop(char *s, ub2_t len)
    { return pop((ub1_t *)s, len); }

    inline T get(ub1_t *s, ub2_t len)
    { return (T)blob_get(bs, s, len); }
    
    inline T get(char *s, ub2_t len)
    { return get((ub1_t*)s, len); }
    
};

template <class T>
struct BlobCursor : blobcursor {

    BlobCursor(BlobSet<T> *bsp)
    {
        blob_cursor_init(this, bsp->bs);
    }

    inline void reset()
    { blob_cursor_init(this, bs); }

    inline T get(ub1_t *s, ub2_t len)
    { return (T)blob_cursor_get(this, s, len); }
    
    inline T get(char *s, ub2_t len)
    { return get((ub1_t*)s, len); }

    inline T value()
    { return (T)blob_cursor_value(this); }

    inline ub1_t find_first(ub1_t *name, ub2_t namesize, T *data_out)
    { return blob_cursor_find_first(this, name, namesize, data_out); }

    inline ub1_t find_first(char *name, ub2_t namesize, T *data_out)
    { return find_first((ub1_t*)name, namesize, data_out); }

    inline ub1_t next(T *data_out, ub1_t **name_out, ub2_t *namesize_out)
    { return blob_cursor_next(this, data_out, name_out, namesize_out); }

    inline ub1_t remove()
    { return blob_cursor_unregister(this); }

    inline void switcheroo(T data)
    { blob_cursor_switcheroo(this, data); }
};

} // namespace ml

#endif /* _MINILIB_BLOB_HPP */
