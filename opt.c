char opt (argc, argv, optchar, optstr)
	int argc;
	char **argv;
	char optchar;
	char *optstr;
{
	static char *optptr;
	static char *argptr;
	static unsigned int argnum = 1;

	while (argnum < argc) {
		optptr = argv[argnum];
		if (*optptr == optchar) {
			
