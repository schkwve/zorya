/**
 * @file browser.c
 * @brief Source file for suzTK/browser.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#include "browser.h"

// TODO: Make this handle params.
void render_page(const char* url) {
  const char* protocol_end = strstr(url, "://");
  const char* protocol;
  int port = 80; // Default port

  if (protocol_end == NULL) {
    log_info("No protocol specified, defaulting to http");
    protocol = "http";
  } else {
    size_t protocol_len = protocol_end - url;
    char* temp_protocol = malloc(protocol_len + 1);
    strncpy(temp_protocol, url, protocol_len);
    temp_protocol[protocol_len] = '\0';
    protocol = temp_protocol;
  }

  if (strcmp(protocol, "http") == 0) {
    log_info("HTTP protocol detected");
    port = 80;
  } else if (strcmp(protocol, "https") == 0) {
    log_info("HTTPS protocol detected, setting port to 443 (not supported but processing)");
    port = 443;
  } else {
    log_error("Invalid protocol: %s, falling back to http", protocol);
    protocol = "http";
    port = 80;
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
  strncpy(base_url, base_url_start, base_url_len);
  base_url[base_url_len] = '\0';

  char* port_start = strchr(base_url, ':');
  if (port_start != NULL) {
    char* endptr;
    long int parsed_port = strtol(port_start + 1, &endptr, 10);
    if (*endptr == '\0') {
      log_info("Found port define in URL: %d", (int)parsed_port);
      log_debug("Found port define in %s: %d", url, (int)parsed_port);
      port = (int)parsed_port;
      *port_start = '\0';
      protocol = "unknown";
    }
  }

  char* method = "GET";

  log_debug("===================");
  log_debug("Protocol: %s", protocol);
  log_debug("Method: %s", method);
  log_debug("Base URL: %s", base_url);
  log_debug("Port: %d", port);
  log_debug("Path: %s", path);
  log_debug("===================");

  http_header_t *headers = malloc(sizeof(http_header_t) * 2);
  headers[0].name = "User-Agent";
  headers[0].data = "suzTK/1.0";

  headers[1].name = "Host";
  headers[1].data = base_url;

  http_request_t req = {
    .method = method,
    .path = path,
    .ver = HTTP_1_1,
    .headers = headers,
    .header_len = 2,
    .data_len = 0,
    .data = 0
  };

  buffer_t* req_raw = http_gen_request(&req);

  struct net_connection* con = net_create_connection(base_url, port);
  net_send_data(con, req_raw);

  buffer_t* res_raw = malloc(sizeof(buffer_t));
  memset(res_raw, 0, sizeof(buffer_t));
  net_recv_data(con, &res_raw);

  char* ptr = malloc(res_raw->data_len + 1);
  memcpy(ptr, res_raw->data_ptr, res_raw->data_len);
  ptr[res_raw->data_len] = '\0';

  // TODO: Make this store the response headers.
  ptr = strchr(ptr, '<');

  node_t* tree = parse_html(ptr, strlen(ptr));
  print_html_tree(tree, 0);
  handle_html(tree, base_url);

  // cleanup
  free_html_tree(tree);
  buffer_destroy(req_raw);
  buffer_destroy(res_raw);
  net_destroy_connection(con);
  free(headers);
  free(base_url);
  if (protocol_end != NULL) {
    free((void*)protocol); // Cast to void* to avoid warning
  }
}