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

struct display_buffer *display_buffer_new()
{
    struct display_buffer *db;

    db = malloc(sizeof(*db));
    if ( db ) {
        db->win = NULL;
        db->panel = NULL;
        db->cursor_x = 0;
        db->cursor_y = 0;
        db->data = NULL;
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

