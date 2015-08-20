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

#include <getan_buffer.h>

#include <string.h>

struct getan_buffer {
    getan_buftype          gb_type;  // Buffer type
    struct getan_buffer_cb *gb_cb;   // Buffer callbacks
    void                   *gb_priv; // Buffer private data
};

struct getan_buffer * getan_buffer_new()
{
    struct getan_buffer *gb = NULL;

    gb = malloc(sizeof(struct getan_buffer));
    if ( gb ) {
        gb->gb_type = GETAN_BUFFER_NOT_USED;
        gb->gb_cb = NULL;
        gb->gb_priv = NULL;
    }

    return gb;
}

int getan_buffer_destroy(struct getan_buffer *gb)
{
    if ( gb ) {
        getan_buffer_cb_destroy(gb);
        free(gb);
        gb = NULL;
    }

    return 0;
}

int getan_buffer_setup(struct getan_buffer *gb, getan_buftype type,
        struct getan_buffer_cb *cb, void *priv)
{
    if ( !gb ) return -1;

    gb->gb_type = type;
    gb->gb_cb = cb;
    gb->gb_priv = priv;

    return 0;
}

int getan_buffer_is_used(struct getan_buffer *gb)
{
    return (gb->gb_type != GETAN_BUFFER_NOT_USED);
}

size_t getan_buffer_size_of()
{
    return sizeof(struct getan_buffer);
}

getan_error getan_buffer_cb_destroy(struct getan_buffer *gb)
{
    if ( (!gb) || (!gb->gb_cb->destroy) ) return GETAN_GEN_FAIL;
    return gb->gb_cb->destroy(gb->gb_priv);
}

getan_error getan_buffer_cb_call(struct getan_buffer *gb, unsigned int method,
        void *parm, size_t plen)
{
    if ( (!gb) || (!gb->gb_cb->call) ) return GETAN_GEN_FAIL;
    return gb->gb_cb->call(gb->gb_priv, method, parm, plen);
}

getan_error getan_buffer_cb_get(struct getan_buffer *gb,
        unsigned int attribute, void *data, int *dlen)
{
    if ( (!gb) || (!gb->gb_cb->get) ) return GETAN_GEN_FAIL;
    return gb->gb_cb->get(gb->gb_priv, attribute, data, dlen);
}

