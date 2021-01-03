#ifndef DLGABOUT_H
#define DLGABOUT_H
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

#include <QDialog>

namespace Ui {
class dlgabout;
}

class dlgabout : public QDialog
{
  Q_OBJECT

public:
  explicit dlgabout(QWidget *parent = nullptr);
  ~dlgabout();

private:
  Ui::dlgabout *ui;
};

#endif // DLGABOUT_H
