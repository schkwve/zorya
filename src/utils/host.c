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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/utsname.h>
#endif

#include "host.h"

// To lolguy91: ????????
// - schkwve.
struct host_info get_host_info()
{
    char *name;
    char *version;
    struct host_info ret;

    // This is hacky as fuck but IDC
    name = malloc(64);
    version = malloc(64);

#if defined(_WIN32)
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    strcpy(name, "Windows");

    if (GetVersionEx(&osvi)) {
        sprintf(version, "%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion);
    } else {
        strcpy(version, "Unknown");
    }
#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != -1) {
        strcpy(name, sysinfo.sysname);
        strcpy(version, sysinfo.release);
    } else {
        strcpy(name, "Unknown");
        strcpy(version, "Unknown");
    }
#endif
    ret.name = name;
    ret.version = version;

    return ret;
}

/**
 * @brief Frees a host_info structure.
 *
 * @param info
 *        Structure to be free'd
 */
void free_host_info(struct host_info *info)
{
    free(info->name);
    free(info->version);
}
