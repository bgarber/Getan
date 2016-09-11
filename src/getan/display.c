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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include <getan_log.h>

#include "display.h"

struct display * display_new()
{
    struct display *new_d;

    new_d = malloc(sizeof(*new_d));
    if ( new_d != NULL ) {
        new_d->win = NULL;
        //new_d->geometry.x = 0;
        //new_d->geometry.y = 0;
        new_d->pl = panelist_new();
    }

    return new_d;
}

void display_destroy(struct display *d)
{
    if ( d != NULL ) {
        delwin(d->win);
        panelist_destroy(d->pl);
    }
}

