/**
 * @file url.h
 * @brief URL Parser
 * @author lolguy91 <retek1544@gmail.com>
 * @date 02/03/2024
 */

#ifndef NETWERK_URL_H
#define NETWERK_URL_H

struct url
{
    char *scheme;
    char *authority;
    char *host;
    char *path;
    char *fragment;
    char *query;
};

struct url parse_url(const char *url);

void free_url(struct url *url);

#endif /* NETWERK_URL_H */
