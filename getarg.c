
#if 0
	*** getarg ***
	arg: the rest of the argument string after the option
	     (e.g. if option (char *)opt is '-r', you may pass it as
	     (opt+2).  Therefore, if the user gave '-rstuff' as the option,
	     arg would be 'stuff').

	argv: this should be obvious

	argi: an integer pointer to the argv location of argument arg (e.g. in
	      the example above, argv[*argi] would be '-rstuff')

	If arg is a non-empty string, it is returned.  If arg is empty,
	*argi is incremented and the new argv[*argi] is returned.

	returns the string argument to whatever the last option was,
	incrementing the argument location holder if necessary.  If there
	are no more arguments, the null value of the last argv element is
	returned.
#endif

char *getarg (arg, argv, argi)
	char *arg;
	char **argv;
	int *argi;
{
	if (*arg) return (arg);

	return (argv[++(*argi)]);
}
