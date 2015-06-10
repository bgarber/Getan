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

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include <getan_filebuf.h>

/*
 * Taken from the Ext4 definitions; I don't know if this works for every file
 * system in the world, but I think it does.
 */
#define MAX_FILENAME_LENGTH 255

/*
 * Arbitrary defined buffer size; research for better options.
 */
#define MAX_CHARS_IN_BUFFER 2048

struct filebuf_priv {
	char        *fpath;                     // file path
	char        fname[MAX_FILENAME_LENGTH]; // file name
	struct stat file_st;                    // system file status
	int         fd;                         // file descriptor
	char        *fchars;                    // file chars
};

static getan_error __filebuf_init(void **gb_priv)
{
	struct filebuf_priv *priv;

	priv = malloc(sizeof(struct filebuf_priv));
	if ( !priv ) return GETAN_CREATE_FAIL;

	priv->fpath = NULL;
	memset(priv->fname, 0, sizeof(priv->fname));
	priv->fd = -1;
	priv->fchars = NULL;

	(*gb_priv) = priv;

	return GETAN_SUCCESS;
}

static getan_error __filebuf_destroy(void *gb_priv)
{
	struct filebuf_priv *priv = (struct filebuf_priv *)gb_priv;
	munmap(priv->fchars, priv->file_st.st_size);
	close(priv->fd);
	free(priv);
	priv = NULL;
	return GETAN_SUCCESS;
}

static getan_error __filebuf_open(struct filebuf_priv *priv,
		const char *filepath, size_t plen)
{
	if ( (!filepath) || (plen > sizeof(priv->fname)) )
		return GETAN_OPEN_FAIL;

	priv->fd = open(filepath, O_CREAT);
	if ( priv->fd < 0 )
		return GETAN_OPEN_FAIL;

	if ( fstat(priv->fd, &priv->file_st) < 0 )
		return GETAN_OPEN_FAIL;

	priv->fchars = mmap(NULL, priv->file_st.st_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE, priv->fd, 0);
	if ( priv->fchars == MAP_FAILED )
		return GETAN_OPEN_FAIL;

	strncpy(priv->fname, filepath, sizeof(priv->fname));

	return GETAN_SUCCESS;
}

static getan_error __filebuf_call(void *gb_priv, unsigned int method,
		void *parm, size_t plen)
{
	struct filebuf_priv *priv = (struct filebuf_priv *)gb_priv;

	if ( !priv ) return GETAN_NO_PRIV;

	switch ( method ) {
		case FILEBUF_OPEN:
			return __filebuf_open(priv, (char *)parm, plen);
	}

	return GETAN_UNKNOWN_METHOD;
}

static getan_error __filebuf_get(void *priv, unsigned int attr, void *data,
		size_t *dlen)
{
	struct filebuf_priv *priv = (struct filebuf_priv *)gb_priv;

	if ( !priv ) return GETAN_NO_PRIV;

	switch ( attr ) {
		case FILEBUF_CONTENT:
			data = priv->fchars;
			(*dlen) = priv->file_st.st_size;
			break;
	}

	return GETAN_SUCCESS;
}

static struct getan_buffer_cb filebuf_cb = {
	.init = __filebuf_init,
	.destroy = __filebuf_destroy,
	.call = __filebuf_call,
	.get = __filebuf_get,
	.set = NULL,
};

getan_error getan_filebuf_create(struct getan_buffer *gb)
{
	struct filebuf_priv *priv = NULL;
	getan_error ret;

	ret = __filebuf_init((void **)&priv);
	ret |= getan_buffer_setup(gb, GETAN_BUFFER_FILEIO, &filebuf_cb, priv);

	return ret;
}

