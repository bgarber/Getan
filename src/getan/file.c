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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <unistd.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

struct getan_buffer *file_open(struct getan_buflist *buflist,
		char *filename)
{
	struct getan_buffer *fbuf = NULL;

	if ( !buflist ) return NULL;

	// Create a new buffer for the file.
	fbuf = getan_buffer_new();
	if ( !fbuf ) return NULL;

	// Make that buffer allocated above a file buffer.
	if ( getan_filebuf_create(fbuf) != GETAN_SUCCESS )
	{
		printf("Could not make the new buffer a file buffer.\n");
		getan_buffer_destroy(fbuf);
		return NULL;
	}

	// Add the file buffer in the buffer list.
	if ( getan_buflist_add(buflist, fbuf) != GETAN_SUCCESS )
	{
		printf("Error adding the buffer in the list...\n");
		getan_buffer_destroy(fbuf);
		return NULL;
	}

	// Open a file in the file buffer
	if ( getan_buffer_cb_call(fbuf, FILEBUF_OPEN, filename,
			strnlen(filename, MAX_FILENAME_LENGTH)) != GETAN_SUCCESS )
	{
		perror("Could not open the file");
		getan_buffer_destroy(fbuf);
		return NULL;
	}

	return fbuf;
}

char *file_read(struct getan_buffer *fbuf, unsigned int *file_sz)
{
	int fd, int_sz;

	if ( !fbuf ) return NULL;

	int_sz = sizeof(int);
	getan_buffer_cb_get(fbuf, FILEBUF_FD, &fd, &int_sz);
	getan_buffer_cb_get(fbuf, FILEBUF_FILESZ, file_sz, &int_sz);

	return (char *)mmap(NULL, (*file_sz), PROT_READ | PROT_WRITE,
			MAP_PRIVATE, fd, 0);
}

int file_unread(char *file_cs, unsigned int file_sz)
{
	return munmap(file_cs, file_sz);
}

