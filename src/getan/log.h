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

#ifndef LOG_H
#define LOG_H

void log_init(int ndebug);
void log_exit();

void log_verbose(int v);

void logit(int pri, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

void log_err(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void log_warn(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void log_warnx(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void log_info(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void log_debug(const char *emsg, ...) __attribute__((format(printf, 1, 2)));

#endif // LOG_H

