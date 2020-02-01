ZToolkit
========

ZToolkit (Ztk) is a GUI toolkit for LV2 plugins
heavily inspired by GTK.

It handles events and low level drawing on
behalf of the user and provides a high-level API
for managing the UI and custom widgets.

ZToolkit is written in C and was created to be
used for various plugins bundled with the Zrythm
digital audio workstation.

This is a work in progress.

Dependencies
------------
Cairo and X11

Building
--------

    meson build
    ninja -C build
    ninja -C build install

Usage
-----
ZToolkit will install a static library that can be
linked to. All of the API is exposed in a single
header for convenience.

    #include <ztoolkit/ztk.h>

Docs are coming soon.

License
-------
ZToolkit is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

ZToolkit is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

The full text of the license can be found in the
[COPYING](COPYING) file.

For the copyright years, ZToolkit uses a range (“2008-2010”) instead of
listing individual years (“2008, 2009, 2010”) if and only if every year
in the range, inclusive, is a “copyrightable” year that would be listed
individually.

Some files, where specified, are licensed under
different licenses.

----

Copyright (C) 2020 Alexandros Theodotou

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.  This file is offered as-is,
without any warranty.
