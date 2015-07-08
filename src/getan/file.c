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

#define LINE_BUFFER_LEN 80

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

// Internal function that reads a line from the char buffer.
// When end of buffer reached, returns NULL.
static char *readln(const char *flines, size_t fsize, unsigned int offset,
        size_t *line_len)
{
    unsigned int fidx, char_pos;
    char *line = NULL;

    fidx = offset;
    char_pos = 0;
    while ( fidx < fsize ) {
        char *nline = realloc(line, char_pos+1);
        if ( !nline ) {
            if ( line ) free(line);
            line = NULL;
            char_pos = 0;
            break;
        }

        line = nline;

        if ( flines[fidx] == '\n' ) {
            line[char_pos++] = '\0';
            break;
        }

        line[char_pos] = flines[fidx];

        char_pos++;
        fidx++;
    }

    (*line_len) = (size_t) char_pos;

    return line;
}

struct file_line *file_read(struct getan_buffer *fbuf, uint32_t *nlines)
{
    struct file_line *lines;
    uint32_t line_idx;
    size_t   line_len, fsize;
    char     *flines, *cur_line;
    int      fd, int_sz, off;

    if ( !fbuf ) return NULL;

    int_sz = sizeof(int);
    getan_buffer_cb_get(fbuf, FILEBUF_FD, &fd, &int_sz);

    fsize = file_get_size(fbuf);
    flines = (char *) mmap(NULL, fsize, PROT_READ | PROT_WRITE,
            MAP_PRIVATE, fd, 0);

    if ( flines == MAP_FAILED ) {
        perror("GETAN ERROR");
        return NULL;
    }

    lines = NULL;
    line_idx = 0;
    off = 0;
    cur_line = readln(flines, fsize, off, &line_len);
    while ( cur_line ) {
        struct file_line *new_lines;

        new_lines = realloc(lines, (++line_idx) * sizeof(struct file_line));
        if ( !new_lines ) {
            if ( lines ) free(lines);
            lines = NULL;
            line_idx = 0;
            break;
        }

        lines = new_lines;

        lines[line_idx - 1].fl_line  = strndup(cur_line, line_len);
        lines[line_idx - 1].fl_len   = line_len;
        lines[line_idx - 1].fl_dirty = 0;

        free(cur_line);

        off = off + line_len;
        cur_line = readln(flines, fsize, off, &line_len);
    }

    (*nlines) = line_idx;

    if ( munmap(flines, fsize) < 0 )
        perror("GETAN ERROR");

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

