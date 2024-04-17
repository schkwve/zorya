/**
 * @file browser.c
 * @authors Kevin Alavik <kevin@alavik.se>
 *          lolguy91 <retek1544@gmail.com>
            maalos <maalos@pex.ovh>
 * @date 02/03/2024
 * @brief Source file for core/browser.h
 */

#include <signal.h>
#include <stdbool.h>

#include <config.h>
#include <core/browser.h>
#include <utils/logging.h>

/**
 * @brief Initializes the browser.
 *
 * @return True if the browser was initialized successfully;
 *         False otherwise.
 */
bool browser_init()
{
    // OpenSSL can shit itself if SIGPIPE isn't ignored
    signal(SIGPIPE, SIG_IGN);

    log_trace("Browser identifies as \"%s v%s\"",
              BROWSER_NAME,
              BROWSER_VERSION_STRING);

    return true;
}

/**
 * @brief Updated the browser. This function is called on every tick.
 *
 * @return True if the browser was updated successfully;
 *         False otherwise.
 */
bool browser_update()
{
    return true;
}

void browser_destroy()
{
}
