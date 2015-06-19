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

#ifndef GETAN_BUFLIST_H
#define GETAN_BUFLIST_H

#include <getan_buffer.h>
#include <getan_errors.h>

/**
 * \struct getan_buflist
 * Opaque struct to a Getan buffer list.
 */
struct getan_buflist;

/**
 * \brief Creates a new buffer list.
 *
 * This function will allocate and initialize a new buffer list. It is intended
 * to be called only once, unless you need more than one buffer list.
 *
 * \param list The buffer list to be allocated.
 *
 * \return  a pointer to a newly allocated getan_buflist or NULL in case of
 *          error.
 */
struct getan_buflist * getan_buflist_new();

/**
 * \brief Destroy a buffer list.
 *
 * This function will free the buffer list in the memory and make list point to
 * NULL. It is intended to be called only once, unless you created more than one
 * buffer list, than you should call this function for each buffer you created.
 *
 * \param list The buffer list to be free'd.
 *
 * \return  0 on success
 * \return -1 on error
 */
int getan_buflist_destroy(struct getan_buflist *list);

/**
 * \brief Add a buffer to the list.
 *
 * This function will add a given buffer to the list, checking if there's enough
 * space to store it. If there's not enough room for the new buffer, resize the
 * list and store it.
 *
 * \param list The buffer list.
 * \param gb   The buffer to add.
 *
 * \return GETAN_SUCCESS  on success
 * \return GETAN_NO_LIST  if no list was found
 * \return GETAN_GEN_FAIL a general failure occurred
 */
getan_error getan_buflist_add(struct getan_buflist *list, struct getan_buffer *gb);

/**
 * \brief Gets a buffer from the list.
 *
 * This function will search for a buffer in the list, returning a pointer to
 * it.
 *
 * \param list  The buffer list.
 * \param index The index to the buffer.
 *
 * \return a pointer to the buffer on success; or NULL, in case of error.
 */
struct getan_buffer *getan_buflist_get_buffer(struct getan_buflist *list,
        unsigned int index);


#endif

