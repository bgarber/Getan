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

#include "logger.h"

#include <time.h>

FILE *flog = NULL;

void logger_open()
{
    if ( flog == NULL ) {
        flog = fopen("getan.log", "w+");
        if ( !flog )
            perror("Could not create getan.log");
    }
}

void logger_close()
{
    if ( flog != NULL ) {
        fflush(flog);
        fclose(flog);
        flog = NULL;
    }
}

int logger_log(const char *fmt, ...)
{
    char timestamp[128] = { '\0' };
    char line[128];
    va_list argp;
    time_t t;
    int r;

    r = 0;

    t = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%c", localtime(&t));

    va_start(argp, fmt);
    vsnprintf(line, sizeof(line), fmt, argp);
    va_end(argp);

    r = fprintf(flog, "%s [Getan] %s", timestamp, line);
    fflush(flog);


    return r;
}

