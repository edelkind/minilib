#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "minimisc.h"

extern char **environ;

int main(int argc, const char *argv[])
{
    char **envp = environ;
    char *key, *value;
    blobset *bs = blob_new(20, NULL);
    blobcursor bc;
    ub2_t keysize;

    for (;key = *envp; envp++) {
        value = index(key, '=');
        if (!value) {
            fprintf(stderr, "bad env: %s\n", key);
            continue;
        }
        *value++ = 0;
        blob_register(bs, key, strlen(key), value, 0);
    }

    blob_cursor_init(&bc, bs);

    //printf("%s = %s\n", "SHELL", (char*)blob_cursor_get(&bc, "SHELL", 5));

    //if (!blob_cursor_find_first(&bc, "SHELL", 5, (void**)&value))
    //    printf("%s = %s\n", "SHELL", value);

    while (!blob_cursor_next(&bc, (void**)&value, (ub1_t**)&key, &keysize)) {
        printf("%.*s=%s\n", keysize, key, value);
    }

    assert (blob_cursor_next(&bc, (void**)&value, (ub1_t**)&key, &keysize));
    return 0;
}
