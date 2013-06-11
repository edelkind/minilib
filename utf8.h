#ifndef _MINILIB_UTF8_H
# define _MINILIB_UTF8_H

/** How many extra bytes are expected for the current header.  If this is not a
 * UTF-8 header, 0 is returned (0 extra bytes).
 */
int utf8_extra(int c);

/** Is \a c valid as a UTF-8 continuation character?
 */
static inline ub1_t is_continuation(int c)
{
    if ((c & 0xc0) == 0x80)
        return 1;
    return 0;
}

/** Copy a utf-8 character from \a uc to \a out.  \a out must have enough space
 * to hold \a uc, which may require up to 4 bytes.
 */
int utf8_cpy(char *out, ub4_t uc);


/** Copy a utf-8 character of size \a uc_sz from \a uc to \a out.  \a out must
 * have enough space to hold \a uc_sz bytes.
 *
 * \returns a pointer to out
 */
char *utf8_ncpy(char *out, ub4_t uc, ub1_t uc_sz);

/** Pull one UTF-8 character off of \a p (which has length \a l), and return
 * it.  If \a l is not >= 1, the behavior is undefined.  If a proper UTF-8
 * character cannot be resolved, then it is treated as if it is not a UTF-8
 * character at all (i.e. a single byte is returned).
 *
 * \a *csize_out will point to the size of the returned character.
 */
ub4_t utf8_char_pop(const char *p, ub4_t l, int *csize_out);

#endif /* _MINILIB_UTF8_H */
