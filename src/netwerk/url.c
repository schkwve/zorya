/**
 * @file url.h
 * @brief Impelementation for the url parser
 * @author lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */

#include "url.h"

#include <string.h>
#include <stdlib.h>
#include <utils/logging.h>

Url parseUrl(const char *url) {
    char* urlCopy = malloc(strlen(url) + 1);
    strcpy(urlCopy, url);
    Url result = {
        .scheme = NULL,
        .authority = NULL,
        .host = NULL,
        .path = NULL,
        .fragment = NULL,
        .query = NULL,
        
    };
    char* schemeTok = strchr(urlCopy, ':');
    result.scheme = malloc (schemeTok - urlCopy + 1);
    memcpy(result.scheme, urlCopy, schemeTok - urlCopy);
    result.scheme[schemeTok - urlCopy] = '\0';

    if(*(schemeTok + 1) != '/' || *(schemeTok + 2) != '/') {
        free(urlCopy);
        free(result.scheme);
        log_error("Invalid URL(missing \"//\"): %s", url);
        return result;
    }

    char* atTok = strchr(schemeTok + 3, '@');
    char* moveOnTok = strchr(schemeTok + 3, '/');
    if(atTok < moveOnTok || atTok != NULL) {
        //Authority is present
        result.authority = malloc (atTok - schemeTok - 3 + 1);
        memcpy(result.authority, schemeTok + 3, atTok - schemeTok - 3);
        result.authority[atTok - schemeTok - 3] = '\0';

        // host is between the at and moveOn
        result.host = malloc (moveOnTok - atTok);
        memcpy(result.host, atTok + 1, moveOnTok - atTok - 1);
        result.host[moveOnTok - atTok - 1] = '\0';
    } else { 
        // no authority
        result.host = malloc (moveOnTok - schemeTok + 4);
        memcpy(result.host, schemeTok + 3,moveOnTok - schemeTok + 3);
        result.host[moveOnTok - schemeTok + 3] = '\0';
    }

    char* fragmentStart = strchr(moveOnTok, '#');
    char* queryStart = strchr(moveOnTok, '?');
    if (fragmentStart == NULL && queryStart == NULL) {
        result.path = malloc(strlen(moveOnTok+1) + 1);
        memcpy(result.path, moveOnTok+1, strlen(moveOnTok+1));
        result.path[strlen(moveOnTok+1)] = '\0';
    }else if (fragmentStart != NULL && queryStart == NULL) {
        result.path = malloc(fragmentStart - moveOnTok);
        memcpy(result.path, moveOnTok+1, fragmentStart - moveOnTok - 1);
        result.path[fragmentStart - moveOnTok - 1] = '\0';

        result.fragment = malloc(strlen(fragmentStart + 1) + 1);
        memcpy(result.fragment, fragmentStart + 1, strlen(fragmentStart + 1));
        result.fragment[strlen(fragmentStart + 1)] = '\0';
    }else if (queryStart != NULL && fragmentStart == NULL) {
        result.path = malloc(queryStart - moveOnTok );
        memcpy(result.path, moveOnTok, queryStart - moveOnTok -1);
        result.path[queryStart - moveOnTok - 1] = '\0';

        result.query = malloc(strlen(queryStart + 1) + 1);
        memcpy(result.query, queryStart + 1, strlen(queryStart + 1));
        result.query[strlen(queryStart + 1)] = '\0';
    }else {
        result.path = malloc(fragmentStart - moveOnTok);
        memcpy(result.path, moveOnTok + 1, fragmentStart - moveOnTok - 1);
        result.path[fragmentStart - moveOnTok - 1] = '\0';

        result.fragment = malloc(queryStart - fragmentStart);
        memcpy(result.fragment, fragmentStart + 1, queryStart - fragmentStart - 1);
        result.fragment[queryStart - fragmentStart - 1] = '\0';

        result.query = malloc(strlen(queryStart + 1) + 1);
        memcpy(result.query, queryStart + 1, strlen(queryStart + 1));
        result.query[strlen(queryStart + 1)] = '\0';
    }
    free(urlCopy);

    return result;
}

void freeUrl(Url *url) {
    free(url->scheme);
    free(url->authority);
    free(url->host);
    free(url->path);
    free(url->query);
    free(url->fragment);
}