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

#include <getan_buflist.h>
#include <getan_errors.h>

#include "file.h"
#include "display_buffer.h"

void command_mode(struct db_list *dblist, struct getan_buflist *buflist)
{
    getch();
}

int main(int argc, char *argv[])
{
    struct getan_buflist *buflist;
    struct db_list       *dblist;

    /*
     * First, start ncurses library, with the desired options.
     */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    /*
     * Second, start the list of Getan buffers.
     */
    buflist = getan_buflist_new();
    if ( !buflist ) {
        fprintf(stderr, "Error starting Getan.\n");
        goto exit;
    }

    /*
     * Third, start the display buffers. They are different from the Getan
     * buffers in the sense that these buffers controls screen rendering.
     */
    dblist = db_list_new();
    if ( !dblist ) {
        fprintf(stderr, "Could not allocate a new display buffer for the "
                "file.\n");
        goto exit;
    }

    /*
     * Fourth, process command line arguments.
     */
    if ( argc > 1 ) {
        struct getan_buffer *fbuf;
        struct display_buffer *db;
        struct buffer_data *data;
        char filename[255];

        strncpy(filename, argv[1], sizeof(filename));

        // Create the Getan file buffer.
        fbuf = getan_buffer_new();
        if ( !fbuf ) {
            fprintf(stderr, "Error creating Getan file buffer\n");
            goto exit;
        }

        // Open the requested file.
        if ( file_open(fbuf, filename) != GETAN_SUCCESS ) {
            fprintf(stderr, "Could not open file %s\n", filename);
            getan_buffer_destroy(fbuf);
            goto exit;
        }

        // Add the file buffer into the Getan buffer list.
        if ( getan_buflist_add(buflist, fbuf) != GETAN_SUCCESS ) {
            fprintf(stderr, "Error adding the buffer in the list...\n");
            getan_buffer_destroy(fbuf);
            goto exit;
        }

        // XXX: Since the file buffer is already added to the Getan buffer list,
        // getan_buflist_destroy takes responsibility of destroying it.

        // Create the data buffer.
        data = buffer_data_new();
        if ( !data ) {
            fprintf(stderr, "Error creating data buffer.\n");
            goto exit;
        }

        // Create the display buffer.
        db = display_buffer_new();
        if ( !db ) {
            fprintf(stderr, "Error allocating new display buffer.\n");
            goto exit;
        }

        if ( buffer_data_setup(data, fbuf) != GETAN_SUCCESS ) {
            fprintf(stderr, "Error setting up the data buffer.\n");
            goto exit;
        }

        db->data = data;

        if ( db_list_add(dblist, db) != GETAN_SUCCESS ) {
            fprintf(stderr, "Error adding buffer to display list.\n");
            goto exit;
        }
    }

    /*
     * Fifth, enter command mode.
     */
    command_mode(dblist, buflist);

exit:
    if ( buflist ) getan_buflist_destroy(buflist);
    if ( dblist ) db_list_destroy(dblist);

    endwin();
    return 0;
}

