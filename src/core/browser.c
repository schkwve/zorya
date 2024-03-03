/**
 * @file browser.c
 * @brief Source file for core/browser.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#include "browser.h"

void handle_http_request(const char* base_url, const char* path, int port) {
  http_header_t *headers = malloc(sizeof(http_header_t) * 2);
  if (headers == NULL) {
    log_fatal("Memory allocation failed for HTTP headers");
    return;
  }
  headers[0].name = strdup("User-Agent");
  headers[0].data = strdup("suzTK/1.0");

  headers[1].name = strdup("Host");
  headers[1].data = strdup(base_url);

  http_request_t req = {
    .method = strdup("GET"),
    .path = strdup(path),
    .ver = HTTP_1_1,
    .headers = headers,
    .header_len = 2,
    .data_len = 0,
    .data = NULL
  };

  buffer_t* req_raw = http_gen_request(&req);

  struct net_connection* con = net_create_connection((char*)base_url, port);
  if (con == NULL) {
    log_fatal("Failed to create connection");
    free(req_raw);
    free(&headers[0].name);
    free(&headers[0].data);
    free(&headers[1].name);
    free(&headers[1].data);
    free(headers);
    return;
  }
  net_send_data(con, req_raw);

  buffer_t* res_raw = malloc(sizeof(buffer_t));
  if (res_raw == NULL) {
    log_fatal("Memory allocation failed for HTTP response buffer");
    buffer_destroy(req_raw);
    net_destroy_connection(con);
    return;
  }
  memset(res_raw, 0, sizeof(buffer_t));
  net_recv_data(con, &res_raw);

  char* ptr = malloc(res_raw->data_len + 1);
  if (ptr == NULL) {
    log_fatal("Memory allocation failed for HTML response buffer");
    buffer_destroy(req_raw);
    buffer_destroy(res_raw);
    net_destroy_connection(con);
    return;
  }

  log_debug("Response loc: 0x%lx", (uint64_t)res_raw->data_ptr);
  log_debug("Response size: %lu", res_raw->data_len);

  memcpy(ptr, res_raw->data_ptr, res_raw->data_len);
  ptr[res_raw->data_len] = '\0';

  ptr = strchr(ptr, '<');

  node_t* tree = parse_html(ptr, strlen(ptr));
  if (tree == NULL) {
    log_fatal("Failed to parse HTML");
    if(req_raw != NULL)
      buffer_destroy(req_raw);
    if(res_raw != NULL)
      buffer_destroy(res_raw);
    net_destroy_connection(con);
    return;
  }
  print_html_tree(tree, 0);
  handle_html(tree, (char*)base_url);

  if(req_raw != NULL)
    buffer_destroy(req_raw);
  if(res_raw != NULL)
    buffer_destroy(res_raw);
  net_destroy_connection(con);
}

void render_page(const char* url) {
  const char* protocol_end = strstr(url, "://");
  const char* protocol;
  int port = 80;
  char* temp_protocol = NULL;

  if (protocol_end == NULL) {
    protocol = "http";
  } else {
    size_t protocol_len = protocol_end - url;
    temp_protocol = malloc(protocol_len + 1);
    if (temp_protocol == NULL) {
      return;
    }
    strncpy(temp_protocol, url, protocol_len);
    temp_protocol[protocol_len] = '\0';
    protocol = temp_protocol;
  }

  if (strcmp(protocol, "http") != 0) {
    protocol = "http";
  }

  const char* base_url_start;
  if (protocol_end == NULL) {
    base_url_start = url;
  } else {
    base_url_start = protocol_end + 3;
  }

  const char* path_start = strchr(base_url_start, '/');
  const char* path = (path_start != NULL) ? path_start : "/";
  size_t base_url_len = (path_start != NULL) ? (path_start - base_url_start) : (strlen(base_url_start));
  char* base_url = malloc(base_url_len + 1);
  if (base_url == NULL) {
    if (protocol_end != NULL) {
      free((void*)protocol);
    }
    return;
  }
  strncpy(base_url, base_url_start, base_url_len);
  base_url[base_url_len] = '\0';

  char* port_start = strchr(base_url, ':');
  if (port_start != NULL) {
    char* endptr;
    long int parsed_port = strtol(port_start + 1, &endptr, 10);
    if (*endptr == '\0') {
      port = (int)parsed_port;
      *port_start = '\0';
      protocol = "unknown";
    }
  }

  if(!protocol && !port) {
    log_info("No protocol specified (or port). Defaulting to HTTP");
  }

  if(strcmp(protocol, "http") == 0 || port == 80) {
    log_debug("===============");
    log_debug("Protocol: %s", protocol);
    log_debug("URL: %s", base_url);
    log_debug("Port: %d", port);
    log_debug("Path: %s", path);
    log_debug("===============");
    handle_http_request(base_url, path, port);
  }

  free(base_url);
  if (protocol_end != NULL) {
    free((void*)protocol);
  }
  free(temp_protocol);
}
