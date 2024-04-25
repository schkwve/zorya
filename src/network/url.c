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

#include <stdlib.h>
#include <string.h>

#include <net/url.h>
#include <utils/logging.h>

/**
 * @brief Parses a URL string.
 *
 * @param url
 *        URL string to be parsed
 *
 * @return Parsed URL structure
 */
struct url parse_url(const char *url)
{
    //TODO: make this func more versatile and more readable
    char *urlCopy = malloc(strlen(url) + 1);
    strcpy(urlCopy, url);
    struct url res = {
        .scheme = NULL,
        .authority = NULL,
        .host = NULL,
        .path = NULL,
        .fragment = NULL,
        .query = NULL,

    };
    char *schemeTok = strchr(urlCopy, ':');
    res.scheme = malloc(schemeTok - urlCopy + 1);
    memcpy(res.scheme, urlCopy, schemeTok - urlCopy);
    res.scheme[schemeTok - urlCopy] = '\0';

    if (*(schemeTok + 1) != '/' || *(schemeTok + 2) != '/') {
        log_error("Invalid URL(missing \"//\"): %s", url);
        free(res.scheme);
        free(urlCopy);
        return res;
    }

    char *atTok = strchr(schemeTok + 3, '@');
    char *moveOnTok = strchr(schemeTok + 3, '/');
    if (atTok < moveOnTok && atTok != NULL) {
        // Authority is present
        res.authority = malloc(atTok - schemeTok - 3 + 1);
        memcpy(res.authority, schemeTok + 3, atTok - schemeTok - 3);
        res.authority[atTok - schemeTok - 3] = '\0';

        // host is between AtTok and moveOn
        res.host = malloc(moveOnTok - atTok);
        memcpy(res.host, atTok + 1, moveOnTok - atTok - 1);
        res.host[moveOnTok - atTok - 1] = '\0';
    } else {
        if (moveOnTok == NULL) {
            res.path = NULL;

            res.host = malloc(strlen(schemeTok + 3) + 1);
            memcpy(res.host, schemeTok + 3, strlen(schemeTok + 3));
            res.host[strlen(schemeTok + 3)] = '\0';

            goto cleanup;
        }
        // no authority, host is between schemeTok and moveOn
        res.host = malloc(moveOnTok - schemeTok - 2);
        memcpy(res.host, schemeTok + 3, moveOnTok - schemeTok - 3);
        res.host[moveOnTok - schemeTok - 3] = '\0';
    }

    char *fragmentStart = strchr(moveOnTok, '#');
    char *queryStart = strchr(moveOnTok, '?');
    if (fragmentStart == NULL && queryStart == NULL) {
        // no query or fragment, path is everything after moveOn
        res.path = malloc(strlen(moveOnTok) + 1);
        memcpy(res.path, moveOnTok, strlen(moveOnTok));
        res.path[strlen(moveOnTok)] = '\0';
    } else if (fragmentStart != NULL && queryStart == NULL) {
        // path is between moveOn and fragment
        res.path = malloc(fragmentStart - moveOnTok + 1);
        memcpy(res.path, moveOnTok, fragmentStart - moveOnTok);
        res.path[fragmentStart - moveOnTok] = '\0';

        // fragment is everything after fragmentStart
        res.fragment = malloc(strlen(fragmentStart + 1) + 1);
        memcpy(res.fragment, fragmentStart + 1, strlen(fragmentStart + 1));
        res.fragment[strlen(fragmentStart + 1)] = '\0';
    } else if (queryStart != NULL && fragmentStart == NULL) {
        // path is between moveOn and queryStart
        res.path = malloc(queryStart - moveOnTok);
        memcpy(res.path, moveOnTok, queryStart - moveOnTok - 1);
        res.path[queryStart - moveOnTok - 1] = '\0';

        // query is everything after queryStart
        res.query = malloc(strlen(queryStart + 1) + 1);
        memcpy(res.query, queryStart + 1, strlen(queryStart + 1));
        res.query[strlen(queryStart + 1)] = '\0';
    } else {
        // path is between moveOn and fragment
        res.path = malloc(fragmentStart - moveOnTok + 1);
        memcpy(res.path, moveOnTok, fragmentStart - moveOnTok);
        res.path[fragmentStart - moveOnTok] = '\0';

        // fragment is between fragmentStart and queryStart
        res.fragment = malloc(queryStart - fragmentStart);
        memcpy(res.fragment, fragmentStart + 1, queryStart - fragmentStart - 1);
        res.fragment[queryStart - fragmentStart - 1] = '\0';

        // query is everything after queryStart
        res.query = malloc(strlen(queryStart + 1) + 1);
        memcpy(res.query, queryStart + 1, strlen(queryStart + 1));
        res.query[strlen(queryStart + 1)] = '\0';
    }

cleanup:
    free(urlCopy);
    return res;
}

/**
 * @brief Frees a URL structure.
 *
 * @param url
 *        URL structure to be free'd
 */
void free_url(struct url *url)
{
    free(url->scheme);
    if (url->authority != NULL)
        free(url->authority);
    free(url->host);
    if (url->path != NULL)
        free(url->path);
    if (url->query != NULL)
        free(url->query);
    if (url->fragment != NULL)
        free(url->fragment);
    url = NULL;
}
