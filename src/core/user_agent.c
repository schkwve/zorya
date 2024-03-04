/*
    @file user_agent.c
    @authors lolguy91 <retek1544@gmail.com>
    @date 04/03/2024
    @brief User agent generator
*/

#include "user_agent.h"

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
        "SovyetskiSoyouzy/1.0 (OS: %s, Version: %s) AntiRalsei/1.0 (HTML 2.0)",
        host.name,
        host.version);
    free_host_info(&host);
}