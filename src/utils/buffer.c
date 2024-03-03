#include "buffer.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
buffer_append_data(buffer_t* buf, void* ptr, size_t dataLen)
{
    if (buf->dataLen == 0 || buf->dataPtr == NULL) {
        buf->dataPtr = malloc(dataLen);
        buf->dataLen = dataLen;
    }
    if (buf->dataLen < dataLen + buf->buf_cursor) {
        buf->dataPtr = realloc(buf->dataPtr, dataLen + buf->buf_cursor);
        buf->dataLen = dataLen + buf->buf_cursor;
    }
    memcpy(buf->dataPtr + buf->buf_cursor, ptr, dataLen);
    buf->buf_cursor += dataLen;
}

void
buffer_destroy(buffer_t *buf) {
    if (buf->dataPtr && buf->dataLen) {
        free(buf->dataPtr);
    }
    free(buf);
}