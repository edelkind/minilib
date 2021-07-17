#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "minimisc.h"

void
die(int exitno, char *fmt, ...)
{

#ifdef DEBUG
	if (fmt) {
		va_list ap;

		fflush(stdout);
		fflush(stderr);

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

#ifdef DEBUG
	if (fmt) {
		va_list ap;

		fflush(stdout);
		fflush(stderr);

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

#ifdef DEBUG
	if (fmt) {
		va_list ap;

		fflush(stdout);
		fflush(stderr);

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

#ifdef DEBUG
	if (fmt) {
		va_list ap;

		fflush(stdout);
		fflush(stderr);

		va_start (ap, fmt);
		fprintf  (stderr, "warning: ");
		vfprintf (stderr, fmt, ap);
		fprintf  (stderr, ": %s\n", strerror(errno));
		va_end (ap);

		fflush(stderr);
	}
#endif

}

