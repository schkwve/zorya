/**
 * @file netwerk/resolver.c
 * @authors TendingStream73 <sasasabaev679@gmail.com>
 *          lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */

#include <string.h>

#include "resolver.h"
#include <netwerk/protocols/http.h>
#include <netwerk/url.h>

/**
 * @brief Resolves a URL structure
 *
 * @param url
 *        URL structure to be resolved
 *
 * @return Response structure
 */
struct net_response
resolve_url(struct url url)
{
    if (strcmp(url.scheme, "http") == 0) {

        struct http_response res = http_get(url);
        if (res.status == 1) {
            return (struct net_response){ .status = RESPONSE_OK,
                                          .code = 0,
                                          .pageData = (buffer_t){
                                              .dataPtr = res.data,
                                              .data_len = strlen(res.data) } };
        } else {
            return (struct net_response){ .status = RESPONSE_HTTP_ERROR,
                                          .code = res.status };
        }

    } else if (strcmp(url.scheme, "ftp") == 0) {
        return (struct net_response){ .status = RESPONSE_ERROR,
                                      .code = ERR_UNIMPLEMENTED };
    } else if (strcmp(url.scheme, "file") == 0) {
        return (struct net_response){ .status = RESPONSE_ERROR,
                                      .code = ERR_UNIMPLEMENTED };
    } else if (strcmp(url.scheme, "suz") == 0) {
        return (struct net_response){ .status = RESPONSE_BUILTIN,
                                      .code = 0,
                                      .pageData = (buffer_t){
                                          .dataPtr = url.path,
                                          .data_len = strlen(url.path) + 1 } };
    } else {
        return (struct net_response){ .status = RESPONSE_ERROR,
                                      .code = ERR_BAD_SCHEME };
    }

    char *retdata = "<!DOCTYPE html><html><head><title>Page "
                    "Title</title></head><body><h1>This is a "
                    "Heading</h1><p>This is a paragraph.</p></body></html>";

    return (struct net_response){ .status = RESPONSE_OK,
                                  .code = 0,
                                  .pageData.dataPtr = retdata,
                                  .pageData.data_len = strlen(retdata) };
}