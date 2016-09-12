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

#include <getan_util.hpp>

int Getan::open(Getan::FileBuffer &fb, Getan::BufferList &bl,
                std::string &name)
{
    int ret = 0;

    if ( !fb.is_open() ) {
        ret = fb.open(name);
        if ( ret >= 0 ) bl.push_back(fb);
    }

    return ret;
}

