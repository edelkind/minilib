#include <stdlib.h>

#if 0
	*** dup_elem ***
	duplicate pointer array elements (sort of like strdup(), but not)
	note that array must end with a 0-element.
#endif

extern void *memset();

void **dup_elem (array)
	register char **array;
{
	register unsigned int nelem = 1;
	char **array2;

	for (;;) {
		if (!*array) break; ++array; ++nelem;
		if (!*array) break; ++array; ++nelem;
		if (!*array) break; ++array; ++nelem;
	}

	array2 = (char **)malloc(nelem * sizeof(char *));


	for (;;) {
		if (!nelem--) break; array2[nelem] = *array--;
		if (!nelem--) break; array2[nelem] = *array--;
		if (!nelem--) break; array2[nelem] = *array--;
	}

	return ((void **)array2);
}


void **dup_elem_zalloc(array)
	register char **array;
{
	register unsigned int nelem = 1;

	for (;;) {
		if (!*array) break; ++array; ++nelem;
		if (!*array) break; ++array; ++nelem;
		if (!*array) break; ++array; ++nelem;
	}

	array = (char **)malloc(nelem * sizeof(char *));
	if (!array) return (void **)0;

	memset (array, 0, nelem*sizeof(char *));

	return ((void **)array);
}
