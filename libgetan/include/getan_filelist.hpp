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

#include <fstream>
#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

namespace Getan {
    typedef boost::shared_ptr<std::fstream> FilePtr;

    class FileList {
    public:
        FileList();
        ~FileList();

        void open(const char *fname);
        void close(unsigned int n);

        FilePtr operator[](unsigned int n);

    private:
        std::vector<FilePtr> flist;
    };
}

#endif // __GETAN_FILEBUFFER__

