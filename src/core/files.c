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

/*
 * Taken from the Ext4 definitions; I don't know if this works for every file
 * system in the world, but I think it does.
 */
#define MAX_FILENAME_LENGTH 255

/******************************************************************************
 *                   File item structures and functions.                      *
 ******************************************************************************/

struct file_item {
	const char *fpath; // file path
	const char fname[MAX_FILENAME_LENGTH]; // file name
	int        fd;     // file descriptor
	struct file_item *next;  // pointer to the next file data
}

static int file_item_new(struct file_item *data)
{
	struct file_item *new_data;

	new_data = malloc(sizeof(struct file_item));
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

static int file_item_open(struct file_item *data, const char *filepath)
{
	strncpy(new_file->fname, filepath, sizeof(new_file->fname));
	new_file->fd = open(new_file->fname, O_CREAT);
	if ( new_file->fd < 0 )
		return -1;

	return 0;
}

static int file_item_destroy(struct file_item *data)
{
	close(fd);
	free(data);
	data = NULL;
	return 0;
}


/******************************************************************************
 *                   File list structures and functions.                      *
 ******************************************************************************/

struct __files_list {
	unsigned int  n_files;        // n of opened files
	struct file_item *list_head;  // list of open files - HEAD
	struct file_item *list_tail;  // list of open files - TAIL
}

/**
 * Returns the index for the opened file; on error, returns -1.
 */
static int __files_open(struct __files_list *files, const char *filepath)
{
	struct file_item *new_file;
	struct file_item *cur_fdata;
	int findex = 0;

	/*
	 * Check if the file is not already opened.
	 */
	cur_fdata = files->list_head;
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
	if ( file_item_new(new_file) )
		return -1;

	/*
	 * Open file, storing file descriptor in structure.
	 */
	if ( file_item_open(new_file, filepath) )
		return -1;

	/*
	 * Put opened file in the open files list.
	 */
	if ( files->n_files == 0 ) files->list_head = new_file;
	files->list_tail->next = new_file;
	files->list_tail = new_file;

	findex = files->n_files;
	files->n_files++;

	return findex;
}

static int __files_close(struct __files_list *files, unsigned int index)
{
	struct file_item *data;
	struct file_item *data_prev;
	unsigned int i;

	if ( index > files->n_files )
		return -1;

	data_prev = NULL;
	data = (struct file_item *) files->list_head;
	for ( i = 0; i <= index; i++ ) {
		data_prev = data;
		data = data->next;
	}

	if ( data_prev )
		data_prev->next = data->next;
	else
		files->list_head = data->next;

	/*
	 * If this file was the last item in the list, also update the tail pointer.
	 */
	if ( !data->next ) files->list_tail = data_prev;

	file_item_destroy(data);

	files->n_files--;

	return 0;
}

int files_new(files_list f)
{
	struct __files_list *newf;

	newf = malloc(sizeof(struct __files_list));
	if ( !newf )
		return -1;

	newf->n_files = 0;
	newf->list_head = NULL;
	newf->list_tail = NULL;
	f = (files_list) newf;

	return 0;
}

int files_destroy(files_list f)
{
	struct __files_list *files;
	unsigned int index;

	files = (struct __files_list *) f;

	if ( (files->n_files > 0) && (files->list_head) )
		for ( index = 0; i < files->n_files; index++ ) {
			__files_close(files, index);
		}

	free(files);
	f = NULL;

	return 0;
}

int files_open(files_list f, const char *filepath)
{
	struct __files_list *files;

	files = (struct __files_list *) f;
	return __files_open(files, filepath);
}

int files_close(files_list f, unsigned int index)
{
	struct __files_list *files;

	files = (struct __files_list *) f;
	return __files_close(files, index);
}

