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

#ifndef GETAN_LOG_H
#define GETAN_LOG_H

void getan_loginit(int level);
void getan_logexit(void);

void getan_logverbose(int v);

void getan_logerr(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void getan_logwarn(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void getan_logwarnx(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void getan_loginfo(const char *emsg, ...) __attribute__((format(printf, 1, 2)));
void getan_logdebug(const char *emsg, ...) __attribute__((format(printf, 1, 2)));

#endif // GETAN_LOG_H

