/**
 * @file main.c
 * @authors lolguy91 <retek1544@gmail.com>
 *          KapPetrov <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <core/browser.h>
#include <network/connect.h>
#include <utils/buffer.h>

#include "utils/logging.h"

/**
 * @brief Browser entry point.
 */
int main(void)
{
    // initialize browser
    if (!browser_init()) {
        log_fatal("Failed to initialize browser.");
        return EXIT_FAILURE;
    }
    bool should_quit = false;

    // browser loop
    while (should_quit != true) {
        if (!browser_update()) {
            log_fatal("Failed to update browser 5 times in a row! Exitting...");
            should_quit = true;
        }
    }

    browser_destroy();

    return EXIT_SUCCESS;
}
