/**
 * @file netwerk/connect.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 28/02/2024
 * @brief Network connection manager
 */

#ifndef NET_CONNECT_H
#define NET_CONNECT_H

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>

#include "../utils/buffer.h"

/**
 * @brief The max ammount of allowed connections
 */

#define MAX_CONNECTIONS 256

/**
 * @brief Default buffer size for network-related arrays.
 */
#define NET_BUFFER_SIZE 1024

/**
 * @brief This contains all information required to open, keep and close
 *        a connection.
 */
struct net_connection
{
    int id; 
    int socket;
    bool alive;
    bool ssl;
    char* host;
    struct sockaddr_in server;
};

void
net_send_data(struct net_connection* connection, buffer_t* buffer);
size_t
net_recv_data(struct net_connection* connection, buffer_t** buffer);

struct net_connection*
net_create_connection(char* url, uint16_t port);
void
net_destroy_connection(struct net_connection* conn);

#endif /* NET_CONNECT_H */
