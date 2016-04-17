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


#include "display_buffer.h"

#include <getan_log.h>

struct db_list *db_list_new()
{
    struct db_list *list;

    list = malloc(sizeof(*list));
    if ( list ) {
        list->length = 0;
        LIST_INIT(&(list->head));
    }

    return list;
}

getan_error db_list_destroy(struct db_list *list)
{
    struct display_buffer *entry;

    if ( !list ) return GETAN_NO_LIST;

    while ( !LIST_EMPTY(&(list->head)) ) {
        entry = LIST_FIRST(&(list->head));
        LIST_REMOVE(entry, entries);
        display_buffer_destroy(entry);
    }

    free(list);
    list = NULL;

    return GETAN_SUCCESS;
}

getan_error db_list_add(struct db_list *list, struct display_buffer *db)
{
    if ( !list ) return GETAN_GEN_FAIL;

    LIST_INSERT_HEAD(&(list->head), db, entries);
    list->length += 1;

    return GETAN_SUCCESS;
}

struct display_buffer *db_list_get(struct db_list *list, int idx)
{
    struct display_buffer *d;

    LIST_FOREACH (d, &(list->head), entries) {
        if ( idx > 0 ) idx--;
        else break;
    }

    return d;
}

struct display_buffer *display_buffer_new()
{
    struct display_buffer *db;

    db = malloc(sizeof(*db));
    if ( db ) {
        db->win = NULL;
        db->panel = NULL;
        db->data = NULL;
        db->top_line = 0;
        db->bot_line = 0;
        db->dirty = 1; // set this display_buffer to be reprinted.
    }

    return db;
}

void display_buffer_destroy(struct display_buffer *db)
{
    if ( db->win ) delwin(db->win);
    //if ( db->panel ) ????

    buffer_destroy(db->data);

    free(db);
    db = NULL;
}

void display_buffer_show(struct display_buffer *db)
{
    struct buffer *data = db->data;
    unsigned int l;

    if ( !db->win ) db->win = newwin(LINES, COLS, 0, 0);

    // I'm planning on using panels library from ncurses to manage the display
    // of windows, so update them here.
    //update_panels();
    //doupdate();

    if ( db->bot_line == 0 )
        db->bot_line = ( LINES < data->n_lines ) ?
            LINES - 1 : data->n_lines - 1;

    if ( db->dirty ) {
        wmove(db->win, 0, 0);

        for ( l = db->top_line; l <= db->bot_line; l++ )
            wprintw(db->win, "%s\n", data->lines[l].fl_line);

        db->dirty = 0;
    }

    wrefresh(db->win);
}

void display_buffer_topline(struct display_buffer *db, uint32_t top)
{
    db->top_line = top;
    db->bot_line = top + (LINES - 1);
    db->dirty = 1;
    getan_logdebug("New top_line: %d; new bot_line: %d\n", db->top_line,
            db->bot_line);
}

void display_buffer_botline(struct display_buffer *db, uint32_t bot)
{
    db->bot_line = bot;
    db->top_line = bot - (LINES - 1);
    db->dirty = 1;
    getan_logdebug("New top_line: %d; new bot_line: %d\n", db->top_line,
            db->bot_line);
}

