#include "../src/netwerk/connect.h"
#include "../src/netwerk/http.h"
#include "../src/utils/buffer.h"
#include "../src/utils/logging.h"

int main() {
  http_header_t headers[] = {{"User-Agent", "USSR"}};

  http_request_t req = {
    .method = "GET",
    .path = "/",
    .ver = HTTP_1_1,
    .headers = &headers[0],
    .header_len = 0,
    .data_len = 100,
    .data = 0
  };
  
  buffer_t* result = http_gen_request(&req);
  
  struct net_connection* con = net_create_connection("example.com", 80);
  net_send_data(con, (char*)result->data_ptr);
  
  buffer_t* res;
  net_recv_data(con, &res);

  log_debug("%s", (char*)res->data_ptr);

}
