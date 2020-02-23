/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
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

#ifndef __Z_TOOLKIT_ZTK_DIALOG_H__
#define __Z_TOOLKIT_ZTK_DIALOG_H__

#include "rsvg.h"
#include "ztk_color.h"
#include "ztk_widget.h"

/**
 * Dialog type.
 */
typedef enum ZtkDialogType
{
  /** Standard about dialog. */
  ZTK_DIALOG_ABOUT,

  ZTK_DIALOG_INFO,
  ZTK_DIALOG_ERROR,

  /** Dialog for custom drawing. */
  ZTK_DIALOG_CUSTOM,
} ZtkDialogType;

typedef enum ZtkDialogAboutLicense
{
  ZTK_DIALOG_ABOUT_LICENSE_AGPL_3_PLUS,
} ZtkDialogAboutLicense;

/**
 * Dialog widget.
 */
typedef struct ZtkDialog
{
  /** Base widget. */
  ZtkWidget         base;

  /** Close button on the top right. */
  ZtkButton *       close_btn;

  ZtkRect           internal_rect;

  /** Dialog title. */
  char              title[256];

  /** Used by about dialogs. */
  char              copyright[600];

  /** Used by about dialogs. */
  char              version[600];

  /** Used by about dialogs. */
  ZtkDialogAboutLicense license;

  /** Dialog text. */
  char              text[6000];

  /** Dialog type. */
  ZtkDialogType     type;

} ZtkDialog;

/**
 * Creates a new ZtkDialog.
 *
 * This must then be set to its type using the setters
 * below.
 */
ZtkDialog *
ztk_dialog_new (
  ZtkApp *        app,
  ZtkRect *       modal_rect,
  ZtkRect *       rect,
  void *          data);

void
ztk_dialog_make_about (
  ZtkDialog *     self,
  const char *    title,
  const char *    version,
  const char *    copyright,
  ZtkDialogAboutLicense license,
  const char *    text);

#endif
