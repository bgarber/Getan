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

#include "buffer_data.h"

struct buffer_data *buffer_data_new()
{
    struct buffer_data *data;

    data = malloc(sizeof(*data));
    if ( data ) {
        data->buffer = NULL;
        data->lines  = NULL;
        data->n_lines = 0;
    }

    return data;
}

void buffer_data_destroy(struct buffer_data *data)
{
    /*
     * Achtung!
     * WARNING: Don't touch the getan_buffer here! We just have a reference to
     * the item in the getan_buflist, so the function getan_buflist_destroy
     * should take care on destroying it!
     */

    file_unread(data->lines, data->n_lines);
    free(data);
}

getan_error buffer_data_setup(struct buffer_data *data, struct getan_buffer *buf)
{
    if ( !data ) return GETAN_GEN_FAIL;

    data->buffer = buf;
    data->lines = file_read(buf, &data->n_lines);

    return GETAN_SUCCESS;
}

