/**
 * @file netwerk/resolver.h
 * @author TendingStream73 <root@tendhost.ddns.net> lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */

#ifndef __NETWERK_RESOLVER_H__
#define __NETWERK_RESOLVER_H__

#include <utils/buffer.h>
#include <netwerk/url.h>

#define RESPONSE_OK         0
#define RESPONSE_ERROR      1
#define RESPONSE_HTTP_ERROR 2
#define RESPONSE_BUILTIN    3

#define ERR_BAD_SCHEME      0
#define ERR_UNIMPLEMENTED   1

typedef struct {
    char status;
    int code;
    buffer_t pageData;
    //TODO: Media types
} response_t;

response_t resolveUrl(Url url);

#endif // __NETWERK_RESOLVER_H__
