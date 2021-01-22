#include <string.h>

#if 0
	*** process ***
	get information from stdin and process that information
	returns nothing
#endif

extern void *memchr();

void *getseg (buf, len)
	char **buf;
	unsigned int *len;
{
	char *bufp;
	char *bufo = *buf;

	bufp = memchr (bufo, '\0', *len);
	if (bufp == 0)
		return (void *)0;

	*len -= ++bufp - bufo; /* advance past 0 */
	*buf = bufp;
	return (bufo);
}
