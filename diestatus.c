#include "minimisc.h"

void diestatus_normal (status)
	int status;
{
	die (exitstatus_return_normal(status), 0);
}

void diestatus_crashed (status)
	int status;
{
	die (RET_USAGE, "process crashed: signal %d%s",
			exitstatus_return_signal(status),
			exitstatus_coredumped(status) ? " (core dumped)" : "");
}

void diestatus_stopped (status)
	int status;
{
	die (RET_USAGE, "process stopped: signal %d",
			exitstatus_return_stopsig(status));
}

