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

#ifndef DISPLAY_BUFFER_H
#define DISPLAY_BUFFER_H

#include <ncurses.h>
#include <panel.h>
#include <sys/queue.h> // Use BSD lists!

#include "buffer.h"

struct display_buffer {
    WINDOW *win;
    PANEL  *panel;

    struct buffer *data;
    uint32_t top_line;
    uint32_t bot_line;

    int dirty;

    LIST_ENTRY(display_buffer) entries;
};

struct db_list {
    unsigned int length;
    LIST_HEAD(db, display_buffer) head;
};


/**
 * \brief Create a display buffer list.
 *
 * This function will create a new display_buffer list structure.
 *
 * \return a pointer to a newly allocated list, or NULL in case of error;
 */
struct db_list *db_list_new();


/**
 * \brief Destroy display buffer list.
 *
 * This function will free up the space.
 *
 * \param list  Pointer to the list.
 */
getan_error db_list_destroy(struct db_list *list);


/**
 * \brief Add a new display_buffer to list.
 *
 * This function simply adds a display buffer to the list.
 *
 * \param list The display_buffer list.
 * \param db   The display_buffer to add.
 *
 * \return GETAN_SUCCESS  on success;
 *         GETAN_GEN_FAIL in case of error.
 */
getan_error db_list_add(struct db_list *list, struct display_buffer *db);


/**
 * \brief Get a display_buffer by index.
 *
 * This function iterates in the list, until it reaches the desired index.
 *
 * \param list The display_buffer list.
 * \param idx  The index to get.
 *
 * \return a pointer to a display_buffer; or NULL if not found.
 */
struct display_buffer *db_list_get(struct db_list *list, int idx);


/**
 * \brief Create a display buffer.
 *
 * This function will create a new display_buffer structure with the data
 * pointer sent by parameter.
 *
 * \return a pointer to a newly allocated display_buffer, or NULL in case of
 *         error;
 */
struct display_buffer *display_buffer_new();


/**
 * \brief Destroy display buffer.
 *
 * This function will free up the space.
 *
 * \param db  Pointer to the display_buffer.
 */
void display_buffer_destroy(struct display_buffer *db);


/**
 * \brief Show the display buffer.
 *
 * This function will create a ncurses WINDOW if needed; set up
 * everything and refresh the screen.
 *
 * \param db  Pointer to the display_buffer.
 */
void display_buffer_show(struct display_buffer *db);


/**
 * \brief Update the top line from the display buffer.
 *
 * This function will update the top line from the display buffer, updating its
 * bottom line and setting the dirty boolean.
 *
 * \param db  Pointer to the display_buffer.
 * \param top The index for the top line.
 */
void display_buffer_topline(struct display_buffer *db, uint32_t top);


/**
 * \brief Update the bottom line from the display buffer.
 *
 * This function will update the bottom line from the display buffer, updating
 * its top line and setting the dirty boolean.
 *
 * \param db  Pointer to the display_buffer.
 * \param bot The index for the top line.
 */
void display_buffer_botline(struct display_buffer *db, uint32_t bot);


#endif // DISPLAY_BUFFER_H

