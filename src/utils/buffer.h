/**
 * @file utils/buffer.h
 * @author TendingStream73 <root@tendhost.ddns.net> <sasasabaev679@gmail.com>
 * @date 29/02/2024
 * @brief simple struct containing buffer(useful for data)
*/
#ifndef UTIL_BUFFER_H
#define UTIL_BUFFER_H

#include <stddef.h>

typedef struct buffer {
    size_t data_len;
    void *data_ptr;
} buffer_t;

#endif // UTIL_BUFFER_H