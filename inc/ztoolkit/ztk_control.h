/*
 * Copyright (C) 2019-2020 Alexandros Theodotou <alex at zrythm dot org>
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

#ifndef __Z_TOOLKIT_ZTK_CONTROL_H__
#define __Z_TOOLKIT_ZTK_CONTROL_H__

#include "ztoolkit/ztk_widget.h"

typedef struct ZtkControl ZtkControl;

typedef void (*ZtkControlSetter) (
  ZtkControl * control,
  void *       object,
  float        val);

typedef float (*ZtkControlGetter) (
  ZtkControl * control,
  void *       object);

typedef enum ZtkControlDragMode
{
  ZTK_CTRL_DRAG_HORIZONTAL,
  ZTK_CTRL_DRAG_VERTICAL,
  ZTK_CTRL_DRAG_BOTH,
} ZtkControlDragMode;

/**
 * Generic control with custom drawing.
 */
typedef struct ZtkControl
{
  /** Base widget. */
  ZtkWidget         base;

  /** Getter. */
  ZtkControlGetter  getter;

  /** Setter. */
  ZtkControlSetter  setter;

  /** Object to call get/set with. */
  void *            object;

  /** Zero point 0.0-1.0. */
  float             zero;
  float             min;    ///< min value (eg. 1)
  float             max;    ///< max value (eg. 180)

  /** Drag mode. */
  ZtkControlDragMode drag_mode;

  /** Used during drags. */
  double            last_x;

  /** Used during drags. */
  double            last_y;

  /**
   * Relative mode or not.
   *
   * In relative mode, the movement is relative
   * to the amount that the cursor moved.
   *
   * In absolute mode, the value is set to where
   * the cursor is.
   */
  int               relative_mode;

  /** Sensitivity value (default 0.007f). */
  float             sensitivity;

} ZtkControl;

/**
 * Creates a new control.
 *
 * @param get_val Getter function.
 * @param set_val Setter function.
 * @param draw_cb Custom draw callback.
 * @param object Object to call get/set with.
 */
ZtkControl *
ztk_control_new (
  ZtkRect * rect,
  ZtkControlGetter get_val,
  ZtkControlSetter set_val,
  ZtkWidgetDrawCallback draw_cb,
  ZtkControlDragMode drag_mode,
  void * object,
  float  min,
  float  max,
  float  zero);

void
ztk_control_set_relative_mode (
  ZtkControl * self,
  int          on);

#endif
