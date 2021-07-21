#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "minimisc.h"

/* NOTE: If you want to disable all error message output,
 * compile with -DMINIMISC_ERROR_PRINT=0
 */

void
die(int exitno, char *fmt, ...)
{

#if MINIMISC_ERROR_PRINT
	if (fmt) {
		va_list ap;

		fflush(stdout);

		va_start (ap, fmt);
		fprintf  (stderr, "exit code %d", exitno);
		if (fmt) {
			fprintf (stderr, ": ");
			vfprintf (stderr, fmt, ap);
		}
		fprintf  (stderr, "\n");
		va_end (ap);

		fflush(stderr);
	}
#endif


	_exit (exitno);
}

void
die_err(int exitno, char *fmt, ...)
{

#if MINIMISC_ERROR_PRINT
	if (fmt) {
		va_list ap;

		fflush(stdout);

		va_start (ap, fmt);
		fprintf  (stderr, "exit code %d", exitno);
		if (fmt) {
			fprintf (stderr, ": ");
			vfprintf (stderr, fmt, ap);
		}
		fprintf  (stderr, ": %s\n", strerror(errno));
		va_end (ap);

		fflush(stderr);
	}
#endif


	_exit (exitno);
}

void
warn(char *fmt, ...)
{

#if MINIMISC_ERROR_PRINT
	if (fmt) {
		va_list ap;

		fflush(stdout);

		va_start (ap, fmt);
		fprintf  (stderr, "warning: ");
		vfprintf (stderr, fmt, ap);
		fprintf  (stderr, "\n");
		va_end (ap);

		fflush(stderr);
	}
#endif

}

void
warn_err(char *fmt, ...)
{

#if MINIMISC_ERROR_PRINT
	if (fmt) {
		va_list ap;

		fflush(stdout);

		va_start (ap, fmt);
		fprintf  (stderr, "warning: ");
		vfprintf (stderr, fmt, ap);
		fprintf  (stderr, ": %s\n", strerror(errno));
		va_end (ap);

		fflush(stderr);
	}
#endif

}

