#include "connect.h"
#include <stdlib.h>
#include <unistd.h>
#include "http.h"

/**
 @brief Converts http_request_t to char *, that can be sent to server
*/

char *http_gen_request(http_request_t *request) {
    if (!request) { // safety first.
        return (char *)"";
    }
    return (char *)"GET /NOT_IMPLEMENTED HTTP/1.0\r\n";
}