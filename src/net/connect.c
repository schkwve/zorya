/**
 * @file net/connect.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 28/02/2024
 * @brief Network connection manager
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../log/logging.h"
#include "connect.h"

/**
 * @brief Creates a new connection entry and connects to a remote server.
 *
 * @param url
 *        Stripped URL string (only hostname/IP address
 *        should be present). Ex: www.website.com OR 127.0.0.1
 *
 * @param port
 *        Which port to connect to
 *
 * @return New connection structure if it was created successfully;
 *         NULL otherwise.
 */
struct net_connection *net_create_connection(char *url, uint16_t port)
{
  int status = 0;
  struct net_connection *new;

  new = malloc(sizeof(struct net_connection));
  if (new == NULL) {
    log_error("Failed to allocate memory for connection to %s:%d!", url, port);
    return NULL;
  }

  memset(new, 0, sizeof(struct net_connection));

  // set up some nice defaults
  // @note: SSL is disabled by default before it is implemented.
  strcpy(new->url, url);
  new->ssl = false;

  // convert hostname to IP address
  char portstr[5] = {0};
  sprintf(portstr, "%d", port);

  struct addrinfo hints = {0};
  struct addrinfo *server_info;

  // prefer TCP, get IPv4 and/or IPv6
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(url, portstr, &hints, &server_info);
  if (status != 0) {
    log_error("getaddrinfo() returned %d (errno = %s)!", status, strerror(errno));
    free(new);
    return NULL;
  }

  for (struct addrinfo *ptr = server_info; ptr != NULL; ptr = ptr->ai_next) {
    // only take IPv4 for now
    if (ptr->ai_family == AF_INET) {
      new->server.sin_addr = (struct in_addr)(((struct sockaddr_in *)ptr->ai_addr)->sin_addr);
      break;
    }
  }

  freeaddrinfo(server_info);

  // we're ready to rock n' roll
  new->socket = socket(PF_INET, SOCK_STREAM, 0);
  new->server.sin_family = AF_INET;
  new->server.sin_port = htons(port);

  if (new->socket == -1) {
    log_error("socket() returned %d (errno = %s)!", status, strerror(errno));
    free(new);
    return NULL;
}

  status = connect(new->socket, (struct sockaddr *)&new->server, sizeof(new->server));
  if (status != 0) {
    log_error("connect() returned %d (errno = %s)!", status, strerror(errno));
    free(new);
    return NULL;
  }

  log_debug("Connected to %s:%d", url, port);

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
  if (conn->socket) {
    close(conn->socket);
  }
  if (conn) {
    free(conn);
  }
}
