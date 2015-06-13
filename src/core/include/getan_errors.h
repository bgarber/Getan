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

#ifndef GETAN_ERRORS_H
#define GETAN_ERRORS_H

typedef enum {
	GETAN_SUCCESS,
	GETAN_GEN_FAIL,
	GETAN_OPEN_FAIL,
	GETAN_CREATE_FAIL,
	GETAN_UNKNOWN_METHOD,
	GETAN_NO_PRIV,
	GETAN_NO_LIST,
} getan_error;

#endif

