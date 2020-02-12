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

#define TITLE_BAR_HEIGHT 32

static void
draw_cb (
  ZtkWidget * widget,
  cairo_t *   cr,
  ZtkRect *   draw_rect,
  void *      data)
{
  ZtkDialog * self = (ZtkDialog *) widget;

  double x = self->internal_rect.x;
  double y = self->internal_rect.y;
  double width = self->internal_rect.width;
  double height = self->internal_rect.height;

  /* draw modal bg */
  cairo_set_source_rgba (
    cr, 0, 0, 0, 0.4);
  cairo_rectangle (
    cr, widget->rect.x, widget->rect.y,
    widget->rect.width, widget->rect.height);
  cairo_fill (cr);

  /* draw bg */
  cairo_set_source_rgba (
    cr, 0.2, 0.2, 0.2, 1);
  cairo_rectangle (
    cr, x, y,
    width, height);
  cairo_fill (cr);

  /* draw frame */
  cairo_set_source_rgba (
    cr, 1, 1, 1, 0.5);
  cairo_set_line_width (
    cr, 2);
  cairo_rectangle (
    cr, x, y,
    width, height);
  cairo_stroke (cr);

  /* draw title line */
  cairo_set_source_rgba (
    cr, 1, 1, 1, 1);
  cairo_set_line_width (
    cr, 3);
  cairo_move_to (
    cr, x,
    y + TITLE_BAR_HEIGHT);
  cairo_line_to (
    cr, x + width,
    y + TITLE_BAR_HEIGHT);
  cairo_stroke (cr);

  /* draw title */
  cairo_text_extents_t extents;
  cairo_set_font_size (cr, 14);
  cairo_text_extents (
    cr, self->title, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT / 2 +
     extents.height / 2);
  cairo_show_text (cr, self->title);

  double avail_height =
    height - TITLE_BAR_HEIGHT;
  double avail_height_per_str =
    avail_height / 4;

  cairo_set_font_size (cr, 12);

  /* draw ver */
  cairo_text_extents (
    cr, self->version, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT +
     avail_height_per_str / 2 + extents.height / 2);
  cairo_show_text (cr, self->version);

  /* draw copyright */
  cairo_text_extents (
    cr, self->copyright, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT + avail_height_per_str +
     avail_height_per_str / 2 + extents.height / 2);
  cairo_show_text (cr, self->copyright);

  /* draw text */
  cairo_text_extents (
    cr, self->text, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT +
      avail_height_per_str * 2 + extents.height / 2);
  cairo_show_text (cr, self->text);

  /* draw license */
  cairo_set_font_size (cr, 10);
  const char * license1 =
    "This program comes with absolutely no "
    "warranty.";
  const char * license2 =
    "See the GNU Affero General Public License, "
    "version 3 or later for details.";
  cairo_text_extents (
    cr, license1, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT +
      avail_height_per_str * 2 +
      avail_height_per_str / 2 +
      avail_height_per_str / 2 + extents.height / 2);
  cairo_show_text (cr, license1);
  cairo_text_extents (
    cr, license2, &extents);
  cairo_move_to (
    cr,
    (x + width / 2) -
      extents.width / 2,
    y + TITLE_BAR_HEIGHT +
      avail_height_per_str * 3 +
      avail_height_per_str / 2 + extents.height / 2);
  cairo_show_text (cr, license2);
}

static void
on_close_btn_clicked (
  ZtkWidget * widget,
  void *      data)
{
  ZtkWidget * self = (ZtkWidget *) data;
  ztk_app_remove_widget (
    widget->app, widget);
  ztk_app_remove_widget (
    widget->app, self);
}

static void
close_btn_draw_cb (
  ZtkWidget * widget,
  cairo_t *   cr,
  ZtkRect *   draw_rect,
  void *      data)
{
  const double padding = 4;
  cairo_set_source_rgba (
    cr, 0.2, 0.2, 0.2, 1);
  cairo_move_to (
    cr,
    widget->rect.x + padding,
    widget->rect.y + padding);
  cairo_line_to (
    cr,
    widget->rect.x + widget->rect.width - padding,
    widget->rect.y + widget->rect.height - padding);
  cairo_move_to (
    cr,
    widget->rect.x + widget->rect.width - padding,
    widget->rect.y + padding);
  cairo_line_to (
    cr, widget->rect.x + padding,
    widget->rect.y + widget->rect.height - padding);
  cairo_stroke (cr);
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
  ZtkApp *        app,
  ZtkRect *       modal_rect,
  ZtkRect *       rect,
  void *          data)
{
  ZtkDialog * self = calloc (1, sizeof (ZtkDialog));
  ZtkWidget * widget = (ZtkWidget *) self;
  ztk_widget_init (
    (ZtkWidget *) self, ZTK_WIDGET_TYPE_DIALOG,
    modal_rect, update_cb, draw_cb, free_cb);

  self->internal_rect = *rect;

  const double padding = 1;
  ZtkRect close_btn_rect = {
    rect->x + rect->width + padding -
      (TITLE_BAR_HEIGHT),
    rect->y + padding,
    TITLE_BAR_HEIGHT - padding * 2,
    TITLE_BAR_HEIGHT - padding * 2 };
  self->close_btn =
    ztk_button_new (
      &close_btn_rect,
      (ZtkWidgetActivateCallback)
      on_close_btn_clicked, self);
  ZtkColor normal;
  ztk_color_parse_hex (
    &normal, "#908888");
  ZtkColor hover;
  ztk_color_parse_hex (
    &hover, "#CC575D");
  ZtkColor click;
  ztk_color_parse_hex (
    &click, "#FF4D4D");
  ztk_button_set_background_colors (
    self->close_btn, &normal, &hover, &click);
  ztk_button_make_custom (
    self->close_btn, close_btn_draw_cb);
  ztk_app_add_widget (
    app, (ZtkWidget *) self->close_btn, 800);

  widget->user_data = data;

  return self;
}

void
ztk_dialog_make_about (
  ZtkDialog *     self,
  const char *    title,
  const char *    version,
  const char *    copyright,
  ZtkDialogAboutLicense license,
  const char *    text)
{
  self->type = ZTK_DIALOG_ABOUT;
  strcpy (self->title, title);
  strcpy (self->text, text);
  strcpy (self->version, version);
  strcpy (self->copyright, copyright);
  self->license = license;
}
