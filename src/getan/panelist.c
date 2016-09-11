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

#include "panelist.h"

/**** Start of pane functions. ****/
struct pane * pane_new()
{
    struct pane *p;

    p = (struct pane *)malloc(sizeof(*p));
    if ( p != NULL ) {
        //p->win = NULL;
    }

    return p;
}

void pane_destroy(struct pane *p)
{
    if ( p != NULL ) free(p); // Do not touch the buffer!
}

void pane_repaint(struct pane *p);


/**** Start of panelist functions ****/
struct panelist *panelist_new()
{
    struct panelist *p;

    p = (struct panelist *)malloc(sizeof(*p));
    if ( p != NULL )
        LIST_INIT(&(p->head));

    return p;
}

void panelist_destroy(struct panelist *p)
{
    struct pane *entry;

    if ( p != NULL ) {
        while ( !LIST_EMPTY(&(p->head)) ) {
            entry = LIST_FIRST(&(p->head));
            LIST_REMOVE(entry, entries);
            pane_destroy(entry);
            free(entry);
        }

        free(p);
        p = NULL;
    }
}

