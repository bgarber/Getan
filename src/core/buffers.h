/*
 * Copyright 2015 Bryan Garber
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

#include "buffers.h"

typedef void * buffer_list;

// Create a new buffer *list*. Should be called once.
int buffer_list_new(buffer_list b);
// Destroy the buffer *list*. Should be called once.
int buffer_list_destroy(buffer_list b);
// Create a new, empty buffer.
int buffer_list_create_buffer(buffer_list b);
// Create a buffer associated to a file.
int buffer_list_create_buffer_file(buffer_list b, const char *file);
// Destroy a buffer.
int buffer_list_destroy_buffer(buffer_list b, unsigned int index);

