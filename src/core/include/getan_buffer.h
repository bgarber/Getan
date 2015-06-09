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

#ifndef GETAN_BUFFER_H
#define GETAN_BUFFER_H

#include <getan_errors.h>

/**
 * \enum getan_buffer_type
 * Declaration of built-in buffer types.
 */
typedef enum {
	GETAN_BUFFER_NOT_USED,
	GETAN_BUFFER_FILEIO,
	GETAN_BUFFER_SHELL,
	GETAN_BUFFER_DIRLIST,
} getan_buftype;

/**
 * \struct getan_buffer_cb
 * Generic buffer callbacks.
 *
 * init    private data constructor
 * destroy private data destructor
 * get     get some data from priv
 * set     set some data in to the priv
 */
struct getan_buffer_cb {
	getan_error (*init)(void *priv);
	getan_error (*destroy)(void *priv);
	getan_error (*call)(void *priv, unsigned int met, void *parm, size_t plen);
	getan_error (*get)(void *priv, void *data);
	getan_error (*set)(void *priv, void *data, size_t dlen);
};

/**
 * \struct getan_buffer
 * Opaque struct to a Getan buffer.
 */
struct getan_buffer;

/**
 * \brief Creates a new buffer.
 *
 * This function will allocate and initialize a new EMPTY Getan buffer.
 *
 * \return a pointer to a getan_buffer; or NULL in case of error.
 */
struct getan_buffer * getan_buffer_new();

/**
 * \brief Destroy a buffer.
 *
 * This function will destroy Getan buffer. This function must destroy the
 * private data from the buffer type.
 *
 * \param gb The buffer to destroy.
 *
 * \return  0 on success
 * \return -1 on error
 */
int getan_buffer_destroy(struct getan_buffer *gb);

/**
 * \brief Setup a buffer.
 *
 * This function intends to set up an already created buffer to use it with an
 * specific type of buffer.
 *
 * \param gb   The getan_buffer to update.
 * \param type The type of this getan_buffer.
 * \param cb   The callbacks for this getan_buffer.
 *
 * \return  0 on success
 * \return -1 on error
 */
int getan_buffer_setup(struct getan_buffer *gb, getan_buftype type,
		struct getan_buffer_cb *cb, void *priv);

/**
 * \brief Check if the buffer is used.
 *
 * This function will verify if a buffer is used or not.
 *
 * \param gb   Pointer to a getan_buffer
 *
 * \return  0 on success
 * \return -1 on error
 */
int getan_buffer_is_used(struct getan_buffer *gb);

/**
 * \brief Call callback.
 *
 * This function will call the callback function "call" for the buffer sending
 * its private data. This works like an "ioctl"; if you need more than one
 * parameter to be sent, declare it in a struct and send the size of this struct
 * in the last parameter.
 *
 * \param gb     Pointer to a getan_buffer
 * \param method Method to be called on the private data
 * \param parm   The parameter(s) to be sent
 * \param plen   Size of the parameter(s)
 *
 * \return  0 on success
 * \return -1 on error
 */
getan_error getan_buffer_cb_call(struct getan_buffer *gb, unsigned int method,
		void *parm, size_t plen);

#endif //GETAN_BUFFER_H

