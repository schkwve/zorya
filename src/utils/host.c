/**
 * @file host.c
 * @brief Host information getter implementation
 * @author lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */
#include "host.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/utsname.h>
#endif

HostInfo getHostInfo() {
    char* name;
    char* version;

    //This is hacky as fuck but IDC
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
    return (HostInfo){ name, version };
}

void freeHostInfo(HostInfo *info) {
    free(info->name);
    free(info->version);
}