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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <getan_buflist.h>
#include <getan_filebuf.h>
#include <getan_errors.h>

#include "file.h"

struct getan_buffer *file_open(struct getan_buflist *buflist,
        char *filename)
{
    struct getan_buffer *fbuf = NULL;

    if ( !buflist ) return NULL;

    // Create a new buffer for the file.
    fbuf = getan_buffer_new();
    if ( !fbuf ) return NULL;

    // Make that buffer allocated above a file buffer.
    if ( getan_filebuf_create(fbuf) != GETAN_SUCCESS ) {
        printf("Could not make the new buffer a file buffer.\n");
        getan_buffer_destroy(fbuf);
        return NULL;
    }

    // Add the file buffer in the buffer list.
    if ( getan_buflist_add(buflist, fbuf) != GETAN_SUCCESS ) {
        printf("Error adding the buffer in the list...\n");
        getan_buffer_destroy(fbuf);
        return NULL;
    }

    // Open a file in the file buffer
    if ( getan_buffer_cb_call(fbuf, FILEBUF_OPEN, filename,
                strnlen(filename, MAX_FILENAME_LENGTH)) != GETAN_SUCCESS ) {
        perror("Could not open the file");
        getan_buffer_destroy(fbuf);
        return NULL;
    }

    return fbuf;
}

// Reads a line from the file descriptor.
// Returns NULL if EOF or no line.
static char *freadln(int fd, size_t *len)
{
    unsigned int idx;
    char *line = NULL;
    char c;

    idx = 0;

    while ( read(fd, &c, 1) > 0 ) {
        char *nline = realloc(line, ++idx);
        if ( nline != line )
            free(line);

        line = nline;
        line[idx - 1] = c;

        if ( c == '\n' ) break;
    }

    (*len) = (size_t) idx;

    return line;
}

struct file_line *file_read(struct getan_buffer *fbuf, uint32_t *nlines)
{
    struct file_line *lines = NULL;
    int fd, int_sz;
    char *line;
    size_t line_len;
    uint32_t line_idx;

    if ( !fbuf ) return NULL;

    int_sz = sizeof(int);
    getan_buffer_cb_get(fbuf, FILEBUF_FD, &fd, &int_sz);

    line_idx = 0;
    while ( (line = freadln(fd, &line_len)) ) {
        struct file_line *nlines;

        nlines = realloc(lines, (++line_idx) * sizeof(struct file_line));

        if ( nlines != lines )
            free(lines);

        lines = nlines;

        lines[line_idx - 1].fl_line  = strndup(line, line_len);
        lines[line_idx - 1].fl_len   = line_len;
        lines[line_idx - 1].fl_dirty = 0;

        free(line);
    }

    (*nlines) = line_idx;

    return lines;
}

void file_unread(struct file_line *lines, size_t lines_len)
{
    size_t line_idx;

    if ( lines ) {
        for ( line_idx = 0; line_idx < lines_len; line_idx++ )
            free(lines[line_idx].fl_line);

        free(lines);
    }
}

size_t file_get_size(struct getan_buffer *fbuf) {
    size_t size;
    int int_sz = sizeof(size_t);

    if ( getan_buffer_cb_get(fbuf, FILEBUF_FILESZ, &size, &int_sz) !=
            GETAN_SUCCESS ) return 0;

    return size;
}

