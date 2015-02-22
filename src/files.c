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

struct file_metadata {
	const char *fpath; // file path
	const char fname[EXT4_MAX_FILENAME_LENGTH]; // file name
	int        fd;     // file descriptor
	struct file_metadata *next;  // pointer to the next file data
}

struct __files_t {
	unsigned int  n_files;        // n of opened files
	file_metadata *filemd_lhead;  // list of open files - HEAD
	file_metadata *filemd_ltail;  // list of open files - TAIL
}

static int file_metadata_new(struct file_metadata *data)
{
	struct file_metadata *new_data;

	new_data = malloc(sizeof(struct file_metadata));
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

static int file_metadata_open(struct file_metadata *data, const char *filepath)
{
	strncpy(new_file->fname, filepath, sizeof(new_file->fname));
	new_file->fd = open(new_file->fname, O_CREAT);
	if ( new_file->fd < 0 )
		return -1;

	return 0;
}

static int file_metadata_destroy(struct file_metadata *data)
{
	close(fd);
	free(data);
	data = NULL;
	return 0;
}

/**
 * Returns the index for the opened file; on error, returns -1.
 */
static int __files_open(struct __files_t *files, const char *filepath)
{
	struct file_metadata *new_file;
	struct file_metadata *cur_fdata;
	int findex = 0;

	/*
	 * Check if the file is not already opened.
	 */
	cur_fdata = files->filemd_lhead;
	while ( cur_fdata ) {
		if ( !strncmp(cur_fdata->fname, filepath, sizeof(cur_fdata->fname)) )
			return findex;
		findex++;
		cur_fdata = cur_fdata->next;
	}

	/*
	 * File not opened, proceed.
	 */

	/*
	 * Create new metadata for file.
	 */
	if ( file_metadata_new(new_file) )
		return -1;

	/*
	 * Open file, storing file descriptor in structure.
	 */
	if ( file_metadata_open(new_file, filepath) )
		return -1;

	/*
	 * Put opened file in the open files list.
	 */
	if ( files->n_files == 0 ) files->filemd_lhead = new_file;
	files->filemd_ltail->next = new_file;
	files->filemd_ltail = new_file;

	findex = files->n_files;
	files->n_files++;

	return findex;
}

static int __files_close(struct __files_t *files, unsigned int index)
{
	struct file_metadata *data;
	struct file_metadata *data_prev;
	unsigned int i;

	if ( index > files->n_files )
		return -1;

	data_prev = NULL;
	data = (struct file_metadata *) files->filemd_lhead;
	for ( i = 0; i <= index; i++ ) {
		data_prev = data;
		data = data->next;
	}

	if ( data_prev )
		data_prev->next = data->next;
	else
		files->filemd_lhead = data->next;

	/*
	 * If this file was the last item in the list, also update the tail pointer.
	 */
	if ( !data->next ) files->filemd_ltail = data_prev;

	file_metadata_destroy(data);

	files->n_files--;

	return 0;
}

int files_new(files_t f)
{
	struct __files_t *newf;

	newf = malloc(sizeof(struct __files_t));
	if ( !newf )
		return -1;

	newf->n_files = 0;
	newf->filemd_lhead = NULL;
	newf->filemd_ltail = NULL;
	f = (files_t) newf;

	return 0;
}

int files_destroy(files_t f)
{
	struct __files_t *files;
	unsigned int index;

	files = (struct __files_t *) f;

	if ( (files->n_files > 0) && (files->filemd_lhead) )
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

