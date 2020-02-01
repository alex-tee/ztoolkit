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
} ZtkLogLevel;

static int ztk_log_enabled = 1;

/**
 * Enables or disables logging.
 */
static inline void
ztk_log_set_enabled (
  int enabled)
{
  ztk_log_enabled = enabled;
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
  ...);

#define ztk_debug(msg) \
  ztk_log (__func__, ZTK_LOG_LEVEL_DEBUG, msg)

#define ztk_message(msg) \
  ztk_log (__func__, ZTK_LOG_LEVEL_MESSAGE, msg)

#define ztk_warning(msg) \
  ztk_log (__func__, ZTK_LOG_LEVEL_WARNING, msg)

#define ztk_error(msg) \
  ztk_log (__func__, ZTK_LOG_LEVEL_ERROR, msg)

#endif
