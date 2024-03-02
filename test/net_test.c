#include "../src/netwerk/connect.h"
#include "../src/netwerk/http.h"
#include "../src/utils/buffer.h"
#include "../src/utils/logging.h"
#include <stdlib.h>
#include <string.h>

int main() {
  http_header_t *headers[] = {{"User-Agent", "USSR"}};

  http_request_t req = {
    .method = "GET",
    .path = "/",
    .ver = HTTP_1_1,
    .headers = (http_header_t *)headers,
    .header_len = 0,
    .data_len = 100,
    .data = 0
  };
  
  buffer_t* result = http_gen_request(&req);
  
  struct net_connection* con = net_create_connection("example.com", 80);
  net_send_data(con, result);
  
  buffer_t* res = malloc(sizeof(buffer_t));
  memset(res, 0, sizeof(buffer_t));
  net_recv_data(con, &res);

  log_debug("data ptr: 0x%lx data len: %u", res->data_ptr, res->data_len);

  //log_debug("%s", (char*)res->data_ptr);
  log_debug("we received something, idk what");
  buffer_destroy(result);
  buffer_destroy(res);
  net_destroy_connection(con);
}
