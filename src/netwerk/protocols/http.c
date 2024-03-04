/**
 * @file netwerk/protocols/http.c
 * @authors TendingStream73 <sasasabaev679@gmail.com>
 *          lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief HTTP implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"
#include <core/user_agent.h>
#include <netwerk/connect.h>
#include <utils/buffer.h>
#include <utils/logging.h>

/**
 * @brief Stringized HTTP versions
 */
static const char *http_ver_str[] = { "0.9", "1.0", "1.1" };

/**
 * @brief Converts an HTTP request to a buffer which can be sent to server
 *
 * @param request
 *        HTTP request struct which contains data to generate proper HTTP
 *        request for server
 *
 * @return Buffer containing request data if no error has occured;
 *         NULL otherwise.
 */
buffer_t *http_gen_request(struct http_request *request)
{
    if (request == NULL) { // safety first.
        log_error("request == NULL");
        return NULL;
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
    char *out = malloc(buf_len);
    if (out == NULL) {
        log_fatal("Failed to allocate http request output buffer\n");
        return NULL;
    }
    memset(out, 0, buf_len);
    char *out_pos = out;
    out_pos += snprintf(out_pos,
                        buf_len,
                        "%s %s HTTP/%s\r\n",
                        request->method,
                        request->path,
                        http_ver_str[request->ver]);

    // Add headers to request
    for (size_t i = 0; i < request->header_len; i++) {
        out_pos += snprintf(out_pos,
                            buf_len,
                            "%s: %s\r\n",
                            request->headers[i].name,
                            request->headers[i].data);
    }

    // (If data_len is not null) add additional data to request
    if (request->data && request->data_len) {
        out_pos = memcpy(out_pos, request->data, request->data_len);
    }

    memcpy(out_pos - 2, "\r\n\r\n", 4);

    // Request is generated, put it into buffer struct.
    buffer_t *buf = malloc(sizeof(buffer_t));
    buf->data_len = buf_len;
    buf->data_ptr = out;
    return buf;
}

/**
 * @brief Generates a GET request.
 *
 * @param url
 *        Complete URL to access
 *
 * @return A valid HTTP response structure if status == 1;
 *         if status == 0, the response is invalid or an error has occured.
 */
struct http_response http_get(struct url url)
{
    struct http_response ret;
    char *base_url = strdup(url.host);
    unsigned short port = 80;
    char *colon = strchr(base_url, ':');
    if (colon) {
        *colon = '\0';
        port = atoi(colon + 1);
    }

    log_debug("Connecting to %s:%d...", base_url, port);

    struct http_header headers[2];

    headers[0].name = "User-Agent";
    headers[0].data = g_user_agent;

    headers[1].name = "Host";
    headers[1].data = url.host;

    //get the right path
    char* path;
    if(url.path == NULL)
        path = "/";
    else
        path = url.path;


    struct http_request req = { .method = "GET",
                                .path = path,
                                .ver = HTTP_1_1,
                                .headers = headers,
                                .header_len = 2,
                                .data_len = 0,
                                .data = NULL };

    buffer_t *req_raw = http_gen_request(&req);
    struct net_connection *con = net_create_connection((char *)base_url, port);
    if (con == NULL) {
        log_fatal("Failed to create connection");

        ret.status = 0;
        ret.data = NULL;

        goto cleanup;
    }
    net_send_data(con, req_raw);
    buffer_t *res_raw = malloc(sizeof(buffer_t));
    if (res_raw == NULL) {
        log_fatal("Memory allocation failed for HTTP response buffer");

        ret.status = 0;
        ret.data = NULL;

        goto cleanup;
    }
    memset(res_raw, 0, sizeof(buffer_t));
    net_recv_data(con, &res_raw);

    char *ptr = malloc(res_raw->data_len + 1);
    if (ptr == NULL) {
        log_fatal("Memory allocation failed for HTML response buffer");

        ret.status = 0;
        ret.data = NULL;
        goto cleanup;
    }
    memset(ptr, 0, res_raw->data_len + 1);
    memcpy(ptr, res_raw->data_ptr, res_raw->data_len);
    ptr[res_raw->data_len] = '\0';

    ptr = strchr(ptr, '<');

    ret.status = 1;
    ret.data = ptr;

cleanup:
    buffer_destroy(req_raw);
    buffer_destroy(res_raw);
    free((void *)base_url);
    net_destroy_connection(con);

    return ret;
}
