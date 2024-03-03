/**
 * @file netwerk/protocols/http.c
 * @author TendingStream73 <root@tendhost.ddns.net> lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief HTTP implementation
 */

#include "http.h"
#include <utils/buffer.h>
#include <utils/logging.h>
#include <utils/host.h>
#include <netwerk/connect.h>
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

buffer_t* httpGenRequest(http_request_t* request)
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
    buf_len += request->dataLen;
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


    // Add headers to request
    for (size_t i = 0; i < request->header_len; i++) {
        out_pos += sprintf(out_pos,
                       "%s: %s\r\n",
                       request->headers[i].name,
                       request->headers[i].data);
    }

    // (If dataLen is not null) add additional data to request
    if (request->data && request->dataLen) {
        out_pos = memcpy(out_pos, request->data, request->dataLen);
    }

    memcpy(out_pos - 2, "\r\n\r\n", 4);

    // Request is generated, put it into buffer struct.
    buffer_t* buf = malloc(sizeof(buffer_t));
    buf->dataLen = buf_len;
    buf->dataPtr = out;
    return buf;
}


http_response_t httpGET(Url url){
    char* base_url = strdup(url.host);
    unsigned short port = 80;
    char* colon = strchr(base_url, ':');
    if (colon) {
      *colon = '\0';
      port = atoi(colon+1);
    } 

    log_debug("Connecting to %s:%d", base_url, port);

    HostInfo host = getHostInfo(url);

    char user_agent[100];
    snprintf(user_agent, sizeof(user_agent), "SovyetskiSoyouzy/1.0 (OS: %s, Version: %s) AntiRalsei/1.0 (HTML 2.0)", host.name, host.version);

    http_header_t *headers = malloc(sizeof(http_header_t) * 2);
    if (headers == NULL) {
      log_fatal("Memory allocation failed for HTTP headers");
      return (http_response_t){.status = 0};
    }

    headers[0].name = "User-Agent";
    headers[0].data = strdup(user_agent);

    headers[1].name = "Host";
    headers[1].data = malloc(strlen(url.host) + 4);
    snprintf(headers[1].data, strlen(url.host) + 4, "%s:%d", url.host, port);

    http_request_t req = {
      .method = "GET",
      .path = strdup(url.path),
      .ver = HTTP_1_1,
      .headers = headers,
      .header_len = 2,
      .dataLen = 0,
      .data = NULL
    };

    buffer_t* req_raw = httpGenRequest(&req);
    struct net_connection* con = net_create_connection((char*)base_url, port);
    if (con == NULL) {
      log_fatal("Failed to create connection");

      //free everything
      free(base_url);
      free(req.path);
      buffer_destroy(req_raw);
      free(headers[0].data);
      free(headers[1].data);
      free(headers);
      freeHostInfo(&host);
      net_destroy_connection(con);

      return (http_response_t){.status = 0};
    }
    net_send_data(con, req_raw);
    buffer_t* res_raw = malloc(sizeof(buffer_t));
    if (res_raw == NULL) {
      log_fatal("Memory allocation failed for HTTP response buffer");

      //free everything
      buffer_destroy(req_raw);
      buffer_destroy(res_raw);
      free(base_url);
      free(req.path);
      free(headers[0].data);
      free(headers[1].data);
      free(headers);
      freeHostInfo(&host);
      net_destroy_connection(con);

      return (http_response_t){.status = 0};
    }
    memset(res_raw, 0, sizeof(buffer_t));
    net_recv_data(con, &res_raw);

    char* ptr = malloc(res_raw->dataLen + 1);
    if (ptr == NULL) {
      log_fatal("Memory allocation failed for HTML response buffer");

      //free everything
      buffer_destroy(req_raw);
      buffer_destroy(res_raw);
      free(base_url);
      free(req.path);
      free(headers[0].data);
      free(headers[1].data);
      free(headers);
      freeHostInfo(&host);
      net_destroy_connection(con);

      return (http_response_t){.status = 0};
    }
    memset(ptr, 0, res_raw->dataLen + 1);
    memcpy(ptr, res_raw->dataPtr, res_raw->dataLen);
    ptr[res_raw->dataLen] = '\0';

    ptr = strchr(ptr, '<');

    buffer_destroy(req_raw);
    buffer_destroy(res_raw);
    free(base_url);
    free(req.path);
    free(headers[0].data);
    free(headers[1].data);
    free(headers);
    freeHostInfo(&host);
    net_destroy_connection(con);

    return (http_response_t){.status = 1, .data = ptr};
}