#include "../utils/buffer.h"
#include <stddef.h>
#include <stdint.h>

enum HTTP_VERSION
{
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1
};

typedef struct HTTPHeader
{
    const char* name;
    const char* data;
} http_header_t;

typedef struct HTTPRequest
{
    const char* method;
    const char* path;
    enum HTTP_VERSION ver;
    size_t header_len;
    http_header_t* headers;
    size_t data_len;
    uint8_t* data;
} http_request_t;

buffer_t*
http_gen_request(http_request_t* request);