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

#include <vector>
#include <string>
#include <fstream>

#include <getan_filelist.hpp>

namespace Getan {
    typedef std::vector<std::string> BufferLines;

    class Buffer {
    public:
        Buffer();
        Buffer(FilePtr fs);
        ~Buffer();

        BufferLines getLines();

    private:
        BufferLines buflines;
        FilePtr file;
    };

    class BufferList {
    public:
        BufferList();
        ~BufferList();

        void createBuffer(FilePtr fs);
        Buffer& operator[](unsigned int n);

    private:
        std::vector<Buffer> blist;
    };
}

#endif //__GETAN_BUFFER__

