#include <signal.h>
#include "minimisc.h"

/* catch signals */
void sig_catch_hup (f) void (*f)(); { sig_catch (SIGHUP, f); }
void sig_catch_int (f) void (*f)(); { sig_catch (SIGINT, f); }
void sig_catch_bus (f) void (*f)(); { sig_catch (SIGBUS, f); }
void sig_catch_segv (f) void (*f)(); { sig_catch (SIGSEGV, f); }
void sig_catch_pipe (f) void (*f)(); { sig_catch (SIGPIPE, f); }
void sig_catch_alrm (f) void (*f)(); { sig_catch (SIGALRM, f); }
void sig_catch_term (f) void (*f)(); { sig_catch (SIGTERM, f); }
void sig_catch_chld (f) void (*f)(); { sig_catch (SIGCHLD, f); }
void sig_catch_usr1 (f) void (*f)(); { sig_catch (SIGUSR1, f); }
void sig_catch_usr2 (f) void (*f)(); { sig_catch (SIGUSR2, f); }

/* reset signal actions to the default */
void sig_default_hup () { sig_catch (SIGHUP, SIG_DFL); }
void sig_default_int () { sig_catch (SIGINT, SIG_DFL); }
void sig_default_bus () { sig_catch (SIGBUS, SIG_DFL); }
void sig_default_segv () { sig_catch (SIGSEGV, SIG_DFL); }
void sig_default_pipe () { sig_catch (SIGPIPE, SIG_DFL); }
void sig_default_alrm () { sig_catch (SIGALRM, SIG_DFL); }
void sig_default_term () { sig_catch (SIGTERM, SIG_DFL); }
void sig_default_chld () { sig_catch (SIGCHLD, SIG_DFL); }
void sig_default_usr1 () { sig_catch (SIGUSR1, SIG_DFL); }
void sig_default_usr2 () { sig_catch (SIGUSR2, SIG_DFL); }

/* block signals */
void sig_block_hup () { sig_setblock (SIG_BLOCK, SIGHUP); }
void sig_block_int () { sig_setblock (SIG_BLOCK, SIGINT); }
void sig_block_bus () { sig_setblock (SIG_BLOCK, SIGBUS); }
void sig_block_segv () { sig_setblock (SIG_BLOCK, SIGSEGV); }
void sig_block_pipe () { sig_setblock (SIG_BLOCK, SIGPIPE); }
void sig_block_alrm () { sig_setblock (SIG_BLOCK, SIGALRM); }
void sig_block_term () { sig_setblock (SIG_BLOCK, SIGTERM); }
void sig_block_chld () { sig_setblock (SIG_BLOCK, SIGCHLD); }
void sig_block_usr1 () { sig_setblock (SIG_BLOCK, SIGUSR1); }
void sig_block_usr2 () { sig_setblock (SIG_BLOCK, SIGUSR2); }

/* unblock signals */
void sig_unblock_hup () { sig_setblock (SIG_UNBLOCK, SIGHUP); }
void sig_unblock_int () { sig_setblock (SIG_UNBLOCK, SIGINT); }
void sig_unblock_bus () { sig_setblock (SIG_UNBLOCK, SIGBUS); }
void sig_unblock_segv () { sig_setblock (SIG_UNBLOCK, SIGSEGV); }
void sig_unblock_pipe () { sig_setblock (SIG_UNBLOCK, SIGPIPE); }
void sig_unblock_alrm () { sig_setblock (SIG_UNBLOCK, SIGALRM); }
void sig_unblock_term () { sig_setblock (SIG_UNBLOCK, SIGTERM); }
void sig_unblock_chld () { sig_setblock (SIG_UNBLOCK, SIGCHLD); }
void sig_unblock_usr1 () { sig_setblock (SIG_UNBLOCK, SIGUSR1); }
void sig_unblock_usr2 () { sig_setblock (SIG_UNBLOCK, SIGUSR2); }
