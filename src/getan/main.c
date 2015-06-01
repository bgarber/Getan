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

#include <getan_buffers.h>
#include <getan_files.h>
#include <getan_errors.h>

getan_error initialize(getan_files f, getan_buffers b)
{
	getan_error ret;

	if ( getan_files_new(f) )
		ret = GETAN_GEN_FAIL;

	if ( getan_buffers_new(b))
		ret = GETAN_GEN_FAIL;

	return ret;
}

int main(int argc, char *argv[])
{
	getan_files   files;
	getan_buffers buffers;

	// Process command line arguments.
	//   Common function to process this?
	//   struct getan_options opts;
	//   getan_options(&opts, argv, argc);

	// getan_initialize(files, buffers);

	if ( initialize(files, buffers) != GETAN_SUCCESS )
	{
		printf("Error starting Getan... :(\n");
		return -1;
	}

	// getan_open_file(buffers, files, filename);

	initscr();
	printw("Hello world!!!");
	refresh();
	getch();
	endwin();

	// getan_finish(buffers, files);
	getan_files_destroy(files);
	getan_buffers_destroy(buffers);

	return 0;
}
