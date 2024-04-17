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

#ifndef NET_RESOLVER_H
#define NET_RESOLVER_H

#include <net/url.h>
#include <utils/buffer.h>

#define RESPONSE_OK 0
#define RESPONSE_ERROR 1
#define RESPONSE_HTTP_ERROR 2
#define RESPONSE_BUILTIN 3

#define ERR_BAD_SCHEME 0
#define ERR_UNIMPLEMENTED 1

#define RAW_RESPONSE_TYPE_HTTP 0

/**
 * @brief Network response structure
 */
struct net_response
{
    char status;
    int code;
    buffer_t page_data;
    int raw_response_type;
    char *raw_response;

    // TODO: Media types
};

struct net_response resolve_url(struct url url);

#endif /* NET_RESOLVER_H */
