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

struct getan_buflist {
	unsigned int length;
	struct getan_buffer **buf_list;
};

static int __getan_buflist_get_unused_buffer(struct getan_buflist *list)
{
	struct getan_buffer *b = NULL;
	int index;

	// Returns the first empty buffer in the list.
	for ( index = 0; index < list->length; index++ ) {
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

	if ( list->length == 0 )
		list->length = 1;

	new_size = 2 * list->length;
	bkp_buf_list = list->buf_list;
	list->buf_list = realloc(list->buf_list, new_size * getan_buffer_size_of());
	if ( !(list->buf_list) )
		return -1;

	list->length = new_size;

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
		list->length = 0;
		list->buf_list = NULL;
	}

	return list;
}

int getan_buflist_destroy(struct getan_buflist *list)
{
	struct getan_buffer *buf;
	unsigned int index;

	if ( !list ) return -1;

	for ( index = 0; index < list->length; index++ ) {
		buf = list->buf_list[index];
		getan_buffer_destroy(buf);
	}

	free(list);

	return 0;
}

getan_error getan_buflist_add(struct getan_buflist *list, struct getan_buffer *gb)
{
	int free_index;

	if ( !list ) return GETAN_NO_LIST;

	free_index = __getan_buflist_get_unused_buffer(list);
	if ( free_index < 0 ) {
		// No free index... Get a new one!
		if ( __getan_buflist_resize(list) < 0)
			return GETAN_GEN_FAIL;

		list->buf_list[list->length++] = gb;
	} else {
		// Free index found! Use it!
		list->buf_list[free_index] = gb;
	}

	return GETAN_SUCCESS;
}

struct getan_buffer *getan_buflist_get_buffer(struct getan_buflist *list,
		unsigned int index)
{
	struct getan_buffer *buffer = NULL;

	if ( index < list->length ) buffer = list->buf_list[index];

	return buffer;
}

