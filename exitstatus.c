#include <sys/wait.h>

/* process exited normally */
char exitstatus_normal (status)
	int status;
{
	if (WIFEXITED(status)) return 1;
	return 0;
}

/* process exited with a signal */
char exitstatus_crashed (status)
	int status;
{
	if (WIFSIGNALED(status)) return 1;
	return 0;
}

/* process was stopped */
char exitstatus_stopped (status)
	int status;
{
	if (WIFSTOPPED(status)) return 1;
	return 0;
}

/* process dumped core (!posix) */
char exitstatus_coredumped (status)
	int status;
{
	if (WCOREDUMP(status)) return 1;
	return 0;
}

/* offer the return value */
int exitstatus_return_normal (status)
	int status;
{
	return (WEXITSTATUS(status));
}

/* offer the signal that forced process termination or crash */
int exitstatus_return_signal (status)
	int status;
{
	return (WTERMSIG(status));
}

/* offer the signal that forced the process to stop */
int exitstatus_return_stopsig (status)
	int status;
{
	return (WSTOPSIG(status));
}

