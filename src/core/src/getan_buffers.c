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

#include <stdlib.h>
#include <string.h>

#include <getan_buffers.h>
#include <getan_files.h>

/******************************************************************************
 * Structs declarations.                                                      *
 ******************************************************************************/

struct buffer {
	getan_buffer_type buftype; // buffer type
	int file_index;   // -1 when pointing to no file
	int file_cneedle; // index of the first char we are pointing in this buffer
	int file_cstack;  // index of the last char we are pointing in this buffer
};

struct __getan_buffers {
	unsigned int number_of_buffers;
	struct buffer **buf_list;
};

/******************************************************************************
 * Buffer handlers declarations                                               *
 ******************************************************************************/

static int buffer_new(struct buffer *b)
{
	b = malloc(sizeof(struct buffer));
	b->file_index = -1;
	b->file_cneedle = 0;
	b->file_cstack = 0;
	return 0;
}

static int __getan_buffers_check_free_index(struct __getan_buffers *b)
{
	struct buffer *tmp = NULL;
	int index;

	// Returns the first null pointer in the list.
	for ( index = 0; index < b->number_of_buffers; index++ ) {
		tmp = b->buf_list[index];
		if ( tmp->file_index == -1 )
			return index;
	}

	return -1;
}

static int __getan_buffers_resize(struct __getan_buffers *b)
{
	struct buffer **bkp_buf_list;
	size_t new_size;

	if ( b->number_of_buffers == 0 )
		b->number_of_buffers = 1;

	new_size = 2 * b->number_of_buffers;
	bkp_buf_list = b->buf_list;
	b->buf_list = realloc(b->buf_list, new_size);
	if ( !(b->buf_list) )
		return -1;

	b->number_of_buffers = new_size;

	/*
	 * Realloc may return a different pointer, to a newly allocated area.
	 * If this is the case, we need to free the original pointer.
	 */
	if ( b->buf_list != bkp_buf_list )
		free(bkp_buf_list);

	return 0;
}

int getan_buffers_new(getan_buffers b)
{
	struct __getan_buffers *new;

	new = malloc(sizeof(struct __getan_buffers));
	if ( !new ) return -1;

	new->number_of_buffers = 0;
	new->buf_list = NULL;

	b = (getan_buffers) new;

	return 0;
}

int getan_buffers_destroy(getan_buffers b)
{
	struct __getan_buffers *buffer;
	unsigned int index;

	if ( !b ) return -1;

	buffer = (struct __getan_buffers *)b;

	for ( index = 0; index < buffer->number_of_buffers; index++ ) {
		getan_buffers_destroy_buffer(b, index);
	}

	free(buffer);

	return 0;
}

int getan_buffers_create_buffer(getan_buffers b)
{
	struct __getan_buffers *blist = b;
	struct buffer *buf;
	int free_index;

	if ( buffer_new(buf) < 0 )
		return -1;

	free_index = __getan_buffers_check_free_index(blist);
	if ( free_index < 0 ) {
		// No free index... Get a new one!
		if ( __getan_buffers_resize(blist) > 0)
			blist->buf_list[blist->number_of_buffers++] = buf;
		else
			return -1;
	} else {
		// Free index found! Use it!
		blist->buf_list[free_index] = buf;
	}

	return 0;
}

int getan_buffers_create_buffer_file(getan_buffers b, const char *file)
{
	return 0;
}

int getan_buffers_destroy_buffer(getan_buffers b, unsigned int index)
{
	return 0;
}

