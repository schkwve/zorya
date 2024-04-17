/**
 * Copyright (c) 2024 Zorya Browser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
