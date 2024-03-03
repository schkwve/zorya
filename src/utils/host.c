/**
 * @file host.c
 * @brief Host information getter implementation
 * @author lolguy91 <retek1544@gmail.com>
 * @date 02/03/2024
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
struct host_info
get_host_info()
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
void
free_host_info(struct host_info *info)
{
    free(info->name);
    free(info->version);
}
