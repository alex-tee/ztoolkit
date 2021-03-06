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

#ifndef __ZTOOLKIT_RECT_H__
#define __ZTOOLKIT_RECT_H__

/**
 * Wrapper over PuglRect.
 */
typedef struct ZtkRect
{
  double x;
  double y;
  double width;
  double height;
} ZtkRect;

int
ztk_rect_is_equal (
  ZtkRect * src,
  ZtkRect * dest);

void
ztk_rect_copy (
  ZtkRect * dest,
  ZtkRect * src);

#endif
