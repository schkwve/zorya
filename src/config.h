/*
 * @file config.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 04/03/2024
 * @brief Browser configuration
 */

// note for @lolguy91:
// please learn doxygen-style comments. -schkwve

#ifndef CONFIG_H
#define CONFIG_H

#include "utils/string.h"

#define BROWSER_NAME "Zorya"

#define BROWSER_VERSION_MAJOR 0
#define BROWSER_VERSION_MINOR 1
#define BROWSER_VERSION_PATCH 0
#define BROWSER_VERSION_STRING                                                 \
    (STRINGIZE(BROWSER_VERSION_MAJOR) "." STRINGIZE(BROWSER_VERSION_MINOR) "." STRINGIZE(BROWSER_VERSION_PATCH))

#endif