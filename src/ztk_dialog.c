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
#include <string.h>

#include <ztoolkit/ztk.h>

static void
draw_cb (
  ZtkWidget * widget,
  cairo_t *   cr,
  ZtkRect *   draw_rect,
  void *      data)
{
  /*ZtkDialog * self = (ZtkDialog *) widget;*/

}

static void
update_cb (
  ZtkWidget * w,
  void *      data)
{
}

static void
free_cb (
  ZtkWidget * widget,
  void *      data)
{
  ZtkDialog * self = (ZtkDialog *) widget;

  free (self);
}

/**
 * Creates a new ZtkDialog.
 *
 * This must then be set to its type using the setters
 * below.
 */
ZtkDialog *
ztk_dialog_new (
  ZtkRect *       rect,
  void *          data)
{
  ZtkDialog * self = calloc (1, sizeof (ZtkDialog));
  ZtkWidget * widget = (ZtkWidget *) self;
  ztk_widget_init (
    (ZtkWidget *) self, ZTK_WIDGET_TYPE_DIALOG, rect,
    update_cb, draw_cb, free_cb);

  widget->user_data = data;

  return self;
}

void
ztk_dialog_make_about (
  ZtkDialog *     self,
  const char *    title,
  const char *    text)
{
  self->type = ZTK_DIALOG_ABOUT;
  strcpy (self->title, title);
  strcpy (self->text, text);
}
