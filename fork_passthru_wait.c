#include <errno.h>
#include <sys/wait.h>
#include "minimisc.h"

#if 0
	*** fork_passthru_wait *** [sic]
	use fork_passthru and wait for the pid to exit
#endif

char fork_passthru_wait (argv, status, readfd, buf, bytes, f_errpipe)
	char **argv;
	int *status;
	int readfd;
	char *buf;
	unsigned int bytes;
	void (*f_errpipe)();
{
	int pid;

	if (fork_passthru(argv, readfd, buf, bytes, &pid, f_errpipe)) return 1;

	while (waitpid(pid, status, 0) == -1)
		if (errno != EINTR) return 1;

	return 0;
}

