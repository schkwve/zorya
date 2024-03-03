/**
 * @file netwerk/resolver.c
 * @author TendingStream73 <root@tendhost.ddns.net> lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */
#include "resolver.h"
#include <netwerk/url.h>

response_t resolveUrl(Url url){
    return (response_t){
        .status = RESPONSE_OK,
        .code = 0,
        .pageData = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>"
    };
}
