#ifndef INC_MINILIB_SIG_H
#define INC_MINILIB_SIG_H

extern void sig_catch_hup ();
extern void sig_catch_int ();
extern void sig_catch_bus ();
extern void sig_catch_segv ();
extern void sig_catch_pipe ();
extern void sig_catch_alrm ();
extern void sig_catch_term ();
extern void sig_catch_chld ();
extern void sig_catch_usr1 ();
extern void sig_catch_usr2 ();

extern void sig_scatch_hup ();
extern void sig_scatch_int ();
extern void sig_scatch_bus ();
extern void sig_scatch_segv ();
extern void sig_scatch_pipe ();
extern void sig_scatch_alrm ();
extern void sig_scatch_term ();
extern void sig_scatch_chld ();
extern void sig_scatch_usr1 ();
extern void sig_scatch_usr2 ();

extern void sig_rcatch_hup ();
extern void sig_rcatch_int ();
extern void sig_rcatch_bus ();
extern void sig_rcatch_segv ();
extern void sig_rcatch_pipe ();
extern void sig_rcatch_alrm ();
extern void sig_rcatch_term ();
extern void sig_rcatch_chld ();
extern void sig_rcatch_usr1 ();
extern void sig_rcatch_usr2 ();

extern void sig_default_hup ();
extern void sig_default_int ();
extern void sig_default_bus ();
extern void sig_default_segv ();
extern void sig_default_pipe ();
extern void sig_default_alrm ();
extern void sig_default_term ();
extern void sig_default_chld ();
extern void sig_default_usr1 ();
extern void sig_default_usr2 ();

extern void sig_block_hup ();
extern void sig_block_int ();
extern void sig_block_bus ();
extern void sig_block_segv ();
extern void sig_block_pipe ();
extern void sig_block_alrm ();
extern void sig_block_term ();
extern void sig_block_chld ();
extern void sig_block_usr1 ();
extern void sig_block_usr2 ();

extern void sig_unblock_hup ();
extern void sig_unblock_int ();
extern void sig_unblock_bus ();
extern void sig_unblock_segv ();
extern void sig_unblock_pipe ();
extern void sig_unblock_alrm ();
extern void sig_unblock_term ();
extern void sig_unblock_chld ();
extern void sig_unblock_usr1 ();
extern void sig_unblock_usr2 ();

#endif
