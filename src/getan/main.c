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
#include <stdarg.h>
#include <ncurses.h>

#include <sys/mman.h>
#include <unistd.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

#include "file.h"

//#define ENABLE_DEBUG 1

/*
 * Global declarations... (?)
 * Only for debug!
 */
static WINDOW   *debug;
static uint32_t cur_dbg_line;

/**
 * \struct display_buffer
 *
 * This is a buffer displayed on the screen.
 */
struct display_buffer {
    struct getan_buffer *buffer; // pointer to the buffer
    char     *buffer_chars;      // characters in the buffer
    uint32_t buffer_sz;          // size of the buffer
    uint32_t cursor_y;           // save last cursor y
    uint32_t cursor_x;           // save last cursor x
    WINDOW   *win;               // window pointer for this buffer
};

static WINDOW *create_window(int height, int width, int y, int x)
{
    WINDOW *win;

    win = newwin(height, width, y, x);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

static void log_debug(const char *fmt, ...)
{
    const char *p;
    va_list argp;

#ifdef ENABLE_DEBUG
    va_start(argp, fmt);

    if ( cur_dbg_line >= LINES ) {
        wclear(debug);
        wrefresh(debug);

        cur_dbg_line = 0;
    }

    vwprintw(debug, fmt, argp);
    wrefresh(debug);

    cur_dbg_line += 1;

    va_end(argp);
#endif
}

static void command_mode(struct display_buffer *db)
{
    int chr, cur_col = 0, cur_row = 0,
        win_lines = LINES, win_cols;

#ifdef ENABLE_DEBUG
    win_cols = COLS/2;
#else
    win_cols = COLS;
#endif

    db[0].win = create_window(win_lines, win_cols, 0, 0);
    waddstr(db[0].win, db[0].buffer_chars);
    wmove(db[0].win, cur_row, cur_col);
    wrefresh(db[0].win);

    while ( 1 ) {
        chr = getch();

        if ( chr == 'q' ) break;

        switch ( chr ) {
            case 'l':
            case KEY_LEFT:
                if ( cur_col > 0 ) --cur_col;
                break;
            case 'h':
            case KEY_RIGHT:
                if ( cur_col < (win_cols - 1) ) ++cur_col;
                break;
            case 'k':
            case KEY_UP:
                if ( cur_row > 0 ) --cur_row;
                break;
            case 'j':
            case KEY_DOWN:
                if ( cur_row < (win_lines - 1) ) ++cur_row;
                break;
            case 'i':
            case KEY_IC:
                echo();
                // insertion_mode()
                break;

            default:
                break;
        }

        wmove(db[0].win, cur_row, cur_col);
        wrefresh(db[0].win);
    }
}

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
    //struct getan_options *opts = NULL;

    //opts = getan_options(argv, argc);

    // ncurses init
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

#ifdef ENABLE_DEBUG
    // Start debug pane.
    debug = create_window(LINES, COLS/2, 0, (COLS/2)+1);
    cur_dbg_line = 0;
    wrefresh(debug);
#endif

    // Allocate a new list of buffers.
    buflist = getan_buflist_new();
    if ( !buflist ) {
        printf("Error starting Getan... :(\n");
        goto free_out;
    }

    // Open file in the buffer list.
    if ( !(fbuf = file_open(buflist, "/home/bgarber/.vimrc")) ) {
        printf("Could not open the file...\n");
        goto free_out;
    }

    // Setup the display buffer for this file.
    memset(db, 0, sizeof(db));
    db[0].buffer = fbuf;
    db[0].buffer_chars = file_read(db[0].buffer, &db[0].buffer_sz);

    // Enter command mode
    command_mode(db);

free_out:
    unselect_buffer(&db[0]);
    getan_buflist_destroy(buflist);
    endwin();
    return 0;
}
