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

struct db_list *db_list_new()
{
    struct db_list *list;

    list = malloc(sizeof(*list));
    if ( list ) {
        list->db_first = NULL;
        list->db_last  = NULL;
        list->db_len   = 0;
    }

    return list;
}

void db_list_destroy(struct db_list *list)
{
    struct display_buffer *cur;

    for ( cur = list->db_first; cur; cur = cur->next )
        display_buffer_destroy(cur);

    free(list);
    list = NULL;
}

getan_error db_list_add(struct db_list *list, struct display_buffer *db)
{
    if ( !list ) return GETAN_GEN_FAIL;

    if ( list->db_len == 0 )
        list->db_first = db;
    else
        list->db_last->next = db;

    list->db_last = db;
    list->db_len += 1;

    return GETAN_SUCCESS;
}

struct display_buffer *db_list_get(struct db_list *list, int idx)
{
    struct display_buffer *d;
    int i;

    for ( d = list->db_first, i = 0; (d != NULL && i < idx);
            d = d->next, i++ );

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
        db->prev = NULL;
        db->next = NULL;
    }

    return db;
}

void display_buffer_destroy(struct display_buffer *db)
{
    if ( db->win ) delwin(db->win);
    //if ( db->panel ) ????

    buffer_data_destroy(db->data);

    free(db);
    db = NULL;
}

void display_buffer_show(struct display_buffer *db)
{
    struct buffer_data *data = db->data;
    unsigned int l;

    if ( !db->win )
        db->win = newwin(LINES, COLS, 0, 0);

    // I'm planning on using panels library from ncurses to manage the display
    // of windows, so update them here.
    //update_panels();
    //doupdate();

    if ( db->bot_line == 0 ) db->bot_line = LINES - 1;

    if ( db->dirty ) {
        wmove(db->win, 0, 0);

        for ( l = db->top_line; (l <= db->bot_line) && (l < data->n_lines);
                l++ )
            wprintw(db->win, "%s\n", data->lines[l].fl_line);

        db->dirty = 0;
    }

    wrefresh(db->win);
}

void display_buffer_topline(struct display_buffer *db, uint32_t top)
{
    db->top_line = top;
    db->bot_line = top + LINES - 1;
    db->dirty = 1;
}

void display_buffer_botline(struct display_buffer *db, uint32_t bot)
{
    db->bot_line = bot;
    db->top_line = bot - LINES - 1;
    db->dirty = 1;
}

