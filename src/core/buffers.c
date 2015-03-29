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
#include "files.h"


struct buffer {
	int file_index;   // -1 when pointing to no file
	int file_cneedle; // index of the first char we are pointing in this buffer
	int file_cstack;  // index of the last char we are pointing in this buffer
};

struct __buffer_list {
	unsigned int number_of_buffers;
	struct buffer *buf_list;
};

static int buffer_new(struct buffer *b)
{
	b = malloc(sizeof(struct buffer));
	b->file_index = -1;
	b->file_cneedle = 0;
	b->file_cstack = 0;
	return 0;
}

static int __buffer_list_check_free_index(struct __buffer_list *b)
{
	int index;

	// Returns the first null pointer in the list.
	for ( index = 0; index < b->number_of_buffers; index++ )
		if ( !b->buf_list[index] )
			return index;

	return -1;
}

static int __buffer_list_resize(struct __buffer_list *b)
{
	struct buffer *bkp_buf_list;
	size_t new_size;

	if ( b->number_of_buffers == 0 )
		b->number_of_buffers = 1;

	new_size = 2 * b->number_of_buffers;
	bkp_buf_list = b->buf_list;
	b->buf_list = realloc(b->buf_list, new_size);
	if ( !new_buffer_list )
		return -1;

	b->number_of_buffers = new_size;

	/*
	 * Realloc may return a different pointer, to a newly allocated area.
	 * If this is the case, we need to free the original pointer.
	 */
	if ( b->buf_list != bkp_buffer_list )
		free(bkp_buffer_list);

	b->buf_list = new_buffer_list;
	return 0;
}

int buffer_list_new(buffer_list *b)
{
	struct __buffer_list *new;

	new = malloc(sizeof(struct __buffer_list));
	if ( !new ) return -1;

	new->number_of_buffers = 0;
	new->buf_list = NULL;

	b = (buffer_list) new;

	return 0;
}

int buffer_list_destroy(buffer_list b)
{
	struct __buffer_list *buffer;
	unsigned int index;

	if ( !b ) return -1;

	buffer = (struct __buffer_list *)b;

	for ( index = 0; index < buffer->number_of_buffers; index++ ) {
		buffer_list_destroy_buffer(b, index);
	}

	free(buffer);

	return 0;
}

int buffer_list_create_buffer(buffer_list b)
{
	struct __buffer_list *buf_list = b;
	struct buffer *buf;
	int free_index;

	if ( buffer_new(buf) < 0 )
		return -1;

	free_index = __buffer_list_check_free_index(buf_list);
	if ( free_index < 0 ) {
		// No free index... Get a new one!
		if ( __buffer_list_resize(buf_list) > 0)
			buf_list->buf_list[buf_list->number_of_buffers++] = buf;
		else
			return -1;
	} else {
		// Free index found! Use it!
		buf_list->buf_list[free_index] = buf;
	}

	return 0;
}

int buffer_list_create_buffer_file(buffer_list b, const char *file)
{
	return 0;
}

int buffer_list_destroy_buffer(buffer_list b, unsigned int index)
{
	return 0;
}

