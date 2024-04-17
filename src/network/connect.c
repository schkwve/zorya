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

#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <unistd.h>

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <net/connect.h>
#include <net/ssl.h>
#include <utils/buffer.h>
#include <utils/logging.h>

/**
 * @brief Sends a request to a server.
 *
 * @param connection
 *        Which server to send to
 *
 * @param buffer
 *        Data which will be sent to the server
 */
void net_send_data(struct net_connection *conn, buffer_t *buffer)
{
    assert(conn != NULL);
    assert(buffer != NULL);

    int bytes_sent = 0;
    int total_bytes_sent = 0;
    const int buffer_len = buffer->data_len;
    char *data_cast = (char *)buffer->data_ptr;

    // if not everything is sent in one go,
    // just try to send the rest once again
    while (total_bytes_sent < buffer_len) {
        if (conn->is_ssl) {
            bytes_sent = SSL_write(conn->ssl->ssl,
                                   &data_cast[total_bytes_sent],
                                   buffer_len - total_bytes_sent);
            if (bytes_sent < 1) {
                int ret = SSL_get_error(conn->ssl->ssl, bytes_sent);
                if (ret == SSL_ERROR_NONE) {
                    return;
                }
                log_error("SSL_write returned <1: %d!", ret);
                return;
            }
        } else {
            bytes_sent = send(conn->socket,
                              &data_cast[total_bytes_sent],
                              buffer_len - total_bytes_sent,
                              0);

            if (bytes_sent == -1) {
                log_error("Failed to send data to server!");
                return;
            }
        }
        total_bytes_sent += bytes_sent;
    }
}

/**
 * @brief Receives data from a server.
 *
 * @param connection
 *        Which server to receive from
 *
 * @param buffer [out]
 *        Received data buffer
 *
 * @return Length of received message
 */
size_t net_recv_data(struct net_connection *conn, buffer_t **buffer)
{
    assert(conn != NULL);
    assert(buffer != NULL);

    size_t bytes_received = -1;
    size_t total_bytes_received = 0;
    char received_data[NET_BUFFER_SIZE];

    while (bytes_received != 0) {
        if (conn->is_ssl) {
            bytes_received =
                SSL_read(conn->ssl->ssl, received_data, NET_BUFFER_SIZE);
            if (bytes_received < 1) {
                int res = SSL_get_error(conn->ssl->ssl, bytes_received);
                if (res == SSL_ERROR_NONE) {
                    return total_bytes_received;
                }
                log_error("SSL_read() returned <1: %d!", res);
                return -1;
            }
        } else {
            bytes_received =
                recv(conn->socket, received_data, NET_BUFFER_SIZE, 0);
            if (bytes_received == -1) {
                log_error("recv() returned -1: %s!", strerror(errno));
                return -1;
            } else if (bytes_received == 0) {
                return total_bytes_received;
            }
        }

        total_bytes_received += bytes_received;
        buffer_append_data(*buffer, received_data, bytes_received);
    }
    return total_bytes_received;
}

/**
 * @brief Creates a new connection entry and connects to a remote server.
 *
 * @param host
 *        Stripped URL string (only hostname/IP address
 *        should be present). Ex: www.website.com OR 127.0.0.1
 *
 * @param port
 *        Which port to connect to
 *
 * @return New connection structure if it was created successfully;
 *         NULL otherwise.
 */
struct net_connection *net_create_connection(const char *host,
                                             const char *port,
                                             bool is_ssl)
{
    int status = 0;
    struct net_connection *new;

    new = (struct net_connection *)malloc(sizeof(struct net_connection));
    if (new == NULL) {
        log_error(
            "Failed to allocate memory for connection to %s:%d!", host, port);
        return NULL;
    }

    memset(new, 0, sizeof(struct net_connection));

    // set up some nice defaults
    size_t hostlen = strlen(host);
    new->host = (char *)malloc(hostlen);
    if (new == NULL) {
        log_error("Failed to allocate memory for host string!", host, port);
        return NULL;
    }
    strncpy(new->host, host, hostlen);

    // convert hostname to IP address
    struct addrinfo hints = { 0 };
    struct addrinfo *server_info;

    // prefer TCP, get IPv4 and/or IPv6
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(host, port, &hints, &server_info);
    if (status != 0) {
        log_error("getaddrinfo() returned %d: %s!", status, strerror(errno));
        free(new);
        return NULL;
    }

    for (struct addrinfo *ptr = server_info; ptr != NULL; ptr = ptr->ai_next) {
        // only take IPv4 for now
        if (ptr->ai_family == AF_INET) {
            new->server.sin_addr = (struct in_addr)(
                ((struct sockaddr_in *)ptr->ai_addr)->sin_addr);
            break;
        }
    }

    freeaddrinfo(server_info);

    // we're ready to rock n' roll
    new->socket = socket(PF_INET, SOCK_STREAM, 0);
    new->server.sin_family = AF_INET;
    new->server.sin_port = htons(atoi(port));

    if (new->socket == -1) {
        log_error("socket() returned %d: %s!", status, strerror(errno));
        free(new->host);
        free(new);
        return NULL;
    }

    status = connect(
        new->socket, (struct sockaddr *)&new->server, sizeof(new->server));
    if (status != 0) {
        log_error("connect() returned %d: %s!", status, strerror(errno));
        free(new->host);
        free(new);
        return NULL;
    }

    new->is_ssl = is_ssl;
    if (is_ssl) {
        new->ssl = ssl_priv_create_connection(host, port, new->socket);
        if (new->ssl == NULL) {
            log_error("ssl_priv_create_connection() returned NULL!");
            free(new);
            return NULL;
        }
    }

    new->alive = true;
    log_info("Connected to %s:%s", host, port);

    return new;
}

/**
 * @brief Destroys a connection entry and frees all allocated memory.
 *
 * @param conn
 *        Connection to be destroyed
 */
void net_destroy_connection(struct net_connection *conn)
{
    assert(conn != NULL);

    conn->alive = false;

    if (conn->is_ssl) {
        ssl_destroy_connection(conn->ssl);
    }
    if (conn->socket) {
        close(conn->socket);
    }
    if (conn->host) {
        free(conn->host);
    }
    if (conn) {
        free(conn);
    }
    conn = NULL;
}
