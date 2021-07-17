#include <signal.h>

#include "minimisc.h"

void
sig_catch_save(int signal, void (*func)(int), void *oact)
{
	struct sigaction sigact;

	sigemptyset (&sigact.sa_mask);
	sigact.sa_flags   = 0;
	sigact.sa_handler = func;

	sigaction (signal, &sigact, (struct sigaction *)oact);
	/* there are no crucial errors for sigaction if used correctly */
}

void
sig_catch_restore(int signal, void *oact)
{
	sigaction (signal, (struct sigaction *)oact, 0);
	/* there are no crucial errors for sigaction if used correctly */
}

void
sig_catch(int signal, void (*func)(int))
{
	sig_catch_save (signal, func, 0);
}


void
sig_default(int signal)
{
	sig_catch (signal, SIG_DFL);
}

