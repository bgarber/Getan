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

// Getan lib includes
#include <getan_buffer.hpp>
#include <getan_util.hpp>

int main(int argc, char **argv)
{
    Getan::BufferList buflist;

    if ( argc > 0 ) {
        Getan::FileBuffer file;
        std::string name(argv[1]);

        if ( Getan::open(file, buflist, name) < 0 )
            std::cout << "Could not open file!" << std::endl;
    }

    return 0;
}

