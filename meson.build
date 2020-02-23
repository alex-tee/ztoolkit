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

project (
  'ztoolkit', ['c'],
  version: '0.1.0',
  license: 'AGPLv3+',
  meson_version: '>= 0.43.0',
  default_options: [
    'warning_level=2',
    'buildtype=debug',
    'c_std=gnu11',
    ],
  )

cc = meson.get_compiler ('c')

# detect paths
prefix = get_option ('prefix')
libdir = join_paths (prefix, get_option ('libdir'))
includedir = join_paths (
  prefix, get_option('includedir'))

# detect os
os_darwin = false
os_linux = false
os_freebsd = false
os_windows = false

if host_machine.system() == 'darwin'
  os_darwin = true
elif host_machine.system() == 'linux'
  os_linux = true
elif host_machine.system() == 'freebsd'
  os_freebsd = true
elif host_machine.system() == 'windows'
  os_windows = true
endif

# dependencies
deps = [
  # for drawing
  dependency('cairo', version: '>=1.0.0'),

  # math functions might be implemented in libm
  cc.find_library('m', required: false),
  ]

cdata = configuration_data ()
if os_linux
  deps += dependency('x11')
  cdata.set('HAVE_X11', 1)
endif

if get_option('enable_rsvg')
  rsvg_dep = dependency('librsvg-2.0', version: '>=2.14')
  deps += rsvg_dep
  cdata.set('HAVE_RSVG', 1)
  if rsvg_dep.version().version_compare('>=2.46')
    cdata.set('HAVE_RSVG_2_46', 1)
  endif
endif

# create config.h
config_h = configure_file (
  output: 'ztoolkit_config.h',
  configuration: cdata,
  )
installable_headers = [ config_h ]

# include dirs
inc_dirs = [
  include_directories('.'),
  include_directories('inc'),
  include_directories('pugl'),
  include_directories(
    join_paths ('pugl', 'pugl')),
  ]

# cflags
common_cflags = cc.get_supported_arguments([
  '-fvisibility=hidden',
  '-Wformat=2',
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
  '-Wno-sequence-point',
  '-Wignored-qualifiers',
  '-Wno-cast-function-type',
  ])
strict_cflags = []
if get_option ('strict_flags')
  strict_cflags = cc.get_supported_arguments([
    #'-Werror=cast-qual',
    '-Werror=clobbered',
    #'-Werror=conversion',
    '-Werror=disabled-optimization',
    '-Werror=double-promotion',
    '-Werror=float-equal',
    '-Werror=logical-op',
    '-Werror=pointer-arith',
    '-Werror=sign-conversion',
    '-Werror=overlength-strings',
    '-Werror=stringop-truncation',
    '-Werror=missing-declarations',
    #'-Werror=redundant-decls',
    '-Werror=shadow',
    '-Werror=undef',
    '-Werror=unused',
    '-Werror=strict-aliasing',
    '-fstrict-aliasing',
    #'-Werror=strict-overflow',
    '-Wstrict-overflow=2',
    '-fstrict-overflow',
    '-Werror=duplicated-branches',
    '-Werror=duplicated-cond',
    '-Werror=null-dereference',
    '-Werror=init-self',
    '-Werror=jump-misses-init',
    '-Werror=missing-prototypes',
    '-Werror=nested-externs',
    '-Werror=write-strings',
    '-Werror=implicit-fallthrough',
    '-Werror=sign-compare',
    '-Werror=discarded-qualifiers',
    '-Werror=float-conversion',
    '-Werror=implicit-function-declaration',
    '-Werror=uninitialized',
    '-Werror=maybe-uninitialized',
    '-Werror=return-type',
    '-Werror=int-conversion',
    '-Werror=format-security',
    '-Werror=incompatible-pointer-types',
    '-Werror=implicit-int',
    '-Werror=multistatement-macros',
    '-Werror=switch',
    '-Werror=overflow',
    '-Werror=array-bounds',
    '-Werror=enum-compare',
    '-Werror=misleading-indentation',
    '-Werror=int-in-bool-context',
    '-Werror=type-limits',
    '-Werror=deprecated-declarations',
    '-Werror=format-extra-args',
    '-Werror=format',
    '-Wextra',
    '-Weverything',
    ])
endif

add_project_arguments (
  common_cflags,
  language: [ 'c' ]
  )

subdir('pugl')
subdir('inc')
subdir('src')
subdir('tests')

# this is so that it can be used as a meson
# subproject
ztoolkit_dep = declare_dependency (
  include_directories: inc_dirs,
  dependencies: deps,
  link_with: ztoolkit_lib)

if not meson.is_subproject()
  pkg_mod = import('pkgconfig')
  pkg_mod.generate(
    libraries: ztoolkit_lib,
    version: '0.1.0',
    name: 'ztoolkit',
    filebase: 'ztoolkit',
    description: 'A GUI toolkit for LV2 plugins',
    )
endif
