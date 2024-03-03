/**
 * @file netwerk/http.c
 * @author TendingStream73 <root@tendhost.ddns.net> <sasasabaev679@gmail.com>
 * @date 29/02/2024
 * @brief HTTP Stuff, generates http requests and parses http response
 */

#include "http.h"
#include "../utils/buffer.h"
#include "../utils/logging.h"
#include "connect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char* http_ver_str[] = { "0.9", "1.0", "1.1" };

/**
 * @brief Converts http_request_t to buffer, that can be sent to server
 *
 * @param request
 *        http request struct which contains data to generate proper http
 * request for server
 *
 * @return Buffer containing request ready to be sent to server
 */

buffer_t*
http_gen_request(http_request_t* request)
{
    if (request == NULL) { // safety first.
        return 0;
    }
    size_t buf_len = 0;
    buf_len += strlen(request->method) + 1; // 1 is length of white space
    buf_len += strlen(request->path) + 1;
    buf_len += strlen("HTTP/") + 3 + 2; // 3 is version, 2 is \r\n
    for (size_t i = 0; i < request->header_len; i++) {
        buf_len += strlen(request->headers[i].name) + 2 +
                   strlen(request->headers[i].data) + 2;
    }
    buf_len += request->data_len;
    buf_len += 4; // add \r\n\r\n at end
    // And now, generate http request for server.
    char* out = malloc(buf_len);
    if (out == NULL) {
        log_fatal("Failed to allocate http request output buffer\n");
        return 0;
    }
    memset(out, 0, buf_len);
    char *out_pos = out;
    out_pos += sprintf(out_pos,
                      "%s %s HTTP/%s\r\n",
                      request->method,
                      request->path,
                      http_ver_str[request->ver]);

    log_debug("aaaaaaaaaaaaaaaaaaaaaaaaaaaa %u", out_pos - out);

    // Add headers to request
    for (size_t i = 0; i < request->header_len; i++) {
        out_pos += sprintf(out_pos,
                       "%s: %s\r\n",
                       request->headers[i].name,
                       request->headers[i].data);
        log_debug("aaaaaaaaaaaaaaaaaaaaaaaaaaaa %u", out_pos - out);
    }

    // (If data_len is not null) add additional data to request
    if (request->data && request->data_len) {
        out_pos = memcpy(out_pos, request->data, request->data_len);
    }

    memcpy(out_pos - 2, "\r\n\r\n", 4);

    // Request is generated, put it into buffer struct.
    buffer_t* buf = malloc(sizeof(buffer_t));
    buf->data_len = buf_len;
    buf->data_ptr = out;
    return buf;
}
