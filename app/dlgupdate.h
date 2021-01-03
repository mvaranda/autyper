#ifndef DLGUPDATE_H
#define DLGUPDATE_H
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

#include <QNetworkReply>
#include <QUrl>
#include <QNetworkAccessManager>


#include <QDialog>

namespace Ui {
class DlgUpdate;
}

class DlgUpdate : public QDialog
{
  Q_OBJECT

public:
  explicit DlgUpdate(QWidget *parent = nullptr);
  ~DlgUpdate();

private:
  Ui::DlgUpdate *ui;
  QUrl support_url;
  QNetworkAccessManager qnam;
  QNetworkReply *reply;
  QString replyData;

  // methods
  void startRequest(void);
  int32_t verToNum( QString v );


private slots:
  void httpFinished(void);
  void httpReadyRead(void);

  void on_bt_close2_clicked();
  void on_bt_goto_web_clicked();
  void on_bt_close1_clicked();
};

#endif // DLGUPDATE_H
