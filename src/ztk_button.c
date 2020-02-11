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
button_draw_cb (
  ZtkWidget * widget,
  cairo_t *   cr,
  ZtkRect *   draw_rect,
  void *      data)
{
  ZtkButton * self = (ZtkButton *) widget;

  ZtkWidgetState state = widget->state;
  if (self->has_bg_colors)
    {
      if ((state & ZTK_WIDGET_STATE_PRESSED) ||
          (self->is_toggle &&
             self->toggled_getter (
               self, widget->user_data)))
        {
          ztk_color_set_for_cairo (
            &self->clicked_color, cr);
        }
      else if (state & ZTK_WIDGET_STATE_HOVERED)
        {
          ztk_color_set_for_cairo (
            &self->hovered_color, cr);
        }
      else
        {
          ztk_color_set_for_cairo (
            &self->normal_color, cr);
        }
      cairo_rectangle (
        cr, widget->rect.x, widget->rect.y,
        widget->rect.width, widget->rect.height);
      cairo_fill (cr);
    }
  else if (self->bg_draw_cb)
    {
      self->bg_draw_cb (
        widget, cr, draw_rect, data);
    }

#define DRAW_SVG(svg) \
  ZtkRect rect = { \
    widget->rect.x + self->hpadding, \
    widget->rect.y + self->vpadding, \
    widget->rect.width - self->hpadding * 2, \
    widget->rect.height - self->vpadding * 2 }; \
  ztk_rsvg_draw ( \
    self->svg, cr, &rect)

  switch (self->type)
    {
    case ZTK_BTN_LBL:
      /* TODO draw label */
      break;
#ifdef HAVE_RSVG
    case ZTK_BTN_SVG:
      if ((state & ZTK_WIDGET_STATE_PRESSED) ||
          (self->is_toggle &&
             self->toggled_getter (
               self, widget->user_data)))
        {
          DRAW_SVG (clicked_svg);
        }
      else if (state & ZTK_WIDGET_STATE_HOVERED)
        {
          DRAW_SVG (hover_svg);
        }
      else
        {
          DRAW_SVG (normal_svg);
        }
      break;
#endif
    case ZTK_BTN_CUSTOM:
      self->custom_draw_cb (
        widget, cr, draw_rect, data);
      break;
    default:
      break;
    }

#undef DRAW_SVG
}

static void
update_cb (
  ZtkWidget * w,
  void *      data)
{
}

static int
on_button_event (
  ZtkWidget *             w,
  const PuglEventButton * btn,
  void *                  data)
{
  ZtkButton * self = (ZtkButton *) w;

  ZtkWidgetState state = w->state;
  if (state & ZTK_WIDGET_STATE_PRESSED)
    {
      if (ztk_widget_is_hit (w, btn->x, btn->y))
        {
          self->was_pressed = 1;
        }
    }
  else
    {
      if (self->was_pressed)
        {
          self->activate_cb (w, data);
        }
      self->was_pressed = 0;
    }

  return 1;
}

static void
free_cb (
  ZtkWidget * widget,
  void *      data)
{
  ZtkButton * self = (ZtkButton *) widget;

  free (self);
}

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
  void *                    user_data)
{
  ZtkButton * self = calloc (1, sizeof (ZtkButton));
  ZtkWidget * widget = (ZtkWidget *) self;
  ztk_widget_init (
    (ZtkWidget *) self, ZTK_WIDGET_TYPE_BUTTON, rect,
    update_cb, button_draw_cb, free_cb);

  self->activate_cb = activate_cb;

  widget->button_event_cb = on_button_event;
  widget->user_data = user_data;

  return self;
}

void
ztk_button_make_toggled (
  ZtkButton *            self,
  ZtkButtonToggledGetter toggled_getter)
{
  self->is_toggle = 1;
  self->toggled_getter = toggled_getter;
}

/**
 * Makes a button with a label.
 */
void
ztk_button_make_labeled (
  ZtkButton *           self,
  const char *          label)
{
  self->type = ZTK_BTN_LBL;

  strcpy (self->lbl, label);
}

#ifdef HAVE_RSVG
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
  ZtkRsvgHandle * svg_clicked)
{
  self->type = ZTK_BTN_SVG;

  self->hpadding = hpadding;
  self->vpadding = vpadding;
  self->normal_svg = svg_normal;
  self->hover_svg = svg_hover;
  self->clicked_svg = svg_clicked;
}
#endif

/**
 * Makes a customly drawn button.
 */
void
ztk_button_make_custom (
  ZtkButton *           self,
  ZtkWidgetDrawCallback draw_cb)
{
  self->type = ZTK_BTN_CUSTOM;

  self->custom_draw_cb = draw_cb;
}

void
ztk_button_set_background_colors (
  ZtkButton * self,
  ZtkColor *  normal,
  ZtkColor *  hovered,
  ZtkColor *  clicked)
{
  self->has_bg_colors = 1;

  self->normal_color = * normal;
  self->hovered_color = * hovered;
  self->clicked_color = * clicked;
}

/**
 * Add callback for drawing the background.
 */
void
ztk_button_add_background_callback (
  ZtkButton *           self,
  ZtkWidgetDrawCallback draw_cb)
{
  self->bg_draw_cb = draw_cb;
}
