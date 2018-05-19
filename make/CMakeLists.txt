# Copyright 2017 Bryan Garber
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 3.7.2)

project (getan)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_C_FLAGS "-Wall")

find_package (Curses REQUIRED)
include_directories (${CURSES_INCLUDE_DIR})

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../include")
file (GLOB getan_SRC
    "../source/*.cpp"
    )

add_executable (getan ${getan_SRC})
target_link_libraries (getan ${CURSES_LIBRARIES})
