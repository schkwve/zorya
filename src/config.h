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

#ifndef CONFIG_H
#define CONFIG_H

#include "utils/string.h"

#define BROWSER_NAME "Zorya"

#define BROWSER_VERSION_MAJOR 0
#define BROWSER_VERSION_MINOR 1
#define BROWSER_VERSION_PATCH 0
#define BROWSER_VERSION_STRING                                                 \
    (STRINGIZE(BROWSER_VERSION_MAJOR) "." STRINGIZE(BROWSER_VERSION_MINOR) "." STRINGIZE(BROWSER_VERSION_PATCH))

#endif /* CONFIG_H */
