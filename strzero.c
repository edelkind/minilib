
extern void *memset();
extern int strlen();

#if 0
	*** strzero ***
	zero a string
	returns nothing
#endif

void strzero(str)
	char *str;
{
	memset (str, 0, strlen(str));
}
