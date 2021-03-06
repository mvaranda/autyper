#ifndef AUTYPERMAIN_H
#define AUTYPERMAIN_H

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

#include <QMainWindow>
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

  QString appDataPath;

private slots:
  void on_actionOpen_triggered();
  void handle_voice2text(Voice2Text::CResult * res);
  void handleAbortRequest(void);

  void on_actionNew_triggered();

  void on_actionSave_triggered();

  void on_actionChange_Model_triggered();

  void on_actionAppend_Voice_triggered();

  void on_actionHelp_triggered();

  void on_actionInfo_triggered();

  void on_actionCheck_for_Upgrade_triggered();

  void on_actionCopy_triggered();

  void on_actionPaste_triggered();

  void on_actionCut_triggered();

private:
  Ui::AutyperMain * ui;
  Voice2Text *      voice2Text;
  int               name_cnt;
  QPlainTextEdit *  activeText;
  DlgProgress *     dlgProgress;
  void startVoice2TextThread(QString filename, FeederBase * feeder);
  void enableConvControls(void);
  void disableConvControls(void);
  void updateUserPath(QString path);
  void updateUserAudioPath(QString path);
  void emulKeyPress(uint32_t key, uint32_t modifier);
};
#endif // AUTYPERMAIN_H
