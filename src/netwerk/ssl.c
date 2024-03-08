/**
 * @file netwerk/ssl.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 07/03/2024
 * @brief Secure Socket Layer sslsupport
 */

#include <assert.h>
#include <netdb.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <sys/socket.h>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include "ssl.h"
#include <utils/logging.h>

struct ssl_connection *ssl_create_connection(const char *host, const char *port)
{
    int result = EXIT_FAILURE;
    struct ssl_connection *new =
        (struct ssl_connection *)malloc(sizeof(struct ssl_connection));
    if (new == NULL) {
        log_error("Failed to allocate memory for new SSL connection!");
        return NULL;
    }

    new->ctx = SSL_CTX_new(TLS_client_method());
    if (new->ctx == NULL) {
        log_error("Failed to create SSL context!");
        goto cleanup;
    }

    // *always* drop the handshake if CA verification fails
    SSL_CTX_set_verify(new->ctx, SSL_VERIFY_PEER, NULL);

    // use the default trusted cert store
    if (!SSL_CTX_set_default_verify_paths(new->ctx)) {
        log_error("Failed to set default trusted certificate store!");
        goto cleanup;
    }

    // accept only TLSv1.2 or later
    if (!SSL_CTX_set_min_proto_version(new->ctx, TLS1_2_VERSION)) {
        log_error("Failed to set the minimum TLS protocol version to TLSv1.2!");
        goto cleanup;
    }

    // create an SSL object to represent the connection
    new->ssl = SSL_new(new->ctx);
    if (new->ssl == NULL) {
        log_error("Failed to create SSL object!");
        goto cleanup;
    }

    new->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (new->sock == -1) {
        log_error("socket() returned -1!");
        goto cleanup;
    }

    // find the server
    BIO_ADDRINFO *res;
    const BIO_ADDRINFO *ai = NULL;

    if (!BIO_lookup_ex(
            host, port, BIO_LOOKUP_CLIENT, AF_INET, SOCK_STREAM, 0, &res)) {
        log_error("Failed to lookup hostname %s!", host);
        goto cleanup;
    }

    // loop through all possible addresses
    new->sock = -1;
    for (ai = res; ai != NULL; ai = BIO_ADDRINFO_next(ai)) {
        new->sock = BIO_socket(BIO_ADDRINFO_family(ai), SOCK_STREAM, 0, 0);
        if (new->sock == -1) {
            continue;
        }

        // try connecting
        if (!BIO_connect(
                new->sock, BIO_ADDRINFO_address(ai), BIO_SOCK_NODELAY)) {
            BIO_closesocket(new->sock);
            new->sock = -1;
            continue;
        }

        // we got successfully connected! yay!
        break;
    }

    if (new->sock == -1) {
        log_error("Failed to connect to %s:%s!", host, port);
        goto cleanup;
    }

    BIO_ADDRINFO_free(res);

    new->bio = BIO_new(BIO_s_socket());
    if (new->bio == NULL) {
        log_error("BIO_new() returned NULL!");
        goto cleanup;
    }

    // associate stuff with other stuff :p
    BIO_set_fd(new->bio, new->sock, BIO_NOCLOSE);
    SSL_set_bio(new->ssl, new->bio, new->bio);

    if (!SSL_set_tlsext_host_name(new->ssl, host)) {
        log_error("Failed to set SNI hostname!");
        goto cleanup;
    }

    // make sure the server supplies a certificate
    // for the hostname we are expecting
    if (!SSL_set1_host(new->ssl, host)) {
        log_error("Failed to set certification verification hostname!");
        goto cleanup;
    }

    // can we get a handshake?
    if (SSL_connect(new->ssl) < 1) {
        log_error("Failed to connect to %s:%s!", host, port);

        // is it a verification error?
        if (SSL_get_verify_result(new->ssl) != X509_V_OK) {
            log_error(
                "  Reason: %s",
                X509_verify_cert_error_string(SSL_get_verify_result(new->ssl)));
        }
        goto cleanup;
    }

    // yipee!
    result = EXIT_SUCCESS;

cleanup:
    if (result == EXIT_FAILURE) {
        ERR_print_errors_fp(stderr);

        if (new->ssl) {
            SSL_free(new->ssl);
        }
        if (new->ctx) {
            SSL_CTX_free(new->ctx);
        }
        free(new);
        new = NULL;
    }

    return new;
}

void ssl_destroy_connection(struct ssl_connection *conn)
{
    assert(conn != NULL);

    if (SSL_shutdown(conn->ssl) < 1) {
        log_error("SSL_shutdown() returned <1!");
    }

    SSL_free(conn->ssl);
    SSL_CTX_free(conn->ctx);
    free(conn);
}
