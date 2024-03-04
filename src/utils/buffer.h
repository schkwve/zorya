/**
 * @file utils/buffer.h
 * @author TendingStream73 <sasasabaev679@gmail.com>
 * @date 29/02/2024
 * @brief A simple buffer
 */

#ifndef UTIL_BUFFER_H
#define UTIL_BUFFER_H

#include <stddef.h>

typedef struct buffer
{
    void *dataPtr;
    size_t data_len;
    size_t buf_cursor;
} buffer_t;

void buffer_append_data(buffer_t *buf, void *ptr, size_t dataLen);

void buffer_destroy(buffer_t *buf);

#endif // UTIL_BUFFER_H
