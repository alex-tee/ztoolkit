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

#include "ztoolkit/ztk_widget.h"

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
  ZtkWidgetGenericCallback free_cb)
{
  self->rect = *rect;
  self->type = type;
  self->update_cb = update_cb;
  self->draw_cb = draw_cb;
  self->free_cb = free_cb;
  self->visible = 1;
}

/**
 * Returns if the widget is hit by the given
 * coordinates.
 */
int
ztk_widget_is_hit (
  ZtkWidget * self,
  double      x,
  double      y)
{
  return
    self->visible &&
    x >= self->rect.x &&
    x <= self->rect.x + self->rect.width &&
    y >= self->rect.y &&
    y <= self->rect.y + self->rect.height;
}

/**
 * Sets the user data.
 */
void
ztk_widget_set_user_data (
  ZtkWidget * self,
  void *      data)
{
  self->user_data = data;
}

/**
 * Shows or hides the widget.
 */
void
ztk_widget_set_visible (
  ZtkWidget * self,
  int         visible)
{
  self->visible = visible;
}
