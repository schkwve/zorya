#include "buffer.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void buffer_append_data(buffer_t *buf, void *ptr, size_t data_len) {
    if (buf->data_len == 0 || buf->data_ptr == NULL) {
        buf->data_ptr = malloc(data_len);
        buf->data_len = data_len;
    }
    if (buf->data_len < data_len+buf->buf_cursor) {
        buf->data_ptr = realloc(buf->data_ptr, data_len+buf->buf_cursor);
        buf->data_len = data_len+buf->buf_cursor;
    }
    memcpy(buf->data_ptr+buf->buf_cursor, ptr, data_len);
    buf->buf_cursor += data_len;
}