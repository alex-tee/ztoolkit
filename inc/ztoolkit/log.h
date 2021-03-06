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

/**
 * \file
 *
 * Logging utilities.
 */

#ifndef __Z_TOOLKIT_LOG_H__
#define __Z_TOOLKIT_LOG_H__

typedef enum ZtkLogLevel
{
  ZTK_LOG_LEVEL_DEBUG,
  ZTK_LOG_LEVEL_MESSAGE,
  ZTK_LOG_LEVEL_WARNING,
  ZTK_LOG_LEVEL_ERROR,
  ZTK_LOG_LEVEL_OFF,
} ZtkLogLevel;

/**
 * Sets the log level.
 */
void
ztk_log_set_level (
  ZtkLogLevel level);

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
  ...);

#define ztk_debug(...) \
  ztk_log (__func__, ZTK_LOG_LEVEL_DEBUG, \
    __VA_ARGS__)

#define ztk_message(...) \
  ztk_log (__func__, ZTK_LOG_LEVEL_MESSAGE, \
    __VA_ARGS__)

#define ztk_warning(...) \
  ztk_log (__func__, ZTK_LOG_LEVEL_WARNING, \
    __VA_ARGS__)

#define ztk_error(...) \
  ztk_log (__func__, ZTK_LOG_LEVEL_ERROR, \
    __VA_ARGS__)

#endif
