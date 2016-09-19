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

#include <getan_buffer.hpp>

using namespace Getan;

Buffer::Buffer(FilePtr fs)
    : file(fs)
{
    std::string line;

    if ( fs->is_open() )
        while ( std::getline(*fs, line) )
            buflines.push_back(line);
}

Buffer::~Buffer()
{
    // Nothing to do here.
}

BufferLines Buffer::getLines()
{
    return buflines;
}

BufferList::BufferList()
{

}

BufferList::~BufferList()
{

}

void BufferList::createBuffer(FilePtr fs)
{
    Buffer buf(fs);
    blist.push_back(buf);
}

Buffer BufferList::operator[](unsigned int n) {
    return blist.at(n);
}

