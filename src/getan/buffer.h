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

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <getan_buffer.h>
#include <getan_errors.h>

#include "file.h"

struct buffer {
    struct getan_buffer *buffer;
    struct file_line    *lines;
    uint32_t            n_lines;
};

struct buffer *buffer_new();

void buffer_destroy(struct buffer *data);

getan_error buffer_setup(struct buffer *data, struct getan_buffer *buf);

#endif // __BUFFER_H__

