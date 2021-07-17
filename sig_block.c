#include <signal.h>

#include "minimisc.h"

/* *** sig_setblock ***
 * block or unblock a signal, depending on 'how'.
 * returns nothing
 */
void
sig_setblock(int how, int signal)
{
	sigset_t set;

	sigemptyset (&set);
	sigaddset (&set, signal);
	sigprocmask (how, &set, 0);
}


/* *** sig_block ***
 * block a signal
 * returns nothing
 */
void
sig_block(int signal)
{
	sig_setblock (SIG_BLOCK, signal);
}


/* *** sig_unblock ***
 * unblock a signal
 * returns nothing
 */
void
sig_unblock(int signal)
{
	sig_setblock (SIG_UNBLOCK, signal);
}

