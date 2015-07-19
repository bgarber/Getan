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

#ifndef FILE_H
#define FILE_H

#include <getan_errors.h>

/**
 * \struct file_line
 * Structure to keep a line in the file.
 */
struct file_line {
    char    *fl_line; // the line
    size_t  fl_len;   // the length of the line
    uint8_t fl_dirty; // repaint?
};

/**
 * \brief Open a file.
 *
 * This function will create a new file buffer, opening the file specified by
 * the filename in it. After that, the file buffer is added into the buffer
 * list.
 *
 * \param buflist  The list of buffer to operate.
 * \param filename The complete path to the file to open.
 *
 * \return a pointer to the file buffer; or NULL in case of error.
 */
getan_error file_open(struct getan_buflist *buflist, struct getan_buffer *fbuf,
        char *filename);

/**
 * \brief Read file contents.
 *
 * This function will get the file descriptor from a buffer to create a list of
 * lines in the memory, representing the file content.
 *
 * \param fbuf  The file buffer to operate.
 * \param lines The length of the lines list.
 *
 * \return a pointer to a list of lines; or NULL in case of error.
 */
struct file_line *file_read(struct getan_buffer *fbuf, uint32_t *lines);

/**
 * \brief Free up file contents and data.
 *
 * For now, this function will free up all memory allocated for lines.
 *
 * \param lines     The file lines array to operate.
 * \param lines_len The length of the file lines array.
 */
void file_unread(struct file_line *lines, size_t lines_len);

/**
 * \brief Get file size in bytes.
 *
 * This function will call the FILEBUF_FILESZ callback from the file buffer to
 * get the original size of the file in the system.
 *
 * \param fbuf  The file buffer to operate.
 *
 * \return The size of the file in the system.
 */

size_t file_get_size(struct getan_buffer *fbuf);

#endif // FILE_H

