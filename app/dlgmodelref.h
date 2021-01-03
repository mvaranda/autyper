#ifndef DLGMODELREF_H
#define DLGMODELREF_H
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
class DlgModelRef;
}

class DlgModelRef : public QDialog
{
  Q_OBJECT

public:
  explicit DlgModelRef(QWidget *parent = nullptr);
  ~DlgModelRef();

private slots:
  void on_bt_browse_model_clicked();

  void on_bt_browse_scorer_clicked();

  void on_bt_save_clicked();

  void on_bt_cancel_clicked();

private:
  void updateUserModelPath(QString filePath);
  Ui::DlgModelRef *ui;
  QString model;
  QString scorer;
};

#endif // DLGMODELREF_H
