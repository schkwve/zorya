/**
 * @file netwerk/protocols/http.h
 * @author TendingStream73 <root@tendhost.ddns.net> lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief HTTP implementation
 */
#ifndef __HTTP_H__
#define __HTTP_H__

#include <utils/buffer.h>
#include <netwerk/url.h>
#include <stddef.h>
#include <stdint.h>

enum HTTP_VERSION
{
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1
};

typedef struct HTTPHeader
{
    const char* name;
    const char* data;
} http_header_t;

typedef struct HTTPRequest
{
    const char* method;
    const char* path;
    enum HTTP_VERSION ver;
    size_t header_len;
    http_header_t* headers;
    size_t dataLen;
    uint8_t* data;
} http_request_t;

typedef struct HTTPResponse
{
    int status;
    char* data;
} http_response_t;

buffer_t* httpGenRequest(http_request_t* request);

http_response_t httpGET(Url url);
#endif // __HTTP_H__
