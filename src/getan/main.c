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
#include <ncurses.h>

#include <sys/mman.h>
#include <unistd.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

int main(int argc, char *argv[])
{
	struct getan_buflist *buflist = NULL;
	struct getan_buffer  *fbuf = NULL;
	char *file_chars;
	int fd, int_sz, file_sz;

	// Process command line arguments.
	//   Common function to process this?
	//   struct getan_options opts;
	//   getan_options(&opts, argv, argc);

	// Allocate a new list of buffers.
	buflist = getan_buflist_new();
	if ( !buflist )
	{
		printf("Error starting Getan... :(\n");
		return -1;
	}

	// Create a new buffer for the file.
	fbuf = getan_buffer_new();
	if ( !fbuf )
	{
		printf("Could not create a new buffer!\n");
		return -1;
	}

	// Make that buffer allocated above a file buffer.
	if ( getan_filebuf_create(fbuf) != GETAN_SUCCESS )
	{
		printf("Could not make the new buffer a file buffer.\n");
		return -1;
	}

	// Open a file in the file buffer
	if ( getan_buffer_cb_call(fbuf, FILEBUF_OPEN, "/home/bgarber/.vimrc", 8) != GETAN_SUCCESS )
	{
		perror("Could not open the file");
		return -1;
	}

	// Add the opened file in the buffer list.
	getan_buflist_add(buflist, fbuf);

	int_sz = sizeof(int);
	getan_buffer_cb_get(fbuf, FILEBUF_FD, &fd, &int_sz);
	getan_buffer_cb_get(fbuf, FILEBUF_FILESZ, &file_sz, &int_sz);

	file_chars = mmap(NULL, file_sz, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	initscr();
	//printw("Hello world!!!");
	printw("%s", file_chars, file_sz);
	refresh();
	getch();
	endwin();

	munmap(file_chars, file_sz);
	getan_buflist_destroy(buflist);

	return 0;
}
