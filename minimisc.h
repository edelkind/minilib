#ifndef INC_MINILIB_MINIMISC_H
#define INC_MINILIB_MINIMISC_H

#include "sig.h"
#include "exitstatus.h"
#include "diestatus.h"

#define READ_ERROR  -1
#define READ_EXCESS -2

#define MAX_INPUT    512
#define MAX_INPUTBUF 513  /* MAX_INPUT + 1 */

#define SHELL "/bin/sh"

#define RET_USAGE 255

#define LEN_ULONG 40 /* 128-bit unsigned integer + \0 */

extern void *getseg ();

extern int gather_input();

extern void die();
extern void warn();
extern void die_err();
extern void warn_err();
extern void setnum();
extern void strzero();

extern unsigned int strset_long();
extern unsigned int strset_ulong();
extern unsigned int strset_base10();
extern unsigned int strset_ubase10();

extern void sig_catch();
extern void sig_catch_save();
extern void sig_catch_restore();
extern void sig_default();
extern void sig_setblock();
extern void sig_block();
extern void sig_unblock();

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
