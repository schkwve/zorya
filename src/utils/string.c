#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

char *str_tolower(char *str)
{
    char *d = (char *)malloc(strlen(str));
    while (*str) {
        *d = tolower(*str);
        d++;
        str++;
    }
    return d;
}
