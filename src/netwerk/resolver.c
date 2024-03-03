/**
 * @file netwerk/resolver.c
 * @author TendingStream73 <root@tendhost.ddns.net> lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief URL resolver
 */
#include "resolver.h"
#include <netwerk/url.h>
#include <netwerk/protocols/http.h>

response_t resolveUrl(Url url){
    if(strcmp(url.scheme, "http") == 0) {

        http_response_t res = httpGET(url);
        if (res.status == 1) {
            return (response_t){
                .status = RESPONSE_OK,
                .code = 0,
                .pageData = (buffer_t){
                    .dataPtr = res.data,
                    .dataLen = strlen(res.data)
                }
            };
        } else {
            return (response_t){
                .status = RESPONSE_HTTP_ERROR,
                .code = res.status
            };
        }

    }else if(strcmp(url.scheme, "ftp") == 0) {
        return (response_t){
            .status = RESPONSE_ERROR,
            .code = ERR_UNIMPLEMENTED
        };
    }else if(strcmp(url.scheme, "file") == 0) {
        return (response_t){
            .status = RESPONSE_ERROR,
            .code = ERR_UNIMPLEMENTED
        };
    }else if(strcmp(url.scheme, "suz") == 0) {
        return (response_t){
            .status = RESPONSE_BUILTIN,
            .code = 0,
            .pageData = (buffer_t){
                .dataPtr = url.path,
                .dataLen = strlen(url.path) + 1
            }
        };
    }else{
        return (response_t){
            .status = RESPONSE_ERROR,
            .code = ERR_BAD_SCHEME
        };
    }

    return (response_t){
        .status = RESPONSE_OK,
        .code = 0,
        .pageData = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>"
    };
}
