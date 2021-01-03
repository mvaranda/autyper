
/*
 * This file is part of the AuTyper distribution (https://github.com/mvaranda/autyper).
 * Copyright (c) 2020 Varanda Labs Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "dlgabout.h"
#include "ui_dlgabout.h"
#include "version.h"

dlgabout::dlgabout(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::dlgabout)
{
  ui->setupUi(this);

  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);

  QPixmap img(":rec/images/autyper_icon_128.png");
  int w = ui->lb_logo->width();
  int h = ui->lb_logo->height();
  ui->lb_logo->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));

  ui->t_version->setText(QString::asprintf("Version: %s", AuTyperVersion));
}

dlgabout::~dlgabout()
{
  delete ui;
}
