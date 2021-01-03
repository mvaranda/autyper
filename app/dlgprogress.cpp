
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

#include "dlgprogress.h"
#include "ui_dlgprogress.h"

DlgProgress::DlgProgress(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DlgProgress)
{
  ui->setupUi(this);
  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);
}

DlgProgress::~DlgProgress()
{
  delete ui;
}

void DlgProgress::update(int v)
{
  ui->progressBar->setValue(v);
}

void DlgProgress::on_pushButton_clicked()
{
  emit canceReqToMain();
}
