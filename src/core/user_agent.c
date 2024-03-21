/*
    @file user_agent.c
    @authors lolguy91 <retek1544@gmail.com>
    @date 04/03/2024
    @brief User agent generator
*/

#include "user_agent.h"

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/host.h>
#include <utils/logging.h>

char g_user_agent[100];

void user_agent_infer()
{
    struct host_info host = get_host_info();
    snprintf(
        g_user_agent,
        sizeof(g_user_agent),
        "Mozilla/5.0 (%s %s) AppleWebKit/537.36 (KHTML, like Gecko) %s/%s(%s)",
        host.name,
        host.version,
        BROWSER_NAME,
        BROWSER_VERSION_STRING,
        BROWSER_VERSION_CODENAME);
    free_host_info(&host);
}