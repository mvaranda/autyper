#ifndef AUTYPERMAIN_H
#define AUTYPERMAIN_H

/*
 * This file is part of the AuTyper distribution (https://github.com/mvaranda/autyper).
 * Copyright (c) 2020 Marcelo Varanda.
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


#include <QMainWindow>
#include <QList>
#include <QPlainTextEdit>
#include "voice2text.h"
#include "dlgprogress.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AutyperMain; }
QT_END_NAMESPACE

class AutyperMain : public QMainWindow
{
  Q_OBJECT

public:
  AutyperMain(QWidget *parent = nullptr);
  ~AutyperMain();

private slots:
  void on_actionOpen_triggered();
  void handle_voice2text(Voice2Text::CResult * res);
  void handleAbortRequest(void);

  void on_actionNew_triggered();

private:
  Ui::AutyperMain * ui;
  Voice2Text *      workerThread;
  uint32_t          modelSampleRate;
  int               name_cnt;
  QList<QPlainTextEdit *> mdiList;
  QPlainTextEdit *  activeText;
  DlgProgress *     dlgProgress;
  void startVoice2TextThread(QString filename, FeederBase * feeder);

};
#endif // AUTYPERMAIN_H
