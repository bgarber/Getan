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
struct getan_buffer *file_open(struct getan_buflist *buflist,
        char *filename);

/**
 * \brief Read file contents.
 *
 * This function will get the file descriptor and the file size to create a
 * mmap for this file contents.
 *
 * \param fbuf    The file buffer to operate.
 * \param file_sz The size of the file when read.
 *
 * \return a pointer to the mmap'ed file; or NULL in case of error.
 */
char *file_read(struct getan_buffer *fbuf, unsigned int *file_sz);

/**
 * \brief Free up file contents and data.
 *
 * For now, this function will only do a munmap.
 *
 * \param file_cs The file buffer to operate.
 * \param file_sz The size of the file when read.
 *
 * \return  0 on success
 * \return -1 on error
 */
int file_unread(char *file_cs, unsigned int file_sz);

#endif // FILE_H

