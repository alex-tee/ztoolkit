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

#include <stdio.h>
#include <stdlib.h>

#include <ztoolkit/log.h>
#include <ztoolkit/ztk_color.h>

void
ztk_color_set_for_cairo (
  ZtkColor * color,
  cairo_t *  cr)
{
  cairo_set_source_rgba (
    cr, color->red, color->green, color->blue,
    color->alpha);
}

/**
 * Parses a ZtkColor from the given hex string.
 */
void
ztk_color_parse_hex (
  ZtkColor *   color,
  const char * hex_str)
{
  char str[3];
  long num;
  str[0] = hex_str[1];
  str[1] = hex_str[2];
  str[2] = '\0';
  num = strtol (str, NULL, 16);
  color->red = (double) num / 255;
  str[0] = hex_str[3];
  str[1] = hex_str[4];
  str[2] = '\0';
  num = strtol (str, NULL, 16);
  color->green = (double) num / 255;
  str[0] = hex_str[5];
  str[1] = hex_str[6];
  str[2] = '\0';
  num = strtol (str, NULL, 16);
  color->blue = (double) num / 255;
}
