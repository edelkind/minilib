#ifndef INC_MINILIB_EXITSTATUS_H
#define INC_MINILIB_EXITSTATUS_H

extern char exitstatus_normal ();
extern char exitstatus_crashed ();
extern char exitstatus_stopped ();
extern char exitstatus_coredumped ();
extern char exitstatus_return_normal ();
extern char exitstatus_return_signal ();
extern char exitstatus_return_stopsig ();

#endif
