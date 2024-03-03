/**
 * @file browser.c
 * @brief Source file for core/browser.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#include "browser.h"
#include "utils.h"

typedef struct {
    char* name;
    char* value;
} http_header_info_t;

void _util_remove_suffix(char *str, const char *format, ...);
http_header_info_t* _parse_response_headers(const char* raw, int* num_headers);
http_header_info_t* _get_res_header_from_char(http_header_info_t *headers, const char *header_name, int num_headers);
int _count_headers(const char* raw);

void handle_http_request(const char* base_url, const char* path, int port) {
  http_header_t *headers = malloc(sizeof(http_header_t) * 2);
  if (headers == NULL) {
    log_fatal("Memory allocation failed for HTTP headers");
    return;
  }

  char os_name[256];
  char os_ver[256];

  _get_host_info(os_name, os_ver);

  char user_agent[100];
  snprintf(user_agent, sizeof(user_agent), "SovyetskiSoyouzy/1.0 (OS: %s, Version: %s) AntiRalsei/1.0 (HTML 2.0)", os_name, os_ver);

  headers[0].name = strdup("User-Agent");
  headers[0].data = strdup(user_agent);

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

  log_info("Connecting to %s", (char*)base_url);
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

  char* cpy = strdup(ptr);

  int num_headers = _count_headers(cpy);
  http_header_info_t* h = _parse_response_headers(cpy, &num_headers);

  if (h != NULL) {
    log_info("Response Headers:");
    for (int i = 0; i < num_headers; i++) {
      log_info("  %s: %s", h[i].name, h[i].value);
      free(h[i].name);
      free(h[i].value);
    }
    free(headers);
  }

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
    log_error("Protocol \"%s\" not supported, falling back to http", protocol);
    protocol = "http";
  }

  const char* base_url_start;
  if (protocol_end == NULL) {
    base_url_start = url;
  } else {
    base_url_start = protocol_end + 3;
  }

  const char* port_start = strchr(base_url_start, ':');
  if (port_start != NULL) {
    char* endptr;
    long int parsed_port = strtol(port_start + 1, &endptr, 10);
    if (*endptr == '\0') {
      port = (int)parsed_port;
      if (protocol_end == NULL) {
        log_error("No protocol specified. Defaulting to HTTP.");
      }
    }
  } else {
    if (protocol_end == NULL) {
      log_error("No protocol or port specified. Defaulting to HTTP.");
    }
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
  if(!protocol && !port) {
    log_info("No protocol specified (or port). Defaulting to HTTP");
  }

  _util_remove_suffix(base_url, ":%d", port);

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
}

void _util_remove_suffix(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char suffix[256];
    vsnprintf(suffix, sizeof(suffix), format, args);
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (str_len >= suffix_len && strcmp(str + str_len - suffix_len, suffix) == 0) {
        str[str_len - suffix_len] = '\0';
    }
    
    va_end(args);
}

http_header_info_t* _parse_response_headers(const char* raw, int* num_headers) {
  http_header_info_t* headers = malloc(sizeof(http_header_info_t) * (*num_headers));
  if (headers == NULL) {
    log_fatal("Memory allocation failed for headers array");
    return NULL;
  }

  int header_count = 0;

  char* line = strtok((char*)raw, "\r\n");
  while (line != NULL && strlen(line) > 0) {
    char* colon_pos = strchr(line, ':');

    if (colon_pos != NULL) {
      size_t name_len = colon_pos - line;
      char* name = malloc(name_len + 1);
      if (name == NULL) {
        log_fatal("Memory allocation failed for header name");
        for (int i = 0; i < header_count; i++) {
          free(headers[i].name);
          free(headers[i].value);
        }
        free(headers);
        *num_headers = 0;
        return NULL;
      }
      strncpy(name, line, name_len);
      name[name_len] = '\0';

      colon_pos++;

      while (*colon_pos == ' ' || *colon_pos == '\t') {
        colon_pos++;
      }

      size_t value_len = strlen(colon_pos);
      char* value = malloc(value_len + 1);
      if (value == NULL) {
        log_fatal("Memory allocation failed for header value");
        free(name);
        for (int i = 0; i < header_count; i++) {
          free(headers[i].name);
          free(headers[i].value);
        }
        free(headers);
        *num_headers = 0;
        return NULL;
      }
      strncpy(value, colon_pos, value_len);
      value[value_len] = '\0';

      headers[header_count].name = name;
      headers[header_count].value = value;
      header_count++;
    }

    line = strtok(NULL, "\r\n");
  }

  *num_headers = header_count;
  return headers;
}


int _count_headers(const char* raw) {
  int header_count = 0;
  const char* line = raw;

  while (*line != '\0') {
    const char* colon_pos = strchr(line, ':');
    if (colon_pos != NULL) {
      header_count++;
    }
    line = strchr(line, '\n');
    if (line != NULL) {
      line++;
    }
  }
  return header_count;
}

http_header_info_t* _get_res_header_from_char(http_header_info_t *headers, const char *header_name, int num_headers) {
    for (int i = 0; i < num_headers; ++i) {
        if (strcmp(headers[i].name, header_name) == 0) {
            return &headers[i];
        }
    }
    return NULL;
}
