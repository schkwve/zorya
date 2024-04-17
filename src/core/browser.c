/**
 * Copyright (c) 2024 Zorya Browser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

void browser_destroy() {}
