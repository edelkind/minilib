#include <fcntl.h>

int main(argc, argv)
	int argc;
	char **argv;
{
	char **argp = argv+1;
	int fd;

	if (!*argp) _exit (2);

	fd = open (argp, O_RDWR|O_CREAT|O_EXCL, 0600);

	if (fd == -1) _exit(2);

	if (fcntl (fd, F_
