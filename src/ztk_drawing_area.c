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

#include <stdlib.h>

#include "ztoolkit/ztk_drawing_area.h"

static void
ztk_drawing_area_update (
  ZtkWidget * widget,
  void *      data)
{
}

static void
ztk_drawing_area_free (
  ZtkWidget * widget,
  void *      data)
{
  ZtkDrawingArea * self = (ZtkDrawingArea *) widget;

  if (widget->dispose_cb)
    {
      widget->dispose_cb (
        widget, widget->user_data);
    }

  free (self);
}

/**
 * Creates a new ZtkDrawingArea.
 *
 * @param update_cb Optional callback to be called
 *   for updating the user data based on the current
 *   state of the widget. See ztk_knob.c for an
 *   example.
 * @param draw_cb Required callback to be called
 *   when the widget needs to redraw itself.
 * @param dispose_cb Optional callback to be called
 *   when disposing the widget. This will be called
 *   right before freeing the widget.
 * @param data User data.
 */
ZtkDrawingArea *
ztk_drawing_area_new (
  PuglRect *         rect,
  ZtkWidgetGenericCallback  update_cb,
  ZtkWidgetDrawCallback  draw_cb,
  ZtkWidgetGenericCallback  dispose_cb,
  void *             data)
{
  ZtkDrawingArea * self =
    calloc (1, sizeof (ZtkDrawingArea));
  ztk_widget_init (
    (ZtkWidget *) self, rect,
    update_cb ? update_cb : ztk_drawing_area_update,
    draw_cb,
    ztk_drawing_area_free);

  return self;
}
