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
void
buffer_append_data(buffer_t *buf, void *ptr, size_t data_len)
{
    if (buf->data_len == 0 || buf->dataPtr == NULL) {
        buf->dataPtr = malloc(data_len);
        buf->data_len = data_len;
    }
    if (buf->data_len < data_len + buf->buf_cursor) {
        buf->dataPtr = realloc(buf->dataPtr, data_len + buf->buf_cursor);
        buf->data_len = data_len + buf->buf_cursor;
    }
    memcpy(buf->dataPtr + buf->buf_cursor, ptr, data_len);
    buf->buf_cursor += data_len;
}

/**
 * @brief Destroys a buffer.
 *
 * @param buf
 *        Buffer to be destroyed
 */
void
buffer_destroy(buffer_t *buf)
{
    if (buf->dataPtr && buf->data_len) {
        free(buf->dataPtr);
    }
    free(buf);
}