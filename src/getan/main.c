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

#define MIN(x,y) (x <= y)? x : y

/*
 * This function will open a file and create the needed buffers.
 */
static getan_error create_buffers(struct getan_buflist *bl, struct db_list *dl,
        char *f)
{
    struct getan_buffer *fbuf;
    struct display_buffer *db;
    struct buffer_data *data;
    char filename[255];

    strncpy(filename, f, sizeof(filename));

    fbuf = getan_buffer_new();
    if ( !fbuf ) {
        fprintf(stderr, "Error creating Getan file buffer\n");
        return GETAN_GEN_FAIL;
    }

    if ( file_open(fbuf, filename) != GETAN_SUCCESS ) {
        fprintf(stderr, "Could not open file %s\n", filename);
        getan_buffer_destroy(fbuf);
        return GETAN_GEN_FAIL;
    }

    if ( getan_buflist_add(bl, fbuf) != GETAN_SUCCESS ) {
        fprintf(stderr, "Error adding the buffer in the list...\n");
        getan_buffer_destroy(fbuf);
        return GETAN_GEN_FAIL;
    }

    // XXX: Since the file buffer is already added to the Getan buffer list,
    // getan_buflist_destroy takes responsibility of destroying it.

    data = buffer_data_new();
    if ( !data ) {
        fprintf(stderr, "Error creating data buffer.\n");
        return GETAN_GEN_FAIL;
    }

    db = display_buffer_new();
    if ( !db ) {
        fprintf(stderr, "Error allocating new display buffer.\n");
        return GETAN_GEN_FAIL;
    }

    if ( buffer_data_setup(data, fbuf) != GETAN_SUCCESS ) {
        fprintf(stderr, "Error setting up the data buffer.\n");
        return GETAN_GEN_FAIL;
    }

    db->data = data;

    if ( db_list_add(dl, db) != GETAN_SUCCESS ) {
        fprintf(stderr, "Error adding buffer to display list.\n");
        return GETAN_GEN_FAIL;
    }

    return GETAN_SUCCESS;
}

static void command_mode(struct db_list *dblist, struct getan_buflist *buflist)
{
    struct display_buffer *cur_db;
    int chr, selected_db;
    uint32_t cursor_x, cursor_y, cur_line;

    selected_db = 0;
    cur_db = NULL;
    cursor_x = cursor_y = cur_line = 0;

    // There's already a buffer to display, get it.
    if ( dblist->db_len > 0 )
        cur_db = db_list_get(dblist, selected_db);

    while ( 1 ) {
        struct buffer_data *data;
        uint32_t line_len, data_len;
        int display_len;

        // Update the current display buffer in the screen.
        if ( cur_db ) display_buffer_show(cur_db);

        data = (cur_db)? cur_db->data : NULL;
        line_len = (data)? data->lines[cur_line].fl_len - 1 : 0;
        data_len = (data)? data->n_lines - 1 : 0;
        display_len = (data_len)? MIN(LINES - 1, data_len - 1) : 0;

        move(cursor_y, cursor_x);
        refresh();

        if ( (chr = getch()) == 'q' )
            break;

        // Manage cursor and keyboard shortcuts.
        switch ( chr ) {
            case 'h':
            case KEY_LEFT:
                if ( cursor_x > 0 ) cursor_x--;
                break;
            case 'l':
            case KEY_RIGHT:
                if ( cursor_x < line_len ) cursor_x++;
                break;
            case 'k':
            case KEY_UP:
                if ( cursor_y > 0 ) cursor_y--;

                if ( cur_db ) {
                    if ( cur_line > 0 ) cur_line--;
                    if ( cur_line < cur_db->top_line )
                        display_buffer_topline(cur_db, cur_line);
                }
                break;
            case 'j':
            case KEY_DOWN:
                if ( cursor_y < display_len ) cursor_y++;

                if ( cur_db ) {
                    if ( cur_line < data_len ) cur_line++;
                    if ( cur_line > cur_db->bot_line )
                        display_buffer_botline(cur_db, cur_line);
                }
                break;
            case 'i':
            case KEY_IC:
                /*
                 * GO TO INSERTION MODE!
                 */
                echo();
                // insertion_mode()
                break;
            case ':':
                /*
                 * Send cursor to command buffer!
                 */
                // TODO.
                break;
            default:
                break;
        }
    }
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
    if ( argc > 1 ) 
        if ( create_buffers(buflist, dblist, argv[1]) != GETAN_SUCCESS ) {
            fprintf(stderr, "Could not open the file in a buffer.\n");
            goto exit;
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

