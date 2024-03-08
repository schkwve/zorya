#ifndef SSL_H
#define SSL_H

#include <stdbool.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>

struct ssl_connection
{
    int sock;
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    bool is_initialized;
};

struct ssl_connection *ssl_create_connection(const char *host,
                                             const char *port);
void ssl_destroy_connection(struct ssl_connection *conn);

#endif /* SSL_H */
