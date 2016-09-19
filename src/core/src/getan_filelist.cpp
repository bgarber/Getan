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

#include <boost/foreach.hpp>

#include <getan_filebuffer.hpp>

using namespace Getan;

FileList::FileList()
{
}

FileList::~FileList()
{
    // Close each open file in the list.
    BOOST_FOREACH(std::fstream file, flist) {
        if ( file.is_open() ) file.close();
    }
}

/*
std::istream& FileList::readline(std::string& line)
{
    return std::getline(file, line);
}
*/

std::fstream FileList::operator[] (size_t n)
{
    return flist[n];
}

int FileList::write(void)
{
    return 0;
}

void FileList::open(const char *fname)
{
    std::fstream file;

    file.open(fname);
    if ( file.is_open() )
        flist.push_back(file);
}

void FileList::close(int idx)
{
    flist[idx].close();
    flist.erase(flist.begin()+idx);
}

/*
bool FileList::is_open() const
{
    return file.is_open();
}
*/

