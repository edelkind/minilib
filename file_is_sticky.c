#include <sys/types.h>
#include <sys/stat.h>

#if 0
	*** file_is_sticky ***
	check if a file has the sticky bit set.
	returns:
		 0 if the file is sticky
		 1 if the file is not sticky
		-1 if stat returns an error
#endif

char file_is_sticky (path)
	char *path;
{
	struct stat filestat;

	if (stat (path, &filestat)) return -1;

	if (filestat.st_mode & S_ISVTX) return 0;

	return 1;
}

