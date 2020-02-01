# Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
#
# This file is part of ZToolkit
#
# ZToolkit is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ZToolkit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with ZToolkit.  If not, see <https://www.gnu.org/licenses/>.

ztoolkit_srcs = files([
  'ztk_app.c',
  'ztk_color.c',
  'ztk_knob.c',
  'ztk_knob_with_label.c',
  'ztk_label.c',
  'ztk_theme.c',
  'ztk_widget.c',
  ])

ztoolkit_lib = static_library(
  'ztoolkit',
  sources: [
    ztoolkit_srcs,
    config_h,
    ],
  dependencies: deps,
  include_directories: inc_dirs,
  link_whole: pugl,
  install: not meson.is_subproject(),
  )

install_headers(
  installable_headers, subdir: 'ztoolkit')
