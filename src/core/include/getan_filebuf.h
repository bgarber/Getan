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

#ifndef FILES_H
#define FILES_H

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
 * \return a pointer to getan_buffer of type GETAN_BUFFER_FILEIO;
 *         or NULL in case of error.
 */
getan_error getan_filebuf_create(struct getan_buffer *gb);
//int getan_files_destroy(struct getan_files *f);

/**
 * \brief Open a file
 *
 * This function will open a file in the specified buffer.
 *
 * \param fbuf  The file buffer to operate.
 * \param fname The file name to open.
 *
 * \return GETAN_SUCCESS   on success;
 * \return GETAN_OPEN_FAIL on error.
 */
getan_error getan_filebuf_open(struct getan_buffer *fbuf, const char *fname);

/**
 * \brief Open a file
 *
 * This function will close the file in the specified buffer.
 *
 * \param fbuf  The file buffer to operate.
 *
 * \return GETAN_SUCCESS   on success;
 * \return GETAN_OPEN_FAIL on error.
 */
getan_error getan_filebuf_close(struct getan_buffer *fbuf);

#endif

