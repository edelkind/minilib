#include <stdlib.h>
#include "minimisc.h"

#if 0
	*** strset_ulong ***
	set a string with the format of a specified number and a specified base
	base must be greater than 2.
	if you have a number with a base of more than 35, you are not
	promised a useful result.
	returns the length of the new string, or 0 on error.
#endif

unsigned int strset_ulong (buf, buflen, num, base)
	char *buf;
	unsigned int buflen;
	unsigned long num;
	unsigned int base;
{
	unsigned long n = num;
	unsigned int len = 1;

	for (; n >= base; len++) {
		n /= base;
	}

	/* buflen must include null terminator */
	if (len >= buflen) return 0;
	buflen = len; /* temp */

	buf[len] = 0;
	while (len--) {
		n = (num % base);
		buf[len] = ((n < 10) ? '0' : ('A' - 10)) + n;
		num /= base;
	}

	return (buflen);
}

#if 0
	*** strset_long ***
#endif

extern int abs();

unsigned int strset_long (buf, buflen, num, base)
	char *buf;
	unsigned int buflen;
	signed long num;
	unsigned int base;
{
	if (num >= 0) return (strset_ulong(buf, buflen, num, base));
	*buf = '-';
	return (strset_ulong(buf+1, buflen-1, abs(num), base) + 1);
}


#if 0
	*** strset_base10 ***
	call strset_ulong() with a buflen of LEN_ULONG and a base of 10
#endif

unsigned int strset_base10 (buf, num)
	char *buf;
	signed long num;
{
	return (strset_long(buf, LEN_ULONG, num, 10));
}

unsigned int strset_ubase10 (buf, num)
	char *buf;
	unsigned long num;
{
	return (strset_ulong(buf, LEN_ULONG, num, 10));
}
