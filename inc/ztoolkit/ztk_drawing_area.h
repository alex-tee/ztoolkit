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
 * Widget for custom drawing.
 */

#ifndef __Z_TOOLKIT_ZTK_DRAWING_AREA_H__
#define __Z_TOOLKIT_ZTK_DRAWING_AREA_H__

#include "ztk_widget.h"

/**
 * @addtogroup ztoolkit
 *
 * @{
 */

/**
 * Drawing area widget.
 *
 * This is used for custom drawing.
 */
typedef struct ZtkDrawingArea
{
  /** Base widget. */
  ZtkWidget         base;

} ZtkDrawingArea;

/**
 * Creates a new ZtkDrawingArea.
 *
 * @param update_cb Optional callback to be called
 *   for updating the user data based on the current
 *   state of the widget. See ztk_knob.c for an
 *   example.
 * @param draw_cb Draw callback. This will be called
 *   when the widget needs to redraw itself.
 * @param dispose_cb Optional callback to be called
 *   when disposing the widget. This will be called
 *   right before freeing the widget.
 * @param data User data.
 */
ZtkDrawingArea *
ztk_drawing_area_new (
  ZtkRect *         rect,
  ZtkWidgetGenericCallback  update_cb,
  ZtkWidgetDrawCallback  draw_cb,
  ZtkWidgetGenericCallback  dispose_cb,
  void *             data);

/**
 * @}
 */

#endif
