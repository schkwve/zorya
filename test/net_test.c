#include "../src/netwerk/connect.h"

int main() {
  struct net_connection* con = net_create_connection("127.0.0.1", 6969); 
  if(con != NULL) {
    net_send_data(con, "Hello, World!\n"); 
    net_destroy_connection(con);
  }
}
