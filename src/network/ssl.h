#ifndef SSL_H
#define SSL_H

#include <network/connect.h>

struct ssl_connection *ssl_priv_create_connection(const char *host,
                                                  const char *port,
                                                  int socket);
void ssl_destroy_connection(struct ssl_connection *conn);

#endif /* SSL_H */
