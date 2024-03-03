/**
 * @file browser.c
 * @brief Source file for core/browser.h
 * @author Kevin Alavik <kevin@alavik.se> lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */
#include "browser.h"

#include <antiralsei/parse.h>
#include <antiralsei/handler.h>
#include <netwerk/connect.h>
#include <netwerk/http.h>
#include <netwerk/url.h>
#include <utils/logging.h>
#include <utils/buffer.h>
#include <utils/host.h>
#include <suzTK/window.h>
#include <main.h>

void loadPage(const char* url);

bool browserInit()
{
    // dont't set icon icon on  MacOS
    #ifndef __APPLE__
        setIcon(mainWindow, "../res/logo.png", "../res/logo.png");
    #endif

    loadPage("http://lolguy91:supersecurepassword@info.cern.ch/hypertext/WWW/TheProject.html#CERN?someTrackingID=123456789");
    return true;
}
bool browserUpdate()
{
    //renderHomePage();

    // TODO: Update
    return true;
}
bool
browserDestroy()
{
    //suzwin_destroy_all_windows();
    suzwin_destroy_current_window();
    return true;
}

void loadPage(const char* url){
    HostInfo host = getHostInfo();
    log_debug("Host Info: %s, %s", host.name, host.version);
    freeHostInfo(&host);

    Url urlInfo = parseUrl(url);
    log_debug("Scheme: %s", urlInfo.scheme);
    log_debug("Authority: %s", urlInfo.authority);
    log_debug("Host: %s", urlInfo.host);
    log_debug("Path: %s", urlInfo.path);
    log_debug("Fragment: %s", urlInfo.fragment);
    log_debug("Query: %s", urlInfo.query);
    freeUrl(&urlInfo);
}

//void handle_http_request(const char* base_url, const char* path, int port) {
//  http_header_t *headers = malloc(sizeof(http_header_t) * 2);
//  if (headers == NULL) {
//    log_fatal("Memory allocation failed for HTTP headers");
//    return;
//  }
//
//  char os_name[256];
//  char os_ver[256];
//
//  _get_host_info(os_name, os_ver);
//
//  char user_agent[100];
//  snprintf(user_agent, sizeof(user_agent), "SovyetskiSoyouzy/1.0 (OS: %s, Version: %s) AntiRalsei/1.0 (HTML 2.0)", os_name, os_ver);
//
//  headers[0].name = strdup("User-Agent");
//  headers[0].data = strdup(user_agent);
//
//  headers[1].name = strdup("Host");
//  headers[1].data = strdup(base_url);
//
//  http_request_t req = {
//    .method = strdup("GET"),
//    .path = strdup(path),
//    .ver = HTTP_1_1,
//    .headers = headers,
//    .header_len = 2,
//    .data_len = 0,
//    .data = NULL
//  };
//
//  buffer_t* req_raw = http_gen_request(&req);
//
//  log_info("Connecting to %s", (char*)base_url);
//  struct net_connection* con = net_create_connection((char*)base_url, port);
//  if (con == NULL) {
//    log_fatal("Failed to create connection");
//    free(req_raw);
//    free(&headers[0].name);
//    free(&headers[0].data);
//    free(&headers[1].name);
//    free(&headers[1].data);
//    free(headers);
//    return;
//  }
//  net_send_data(con, req_raw);
//
//  buffer_t* res_raw = malloc(sizeof(buffer_t));
//  if (res_raw == NULL) {
//    log_fatal("Memory allocation failed for HTTP response buffer");
//    buffer_destroy(req_raw);
//    net_destroy_connection(con);
//    return;
//  }
//  memset(res_raw, 0, sizeof(buffer_t));
//  net_recv_data(con, &res_raw);
//
//  char* ptr = malloc(res_raw->data_len + 1);
//  if (ptr == NULL) {
//    log_fatal("Memory allocation failed for HTML response buffer");
//    buffer_destroy(req_raw);
//    buffer_destroy(res_raw);
//    net_destroy_connection(con);
//    return;
//  }
//
//  log_debug("Response loc: 0x%lx", (uint64_t)res_raw->data_ptr);
//  log_debug("Response size: %lu", res_raw->data_len);
//
//  memcpy(ptr, res_raw->data_ptr, res_raw->data_len);
//  ptr[res_raw->data_len] = '\0';
//
//  char* cpy = strdup(ptr);
//
//  int num_headers = _count_headers(cpy);
//  http_header_info_t* h = _parse_response_headers(cpy, &num_headers);
//
//  if (h != NULL) {
//    log_info("Response Headers:");
//    for (int i = 0; i < num_headers; i++) {
//      log_info("  %s: %s", h[i].name, h[i].value);
//      free(h[i].name);
//      free(h[i].value);
//    }
//    free(headers);
//  }
//
//  ptr = strchr(ptr, '<');
//
//  node_t* tree = parse_html(ptr, strlen(ptr));
//
//  if (tree == NULL) {
//    log_fatal("Failed to parse HTML");
//    if(req_raw != NULL)
//      buffer_destroy(req_raw);
//    if(res_raw != NULL)
//      buffer_destroy(res_raw);
//    net_destroy_connection(con);
//    return;
//  }
//  handle_html(tree, (char*)base_url);
//  if(req_raw != NULL)
//    buffer_destroy(req_raw);
//  if(res_raw != NULL)
//    buffer_destroy(res_raw);
//  net_destroy_connection(con);
//}
