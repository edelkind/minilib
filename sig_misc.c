#include <signal.h>
#include "minimisc.h"

/* catch signals */
void sig_catch_hup (f) void (*f)(); { sig_catch (SIGHUP, f); }
void sig_catch_int (f) void (*f)(); { sig_catch (SIGINT, f); }
void sig_catch_bus (f) void (*f)(); { sig_catch (SIGBUS, f); }
void sig_catch_abrt (f) void (*f)(); { sig_catch (SIGABRT, f); }
void sig_catch_segv (f) void (*f)(); { sig_catch (SIGSEGV, f); }
void sig_catch_pipe (f) void (*f)(); { sig_catch (SIGPIPE, f); }
void sig_catch_alrm (f) void (*f)(); { sig_catch (SIGALRM, f); }
void sig_catch_term (f) void (*f)(); { sig_catch (SIGTERM, f); }
void sig_catch_chld (f) void (*f)(); { sig_catch (SIGCHLD, f); }
void sig_catch_usr1 (f) void (*f)(); { sig_catch (SIGUSR1, f); }
void sig_catch_usr2 (f) void (*f)(); { sig_catch (SIGUSR2, f); }

/* ... and save old actions */
void sig_scatch_hup (f, o) void (*f)(),*o; { sig_catch_save(SIGHUP, f, o); }
void sig_scatch_int (f, o) void (*f)(),*o; { sig_catch_save(SIGINT, f, o); }
void sig_scatch_bus (f, o) void (*f)(),*o; { sig_catch_save(SIGBUS, f, o); }
void sig_scatch_abrt (f, o) void (*f)(),*o; { sig_catch_save(SIGABRT, f, o); }
void sig_scatch_segv (f, o) void (*f)(),*o; { sig_catch_save(SIGSEGV, f, o); }
void sig_scatch_pipe (f, o) void (*f)(),*o; { sig_catch_save(SIGPIPE, f, o); }
void sig_scatch_alrm (f, o) void (*f)(),*o; { sig_catch_save(SIGALRM, f, o); }
void sig_scatch_term (f, o) void (*f)(),*o; { sig_catch_save(SIGTERM, f, o); }
void sig_scatch_chld (f, o) void (*f)(),*o; { sig_catch_save(SIGCHLD, f, o); }
void sig_scatch_usr1 (f, o) void (*f)(),*o; { sig_catch_save(SIGUSR1, f, o); }
void sig_scatch_usr2 (f, o) void (*f)(),*o; { sig_catch_save(SIGUSR2, f, o); }

/* ... and restore old actions */
void sig_rcatch_hup (o) void *o; { sig_catch_restore(SIGHUP, o); }
void sig_rcatch_int (o) void *o; { sig_catch_restore(SIGINT, o); }
void sig_rcatch_bus (o) void *o; { sig_catch_restore(SIGBUS, o); }
void sig_rcatch_abrt (o) void *o; { sig_catch_restore(SIGABRT, o); }
void sig_rcatch_segv (o) void *o; { sig_catch_restore(SIGSEGV, o); }
void sig_rcatch_pipe (o) void *o; { sig_catch_restore(SIGPIPE, o); }
void sig_rcatch_alrm (o) void *o; { sig_catch_restore(SIGALRM, o); }
void sig_rcatch_term (o) void *o; { sig_catch_restore(SIGTERM, o); }
void sig_rcatch_chld (o) void *o; { sig_catch_restore(SIGCHLD, o); }
void sig_rcatch_usr1 (o) void *o; { sig_catch_restore(SIGUSR1, o); }
void sig_rcatch_usr2 (o) void *o; { sig_catch_restore(SIGUSR2, o); }

/* reset signal actions to the default */
void sig_default_hup () { sig_catch (SIGHUP, SIG_DFL); }
void sig_default_int () { sig_catch (SIGINT, SIG_DFL); }
void sig_default_bus () { sig_catch (SIGBUS, SIG_DFL); }
void sig_default_abrt () { sig_catch (SIGABRT, SIG_DFL); }
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
void sig_block_abrt () { sig_setblock (SIG_BLOCK, SIGABRT); }
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
void sig_unblock_abrt () { sig_setblock (SIG_UNBLOCK, SIGABRT); }
void sig_unblock_segv () { sig_setblock (SIG_UNBLOCK, SIGSEGV); }
void sig_unblock_pipe () { sig_setblock (SIG_UNBLOCK, SIGPIPE); }
void sig_unblock_alrm () { sig_setblock (SIG_UNBLOCK, SIGALRM); }
void sig_unblock_term () { sig_setblock (SIG_UNBLOCK, SIGTERM); }
void sig_unblock_chld () { sig_setblock (SIG_UNBLOCK, SIGCHLD); }
void sig_unblock_usr1 () { sig_setblock (SIG_UNBLOCK, SIGUSR1); }
void sig_unblock_usr2 () { sig_setblock (SIG_UNBLOCK, SIGUSR2); }
