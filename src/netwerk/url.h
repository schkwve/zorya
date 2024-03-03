/**
 * @file url.h
 * @brief Url parser
 * @author lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */

#ifndef __NETWERK_URL_H__
#define __NETWERK_URL_H__

typedef struct {
    char *scheme;
    char *authority;
    char *host;
    char *path;
    char *fragment;
    char *query;
} Url;


Url parseUrl(const char *url);
void freeUrl(Url *url);

#endif // __NETWERK_URL_H__