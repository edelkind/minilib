#include <signal.h>

#if 0
	*** sig_setblock ***
	block or unblock a signal, depending on 'how'.
	returns nothing
#endif

void sig_setblock (how, signal)
	int how;
	int signal;
{
	sigset_t set;

	sigemptyset (&set);
	sigaddset (&set, signal);
	sigprocmask (how, &set, 0);
}


#if 0
	*** sig_block ***
	block a signal
	returns nothing
#endif

void sig_block (signal)
	int signal;
{
	sig_setblock (SIG_BLOCK, signal);
}


#if 0
	*** sig_unblock ***
	unblock a signal
	returns nothing
#endif

void sig_unblock (signal)
	int signal;
{
	sig_setblock (SIG_UNBLOCK, signal);
}

