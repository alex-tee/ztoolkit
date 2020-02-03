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

#ifndef __Z_TOOLKIT_ZTK_COMBO_BOX_H__
#define __Z_TOOLKIT_ZTK_COMBO_BOX_H__

#include "ztk.h"

/**
 * A combo box element.
 */
typedef struct ZtkComboBoxElement
{
  /** 1 if this is a separator. */
  int                       is_separator;

  /** Label to display. */
  char                      label[420];

  /** Function to call when activated. */
  ZtkWidgetActivateCallback activate_cb;

  /** Data specific to this element. */
  void *                    activate_cb_data;
} ZtkComboBoxElement;

/**
 * Combobox widget.
 */
typedef struct ZtkComboBox
{
  /** Base widget. */
  ZtkWidget         base;

  /** Parent widget to spawn on. */
  ZtkWidget *       parent;

  ZtkComboBoxElement elements[120];
  int               num_elements;

  char              font_name[180];

  double            font_size;

  /** Text color. */
  ZtkColor          text_normal_color;

  /** Text when hovered. */
  ZtkColor          text_hover_color;

  /** Text when hovered. */
  ZtkColor          text_click_color;

  /** Color of the frame around the combo box. */
  ZtkColor          frame_color;

  /** Background color of the whole combobox. */
  ZtkColor          bg_color;

  /** Color of separator elements. */
  ZtkColor          separator_color;

  /** Background color of the hovered element. */
  ZtkColor          hover_color;

  /** Background color of the clicked element. */
  ZtkColor          click_color;

  /** 1 if it the combobox should spawn upwards
   * instead of downards. */
  int               upwards;

  /** 1 if it the combobox should spawn backwards
   * (left) instead of forwards (right). */
  int               backwards;

  /** Hovered index. */
  int               hovered_idx;

} ZtkComboBox;

/**
 * Creates a new combobox.
 *
 * @param parent The parent widget to spawn on.
 * @param spawn_upwards Spawn upwards instead of
 *   downards.
 */
ZtkComboBox *
ztk_combo_box_new (
  ZtkWidget *  parent,
  int          spawn_upwards,
  int          spawn_backwards);

/**
 * @param data Data related to the current element
 *   to pass to the activate callback.
 */
void
ztk_combo_box_add_text_element (
  ZtkComboBox * self,
  const char *  label,
  ZtkWidgetActivateCallback activate_cb,
  void *        data);

void
ztk_combo_box_add_separator (
  ZtkComboBox * self);

void
ztk_combo_box_clear (
  ZtkComboBox * self);

#endif
