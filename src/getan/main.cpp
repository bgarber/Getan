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

// Standard lib includes
#include <iostream>
#include <string>

#include <boost/foreach.hpp>

// Getan lib includes
#include <getan_buffer.hpp>
#include <getan_filelist.hpp>

int main(int argc, char **argv)
{
    Getan::FileList flist;
    Getan::BufferList blist;

    if ( argc > 1 ) {
        flist.open(argv[1]);

        blist.createBuffer(flist[0]);

        BOOST_FOREACH(std::string line, blist[0].getLines()) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}

