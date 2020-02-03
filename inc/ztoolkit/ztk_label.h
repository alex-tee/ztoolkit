/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
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

#ifndef __Z_TOOLKIT_ZTK_LABEL_H__
#define __Z_TOOLKIT_ZTK_LABEL_H__

#include "ztoolkit/ztk.h"

/**
 * Label widget.
 */
typedef struct ZtkLabel
{
  /** Base widget. */
  ZtkWidget         base;

  char *            label;

  double            font_size;

  ZtkColor          color;

} ZtkLabel;

/**
 * Creates a new label.
 */
ZtkLabel *
ztk_label_new (
  double       x,
  double       y,
  double       font_size,
  ZtkColor *   color,
  const char * lbl);

#endif
