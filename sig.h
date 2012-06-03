#ifndef INC_MINILIB_SIG_H
#define INC_MINILIB_SIG_H

typedef void (*m_sigfp)();

extern void sig_catch_hup  (m_sigfp f);
extern void sig_catch_int  (m_sigfp f);
extern void sig_catch_bus  (m_sigfp f);
extern void sig_catch_abrt (m_sigfp f);
extern void sig_catch_segv (m_sigfp f);
extern void sig_catch_pipe (m_sigfp f);
extern void sig_catch_alrm (m_sigfp f);
extern void sig_catch_term (m_sigfp f);
extern void sig_catch_chld (m_sigfp f);
extern void sig_catch_usr1 (m_sigfp f);
extern void sig_catch_usr2 (m_sigfp f);

extern void sig_scatch_hup  (m_sigfp f, void*o);
extern void sig_scatch_int  (m_sigfp f, void*o);
extern void sig_scatch_bus  (m_sigfp f, void*o);
extern void sig_scatch_abrt (m_sigfp f, void*o);
extern void sig_scatch_segv (m_sigfp f, void*o);
extern void sig_scatch_pipe (m_sigfp f, void*o);
extern void sig_scatch_alrm (m_sigfp f, void*o);
extern void sig_scatch_term (m_sigfp f, void*o);
extern void sig_scatch_chld (m_sigfp f, void*o);
extern void sig_scatch_usr1 (m_sigfp f, void*o);
extern void sig_scatch_usr2 (m_sigfp f, void*o);

extern void sig_rcatch_hup  (void *o);
extern void sig_rcatch_int  (void *o);
extern void sig_rcatch_bus  (void *o);
extern void sig_rcatch_abrt (void *o);
extern void sig_rcatch_segv (void *o);
extern void sig_rcatch_pipe (void *o);
extern void sig_rcatch_alrm (void *o);
extern void sig_rcatch_term (void *o);
extern void sig_rcatch_chld (void *o);
extern void sig_rcatch_usr1 (void *o);
extern void sig_rcatch_usr2 (void *o);

extern void sig_default_hup  ();
extern void sig_default_int  ();
extern void sig_default_bus  ();
extern void sig_default_abrt ();
extern void sig_default_segv ();
extern void sig_default_pipe ();
extern void sig_default_alrm ();
extern void sig_default_term ();
extern void sig_default_chld ();
extern void sig_default_usr1 ();
extern void sig_default_usr2 ();

extern void sig_block_hup  ();
extern void sig_block_int  ();
extern void sig_block_bus  ();
extern void sig_block_abrt ();
extern void sig_block_segv ();
extern void sig_block_pipe ();
extern void sig_block_alrm ();
extern void sig_block_term ();
extern void sig_block_chld ();
extern void sig_block_usr1 ();
extern void sig_block_usr2 ();

extern void sig_unblock_hup  ();
extern void sig_unblock_int  ();
extern void sig_unblock_bus  ();
extern void sig_unblock_abrt ();
extern void sig_unblock_segv ();
extern void sig_unblock_pipe ();
extern void sig_unblock_alrm ();
extern void sig_unblock_term ();
extern void sig_unblock_chld ();
extern void sig_unblock_usr1 ();
extern void sig_unblock_usr2 ();

#endif
