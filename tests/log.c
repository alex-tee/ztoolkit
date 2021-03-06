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

int main (
  int argc, const char* argv[])
{
  ztk_debug ("%s", "debug test");
  ztk_message ("%s", "message test");
  ztk_warning ("%s %s", "warning test", "warning");
  ztk_error ("%s", "error test");

  return 0;
}
