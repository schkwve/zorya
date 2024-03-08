#ifndef SSL_H
#define SSL_H

#include <stdbool.h>

#include "connect.h"

void ssl_priv_send_data(struct ssl_connection *conn, buffer_t *buffer);
size_t ssl_priv_recv_data(struct ssl_connection *conn, buffer_t **buffer);

int ssl_priv_create_connection(const char *host, const char *port, struct ssl_connection *new);
void ssl_destroy_connection(struct ssl_connection *conn);

#endif /* SSL_H */
