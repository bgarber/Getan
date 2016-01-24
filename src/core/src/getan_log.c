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
#include <time.h>

#include <getan_log.h>

static int debug;
static int verbose;

static int translate_prio(int prio)
{
    int r;

    switch ( prio ) {
    case LOG_EMERG:
    case LOG_ALERT:
    case LOG_CRIT:
    case LOG_ERR:
        r = 0;
        break;
    case LOG_WARNING:
    case LOG_NOTICE:
        r = 1;
        break;
    case LOG_INFO:
        r = 2;
        break;
    case LOG_DEBUG:
        r = 3;
        break;
    }

    return r;
}

static void vlog(int pri, const char *fmt, va_list ap)
{
    char *nfmt;
    char *prio_str[8] = {
        "[EMERGENCY]",
        "[ALERT]",
        "[CRITICAL]",
        "[ERROR]",
        "[WARNING]",
        "[NOTICE]",
        "[INFO]",
        "[DEBUG]"
    };

    if ( translate_prio(pri) <= verbose ) {
        /* best effort in out of mem situations */
        if ( asprintf(&nfmt, "%s %s\n", prio_str[pri], fmt) == -1 ) {
            vfprintf(stderr, fmt, ap);
            fprintf(stderr, "\n");
        } else {
            if ( debug )
                vfprintf(stderr, nfmt, ap);
            else
                vsyslog(pri, nfmt, ap);

            free(nfmt);
        }
    }
}

static void logit(int pri, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vlog(pri, fmt, ap);
    va_end(ap);
}

void getan_logverbose(int v)
{
    verbose = v;
}

void getan_loginit(int ndebug)
{
    extern char *__progname;

    debug = ndebug;
    verbose = 0;

    if ( !debug )
        openlog(__progname, LOG_PID | LOG_NDELAY, LOG_USER);

    tzset();
}

void getan_logexit()
{
    if ( !debug ) closelog();
}

void getan_logerr(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_ERR, emsg, ap);
    va_end(ap);
}

void getan_logwarn(const char *emsg, ...)
{
    char *nfmt;
    va_list ap;

    /* best effort to even work in out of memory situations */
    if ( emsg == NULL )
        logit(LOG_WARNING, "%s", strerror(errno));
    else {
        va_start(ap, emsg);

        if ( asprintf(&nfmt, "%s: %s", emsg, strerror(errno)) == -1 ) {
            /* we tried it... */
            vlog(LOG_WARNING, emsg, ap);
            logit(LOG_WARNING, "%s", strerror(errno));
        } else {
            vlog(LOG_WARNING, nfmt, ap);
            free(nfmt);
        }

        va_end(ap);
    }
}

void getan_logwarnx(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_WARNING, emsg, ap);
    va_end(ap);
}

void getan_loginfo(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_INFO, emsg, ap);
    va_end(ap);
}

void getan_logdebug(const char *emsg, ...)
{
    va_list ap;
    va_start(ap, emsg);
    vlog(LOG_DEBUG, emsg, ap);
    va_end(ap);
}

