/**
 * @file utils/buffer.h
 * @author TendingStream73 <sasasabaev679@gmail.com>
 * @date 29/02/2024
 * @brief A simple buffer
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"

/**
 * @brief Appends data to an existing buffer, or creates a new buffer.
 *
 * @param buf
 *        Pointer to a buffer where data will be appended
 *
 * @param ptr
 *        Pointer to data which should be appended
 *
 * @param data_len
 *        Size of data to be appended
 */
void buffer_append_data(buffer_t *buf, void *ptr, size_t data_len)
{
    if (buf->data_len == 0 || buf->data_ptr == NULL) {
        buf->data_ptr = malloc(data_len);
        buf->data_len = data_len;
    }
    if (buf->data_len < data_len + buf->buf_cursor) {
        buf->data_ptr = realloc(buf->data_ptr, data_len + buf->buf_cursor);
        buf->data_len = data_len + buf->buf_cursor;
    }
    memcpy(buf->data_ptr + buf->buf_cursor, ptr, data_len);
    buf->buf_cursor += data_len;
}

/**
 * @brief Destroys a buffer.
 *
 * @param buf
 *        Buffer to be destroyed
 */
void buffer_destroy(buffer_t *buf)
{
    if (buf->data_ptr && buf->data_len) {
        free(buf->data_ptr);
    }
    free(buf);
}