/**
 * @file netwerk/resolver.c
 * @authors TendingStream73 <sasasabaev679@gmail.com>
 *          lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */

#include <network/resolver.h>

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
