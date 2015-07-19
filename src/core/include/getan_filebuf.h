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

#ifndef FILEBUF_H
#define FILEBUF_H

#include <getan_buffer.h>
#include <getan_errors.h>

/*
 * Taken from the Ext4 definitions; I don't know if this works for every file
 * system in the world, but I think it does.
 */
#define MAX_FILENAME_LENGTH 255

// Call methods
#define FILEBUF_OPEN 0

// Attributes to get/set
#define FILEBUF_FD      0
#define FILEBUF_FILESZ  1

/**
 * \brief Create a new getan_filebuf.
 *
 * This function will allocate and initialize a new file buffer.
 *
 * \return GETAN_SUCCESS     on success;
 *         GETAN_CREATE_FAIL on failing to allocate memory;
 *         GETAN_GEN_FAILURE on failing initialize buffer.
 */
getan_error getan_filebuf_create(struct getan_buffer *gb);

#endif // FILEBUF_H

