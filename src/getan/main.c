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
#include <stdint.h>
#include <locale.h>
#include <ncurses.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

#include "file.h"

//#define ENABLE_DEBUG 1

/**
 * \struct display_buffer
 *
 * This is a buffer displayed on the screen.
 */
struct display_buffer {
    // Buffer data.
    struct getan_buffer *buffer;   // pointer to the buffer
    size_t              buffer_sz; // size of the buffer, in bytes
    struct file_line    *lines;    // characters in the buffer
    uint32_t            n_lines;   // lines in the buffer

    // Buffer manipulation fields
    uint32_t top_line;  // index of the top line in screen
    uint32_t bot_line;  // index of the bottom line in screen

    // Window manipulation fields
    WINDOW   *win;     // window pointer for this buffer
    uint32_t cursor_y; // save last cursor y
    uint32_t cursor_x; // save last cursor x
};

/*
 * Global declarations... (?)
 * !! Debug-only !!
 */
#ifdef ENABLE_DEBUG
static WINDOW   *debug;
static uint32_t cur_dbg_line;
#endif

static void log_debug(const char *fmt, ...)
{
#ifdef ENABLE_DEBUG
    const char *p;
    va_list argp;

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

static void print_lines(struct display_buffer *db)
{
    int cur_line;

    wmove(db->win, 0, 0);

    log_debug("Reprinting window from line %d to %d\n",
            db->top_line, db->bot_line);

    for ( cur_line = db->top_line; cur_line <= db->bot_line; cur_line++ )
        waddstr(db->win, db->lines[cur_line].fl_line);

    wrefresh(db[0].win);

}

static void command_mode(struct display_buffer *db)
{
    int chr; // char read from keyboard
    int cur_col = 0, cur_row = 0; // screen related cursor position
    int cur_line; // file related cursor position: line
    int reprint; // boolean: should I reprint the the lines in the screen?
    int win_lines, win_cols; // window size

    log_debug("Entered command mode.\n");

    getmaxyx(db[0].win, win_lines, win_cols);
    cur_line = 0;
    reprint = 1;

    while ( 1 ) {
        if ( reprint ) {
            print_lines(&(db[0]));
            reprint = 0;
        }

        /*
         * In the last line, the current column could be valid. This may not be
         * true for the current line.
         */
        if ( cur_col >= db[0].lines[cur_line].fl_len )
            cur_col = db[0].lines[cur_line].fl_len - 1;

        log_debug("Sending cursor to (%d,%d)\n",
                cur_row, cur_col);

        wmove(db[0].win, cur_row, cur_col);
        wrefresh(db[0].win);

        chr = getch();

        if ( chr == 'q' ) break;

        switch ( chr ) {
            case 'h':
            case KEY_LEFT:
                if ( cur_col > 0 ) --cur_col;
                break;
            case 'l':
            case KEY_RIGHT:
                if ( cur_col < (db[0].lines[cur_line].fl_len - 1) )
                    ++cur_col;
                break;
            case 'k':
            case KEY_UP:
                if ( cur_row > 0 )
                    --cur_row;

                if ( cur_line > 0 )
                    cur_line--;

                if ( cur_line < db[0].top_line ) {
                    db[0].top_line = cur_line;
                    db[0].bot_line = cur_line + (win_lines - 1);
                    reprint = 1;
                }
                break;
            case 'j':
            case KEY_DOWN:
                if ( cur_row < (win_lines - 1) )
                    ++cur_row;

                if ( cur_line < (db[0].n_lines - 1) )
                    cur_line++;

                if ( cur_line > db[0].bot_line ) {
                    db[0].top_line = cur_line - (win_lines - 1);
                    db[0].bot_line = cur_line;
                    reprint = 1;
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

static WINDOW *create_window(int height, int width, int y, int x)
{
    WINDOW *win;

    win = newwin(height, width, y, x);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

// Send NULL to the last parameter to search the buffer in the list.
static getan_error select_buffer(struct display_buffer *db,
        struct getan_buflist *buflist, unsigned int bufnumber,
        struct getan_buffer *buf)
{
    int win_cols;

    if ( !db ) return GETAN_GEN_FAIL;

#ifdef ENABLE_DEBUG
    win_cols = COLS/2;
#else
    win_cols = COLS;
#endif

    if ( !buf ) {
        if ( !buflist ) return GETAN_GEN_FAIL;
        buf = getan_buflist_get_buffer(buflist, bufnumber);
    }

    // Setup the display buffer for this file.
    db[0].buffer = buf;
    db[0].buffer_sz = file_get_size(buf);
    db[0].lines = file_read(db[0].buffer, &db[0].n_lines);
    db[0].top_line = 0;
    db[0].bot_line = LINES - 1;
    db[0].win = create_window(LINES, win_cols, 0, 0);
    db[0].cursor_y = 0;
    db[0].cursor_x = 0;

    return GETAN_SUCCESS;
}

static getan_error unselect_buffer(struct display_buffer *db)
{
    // Free memory.
    file_unread(db->lines, db->n_lines);
    delwin(db->win);

    // Clean structure. BE CAREFUL WITH THE db POINTER!
    memset(db, 0, sizeof(struct display_buffer));

    return GETAN_SUCCESS;
}

int main(int argc, char *argv[])
{
    struct display_buffer db[5];
    struct getan_buflist *buflist = NULL;
    struct getan_buffer  *fbuf = NULL;
    //struct getan_options *opts = NULL;

    //opts = getan_options(argv, argc);

    setlocale(LC_ALL, "");

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

    memset(db, 0, sizeof(db));
    select_buffer(db, NULL, 0, fbuf);

    // Enter command mode
    command_mode(db);

free_out:
    unselect_buffer(&(db[0]));
    getan_buflist_destroy(buflist);
    endwin();
    return 0;
}
