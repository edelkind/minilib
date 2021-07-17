#ifndef INC_MINILIB_MINIMISC_H
#define INC_MINILIB_MINIMISC_H

#include "mltypes.h"
#include "sig.h"
#include "blob.h"
#include "utf8.h"
#include "exitstatus.h"
#include "diestatus.h"

#define READ_ERROR  -1
#define READ_EXCESS -2

#define SHELL "/bin/sh"

#define RET_USAGE 255

#define LEN_ULONG 40 /* 128-bit unsigned integer + \0 */

extern void *getseg ();

extern int gather_input();

extern void die(int exitno, char *fmt, ...);
extern void warn(char *fmt, ...);
extern void die_err(int exitno, char *fmt, ...);
extern void warn_err(char *fmt, ...);
extern void setnum();
extern void strzero();

extern unsigned int strset_long();
extern unsigned int strset_ulong();
extern unsigned int strset_base10();
extern unsigned int strset_ubase10();

extern void sig_catch(int signal, void (*func)(int));
extern void sig_catch_save(int signal, void (*func)(int), void *oact);
extern void sig_catch_restore(int signal, void *oact);
extern void sig_default(int signal);
extern void sig_setblock(int how, int signal);
extern void sig_block(int signal);
extern void sig_unblock(int signal);

extern char is_numeric();
extern char is_base10();

extern char file_is_sticky();

extern char fork_pipefdout();
extern char fork_passthru();
extern char fork_passthru_wait();

extern char *get_sessionid();
extern char *getarg();

extern void **dup_elem();
extern void **dup_elem_zalloc();

#endif
