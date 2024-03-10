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
struct net_response resolve_url(struct url url)
{
    if (strncmp(url.scheme, "http",4) == 0) { // http and https
                struct http_response *res = malloc(sizeof(struct http_response));
                *res = http_get(url, strlen(url.scheme) == 5);// I feel so fucking smart now
                if (!http_is_status_error(res->status)) {
                    return (struct net_response){ .status = RESPONSE_OK,
                                                  .code = 0,
                                                  .page_data = (buffer_t){
                                                      .data_ptr = res->data,
                                                      .data_len = strlen(res->data) },  
                                                  .raw_response = (char*)res,
                                                  .raw_response_type = RAW_RESPONSE_TYPE_HTTP
                                                };
                } else { 
                    return (struct net_response){ .status= RESPONSE_HTTP_ERROR, 
                                                  .code = res->status };
                }
    } else if (strcmp(url.scheme, "suz") == 0) {
        return (struct net_response){ .status = RESPONSE_BUILTIN,
                                      .code = 0,
                                      .page_data = (buffer_t){
                                          .data_ptr = url.path,
                                          .data_len = strlen(url.path) + 1 } };
    } else {
        return (struct net_response){ .status = RESPONSE_ERROR,
                                      .code = ERR_BAD_SCHEME };
    }

    return (struct net_response){ .status = RESPONSE_ERROR,
                                  .code = ERR_UNIMPLEMENTED };
}
