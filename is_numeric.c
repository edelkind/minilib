
#if 0
	*** is_numeric ***
	tests if a string argument is fully numeric
	you probably do not want to use this with large bases.

	returns 1 if it is, 0 if not.
#endif

char is_numeric (arg, base)
	char *arg;
	int base;
{
	register char c;
	char rvalue = 0; /* default to 0, in case arg is empty */

	for (;;) {
		c = *arg++;
		if (!c) return rvalue;
		if ((c < '0') || (c > ('0' + base))) return 0;
		rvalue = 1;

		c = *arg++;
		if (!c) return rvalue;
		if ((c < '0') || (c > ('0' + base))) return 0;
		rvalue = 1;
	}

	/* control should not reach here */
	return 0;
}


#if 0
	*** is_base10 ***
	returns 1 if arg is fully base 10, 0 otherwise.
#endif

char is_base10(arg)
	char *arg;
{
	return (is_numeric(arg, 10));
}

