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

#ifndef __ZTOOLKIT_RSVG_H__
#define __ZTOOLKIT_RSVG_H__

#include <cairo.h>

typedef void ZtkRsvgHandle;

/**
 * Loads an SVG from an absolute path.
 *
 * @return An rsvg handle, or NULL if failed.
 */
ZtkRsvgHandle *
ztk_rsvg_load_svg (
  const char * abs_path);

/**
 * Gets the width of the svg.
 */
int
ztk_rsvg_get_width (
  ZtkRsvgHandle * handle);

/**
 * Gets the height of the svg.
 */
int
ztk_rsvg_get_height (
  ZtkRsvgHandle * handle);

/**
 * Draws the SVG on the current cairo context.
 *
 * @return 0 if successful, non-zero if failed.
 */
int
ztk_rsvg_draw (
  ZtkRsvgHandle * handle,
  cairo_t *       cr,
  ZtkRect *       rect);

#endif // header guard
