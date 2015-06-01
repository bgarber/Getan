/*
 * Copyright 2015 Bryan Garber
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

#ifndef FILES_H
#define FILES_H

typedef void * getan_files;

// Create and destroy files_list struct
int getan_files_new(getan_files f);
int getan_files_destroy(getan_files f);

// Open and close files
int getan_files_open(getan_files f, const char *filename);
int getan_files_close(getan_files f, unsigned int index);

#endif

