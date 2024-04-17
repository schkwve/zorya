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

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <utils/buffer.h>

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
    assert(buf != NULL);

    if (buf->data_ptr && buf->data_len) {
        free(buf->data_ptr);
    }
    free(buf);
}
