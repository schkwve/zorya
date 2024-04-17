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

#ifndef UTILS_BUFFER_H
#define UTILS_BUFFER_H

#include <stddef.h>

typedef struct buffer
{
    void *data_ptr;
    size_t data_len;
    size_t buf_cursor;
} buffer_t;

void buffer_append_data(buffer_t *buf, void *ptr, size_t data_len);
void buffer_destroy(buffer_t *buf);

#endif /* UTILS_BUFFER_H */
