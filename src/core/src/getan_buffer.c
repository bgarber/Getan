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

struct __getan_buffer {
	unsigned int          gb_index; // buffer index
	getan_buffer_type     gb_type;  // buffer type
	struct __getan_buffer *gb_prev; // previous buffer
	struct __getan_buffer *gb_next; // next buffer
	void                  *gb_priv; // Buffer private data; depends on buffer type

	// Transfer the next fields to a specific struct implementing file I/O
	int file_index;   // -1 when pointing to no file

	// Next fields aren't needed; let the interface manage the text display
	int file_cneedle; // index of the first char we are pointing in this buffer
	int file_cstack;  // index of the last char we are pointing in this buffer
};

int getan_buffer_new(getan_buffer gb)
{
	struct __getan_buffer *b;

	b = malloc(sizeof(struct buffer));
	b->file_index = -1;
	b->file_cneedle = 0;
	b->file_cstack = 0;

	gb = (getan_buffer) b;
	return 0;
}


