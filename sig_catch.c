#include <signal.h>

void sig_catch (signal, func)
	int signal;
	void (*func)(int);
{
	struct sigaction sigact;

	sigemptyset (&sigact.sa_mask);
	sigact.sa_flags   = 0;
	sigact.sa_handler = func;

	sigaction (signal, &sigact, 0);
	/* there are no crucial errors for sigaction if used correctly */
}

void sig_default (signal)
	int signal;
{
	sig_catch (signal, SIG_DFL);
}

