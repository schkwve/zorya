/**
 * @file netwerk/connect.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 28/02/2024
 * @brief Network connection manager
 */

#ifndef NET_CONNECT_H
#define NET_CONNECT_H

#include <stdbool.h>
#include <stdint.h>
#include <netinet/in.h>

/**
 * @brief This contains all information required to open, keep and close
 *        a connection.
 */
struct net_connection {
    int socket;

    bool ssl;
    char *url;
    struct sockaddr_in server;
};

struct net_connection *net_create_connection(char *url, uint16_t port);
void net_destroy_connection(struct net_connection *conn);

#endif /* NET_CONNECT_H */
