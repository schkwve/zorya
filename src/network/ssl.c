/**
 * Copyright (c) 2024 Zorya Browser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

struct ssl_connection *ssl_priv_create_connection(const char *host,
                                                  const char *port,
                                                  int socket)
{
    int result = EXIT_FAILURE;

    struct ssl_connection *new =
        (struct ssl_connection *)malloc(sizeof(struct ssl_connection));
    if (new == NULL) {
        log_error("Failed to allocate memory for a new SSL connection!");
        return NULL;
    }

    memset(new, 0, sizeof(struct ssl_connection));

    new->ctx = SSL_CTX_new(TLS_method());
    if (new->ctx == NULL) {
        log_error("Failed to create SSL context!");
        goto cleanup;
    }

    // create an SSL object to represent the connection
    new->ssl = SSL_new(new->ctx);
    if (new->ssl == NULL) {
        log_error("Failed to create SSL object!");
        goto cleanup;
    }

    // associate stuff with other stuff :p
    SSL_set_fd(new->ssl, socket);

    // can we get a handshake?
    if (SSL_connect(new->ssl) < 1) {
        log_error("Failed to connect to %s:%s!", host, port);
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
        if (new) {
            free(new);
        }
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
}
