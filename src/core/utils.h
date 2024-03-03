#ifndef __CORE_UTILS_H__
#define __CORE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__APPLE__) || defined(__MACH__)
#include <sys/utsname.h>
#else
#include <sys/utsname.h>
#endif

void _get_host_info(char *name, char *version) {
#if defined(_WIN32)
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi)) {
        sprintf(name, "Windows");
        sprintf(version, "%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion);
    } else {
        strcpy(name, "Unknown");
        strcpy(version, "Unknown");
    }
#elif defined(__APPLE__) || defined(__MACH__)
    struct utsname sysinfo;
    if (uname(&sysinfo) != -1) {
        strcpy(name, sysinfo.sysname);
        strcpy(version, sysinfo.release);
    } else {
        strcpy(name, "Unknown");
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
}

#endif // __CORE_UTILS_H__
