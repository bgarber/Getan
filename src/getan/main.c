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
#include <ncurses.h>

#include <sys/mman.h>
#include <unistd.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

#include "file.h"

/**
 * \struct display_buffer
 *
 * This is a buffer displayed on the screen.
 */
struct display_buffer {
	struct getan_buffer *buffer;
	char *buffer_chars;
	unsigned int buffer_sz;
};

static struct getan_buffer *select_buffer(struct getan_buflist *buflist,
		unsigned int bufnumber)
{
	return getan_buflist_get_buffer(buflist, bufnumber);
}

static getan_error unselect_buffer(struct display_buffer *db)
{
	db->buffer = NULL;
	file_unread(db->buffer_chars, db->buffer_sz);
	db->buffer_sz = 0;
	return GETAN_SUCCESS;
}

int main(int argc, char *argv[])
{
	struct display_buffer db[5];
	struct getan_buflist *buflist = NULL;
	struct getan_buffer  *fbuf = NULL;
	int chr;
	//struct getan_options *opts = NULL;

	// ncurses init
	initscr();
	raw();
	keypad(stdscr, TRUE);

	//opts = getan_options(argv, argc);

	// Allocate a new list of buffers.
	buflist = getan_buflist_new();
	if ( !buflist )
	{
		printf("Error starting Getan... :(\n");
		goto free_out;
	}

	if ( !(fbuf = file_open(buflist, "/home/bgarber/.vimrc")) )
	{
		printf("Could not open the file...\n");
		goto free_out;
	}

	memset(db, 0, sizeof(db));

	db[0].buffer = fbuf;
	db[0].buffer_chars = file_read(db[0].buffer, &db[0].buffer_sz);

	printw("%s", db[0].buffer_chars);
	move(0,0);
	refresh();

	// main loop
	while ( (chr = getch()) != 'q' )
	{
		refresh();
	}

free_out:
	unselect_buffer(&db[0]);
	getan_buflist_destroy(buflist);
	endwin();
	return 0;
}
