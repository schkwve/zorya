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

/**
 * @brief Sends a request to a server via SSL.
 *
 * @param connection
 *        Which server to send to
 *
 * @param buffer
 *        Data which will be sent to the server
 */
void ssl_priv_send_data(struct ssl_connection *conn, buffer_t *buffer)
{
    assert(conn != NULL);
    assert(buffer != NULL);

    size_t bytes_sent = 0;
    size_t total_bytes_sent = 0;
    const int buffer_len = buffer->data_len;
    char *data_cast = (char *)buffer->data_ptr;

    // if not everything is sent in one go,
    // just try to send the rest once again
    while (total_bytes_sent < buffer_len) {
        if (!SSL_write_ex(conn->ssl,
                          &data_cast[total_bytes_sent],
                          buffer_len - total_bytes_sent,
                          &bytes_sent)) {
            log_error("Failed to send data to %s!", data_cast);
            return;
        }
        total_bytes_sent += bytes_sent;
    }
}

/**
 * @brief Receives data from a server via SSL.
 *
 * @param connection
 *        Which server to receive from
 *
 * @param buffer [out]
 *        Received data buffer
 *
 * @return Length of received message;
 *         -1 if an error happened.
 */
size_t ssl_priv_recv_data(struct ssl_connection *conn, buffer_t **buffer)
{
    assert(conn != NULL);
    assert(buffer != NULL);

    size_t bytes_received = -1;
    size_t total_bytes_received = 0;
    char received_data[NET_BUFFER_SIZE];

    while (SSL_read_ex(conn->ssl, received_data, NET_BUFFER_SIZE, &bytes_received)) {
        total_bytes_received += bytes_received;
        buffer_append_data(*buffer, received_data, bytes_received);
    }

    if (SSL_get_error(conn->ssl, 0) != SSL_ERROR_ZERO_RETURN) {
        log_error("SSL_read_ex() error!");
        return -1;
    }

    return total_bytes_received;
}

int ssl_priv_create_connection(const char *host, const char *port, struct ssl_connection *new)
{
    int result = EXIT_FAILURE;

    memset(new, 0, sizeof(struct ssl_connection));

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

    // find the server
    BIO_ADDRINFO *res;
    const BIO_ADDRINFO *ai = NULL;

    if (!BIO_lookup_ex(
            host, port, BIO_LOOKUP_CLIENT, AF_INET, SOCK_STREAM, 0, &res)) {
        log_error("Failed to lookup hostname %s!", host);
        goto cleanup;
    }

    // loop through all possible addresses
    int sock = -1;
    for (ai = res; ai != NULL; ai = BIO_ADDRINFO_next(ai)) {
        sock = BIO_socket(BIO_ADDRINFO_family(ai), SOCK_STREAM, 0, 0);
        if (sock == -1) {
            continue;
        }

        // try connecting
        if (!BIO_connect(
                sock, BIO_ADDRINFO_address(ai), BIO_SOCK_NODELAY)) {
            BIO_closesocket(sock);
            sock = -1;
            continue;
        }

        // we got successfully connected! yay!
        break;
    }

    BIO_ADDRINFO_free(res);

    if (sock == -1) {
        log_error("Failed to connect to %s:%s!", host, port);
        goto cleanup;
    }

    new->bio = BIO_new(BIO_s_socket());
    if (new->bio == NULL) {
        log_error("BIO_new() returned NULL!");
        goto cleanup;
    }

    // associate stuff with other stuff :p
    BIO_set_fd(new->bio, new->sock, BIO_CLOSE);
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
    }

    return result;
}

void ssl_destroy_connection(struct ssl_connection *conn)
{
    assert(conn != NULL);

    if (SSL_shutdown(conn->ssl) < 1) {
        log_error("SSL_shutdown() returned <1!");
    }

    SSL_free(conn->ssl);
    SSL_CTX_free(conn->ctx);
}
