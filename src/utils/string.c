#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <utils/string.h>

char *str_tolower(char *str)
{
    // prep
    if (str == NULL)
        return NULL;
    char *dststr = malloc(strlen(str) + 1);

    // copy the string and make it lowercase
    size_t i;
    for (i = 0; str[i] != '\0'; i++)
        dststr[i] = tolower(str[i]);

    // Null terminate and return the new string
    dststr[i] = '\0';
    return dststr;
}
