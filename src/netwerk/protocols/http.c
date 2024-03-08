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

bool http_is_status_error(int status)
{
    return (status >= 400 && status < 600) ||
           status < 100; // 0-99 are custom errors
}

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
 * @param ssl
 *        Specifies whether the request should be sent over HTTPS.
 *
 * @return A valid HTTP response structure if status == 1;
 *         if status == 0, the response is invalid or an error has occured.
 */
struct http_response http_get(struct url url, bool ssl)
{
    struct http_response ret;
    char *base_url = strdup(url.host);
    const char *portstr = ssl ? "443" : "80";
    uint16_t port = atoi(portstr);
    char *sep = strchr(base_url, ':');
    if (sep) {
        *sep = '\0';
        portstr = (sep + 1);
        port = atoi(sep + 1);
    }

    log_debug("Connecting to %s:%d...", base_url, port);

    struct http_header headers[2];

    headers[0].name = "User-Agent";
    headers[0].data = g_user_agent;

    headers[1].name = "Host";
    headers[1].data = url.host;

    // get the right path
    char *path;
    if (url.path == NULL)
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
    struct net_connection *con = net_create_connection(base_url, portstr, ssl);
    if (con == NULL) {
        log_fatal("Failed to create connection");

        ret.status = 0;
        ret.data = NULL;

        goto cleanup;
    }
    net_send_data(con, req_raw);

    buffer_t *res_raw = (buffer_t *)malloc(sizeof(buffer_t));
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
    if (ptr[0] != 'H' || ptr[1] != 'T' || ptr[2] != 'T' || ptr[3] != 'P') {
        log_error("Invalid HTTP response");
        ret.status = 0;
        ret.data = NULL;
        goto cleanup;
    }
    ptr += 7;

    switch (ptr[0]) {
        case '9':
            log_debug("HTTP version: 0.9");
            ret.ver = HTTP_0_9;
            break;
        case '0':
            log_debug("HTTP version: 1.0");
            ret.ver = HTTP_1_0;
            break;
        case '1':
            log_debug("HTTP version: 1.1");
            ret.ver = HTTP_1_1;
            break;
        default:
            log_error("Unsupported HTTP version");
            ret.status = 0;
            ret.data = NULL;
            goto cleanup;
    }
    ptr += 2;
    char statuschars[4];
    statuschars[0] = ptr[0];
    statuschars[1] = ptr[1];
    statuschars[2] = ptr[2];
    statuschars[3] = '\0';
    ret.status = atoi(statuschars);
    log_debug("Status: %d", ret.status);
    ptr += 4;

    char *nextline = strchr(ptr, '\n');
    if (nextline == NULL) {
        log_error("HTTP response is invalid");
        ret.status = 0;
        ret.data = NULL;
        goto cleanup;
    }
    *nextline = '\0';
    *(nextline - 1) = '\0';

    ret.status_desc = malloc(strlen(ptr) + 1);
    strcpy(ret.status_desc, ptr);
    log_debug("Status description: \"%s\"", ret.status_desc);

    ptr = nextline + 1;

    // parse the headers: each one is on an new line and its key and valuse are
    // separated by a colon
    char *colon = strchr(ptr, ':');
    char *newline = strchr(ptr, '\n');
    ret.headers = malloc(sizeof(struct http_header) + 1);
    while (colon < newline) {
        if (*(newline + 1) == '\r' && colon > newline) {
            break;
        }
        *colon = '\0';
        *newline = '\0';

        struct http_header header = { .name = ptr, .data = colon + 1 };

        log_debug("Header: %s: %s", header.name, header.data);
        ret.headers = realloc(
            ret.headers, sizeof(struct http_header) * (ret.header_len + 1));
        ret.headers[ret.header_len] = header;
        ret.header_len++;
        ptr = newline + 1;
        colon = strchr(ptr, ':');
        newline = strchr(ptr, '\n');
    }

    ret.data = ptr;
    ret.data_len = strlen(ptr);

cleanup:
    if (req_raw) {
        buffer_destroy(req_raw);
    }
    if (res_raw) {
        buffer_destroy(res_raw);
    }
    if (base_url) {
        free(base_url);
    }
    if (con) {
        net_destroy_connection(con);
    }

    return ret;
}

void free_http_response(struct http_response res)
{
    if (res.data) {
        free((void *)res.data);
    }
}
