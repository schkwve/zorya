/**
 * @file netwerk/resolver.h
 * @authors TendingStream73 <sasasabaev679@gmail.com>
 *          lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */

#ifndef NETWERK_RESOLVER_H
#define NETWERK_RESOLVER_H

#include <network/url.h>
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

#endif /* NETWERK_RESOLVER_H */
