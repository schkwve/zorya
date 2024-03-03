#include "../src/netwerk/connect.h"
#include "../src/netwerk/protocols/http.h"
#include "../src/utils/buffer.h"
#include "../src/utils/logging.h"
#include <stdlib.h>
#include <string.h>

int main() {
  http_header_t *headers = malloc(sizeof(http_header_t)*2);
  headers[0].name = "User-Agent";
  headers[0].data = "USSR; Mozilla/4.0";

  headers[1].name = "Host";
  headers[1].data = "example.com";

  http_request_t req = {
    .method = "GET",
    .path = "/",
    .ver = HTTP_1_1,
    .headers = headers,
    .header_len = 2,
    .dataLen = 0,
    .data = 0
  };
  
  buffer_t* result = http_gen_request(&req);
  
  struct net_connection* con = net_create_connection("example.com", 80);
  net_send_data(con, result);
  
  buffer_t* res = malloc(sizeof(buffer_t));
  memset(res, 0, sizeof(buffer_t));
  net_recv_data(con, &res);

  char* ptr = malloc(res->dataLen + 1);
  memcpy(ptr, res->dataPtr, res->dataLen);
  ptr[res->dataLen] = '\0';

  log_debug("%s", ptr);
  buffer_destroy(result);
  buffer_destroy(res);
  net_destroy_connection(con);
  free(headers);
}
