/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of ZPlugins
 *
 * ZPlugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ZPlugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU General Affero Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ztoolkit/ztk.h"

#include <pugl/pugl.h>
#include <pugl/pugl_cairo.h>

static void
on_close (PuglView* view)
{
  (void) view;
}

static void
on_expose (
  PuglView*               view,
  const PuglEventExpose * expose)
{
  ZtkApp * self = puglGetHandle (view);

  /** update each widget */
  ZtkWidget * w = NULL;
  for (int i = 0; i < self->num_widgets; i++)
    {
      w = self->widgets[i];
      w->update_cb (w, w->user_data);
    }

  /* reset offsets */
  self->prev_press_x = self->offset_press_x;
  self->prev_press_y = self->offset_press_y;

  cairo_t* cr = (cairo_t*)puglGetContext(view);

#if 0
  const PuglRect frame  = puglGetFrame(view);
  const double   width  = frame.width;
  const double   height = frame.height;

  // Scale to view size
  const double scaleX =
    (width - (self->width / width)) / self->width;
  const double scaleY =
    (height - (self->height / height)) /
      self->height;
  cairo_scale(cr, scaleX, scaleY);
  cairo_stroke (cr);
#endif

  ZtkRect rect = {
    expose->x, expose->y, expose->width,
    expose->height };
  ztk_app_draw (
    self, cr, &rect);
}

static int
is_first_widget_hit (
  ZtkApp *    self,
  ZtkWidget * widget,
  double      x,
  double      y)
{
  for (int i = self->num_widgets - 1; i >= 0; i--)
    {
      ZtkWidget * w = self->widgets[i];
      if (w->visible && ztk_widget_is_hit (w, x, y))
        {
          if (widget == w)
            return 1;
          else
            return 0;
        }
    }

  return 0;
}

static void
post_event_to_widgets (
  ZtkApp *          self,
  const PuglEvent * event)
{
  ZtkWidget * w = NULL;

  /* if any combo box is active:
   * - if hit, set the flag to ignore other presses
   * - if not hit, remove it */
  int combo_box_hit = 0;
  if (event->type == PUGL_BUTTON_PRESS ||
      event->type == PUGL_BUTTON_RELEASE)
    {
      const PuglEventButton * ev =
        (const PuglEventButton *) event;
      for (int i = self->num_widgets - 1;
           i >= 0; i--)
        {
          w = self->widgets[i];
          if (w->type ==
                 ZTK_WIDGET_TYPE_COMBO_BOX)
            {
              if (w->visible &&
                  ztk_widget_is_hit (
                    w, ev->x, ev->y))
                {
                  combo_box_hit = 1;
                }
              else
                {
                  ztk_app_remove_widget (self, w);
                }
            }
        }
    }

  for (int i = self->num_widgets - 1; i >= 0; i--)
    {
      w = self->widgets[i];
      switch (event->type)
        {
        case PUGL_KEY_PRESS:
        case PUGL_KEY_RELEASE:
          {
            const PuglEventKey * ev =
              (const PuglEventKey *) event;
            if (w->visible && w->key_event_cb)
              {
                w->key_event_cb (w, ev);
                w->mod = ev->state;
              }
          }
          break;
        case PUGL_BUTTON_PRESS:
          {
            const PuglEventButton * ev =
              (const PuglEventButton *) event;
            if (w->visible &&
                ztk_widget_is_hit (
                  w, ev->x, ev->y) &&
                is_first_widget_hit (
                  self, w, ev->x, ev->y))
              {
                w->before_last_btn_press = w->last_btn_press;
                w->last_btn_press = ev->time;
                w->state |=
                  ZTK_WIDGET_STATE_PRESSED;
                w->mod = ev->state;
                if (ev->button == 3)
                  {
                    w->state |=
                      ZTK_WIDGET_STATE_RIGHT_PRESSED;
                  }
                w->state |=
                  ZTK_WIDGET_STATE_SELECTED;
                if (w->button_event_cb &&
                    (w->type ==
                       ZTK_WIDGET_TYPE_COMBO_BOX ||
                     !combo_box_hit))
                  {
                    w->button_event_cb (
                      w, ev, w->user_data);
                  }
              }
            else
              {
                w->state &=
                  (unsigned int)
                  ~ZTK_WIDGET_STATE_SELECTED;
              }
          }
          break;
        case PUGL_BUTTON_RELEASE:
          {
            const PuglEventButton * ev =
              (const PuglEventButton *) event;
            w->state &=
              (unsigned int)
              ~ZTK_WIDGET_STATE_PRESSED;
            w->state &=
              (unsigned int)
              ~ZTK_WIDGET_STATE_RIGHT_PRESSED;
            w->mod = ev->state;
            w->before_last_btn_release =
              w->last_btn_release;
            w->last_btn_release = ev->time;
            if (w->visible &&
                w->button_event_cb &&
                (w->type ==
                   ZTK_WIDGET_TYPE_COMBO_BOX ||
                 !combo_box_hit))
              {
                w->button_event_cb (
                  w, ev, w->user_data);
              }
          }
          break;
        case PUGL_MOTION_NOTIFY:
          {
            const PuglEventMotion * ev =
              (const PuglEventMotion *) event;
            w->mod = ev->state;
            if (w->visible &&
                ztk_widget_is_hit (
                  w, ev->x, ev->y) &&
                is_first_widget_hit (
                  self, w, ev->x, ev->y))
              {
                w->state |=
                  ZTK_WIDGET_STATE_HOVERED;
                if (w->motion_event_cb)
                  {
                    w->motion_event_cb (
                      w, ev, w->user_data);
                  }
              }
            else
              {
                w->state &=
                  (unsigned int)
                  ~ZTK_WIDGET_STATE_HOVERED;
              }
          }
          break;
        case PUGL_LEAVE_NOTIFY:
          {
            const PuglEventMotion * ev =
              (const PuglEventMotion *) event;
            w->mod = ev->state;
            if (w->state & ZTK_WIDGET_STATE_HOVERED)
              {
                w->state &=
                  (unsigned int)
                  ~ZTK_WIDGET_STATE_HOVERED;
                if (w->visible &&
                    w->motion_event_cb)
                  {
                    w->motion_event_cb (
                      w, ev, w->user_data);
                  }
              }
          }
          break;
        case PUGL_SCROLL:
          {
            const PuglEventScroll * ev =
              (const PuglEventScroll *) event;
            w->mod = ev->state;
            if (w->visible &&
                ztk_widget_is_hit (
                  w, ev->x, ev->y) &&
                w->scroll_event_cb)
              {
                w->scroll_event_cb (w, ev);
              }
          }
          break;
        default:
          break;
        }
    }
}

#undef POST_EVENT_FUNC

static PuglStatus
on_event (
  PuglView *        view,
  const PuglEvent * event)
{
  ZtkApp * self = puglGetHandle (view);

  post_event_to_widgets (self, event);

  switch (event->type)
    {
    case PUGL_BUTTON_PRESS:
      {
        const PuglEventButton * ev =
          (const PuglEventButton *) event;
        self->pressing = 1;
        self->start_press_x = ev->x;
        self->start_press_y = ev->y;
        self->prev_press_x = ev->x;
        self->prev_press_y = ev->y;
        self->offset_press_x = ev->x;
        self->offset_press_y = ev->y;
      }
      puglPostRedisplay(view);
      break;
    case PUGL_BUTTON_RELEASE:
      {
        /*const PuglEventButton * ev =*/
          /*(const PuglEventButton *) event;*/
        self->pressing = 0;
        self->start_press_x = 0;
        self->start_press_y = 0;
        self->prev_press_x = 0;
        self->prev_press_y = 0;
        self->offset_press_x = 0;
        self->offset_press_y = 0;
      }
      puglPostRedisplay(view);
      break;
    case PUGL_MOTION_NOTIFY:
      {
        const PuglEventMotion * ev =
          (const PuglEventMotion *) event;
        if (self->pressing)
          {
            self->prev_press_x =
              self->offset_press_x;
            self->prev_press_y =
              self->offset_press_y;
            self->offset_press_x = ev->x;
            self->offset_press_y = ev->y;
          }
      }
      puglPostRedisplay(view);
      break;
    case PUGL_ENTER_NOTIFY:
    case PUGL_LEAVE_NOTIFY:
    case PUGL_SCROLL:
    case PUGL_KEY_PRESS:
    case PUGL_KEY_RELEASE:
      puglPostRedisplay(view);
      break;
    case PUGL_EXPOSE:
      on_expose (view, &event->expose);
      break;
    case PUGL_CLOSE:
      on_close(view);
      break;
    default:
      puglPostRedisplay(view);
      break;
    }

  return PUGL_SUCCESS;
}

/**
 * Creates a new ZtkApp.
 *
 * @param parent Parent window, if any.
 */
ZtkApp *
ztk_app_new (
  const char *     title,
  void*            parent,
  int              width,
  int              height)
{
  ZtkApp * self = calloc (1, sizeof (ZtkApp));

  ztk_theme_init (&self->theme);

  self->world = puglNewWorld ();
  self->title = strdup (title);
  self->width = width;
  self->height = height;
  self->widgets = calloc (1, sizeof (ZtkWidget *));
  self->widgets_size = 1;

  puglSetClassName (self->world, title);
  PuglRect frame = { 0, 0, width, height };
  self->view  = puglNewView (self->world);
  puglSetFrame (self->view, frame);
  puglSetMinSize (self->view, width, height);
  puglSetViewHint (
    self->view, PUGL_RESIZABLE, 0);
  puglSetBackend (self->view, puglCairoBackend());
  puglSetHandle (self->view, self);
  puglSetViewHint (
    self->view, PUGL_IGNORE_KEY_REPEAT, 1);
  puglSetEventFunc (self->view, on_event);

  if (parent)
    {
      puglSetParentWindow (
        self->view, (PuglNativeWindow) parent);
    }

  if (puglCreateWindow (self->view, "Pugl Test"))
    {
      printf ("error, can't create window\n");
    }

  puglShowWindow (self->view);

  return self;
}

static int
cmp_z (
  const void * a,
  const void * b)
{
  return
    (*(ZtkWidget **) a)->z -
      (*(ZtkWidget **) b)->z;
}

/**
 * Adds a widget with the given Z axis.
 */
void
ztk_app_add_widget (
  ZtkApp *    self,
  ZtkWidget * widget,
  int         z)
{
  /* skip if already in app */
  if (ztk_app_contains_widget (self, widget))
    {
      ztk_warning (
        "Attempted to add widget %p to ZtkApp, "
        "but the widget is already in ZtkApp",
        widget);
      return;
    }

  if (self->widgets_size == 0)
    {
      self->widgets_size = 2;
      self->widgets =
        (ZtkWidget **)
        realloc (
          self->widgets,
          (size_t) self->widgets_size *
            sizeof (ZtkWidget *));
    }
  else if (self->num_widgets == self->widgets_size)
    {
      self->widgets_size = self->widgets_size * 2;
      self->widgets =
        (ZtkWidget **)
        realloc (
          self->widgets,
          (size_t) self->widgets_size *
            sizeof (ZtkWidget *));
    }
  self->widgets[self->num_widgets++] = widget;
  widget->app = self;
  widget->z = z;

  /* TODO sort by z */
  qsort (
    self->widgets, (size_t) self->num_widgets,
    sizeof (ZtkWidget *), cmp_z);
}

/**
 * Removes the given widget from the app.
 */
void
ztk_app_remove_widget (
  ZtkApp *    self,
  ZtkWidget * widget)
{
  int match = 0;
  for (int i = self->num_widgets - 1;
       i >= 0; i--)
    {
      ZtkWidget * w = self->widgets[i];
      if (w == widget)
        {
          match = 1;
          for (int j = i; j < self->num_widgets - 1;
               j++)
            {
              self->widgets[j] =
                self->widgets[j + 1];
            }
          break;
        }
    }
  if (!match)
    {
      ztk_warning (
        "Tried to remove widget %p from ZtkApp but "
        "it wasn't found", widget);
      return;
    }

  self->num_widgets--;
}

int
ztk_app_contains_widget (
  ZtkApp * self,
  ZtkWidget * widget)
{
  for (int i = 0; i < self->num_widgets; i++)
    {
      ZtkWidget * w = self->widgets[i];
      if (w == widget)
        return 1;
    }
  return 0;
}

/**
 * Draws each hit widget.
 */
void
ztk_app_draw (
  ZtkApp *  self,
  cairo_t * cr,
  ZtkRect * rect)
{
  for (int i = 0; i < self->num_widgets; i++)
    {
      ZtkWidget * widget = self->widgets[i];
      if (!widget->visible ||
          !ztk_widget_is_hit_by_rect (widget, rect))
        continue;

      widget->draw_cb (
        widget, cr, rect, widget->user_data);
    }
}

void
ztk_app_idle (
  ZtkApp * self)
{
  puglPollEvents (self->world, 0);
  puglDispatchEvents (self->world);
}

/**
 * Shows the window.
 */
void
ztk_app_show_window (
  ZtkApp * self)
{
  puglShowWindow (self->view);
}

/**
 * Hides the window.
 */
void
ztk_app_hide_window (
  ZtkApp * self)
{
  puglHideWindow (self->view);
}

/**
 * Frees the app.
 */
void
ztk_app_free (
  ZtkApp * self)
{
  puglFreeView (self->view);
  puglFreeWorld (self->world);

  if (self->title)
    free (self->title);

  free (self);
}
