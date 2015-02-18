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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "files.h"

#define EXT4_MAX_FILENAME_LENGTH 255

struct __file_data {
	const char         *fpath; // file path
	const char         fname[EXT4_MAX_FILENAME_LENGTH]; // file name
	int                fd;     // file descriptor
	struct __file_data *next;  // pointer to the next file data
}

typedef struct __file_data __file_data_list;

struct __files_t {
	unsigned int     n_files; // n of opened files
	__file_data_list *fdata_list_head;  // list of open files
}

static int __file_data_new(struct __file_data *data)
{
	struct __file_data *new_data;

	new_data = malloc(sizeof(struct __file_data));
	if ( !new_data )
	{
		data = NULL;
		return -1;
	}

	new_data->fpath = NULL;
	memset(new_data->fname, 0, sizeof(new_data->fname));
	new_data->fd = -1;
	new_data->next = NULL;

	data = new_data;

	return 0;
}

static int __file_data_open(struct __file_data *data, const char *filepath)
{
	strncpy(new_file->fname, filepath, sizeof(new_file->fname));
	new_file->fd = open(new_file->fname, O_CREAT);
	if ( new_file->fd < 0 )
		return -1;

	return 0;
}

static int __file_data_destroy(struct __file_data *data)
{
	close(fd);
	free(data);
	data = NULL;
	return 0;
}

/*
 * TODO: check if the file is not already opened!!!
 */
static int __files_open(struct __files_t *files, const char *filepath)
{
	struct __file_data *new_file;
	struct __file_data *cur_fdata;

	/*
	 * Create new metadata for file.
	 */
	if ( __file_data_new(new_file) )
		return -1;

	/*
	 * Open file, storing file descriptor in structure.
	 */
	if ( __file_data_open(new_file, filepath) )
		return -1;

	/*
	 * Put opened file in the open files list.
	 */
	if ( files->n_files == 0 ) {
		files->fdata_list_head = new_file;
	} else {
		cur_fdata = files->fdata_list_head;
		while ( cur_fdata ) cur_fdata = cur_fdata->next;
		cur_fdata->next = new_file;
	}

	files->n_files++;

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
	data = (struct __file_data *) files->fdata_list_head;
	for ( i = 0; i <= index; i++ ) {
		data_prev = data;
		data = data->next;
	}

	if ( data_prev )
		data_prev->next = data->next;
	else
		files->fdata_list_head = data->next;

	return __file_data_destroy(data);
}

int files_new(files_t f)
{
	struct __files_t *newf;

	newf = malloc(sizeof(struct __files_t));
	if ( !newf )
		return -1;

	newf->n_files = 0;
	newf->fdata_list_head = NULL;
	f = (files_t) newf;

	return 0;
}

int files_destroy(files_t f)
{
	struct __files_t *files;
	unsigned int index;

	files = (struct __files_t *) f;

	if ( (files->n_files > 0) && (files->fdata_list_head) )
		for ( index = 0; i < files->n_files; index++ ) {
			__files_close(files, index);
		}

	free(files);
	f = NULL;

	return 0;
}

int files_open(files_t f, const char *filepath)
{
	struct __files_t *files;

	files = (struct __files_t *) f;
	return __files_open(files, filepath);
}

int files_close(files_t f, unsigned int index)
{
	struct __files_t *files;

	files = (struct __files_t *) f;
	return __files_close(files, index);
}

