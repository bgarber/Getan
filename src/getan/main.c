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

#include <ncurses.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

getan_error initialize(struct getan_files *f, struct getan_buflist *b)
{
	getan_error ret;

	if ( !(f = getan_files_new()) )
		ret = GETAN_GEN_FAIL;

	if ( !(b = getan_buflist_new()) )
		ret = GETAN_GEN_FAIL;

	return ret;
}

int main(int argc, char *argv[])
{
	struct getan_files   *files = NULL;
	struct getan_buflist *buflist = NULL;
	struct getan_buffer  *fbuf = NULL;
	int gf_index;

	// Process command line arguments.
	//   Common function to process this?
	//   struct getan_options opts;
	//   getan_options(&opts, argv, argc);

	if ( initialize(files, buflist) != GETAN_SUCCESS )
	{
		printf("Error starting Getan... :(\n");
		return -1;
	}

	fbuf = getan_files_open(files, "~/.vimrc");
	getan_buflist_add(buflist, fbuf);

	initscr();
	printw("Hello world!!!");
	refresh();
	getch();
	endwin();

	// getan_finish(buflist, files);
	getan_files_destroy(files);
	getan_buflist_destroy(buflist);

	return 0;
}
