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

#ifndef __GETAN_FILEBUFFER__
#define __GETAN_FILEBUFFER__

#include <string>
#include <fstream>

#include "getan_buffer.hpp"

namespace Getan {
    class FileBuffer : public Getan::Buffer {
    public:
        FileBuffer();
        ~FileBuffer();

        int read(void);
        int write(void);

        int open(std::string &fname);
        void close();

        bool is_open() const;

    private:
        std::fstream file;
        //std::list<std::string> lines;
    };
}

#endif // __GETAN_FILEBUFFER__

