#include <unistd.h>
#include "minimisc.h"

#if 0
	*** fork_pipefdout ***
	fork a new process, and pipe file descriptors.
	fd[0] should be the inbound fd, read by the child.
	fd[1] should be the outbound fd, written by the parent.
	readfd is the file descriptor that pipefd[0] will be copied to.
	func should be a pointer to a function with no return value.
	if func is 0 (null), it is not executed.
	returns 0 on success, 1 otherwise
	additionally sets *pid to the new child pid
#endif

char fork_pipefdout (argv, pipefd, readfd, pid, func)
	char **argv;
	int *pipefd;
	int readfd;
	int *pid;
	void (*func)();
{
	if (pipe(pipefd)) return 1;

	switch (*pid = fork()) {
		case -1: return 1;
		case 0: /* child */
			 close(pipefd[1]);
			 if (pipefd[0] != readfd)
				 if (dup2(pipefd[0], readfd) == -1)
				 	_exit(RET_USAGE);
			 if (func) func();
			 execvp (argv[0], argv);
			 _exit(RET_USAGE);
	}

	close (pipefd[0]);
	return 0;
}
