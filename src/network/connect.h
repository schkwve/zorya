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

#ifndef NET_CONNECT_H
#define NET_CONNECT_H

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>

#include <utils/buffer.h>

/**
 * @brief The max ammount of allowed connections
 */

#define MAX_CONNECTIONS 256

/**
 * @brief Default buffer size for network-related arrays.
 */
#define NET_BUFFER_SIZE 1024

/**
 * @brief Connection type(secure, insecure, etc...)
 */
enum CONNECTION_TYPE
{
    NET_INSECURE,
    NET_SECURE
};

/**
 * @brief SSL connection structure
 */
struct ssl_connection
{
    int sock;
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    bool is_initialized;
};

/**
 * @brief This contains all information required to open, keep and close
 *        a connection.
 */
struct net_connection
{
    int id;
    int socket;

    char *host;
    char *port;

    struct sockaddr_in server;
    struct ssl_connection *ssl;

    bool alive;
    bool is_ssl;
};

void net_send_data(struct net_connection *connection, buffer_t *buffer);
size_t net_recv_data(struct net_connection *connection, buffer_t **buffer);

struct net_connection *net_create_connection(const char *host,
                                             const char *port,
                                             bool is_ssl);
void net_destroy_connection(struct net_connection *conn);

#endif /* NET_CONNECT_H */
