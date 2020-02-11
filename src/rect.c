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

#include "ztoolkit/math.h"
#include "ztoolkit/rect.h"

int
ztk_rect_is_equal (
  ZtkRect * src,
  ZtkRect * dest)
{
  return
    math_doubles_equal (
      src->x, dest->x) &&
    math_doubles_equal (
      src->y, dest->y) &&
    math_doubles_equal (
      src->width, dest->width) &&
    math_doubles_equal (
      src->height, dest->height);
}

void
ztk_rect_copy (
  ZtkRect * dest,
  ZtkRect * src)
{
  dest->x = src->x;
  dest->y = src->y;
  dest->width = src->width;
  dest->height = src->height;
}
