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

#include <getan_buffer.h>
#include <getan_buflist.h>
#include <getan_files.h>

struct getan_buflist {
	unsigned int number_of_buffers;
	struct getan_buffer **buf_list;
};

static int __getan_buflist_get_unused_buffer(struct getan_buflist *list)
{
	struct getan_buffer *b = NULL;
	int index;

	// Returns the first empty buffer in the list.
	for ( index = 0; index < list->number_of_buffers; index++ ) {
		b = list->buf_list[index];
		if ( !getan_buffer_is_used(b) )
			return index;
	}

	return -1;
}

static int __getan_buflist_resize(struct getan_buflist *list)
{
	struct getan_buffer **bkp_buf_list;
	size_t new_size;

	if ( list->number_of_buffers == 0 )
		list->number_of_buffers = 1;

	new_size = 2 * list->number_of_buffers;
	bkp_buf_list = list->buf_list;
	list->buf_list = realloc(list->buf_list, new_size);
	if ( !(list->buf_list) )
		return -1;

	list->number_of_buffers = new_size;

	/*
	 * Realloc may return a different pointer, to a newly allocated area.
	 * If this is the case, we need to free the original pointer.
	 */
	if ( list->buf_list != bkp_buf_list )
		free(bkp_buf_list);

	return 0;
}

struct getan_buflist * getan_buflist_new()
{
	struct getan_buflist *list = NULL;

	list = malloc(sizeof(struct getan_buflist));
	if ( list ) {
		list->number_of_buffers = 0;
		list->buf_list = NULL;
	}

	return list;
}

int getan_buflist_destroy(struct getan_buflist *list)
{
	struct getan_buffer *buf;
	unsigned int index;

	if ( !list ) return -1;

	for ( index = 0; index < list->number_of_buffers; index++ ) {
		buf = list->buf_list[index];
		getan_buffer_destroy(buf);
	}

	free(list);

	return 0;
}

int getan_buflist_add(struct getan_buflist *list, struct getan_buffer *gb)
{
	int free_index;

	if ( !list ) return -1;

	free_index = __getan_buflist_get_unused_buffer(list);
	if ( free_index < 0 ) {
		// No free index... Get a new one!
		if ( __getan_buflist_resize(list) > 0)
			list->buf_list[list->number_of_buffers++] = gb;
		else
			return -1;
	} else {
		// Free index found! Use it!
		list->buf_list[free_index] = gb;
	}

	return 0;
}

