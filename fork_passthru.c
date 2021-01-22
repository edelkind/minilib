#include <string.h>
#include <unistd.h>
#include "minimisc.h"

#if 0
	*** fork_passthru *** [sic]
	gather a specified amount of input data, fork, and pass it through to
	another program.  Zero said input data upon fork().
#endif

extern void fork_zerodata();
extern void fork_errpipe();

static char *input;
static unsigned int ibytes;

static void (*_f_errpipe)();

char fork_passthru (argv, readfd, buf, bytes, pid, f_errpipe)
	char **argv;
	int readfd;
	char *buf;
	unsigned int bytes;
	int *pid;
	void (*f_errpipe)();
{
	int pipefd[2];

	input = buf;
	ibytes = bytes;

	switch (gather_input(readfd, input, ibytes)) {
		case READ_ERROR:
		case READ_EXCESS: return 1;
	}

	close (readfd);

	_f_errpipe = f_errpipe;
	sig_catch_pipe(fork_errpipe);

	if (fork_pipefdout (argv, (int *)pipefd, readfd, pid, fork_zerodata)) {
		fork_zerodata();
		return 1;
	}

	if (write (pipefd[1], input, ibytes) <= 0) return 1;

	close (pipefd[1]);
	sig_default_pipe();
	fork_zerodata();

	return 0;
}


extern void *memset();

void fork_zerodata (void) {
	memset (input, 0, ibytes);
}

void fork_errpipe (sig)
	int sig;
{
	fork_zerodata();
	_f_errpipe();
}
