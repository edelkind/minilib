#include <stdlib.h>

void setnum(num, numstr)
	int  *num;
	char *numstr;
{
	*num = strtod (numstr, 0);
}
