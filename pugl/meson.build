# Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
#
# This file is part of ZPlugins
#
# ZPlugins is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ZPlugins is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with ZPlugins.  If not, see <https://www.gnu.org/licenses/>.

pugl_srcs = files([
  join_paths ('pugl', 'detail', 'implementation.c'),
  ])

if os_linux or os_freebsd
  pugl_srcs += files([
    join_paths ('pugl', 'detail', 'x11.c'),
    join_paths ('pugl', 'detail', 'x11_cairo.c'),
    ])
elif os_windows
  pugl_srcs += files([
    join_paths ('pugl', 'detail', 'win.c'),
    join_paths ('pugl', 'detail', 'win_cairo.c'),
    ])
elif os_darwin
  pugl_srcs += files([
    join_paths ('pugl', 'detail', 'mac.m'),
    join_paths ('pugl', 'detail', 'mac_cairo.m'),
    ])
endif
