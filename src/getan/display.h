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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <ncurses.h>
#include <panel.h>

#include "panelist.h"

struct display {
    WINDOW *win;

    struct panelist pl;
};

struct display * diplay_new(void);
void display_destroy(struct display *dis);

getan_error display_split(struct display *dis, int hv);

#endif // __DISPLAY_H__

