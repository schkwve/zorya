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

#include <net/resolver.h>

/**
 * @brief Resolves a URL structure
 *
 * @param url
 *        URL structure to be resolved
 *
 * @return Response structure
 */
struct net_response resolve_url(struct url url)
{
    return (struct net_response){ .status = RESPONSE_ERROR,
                                  .code = ERR_UNIMPLEMENTED };
}
