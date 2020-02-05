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

#ifndef __Z_TOOLKIT_ZTK_BUTTON_H__
#define __Z_TOOLKIT_ZTK_BUTTON_H__

#include "ztoolkit/ztk_color.h"
#include "ztoolkit/ztk_widget.h"

typedef struct ZtkButton ZtkButton;

/**
 * Button type.
 */
typedef enum ZtkButtonType
{
  /** Button is a label. */
  ZTK_BTN_LBL,

  /** Button has 3 SVGs, one for each state (normal,
   * hover, press). */
  ZTK_BTN_SVG,

  /** Button will be drawn using user callback. */
  ZTK_BTN_CUSTOM,
} ZtkButtonType;

/**
 * Getter for whether the button is toggled or not.
 */
typedef int (*ZtkButtonToggledGetter) (
  ZtkButton * btn,
  void *      data);

/**
 * Button widget.
 */
typedef struct ZtkButton
{
  /** Base widget. */
  ZtkWidget         base;

  /** Label, if this is a label button. */
  char *            lbl;

  /** If this button is a toggle or not. */
  int               is_toggle;

  /** Getter to check if the button is toggled or not,
   * if toggle button. */
  ZtkButtonToggledGetter toggled_getter;

  /**
   * Activate callback.
   *
   * This will be called when the button is pressed
   * and released (on release).
   */
  ZtkWidgetActivateCallback activate_cb;

  /** Button type. */
  ZtkButtonType     type;

  /** Normal state SVG. */
  ZtkRsvgHandle *   normal_svg;

  /** Hovered SVG. */
  ZtkRsvgHandle *   hover_svg;

  /** Padding to add when using SVGs to control
   * their size. */
  int               hpadding;
  int               vpadding;

  /**
   * Clicked SVG.
   *
   * This will also be used for when toggled.
   */
  ZtkRsvgHandle *   clicked_svg;

  /** If this is 1, background colors will be drawn,
   * regardless if there is a \ref
   * ZtkButton.bg_draw_cb. */
  int                     has_bg_colors;

  ZtkColor          normal_color;
  ZtkColor          hovered_color;
  ZtkColor          clicked_color;

  /** Set to 1 while pressed, and the activate
   * callback will be fired when released. */
  int                     was_pressed;

  /** Custom draw callback for backgrounds. */
  ZtkWidgetDrawCallback  bg_draw_cb;

  /** Custom draw callback for completely custom
   * buttons. */
  ZtkWidgetDrawCallback  custom_draw_cb;

} ZtkButton;

/**
 * Creates a new ZtkButton.
 *
 * This must then be set to its type using the setters
 * below.
 */
ZtkButton *
ztk_button_new (
  ZtkRect *                 rect,
  ZtkWidgetActivateCallback activate_cb,
  void *                    data);

void
ztk_button_make_toggled (
  ZtkButton *            self,
  ZtkButtonToggledGetter toggled_getter);

/**
 * Makes a button with a label.
 */
void
ztk_button_make_labeled (
  ZtkButton *           self,
  const char *          label);

/**
 * Makes a button with SVGs.
 */
void
ztk_button_make_svged (
  ZtkButton *     self,
  int             hpadding,
  int             vpadding,
  ZtkRsvgHandle * svg_normal,
  ZtkRsvgHandle * svg_hover,
  ZtkRsvgHandle * svg_clicked);

/**
 * Makes a customly drawn button.
 */
void
ztk_button_make_custom (
  ZtkButton *           self,
  ZtkWidgetDrawCallback draw_cb);

void
ztk_button_set_background_colors (
  ZtkButton * self,
  ZtkColor *  normal,
  ZtkColor *  hovered,
  ZtkColor *  clicked);

/**
 * Add callback for drawing the background.
 */
void
ztk_button_add_background_callback (
  ZtkButton *           self,
  ZtkWidgetDrawCallback draw_cb);

#endif
