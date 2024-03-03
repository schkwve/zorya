/**
 * @file host.h
 * @brief Host information getter
 * @author lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */

#ifndef __HOST_UTILS_H__
#define __HOST_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *version;
} HostInfo;

HostInfo getHostInfo();
void freeHostInfo(HostInfo *info);

#endif // __CORE_UTILS_H__
