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

#include <getan_buflist.h>

#include <stdlib.h>
#include <string.h>

// Use BSD list macros!
#include <sys/queue.h>

struct buflist_entry {
    struct getan_buffer *buffer;
    LIST_ENTRY(buflist_entry) entries;
};

struct getan_buflist {
    unsigned int length;
    LIST_HEAD(buflist, buflist_entry) head;
};

struct getan_buflist * getan_buflist_new()
{
    struct getan_buflist *list = NULL;

    list = malloc(sizeof(*list));
    if ( list ) {
        list->length = 0;
        LIST_INIT(&(list->head));
    }

    return list;
}

getan_error getan_buflist_destroy(struct getan_buflist *list)
{
    struct buflist_entry *entry;

    if ( !list ) return GETAN_NO_LIST;

    while ( !LIST_EMPTY(&(list->head)) ) {
        entry = LIST_FIRST(&(list->head));
        LIST_REMOVE(entry, entries);
        getan_buffer_destroy(entry->buffer);
        free(entry);
    }

    free(list);
    list = NULL;

    return GETAN_SUCCESS;
}

getan_error getan_buflist_add(struct getan_buflist *list,
        struct getan_buffer *gb)
{
    struct buflist_entry *entry;

    if ( !list ) return GETAN_NO_LIST;

    entry = malloc(sizeof(*entry));
    entry->buffer = gb;

    LIST_INSERT_HEAD(&(list->head), entry, entries);
    list->length++;

    return GETAN_SUCCESS;
}

struct getan_buffer *getan_buflist_get_buffer(struct getan_buflist *list,
        unsigned int index)
{
    struct getan_buffer *gb;
    struct buflist_entry *entry;

    LIST_FOREACH (entry, &(list->head), entries) {
        if ( index > 0 ) index--;
        else break;
    }

    gb = (entry) ? entry->buffer : NULL;

    return gb;
}

