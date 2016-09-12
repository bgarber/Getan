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

#ifndef __GETAN_BUFFER__
#define __GETAN_BUFFER__

#include <list>
#include <string>

namespace Getan {
    class Buffer;

    typedef std::list<Buffer> BufferList;

    /*
     * Pure virtual class to abstract a Buffer.
     */
    class Buffer {
    public:
        virtual ~Buffer();

        /*
         * Operators to read/write from/to the buffer.
         */
        virtual int read(void);
        virtual int write(void);
    };
}

#endif //__GETAN_BUFFER__

