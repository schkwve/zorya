/**
 * @file netwerk/protocols/http.h
 * @authors TendingStream73 <sasasabaev679@gmail.com>
 *          lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief HTTP implementation
 */
#ifndef NET_PROTOCOLS_HTTP_H
#define NET_PROTOCOLS_HTTP_H

#include <netwerk/url.h>
#include <stddef.h>
#include <stdint.h>
#include <utils/buffer.h>

/**
 * @brief HTTP Version enumeration
 */
enum http_version
{
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1
};

/**
 * @brief HTTP Header structure
 */
struct http_header
{
    char *name;
    char *data;
};

/**
 * @brief HTTP Request structure
 */
struct http_request
{
    char *method;
    char *path;
    enum http_version ver;
    size_t header_len;
    struct http_header *headers;
    size_t data_len;
    uint8_t *data;
};

/**
 * @brief HTTP Response structure
 */
struct http_response
{
    int status;
    char *data;
};

buffer_t *
http_gen_request(struct http_request *request);

struct http_response
http_get(struct url url);

#endif /* NET_PROTOCOLS_HTTP_H */