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

#ifndef GETAN_BUFFERS_H
#define GETAN_BUFFERS_H

typedef void * getan_buffers;

typedef enum {
	GETAN_BUFFER_IOFILE,
	GETAN_BUFFER_SHELL,
	GETAN_BUFFER_DIRLIST,
} getan_buffer_type;

// Create a new buffer *list*. Should be called once.
int getan_buffers_new(getan_buffers b);

// Destroy the buffer *list*. Should be called once.
int getan_buffers_destroy(getan_buffers b);

// Create a new, empty buffer.
int getan_buffers_create_buffer(getan_buffers b);

// Create a buffer associated to a file.
int getan_buffers_create_buffer_file(getan_buffers b, const char *file);

// Destroy a buffer.
int getan_buffers_destroy_buffer(getan_buffers b, unsigned int index);

#endif

