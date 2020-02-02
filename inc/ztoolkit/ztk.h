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

#ifndef __Z_TOOLKIT_ZTK_H__
#define __Z_TOOLKIT_ZTK_H__

#include "ztoolkit/ztk_app.h"
#include "ztoolkit/ztk_color.h"
#include "ztoolkit/ztk_drawing_area.h"
#include "ztoolkit/ztk_knob.h"
#include "ztoolkit/ztk_knob_with_label.h"
#include "ztoolkit/ztk_label.h"
#include "ztoolkit/ztk_widget.h"

#ifndef MAX
# define MAX(x,y) (x > y ? x : y)
#endif

#ifndef MIN
# define MIN(x,y) (x < y ? x : y)
#endif

#ifndef CLAMP
# define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#endif

#endif
