/*
 * Copyright 2016 Bryan Garber
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

#ifndef __PANELIST_H__
#define __PANELIST_H__

#include <sys/queue.h>

#include "buffer.h"

struct pane {
    WINDOW *win;

    struct buffer *buf;

    unsigned int geo_x;
    unsigned int geo_y;

    LIST_ENTRY(pane) entries;
};

struct panelist {
    LIST_HEAD(pl, pane) head;
};

/**** Start of pane functions. ****/
struct pane * pane_new();
void pane_destroy(struct pane *p);
void pane_repaint(struct pane *p);

/**** Start of panelist functions ****/
struct panelist * panelist_new();
void panelist_destroy(struct panelist *p);

#endif // __PANELIST_H__

