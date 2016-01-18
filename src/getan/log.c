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


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include "log.h"

static int debug;
static int verbose;

static void vlog(int pri, const char *fmt, va_list ap)
{
    char *nfmt;

    if ( debug ) {
        /* best effort in out of mem situations */
        if ( asprintf(&nfmt, "%s\n", fmt) == -1 ) {
            vfprintf(stderr, fmt, ap);
            fprintf(stderr, "\n");
        } else {
            vfprintf(stderr, nfmt, ap);
            free(nfmt);
        }
        fflush(stderr);
    } else
        vsyslog(pri, fmt, ap);
}

void log_init(int ndebug)
{
    extern char *__progname;

    debug = ndebug;
    verbose = ndebug;

    if ( !debug )
        openlog(__progname, LOG_PID | LOG_NDELAY, LOG_USER);
}

void log_exit()
{
    closelog();
}

void log_verbose(int v)
{
    verbose = v;
}

void logit(int pri, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vlog(pri, fmt, ap);
    va_end(ap);
}

void log_err(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_ERR, emsg, ap);
    va_end(ap);
}

void log_warn(const char *emsg, ...)
{
    char *nfmt;
    va_list ap;

    /* best effort to even work in out of memory situations */
    if ( emsg == NULL )
        logit(LOG_CRIT, "%s", strerror(errno));
    else {
        va_start(ap, emsg);

        if ( asprintf(&nfmt, "%s: %s", emsg, strerror(errno)) == -1 ) {
            /* we tried it... */
            vlog(LOG_CRIT, emsg, ap);
            logit(LOG_CRIT, "%s", strerror(errno));
        } else {
            vlog(LOG_CRIT, nfmt, ap);
            free(nfmt);
        }

        va_end(ap);
    }
}

void log_warnx(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_CRIT, emsg, ap);
    va_end(ap);
}

void log_info(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_INFO, emsg, ap);
    va_end(ap);
}

void log_debug(const char *emsg, ...)
{
    va_list ap;

    if ( verbose ) {
        va_start(ap, emsg);
        vlog(LOG_DEBUG, emsg, ap);
        va_end(ap);
    }
}

