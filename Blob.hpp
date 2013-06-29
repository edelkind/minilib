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

    inline void add(const ub1_t *s, ub2_t len, T dat, void (*destruct)(void*)) {
        if (blob_register(bs, s, len, dat, destruct))
            throw std::bad_alloc();
    }

    inline void add(const ub1_t *s, ub2_t len, T dat)
    { add((const ub1_t*)s, len, dat, 0); }

    inline void add(const char *s, ub2_t len, T dat)
    { add((const ub1_t*)s, len, dat); }

    inline int add_nothrow(const ub1_t *s, ub2_t len, T dat, void (*destruct)(void*)) {
        return blob_register(bs, s, len, dat, destruct);
    }
    inline int add_nothrow(const ub1_t *s, ub2_t len, T dat)
    { return add_nothrow((const ub1_t*)s, len, dat, 0); }

    inline int add_nothrow(const char *s, ub2_t len, T dat)
    { return add_nothrow((const ub1_t*)s, len, dat); }

    inline int remove(const ub1_t *s, ub2_t len)
    { return blob_unregister(bs, s, len); }

    inline int remove(const char *s, ub2_t len)
    { return remove((const ub1_t *)s, len); }

    inline T pop(const ub1_t *s, ub2_t len)
    {
        T dat;
        blobcursor bc;
        blob_cursor_init(&bc, bs);
        if ( !(dat = (T)blob_cursor_get(&bc, s, len)) )
            return (T)0;

        blob_cursor_unregister(&bc);
        return dat;
    }

    inline T pop(const char *s, ub2_t len)
    { return pop((const ub1_t *)s, len); }

    inline T get(const ub1_t *s, ub2_t len)
    { return (T)blob_get(bs, s, len); }
    
    inline T get(const char *s, ub2_t len)
    { return get((const ub1_t*)s, len); }
    
};

template <class T>
struct BlobCursor : blobcursor {

    BlobCursor(BlobSet<T> *bsp)
    {
        blob_cursor_init(this, bsp->bs);
    }

    inline void reset()
    { blob_cursor_init(this, bs); }

    inline T get(const ub1_t *s, ub2_t len)
    { return (T)blob_cursor_get(this, s, len); }
    
    inline T get(const char *s, ub2_t len)
    { return get((const ub1_t*)s, len); }

    inline T value()
    { return (T)blob_cursor_value(this); }

    inline ub1_t find_first(const ub1_t *name, ub2_t namesize, T *data_out)
    { return blob_cursor_find_first(this, name, namesize, data_out); }

    inline ub1_t find_first(const char *name, ub2_t namesize, T *data_out)
    { return find_first((const ub1_t*)name, namesize, data_out); }

    inline ub1_t next(T *data_out, ub1_t **name_out, ub2_t *namesize_out)
    { return blob_cursor_next(this, data_out, name_out, namesize_out); }

    inline ub1_t remove()
    { return blob_cursor_unregister(this); }

    inline void switcheroo(T data)
    { blob_cursor_switcheroo(this, data); }
};

} // namespace ml

#endif /* _MINILIB_BLOB_HPP */
