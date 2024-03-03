/**
 * @file utils/buffer.h
 * @author TendingStream73 <root@tendhost.ddns.net> <sasasabaev679@gmail.com>
 * @date 29/02/2024
 * @brief simple struct containing buffer(useful for data)
 */
#ifndef UTIL_BUFFER_H
#define UTIL_BUFFER_H

#include <stddef.h>

typedef struct buffer
{
    size_t dataLen;
    void* dataPtr;
    size_t buf_cursor;
} buffer_t;

void
buffer_append_data(buffer_t* buf, void* ptr, size_t dataLen);

void
buffer_destroy(buffer_t *buf);

#endif // UTIL_BUFFER_H
