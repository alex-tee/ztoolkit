/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of ZToolkit
 *
 * ZToolkit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ZToolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU General Affero Public License
 * along with ZToolkit.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include <ztoolkit/log.h>

/* ANSI color codes */
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define BOLD "\x1b[1m"

static ZtkLogLevel ztk_log_level =
  ZTK_LOG_LEVEL_WARNING;

/**
 * Fills in the timestamp as a string into \ref buf.
 */
static void
get_timestamp (
  char * buf)
{
  struct timeval curTime;
  gettimeofday(&curTime, NULL);
  int milli = curTime.tv_usec / 1000;

  char buffer [80];
  strftime (
    buffer, 80, "%H:%M:%S",
    localtime (&curTime.tv_sec));

  sprintf(buf, "%s:%03d", buffer, milli);
}

/**
 * Sets the log level.
 */
void
ztk_log_set_level (
  ZtkLogLevel level)
{
  ztk_log_level = level;
}

/**
 * Logs a message.
 *
 * @param func Function name.
 * @param level Log level.
 * @param format The format of the message to log.
 */
void
ztk_log (
  const char * func,
  ZtkLogLevel  level,
  const char * format,
  ...)
{
  if (level < ztk_log_level)
    return;

  va_list arg;

  char buf[6000] = "** ";

  switch (level)
    {
    case ZTK_LOG_LEVEL_DEBUG:
      strcat ( buf, BOLD COLOR_CYAN "DEBUG ");
      break;
    case ZTK_LOG_LEVEL_MESSAGE:
      strcat (
        buf, BOLD COLOR_GREEN "MESSAGE ");
      break;
    case ZTK_LOG_LEVEL_WARNING:
      strcat (
        buf, BOLD COLOR_YELLOW "WARNING ");
      break;
    case ZTK_LOG_LEVEL_ERROR:
      strcat (
        buf, BOLD COLOR_RED "ERROR ");
      break;
    default:
      break;
    }

  /* print the function name */
  char func_part[600];
  sprintf (func_part, "(%s)" COLOR_RESET ": ", func);
  strcat (buf, func_part);

  /* get current time as string*/
  char cur_time[200];
  get_timestamp (cur_time);

  strcat (buf, cur_time);
  strcat (buf, ": ");

  /* format message */
  char log_msg[6000];
  va_start (arg, format);
  vsprintf (log_msg, format, arg);
  va_end (arg);

  strcat (buf, log_msg);
  fprintf (stderr, "%s\n", buf);
}
