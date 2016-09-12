# Copyright 2016 Bryan Garber
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

GCC=g++
AR=ar
DBGFLAGS=-g -O0 -Wall
CFLAGS=$(DBGFLAGS) -I./include/

OBJS=src/getan_util.o src/getan_filebuffer.o src/getan_buffer.o
TARGET=libgetan.a
LIBDIR=.lib

all: $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf $(OBJS) $(TARGET)

