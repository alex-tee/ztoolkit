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

/**
 * \file
 *
 * Ztoolkit base widget.
 */

#ifndef __Z_TOOLKIT_ZTK_WIDGET_H__
#define __Z_TOOLKIT_ZTK_WIDGET_H__

#include <ztoolkit/types.h>

#include <cairo.h>
#include <pugl/pugl.h>

typedef struct ZtkApp ZtkApp;

/**
 * @addtogroup ztoolkit
 *
 * @{
 */

/**
 * Flags to use in the event callbacks.
 */
typedef enum ZtkEventChain
{
  /** Propagate the event down to the next hit
   * widget. */
  ZTK_EVENT_CHAIN_CONTINUE,
  /** Don't propagate the event. */
  ZTK_EVENT_CHAIN_STOP,
} ZtkEventChain;

/**
 * State of the widget.
 */
typedef enum ZtkWidgetState
{
  /** Normal state. */
  ZTK_WIDGET_STATE_NORMAL = 1,

  ZTK_WIDGET_STATE_HOVERED = 1 << 1,
  ZTK_WIDGET_STATE_SELECTED = 1 << 2,
  ZTK_WIDGET_STATE_PRESSED = 1  << 3,
} ZtkWidgetState;

typedef enum ZtkWidgetType
{
  ZTK_WIDGET_TYPE_NONE,
  ZTK_WIDGET_TYPE_LABEL,
  ZTK_WIDGET_TYPE_BUTTON,
  ZTK_WIDGET_TYPE_KNOB,
  ZTK_WIDGET_TYPE_KNOB_WITH_LABEL,
  ZTK_WIDGET_TYPE_DRAWING_AREA,
  ZTK_WIDGET_TYPE_COMBO_BOX,
  ZTK_WIDGET_TYPE_CONTROL,
} ZtkWidgetType;

typedef struct ZtkWidget ZtkWidget;

/**
 * Prototype for generic callbacks.
 *
 * @param widget The ZtkWidget instance.
 * @param data User data passed when instantiating the drawing area.
 */
typedef void (*ZtkWidgetGenericCallback) (
  ZtkWidget * widget,
  void *      data);

/**
 * Prototype for draw callbacks.
 *
 * @param widget The ZtkWidget instance.
 * @param cr The cairo context to draw to.
 * @param data User data passed during
 *   instantiation.
 */
typedef void (*ZtkWidgetDrawCallback) (
  ZtkWidget * widget,
  cairo_t *   cr,
  void *      data);

/**
 * Prototype for activate callbacks.
 *
 * This should be used on widgets that can be
 * activated, like combobox elements or buttons.
 *
 * @param widget The ZtkWidget instance.
 * @param data User data passed during
 *   instantiation.
 */
typedef void (*ZtkWidgetActivateCallback) (
  ZtkWidget * widget,
  void *      data);

/**
 * Button event callback prototype.
 *
 * @return If the next hit widget on the stack
 *   should receive the event (1) or if the chain
 *   should stop here (0).
 */
typedef int (*ZtkWidgetButtonEventCallback) (
  ZtkWidget *             widget,
  const PuglEventButton * btn,
  void *                  data);

/**
 * Motion event callback prototype.
 *
 * @return If the next hit widget on the stack
 *   should receive the event (1) or if the chain
 *   should stop here (0).
 */
typedef int (*ZtkWidgetMotionEventCallback) (
  ZtkWidget *             widget,
  const PuglEventMotion * event,
  void *                  data);

/**
 * Base widget.
 */
typedef struct ZtkWidget
{
  /** Pointer back to app. */
  ZtkApp *          app;

  /** Rectangle. */
  ZtkRect           rect;

  ZtkWidgetState    state;

  /**
   * The type this widget is.
   */
  ZtkWidgetType     type;

  /** Update callback (called right before drawing)
   * (required. */
  ZtkWidgetGenericCallback update_cb;

  /** Draw callback (required). */
  ZtkWidgetDrawCallback draw_cb;

  /** Free callback (required). */
  ZtkWidgetGenericCallback free_cb;

  /** Dispose callback, called right before freeing
   * (optional). */
  ZtkWidgetGenericCallback dispose_cb;

  /** Button event callback (optional). */
  ZtkWidgetButtonEventCallback button_event_cb;

  /** Button event callback (optional). */
  int (*key_event_cb) (ZtkWidget *, const PuglEventKey *);

  /** Enter/leave event callback (optional). */
  int (*crossing_event_cb) (ZtkWidget *, const PuglEventCrossing *);

  /** Motion event callback (optional). */
  ZtkWidgetMotionEventCallback motion_event_cb;

  /** Scroll event callback (optional). */
  int (*scroll_event_cb) (ZtkWidget *, const PuglEventScroll *);

  /* note: Ignore these below for now. */

  /** Visible or not. */
  int               visible;

  /**
   * Z-axis.
   *
   * Widgets with lower z values will be drawn at
   * the bottom.
   */
  int               z;

  /** Set to 1 to redraw. */
  int               redraw;

  /** Last rectangle drawn in. */
  ZtkRect           last_draw_rect;

  /** Cairo caches. */
  cairo_t *         cached_cr;
  cairo_surface_t * cached_surface;

  /** User data. */
  void *            user_data;

} ZtkWidget;

/**
 * Inits a new ZWidget.
 *
 * To be called from inheriting structs.
 */
void
ztk_widget_init (
  ZtkWidget *       self,
  ZtkWidgetType     type,
  ZtkRect *        rect,
  ZtkWidgetGenericCallback update_cb,
  ZtkWidgetDrawCallback draw_cb,
  ZtkWidgetGenericCallback free_cb);

/**
 * Returns if the widget is hit by the given
 * coordinates.
 */
int
ztk_widget_is_hit (
  ZtkWidget * self,
  double      x,
  double      y);

/**
 * Sets the user data.
 */
void
ztk_widget_set_user_data (
  ZtkWidget * self,
  void *      data);

/**
 * Shows or hides the widget.
 */
void
ztk_widget_set_visible (
  ZtkWidget * self,
  int         visible);

/**
 * @}
 */

#endif
