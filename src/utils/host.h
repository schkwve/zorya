/**
 * @file host.h
 * @brief Host information getter
 * @author lolguy91 <retek1544@gmail.com>
 * @date 02/03/2024
 */

#ifndef HOST_UTILS_H
#define HOST_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct host_info
{
    char *name;
    char *version;
};

struct host_info
get_host_info();

void
free_host_info(struct host_info *info);

#endif /* CORE_UTILS_H */
