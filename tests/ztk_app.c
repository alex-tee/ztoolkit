/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of ZToolkit
 *
 * ZToolkit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ZToolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ZToolkit.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "helper.h"

#include <ztoolkit/ztk.h>

int main (
  int argc, const char* argv[])
{
  ZtkApp * app = calloc (1, sizeof (ZtkApp));

  for (int i = 0; i < 24; i++)
    {
      ZtkWidget * widget =
        calloc (1, sizeof (ZtkWidget));
      ztk_app_add_widget (app, widget, 23 - i);
      ztk_assert (widget->z == 23 - i);
    }
  ztk_assert (app->num_widgets == 24);

  /* check z coordinate */
  int last_z = 0;
  for (int i = 0; i < 24; i++)
    {
      ZtkWidget * widget = app->widgets[i];
      ztk_assert (widget->z >= last_z);
      last_z = widget->z;
    }

  /* remove widgets */
  ztk_app_remove_widget (app, app->widgets[23]);
  ztk_assert (app->num_widgets == 23);
  ztk_assert (app->widgets[22]->z == 22);

  ztk_app_remove_widget (app, app->widgets[0]);
  ztk_assert (app->num_widgets == 22);
  ztk_assert (app->widgets[0]->z == 1);

  ztk_app_remove_widget (app, app->widgets[2]);
  ztk_assert (app->num_widgets == 21);
  ztk_assert (app->widgets[2]->z == 4);

  return 0;
}

