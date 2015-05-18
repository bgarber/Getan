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

#include <buffers.h>
#include <files.h>
#include <errors.h>

getan_error initialize(file_list f, buffer_list b)
{
	getan_error ret;

	if ( file_list_new(f) )
		ret = GETAN_GEN_FAIL;

	if ( buffer_list_new(b))
		ret = GETAN_GEN_FAIL;

	return ret;
}

int main(int argc, char *argv[])
{
	file_list files;
	buffer_list buffers;

	if ( initialize(files, buffers) != GETAN_SUCCESS )
	{
		printf("Error starting Getan... :(\n");
		return -1;
	}

	initscr();
	printw("Hello world!!!");
	refresh();
	getch();
	endwin();

	return 0;
}
