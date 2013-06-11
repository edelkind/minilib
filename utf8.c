#include "mltypes.h"
#include "utf8.h"

int utf8_extra(int c)
{
    if ((c & 0xc0) != 0xc0) /* ! 11xx xxxx: not a UTF-8 leader */
        return 0;
    if ((c & 0xe0) == 0xc0) /*   110x xxxx */
        return 1;
    if ((c & 0xf0) == 0xe0) /*   1110 xxxx */
        return 2;
    if ((c & 0xf8) == 0xf0) /*   1111 0xxx */
        return 3;

    return 0;
}

ub1_t utf8_char_size(ub4_t uc)
{
    int l=1;
    if (!(uc >>= 8))
        return l;

    ++l;
    if (!(uc >>= 8))
        return l;

    ++l;
    if (!(uc >>= 8))
        return l;

    return ++l;
}

int utf8_cpy(char *out, ub4_t uc)
{
    ub1_t c;
    char *op = out;

    if ((c = (ub1_t)uc >> 24))
        *op++ = c;
    if ((c = (ub1_t)uc >> 16))
        *op++ = c;
    if ((c = (ub1_t)uc >> 8))
        *op++ = c;
    *op++ = (ub1_t)uc; // at least 1 char will be output

    return op-out;
}

char *utf8_ncpy(char *out, ub4_t uc, ub1_t uc_sz)
{
    for (;uc_sz; uc >>= 8)
        out[--uc_sz] = (ub1_t) uc;

    return out;
}

/** Pull one UTF-8 character off of \a buf (which has length \a len), and
 * return it.  If \a len is not >= 1, the behavior is undefined.  If a proper
 * UTF-8 character cannot be resolved, then it is treated as if it is not a
 * UTF-8 character at all (i.e. a single byte is returned).
 *
 * *buf is advanced to the beginning of the next char, and *len is decremented
 * appropriately.
 */
ub4_t utf8_char_pop(const char *p, ub4_t l, int *csize_out)
{
    ub4_t c = *p;
    int extra = utf8_extra(c);

    p++, l--, *csize_out=1;
    switch (extra) {
        case 0:
            return c;
        case 3:
            if (l < 3 || !is_continuation(p[2]))
                return c;
            // fall through
        case 2:
            if (l < 2 || !is_continuation(p[1]))
                return c;
        case 1:
            if (l < 1 || !is_continuation(*p))
                return c;
    }

    while (extra--) {
        c <<= 8;
        c |= (ub4_t)(ub1_t)*p++;
        (*csize_out)++;
    }

    return c;

}
