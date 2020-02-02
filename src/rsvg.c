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

#include "ztoolkit_config.h"

#ifdef HAVE_RSVG

#include <ztoolkit/ztk.h>

#include <librsvg/rsvg.h>

/**
 * Loads an SVG from an absolute path.
 *
 * @return An rsvg handle, or NULL if failed.
 */
ZtkRsvgHandle *
ztk_rsvg_load_svg (
  const char * abs_path)
{
  GFile * file =
    g_file_new_for_path (abs_path);
  GError * err = NULL;
  RsvgHandle * handle =
    rsvg_handle_new_from_gfile_sync (
      file, RSVG_HANDLE_FLAGS_NONE, NULL, &err);
  if (err)
    {
      ztk_error (
        "An error occurred parsing the SVG file at "
        "%s: %s", abs_path);
      g_object_unref (file);
      return NULL;
    }
  g_object_unref (file);

  /* common values are 75, 90, 300 */
  rsvg_handle_set_dpi (handle, 300);

  return (ZtkRsvgHandle *) handle;
}

/**
 * Gets the width of the svg.
 */
int
ztk_rsvg_get_width (
  ZtkRsvgHandle * handle)
{
  RsvgDimensionData dim;
  rsvg_handle_get_dimensions (
    (RsvgHandle *) handle, &dim);
  return dim.width;
}

/**
 * Gets the height of the svg.
 */
int
ztk_rsvg_get_height (
  ZtkRsvgHandle * handle)
{
  RsvgDimensionData dim;
  rsvg_handle_get_dimensions (
    (RsvgHandle *) handle, &dim);
  return dim.height;
}

/**
 * Draws the SVG on the current cairo context.
 *
 * @return 0 if successful, non-zero if failed.
 */
int
ztk_rsvg_draw (
  ZtkRsvgHandle * handle,
  cairo_t *       cr,
  ZtkRect *       rect)
{
  RsvgRectangle viewport = {
    rect->x, rect->y, rect->width, rect->height };
  GError * err = NULL;
  rsvg_handle_render_document (
    (RsvgHandle *) handle, cr, &viewport, &err);
  if (err)
    {
      return -1;
    }

  return 0;
}

#endif // HAVE_RSVG
