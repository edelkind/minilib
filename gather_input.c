#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "minimisc.h"

#if 0
	*** gather_input ***
	get all information from fd (up to maxlen)
	buf _must_ have sufficient allocation to store data
	returns length, -2 if maxlen was exceeded, or -1 on read error
#endif

extern int errno;

int gather_input (fd, buf, maxlen)
	int fd;
	char *buf;
	unsigned int maxlen;
{
	unsigned int len = 0;
	int r;

	/* gather input data */
	for (;;) {
		if ((r = read (fd, buf+len, maxlen - len)) == -1) {
			if (errno == EINTR) continue;
			return (READ_ERROR);
		}

		if (!r) break;

		len += r;
		if (len == maxlen) return (READ_EXCESS);
	}

	return (len);
}
