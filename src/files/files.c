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

#include "files.h"

struct __file_data {
	const char         *fpath; // file path
	const char         *fname; // file name
	int                fd;     // file descriptor
	struct __file_data *next;  // pointer to the next file data
}

typedef struct __file_data __file_data_list;

struct __files_t {
	unsigned int     n_files; // n of opened files
	__file_data_list *fdata;  // list of open files
}

static int __file_data_open(const char *filename)
{
	return 0;
}

static int __file_data_destroy(struct __file_data *data)
{
	close(fd);
	free(data);
	data = NULL;
	return 0;
}

static int __files_close(struct __files_t *files, unsigned int index)
{
	struct __file_data *data;
	struct __file_data *data_prev;
	unsigned int i;

	if ( index > n_files )
		return -1;

	data_prev = NULL;
	data = (struct __file_data *) files->fdata;
	for ( i = 0; i <= index; i++ ) {
		data_prev = data;
		data = data->next;
	}

	if ( data_prev )
		data_prev->next = data->next;
	else
		files->fdata = data->next;

	return __file_data_destroy(data);
}

int files_new(files_t f)
{
	struct __files_t *newf;

	newf = malloc(sizeof(struct __files_t));
	if ( !newf )
		return -1;

	newf->n_files = 0;
	newf->fdata = NULL;
	f = (files_t) newf;

	return 0;
}

int files_destroy(files_t f)
{
	struct __files_t *files;
	unsigned int index;

	files = (struct __files_t *) f;

	if ( (files->n_files > 0) && (files->fdata) )
		for ( index = 0; i < files->n_files; index++ ) {
			__files_close(files, index);
		}

	free(files);
	f = NULL;

	return 0;
}

int files_open(files_t f, const char *filename)
{
	struct __files_t *files;

	files = (struct __files_t *) f;
	return __files_open(files, filename);
}

int files_close(files_t f, unsigned int index)
{
	struct __files_t *files;

	files = (struct __files_t *) f;
	return __files_close(files, index);
}

