/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>

 * This file is part of ZToolkit

 * ZToolkit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * ZToolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with ZToolkit.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __Z_TOOLKIT_TESTS_HELPER_H__
#define __Z_TOOLKIT_TESTS_HELPER_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ztoolkit/log.h>

#define ztk_assert(x) \
  if (!(x)) \
    { \
      ztk_error ("Assertion failed: %s", #x); \
      exit (1); \
    }

int
str_endswith (
  const char *s, const char *t)
{
  size_t ls = strlen(s); // find length of s
  size_t lt = strlen(t); // find length of t
  if (ls >= lt)  // check if t can fit in s
  {
      // point s to where t should start and compare the strings from there
      return (0 == memcmp(t, s + (ls - lt), lt));
  }
  return 0; // t was longer than s
}

#endif
