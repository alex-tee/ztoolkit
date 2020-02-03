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

#include "ztoolkit/ztk.h"

/** Height of the separator, excluding padding. */
#define SEPARATOR_HEIGHT 2

/** Padding to leave left/right/bot/top of the
 * text. */
#define PADDING 2

static double
get_height (
  ZtkComboBox * self)
{
  double height = PADDING * 2;
  for (int i = 0; i < self->num_elements; i++)
    {
      ZtkComboBoxElement * el = &self->elements[i];
      if (el->is_separator)
        {
          height += SEPARATOR_HEIGHT + PADDING * 2;
        }
      else
        {
          /* the app is not set until the widget gets
           * added to the app */
          ZtkWidget * widget = (ZtkWidget *) self;
          if (!widget->app)
            continue;

          cairo_t* cr =
            (cairo_t*) puglGetContext (
              widget->app->view);
          cairo_text_extents_t extents;
          cairo_set_font_size (cr, self->font_size);
          cairo_text_extents (cr, el->label, &extents);

          height += (int) extents.height + PADDING * 2;
        }
    }

  return height;
}

static double
get_width (
  ZtkComboBox * self)
{
  double width = 12;
  for (int i = 0; i < self->num_elements; i++)
    {
      ZtkComboBoxElement * el = &self->elements[i];
      if (el->is_separator)
        continue;

      /* the app is not set until the widget gets
       * added to the app */
      ZtkWidget * widget = (ZtkWidget *) self;
      if (!widget->app)
        continue;

      cairo_t* cr =
        (cairo_t*) puglGetContext (
          widget->app->view);
      cairo_text_extents_t extents;
      cairo_set_font_size (cr, self->font_size);
      cairo_text_extents (cr, el->label, &extents);

      width =
        /* *2 for the element, *2 for the frame */
        MAX (width, extents.width + PADDING * 4);
    }

  return width;
}

static void
get_dimensions (
  ZtkComboBox * self,
  ZtkRect *     rect)
{
  double height = get_height (self);
  double width = get_width (self);
  rect->width = width;
  rect->height = height;
  if (self->upwards)
    {
      if (self->backwards)
        {
          rect->x =
            (self->parent->rect.x +
               self->parent->rect.width) - width;
          rect->y = self->parent->rect.y - height;
        }
      else
        {
          rect->x = self->parent->rect.x;
          rect->y = self->parent->rect.y - height;
        }
    }
  else /* downwards */
    {
      if (self->backwards)
        {
          rect->x =
            (self->parent->rect.x +
               self->parent->rect.width) - width;
          rect->y =
            self->parent->rect.y +
              self->parent->rect.height;
        }
      else
        {
          rect->x = self->parent->rect.x;
          rect->y =
            self->parent->rect.y +
              self->parent->rect.height;
        }
    }
}

static void
draw_cb (
  ZtkWidget * w,
  cairo_t *   cr,
  void *      data)
{
  ZtkComboBox * self = (ZtkComboBox *) w;

  ZtkRect rect;
  get_dimensions (self, &rect);

  /* draw bg and frame */
  ztk_color_set_for_cairo (
    &self->frame_color, cr);
  cairo_rectangle (
    cr, rect.x, rect.y, rect.width,
    rect.height);
  cairo_fill (cr);
  ztk_color_set_for_cairo (
    &self->bg_color, cr);
  cairo_rectangle (
    cr, rect.x + PADDING, rect.y + PADDING,
    rect.width - PADDING * 2,
    rect.height - PADDING * 2);
  cairo_fill (cr);

  double height = rect.y + PADDING;
  double next_height;

  /* find element hit */
  for (int i = 0; i < self->num_elements; i++)
    {
      ZtkComboBoxElement * el = &self->elements[i];
      if (el->is_separator)
        {
          next_height =
            height + SEPARATOR_HEIGHT +
            PADDING * 2;

          /* draw the element bg */
          if (self->hovered_idx == i)
            {
              if (w->state & ZTK_WIDGET_STATE_PRESSED)
                {
                  ztk_color_set_for_cairo (
                    &self->click_color, cr);
                }
              else
                {
                  ztk_color_set_for_cairo (
                    &self->hover_color, cr);
                }
              cairo_rectangle (
                cr, rect.x + PADDING, height,
                rect.width - PADDING * 2,
                next_height - height);
              cairo_fill (cr);
            }

          /* draw the separator */
          ztk_color_set_for_cairo (
            &self->separator_color, cr);
          cairo_rectangle (
            cr, rect.x + PADDING * 2,
            height + PADDING,
            rect.width - PADDING * 4,
            SEPARATOR_HEIGHT);
          cairo_fill (cr);

          height = next_height;
        }
      else
        {
          cairo_text_extents_t extents;
          cairo_set_font_size (cr, self->font_size);
          cairo_text_extents (
            cr, el->label, &extents);
          next_height =
            height + extents.height +
            PADDING * 2;

          /* draw the element bg */
          if (self->hovered_idx == i)
            {
              if (w->state & ZTK_WIDGET_STATE_PRESSED)
                {
                  ztk_color_set_for_cairo (
                    &self->click_color, cr);
                }
              else
                {
                  ztk_color_set_for_cairo (
                    &self->hover_color, cr);
                }
              cairo_rectangle (
                cr, rect.x + PADDING, height,
                rect.width - PADDING * 2,
                next_height - height);
              cairo_fill (cr);
            }

          /* draw the text */
          if (self->hovered_idx == i)
            {
              if (w->state & ZTK_WIDGET_STATE_PRESSED)
                {
                  ztk_color_set_for_cairo (
                    &self->text_click_color, cr);
                }
              else
                {
                  ztk_color_set_for_cairo (
                    &self->text_hover_color, cr);
                }
            }
          else
            {
              ztk_color_set_for_cairo (
                &self->text_normal_color, cr);
            }

          cairo_move_to (
            cr, rect.x + PADDING * 2,
            height + PADDING + extents.height);
          cairo_show_text (
            cr, el->label);

          height = next_height;
        }
    }
}

static void
update_cb (
  ZtkWidget * w,
  void *      data)
{
}

static int
motion_cb (
  ZtkWidget *             widget,
  const PuglEventMotion * event,
  void *                  data)
{
  /* set hovered */
  ZtkComboBox * self = (ZtkComboBox *) widget;

  double y = event->y;
  double height = widget->rect.y + PADDING;
  double next_height;

  /* find element hit */
  for (int i = 0; i < self->num_elements; i++)
    {
      ZtkComboBoxElement * el = &self->elements[i];
      if (el->is_separator)
        {
          next_height =
            height + SEPARATOR_HEIGHT +
            PADDING * 2;
          if (y >= height && y < next_height)
            {
              self->hovered_idx = i;
              return 0;
            }
          height = next_height;
        }
      else
        {
          cairo_t* cr =
            (cairo_t*) puglGetContext (
              ((ZtkWidget *) self)->app->view);
          cairo_text_extents_t extents;
          cairo_set_font_size (
            cr, self->font_size);
          cairo_text_extents (
            cr, el->label, &extents);
          next_height =
            height + extents.height +
            PADDING * 2;
          if (y >= height && y < next_height)
            {
              self->hovered_idx = i;
              return 0;
            }
          height = next_height;
        }
    }

  self->hovered_idx = -1;
  return 0;
}

static void
free_cb (
  ZtkWidget * w,
  void *      data)
{
  ZtkComboBox * self = (ZtkComboBox *) w;

  free (self);
}

static int
button_event_cb (
  ZtkWidget *             widget,
  const PuglEventButton * btn,
  void *                  data)
{
  ZtkComboBox * self = (ZtkComboBox *) widget;

  const PuglEvent * ev =  (const PuglEvent *) btn;
  if (ztk_widget_is_hit (widget, btn->x, btn->y))
    {
      /* skip if already removed */
      if (!ztk_app_contains_widget (
             widget->app, widget))
        return 0;

      /* skip if not release or no valid hover */
      if (ev->type != PUGL_BUTTON_RELEASE ||
          self->hovered_idx < 0)
        return 0;

      ZtkComboBoxElement * el =
        &self->elements[self->hovered_idx];
      if (!el->is_separator)
        {
          /* activate */
          el->activate_cb (
            widget, el->activate_cb_data);

          /* remove from app to hide the
           * combobox */
          ztk_app_remove_widget (
            widget->app, widget);

          return 0;
        }
    }
  /* clicked outside */
  else
    {
      /* remove widget */
      ztk_app_remove_widget (
        widget->app, widget);
    }

  return 0;
}

/**
 * Initializes the defaults.
 */
static void
ztk_combo_box_init (
  ZtkComboBox * self)
{
  strcpy (self->font_name, "Cantarrel");
  self->font_size = 12.0;
  ztk_color_parse_hex (
    &self->text_normal_color, "#DDDDDD");
  ztk_color_parse_hex (
    &self->text_hover_color, "#EEEEEE");
  ztk_color_parse_hex (
    &self->text_click_color, "#FFFFFF");
  ztk_color_parse_hex (
    &self->bg_color, "#323232");
  ztk_color_parse_hex (
    &self->frame_color, "#646464");
  ztk_color_parse_hex (
    &self->separator_color, "#AAAAAA");
  ztk_color_parse_hex (
    &self->hover_color, "#646464");
  ztk_color_parse_hex (
    &self->click_color, "#868686");
}

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
  int          spawn_backwards)
{
  ZtkComboBox * self =
    calloc (1, sizeof (ZtkComboBox));
  ZtkRect rect = { 0, 0, 0, 0 };
  ztk_widget_init (
    (ZtkWidget *) self, ZTK_WIDGET_TYPE_COMBO_BOX,
    &rect, update_cb, draw_cb,
    free_cb);
  ZtkWidget * widget = (ZtkWidget *) self;

  /* catch button events */
  widget->button_event_cb = button_event_cb;
  widget->motion_event_cb = motion_cb;

  self->parent = parent;
  self->upwards = spawn_upwards;
  self->backwards = spawn_backwards;

  ztk_combo_box_init (self);

  self->hovered_idx = -1;

  /* update dimensions */
  get_dimensions (self, &widget->rect);

  return self;
}

/**
 * @param data Data related to the current element
 *   to pass to the activate callback.
 */
void
ztk_combo_box_add_text_element (
  ZtkComboBox * self,
  const char *  label,
  ZtkWidgetActivateCallback activate_cb,
  void *        data)
{
  ZtkComboBoxElement * el =
    &self->elements[self->num_elements++];

  strcpy (el->label, label);
  el->is_separator = 0;
  el->activate_cb = activate_cb;
  el->activate_cb_data = data;

  /* update dimensions */
  ZtkWidget * widget = (ZtkWidget *) self;
  get_dimensions (self, &widget->rect);
}

void
ztk_combo_box_add_separator (
  ZtkComboBox * self)
{
  ZtkComboBoxElement * el =
    &self->elements[self->num_elements++];
  el->is_separator = 1;

  /* update dimensions */
  ZtkWidget * widget = (ZtkWidget *) self;
  get_dimensions (self, &widget->rect);
}

void
ztk_combo_box_clear (
  ZtkComboBox * self)
{
  self->num_elements = 0;
}
