/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of ZToolkit
 *
 * ZToolkit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ZToolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ZToolkit.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <float.h>

#include "helper.h"

#include <ztoolkit/ztk_color.h>

#define doubles_equal(a,b) \
  ((a) > (b) ? \
   (a) - (b) < DBL_EPSILON : \
   (b) - (a) < DBL_EPSILON)

/* for debugging */
#define print_color(cl) \
  ztk_error ("red %f", color.red); \
  ztk_error ("green %f", color.green); \
  ztk_error ("blue %f", color.blue)

int main (
  int argc, const char* argv[])
{
  ZtkColor color;
  ztk_color_parse_hex (&color, "#000000");
  ztk_assert (doubles_equal (color.red, 0.0));
  ztk_assert (doubles_equal (color.green, 0.0));
  ztk_assert (doubles_equal (color.blue, 0.0));

  ztk_color_parse_hex (&color, "#FFFFFF");
  ztk_assert (doubles_equal (color.red, 1.0));
  ztk_assert (doubles_equal (color.green, 1.0));
  ztk_assert (doubles_equal (color.blue, 1.0));

  ztk_color_parse_hex (&color, "#AA234F");
  ztk_assert (
    doubles_equal (color.red, 170 / 255.0));
  ztk_assert (
    doubles_equal (color.green, 35.0 / 255.0));
  ztk_assert (
    doubles_equal (color.blue, 79.0 / 255.0));

  return 0;
}

