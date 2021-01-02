
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

#include <QDir>
#include "autypermain.h"
#include "ui_autypermain.h"
#include "log.h"
#include <QProcessEnvironment>
#include <QFileDialog>
#include "feederfactory.h"
#include <QMessageBox>
#include <QWindow>
#include <QMdiSubWindow>
#include "version.h"

// Debug only: go straight to convert a file
//#define OPEN_FILE_AT_STARTUP

// hardcode for now:
#define MODEL "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.3-models.pbmm"
#define SCORER "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.3-models.scorer"
// TODO: add model management for models

extern int audio2text(int argc, char **argv);

AutyperMain::AutyperMain(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AutyperMain)
{
  name_cnt=0;
  voice2Text = new Voice2Text( QString(MODEL), QString(SCORER) );
  ui->setupUi(this);
  setWindowTitle("AuTyper - Version " AuTyperVersion);
  dlgProgress = new DlgProgress(this);

  connect(dlgProgress, &DlgProgress::canceReqToMain, this, &AutyperMain::handleAbortRequest);
  connect(voice2Text, &Voice2Text::resultReady, this, &AutyperMain::handle_voice2text);


  // Debug only: go straight to convert a file
#ifdef OPEN_FILE_AT_STARTUP
  on_actionOpen_triggered();
#endif
}

AutyperMain::~AutyperMain()
{
  delete ui;
}

void AutyperMain::handleAbortRequest(void)
{
  if(voice2Text) {
    voice2Text->abortRequest();
  }
}

void AutyperMain::on_actionOpen_triggered()
{

}

void AutyperMain::handle_voice2text(Voice2Text::CResult * res)
{
#if 0 // log res
  QString t("Text result: ");
  t = t + res->text + QString("\n");
  LOG(t.toStdString().c_str());
  LOG("progress = %d\n", res->progress);
#endif

  if ( (res->result_code == Voice2Text::PARTIAL_TEXT) ||
       (res->result_code == Voice2Text::FINAL_TEXT) ) {
    dlgProgress->update(res->progress);
    if (activeText) {
      activeText->moveCursor (QTextCursor::End);
      activeText->insertPlainText (res->text + QString(" "));
      activeText->moveCursor (QTextCursor::End);
    }
    else {
      LOG_E("no active text... dropping\n");
    }
    if (res->result_code == Voice2Text::FINAL_TEXT) {
      dlgProgress->hide();
    }
  }
  else {
    dlgProgress->hide();
    QMessageBox msgBox(QMessageBox::Warning, "Voice Input fail", res->text);
    msgBox.exec();
  }

  delete res;
}

#define UNTITLED_NAME "Untitled"
#define FONT_SIZE     14

void AutyperMain::on_actionNew_triggered()
{

  QPlainTextEdit * e = new QPlainTextEdit(this);

  QFont f1 = e->font();
  QFontMetrics fm(f1);
  f1.setPointSize(FONT_SIZE);
  e->setFont(f1);

  QMdiSubWindow * sub = ui->mdiArea->addSubWindow(e);
  e->setWindowIcon(QIcon("images/autyper_icon.ico"));
  //ui->mdiArea->subWindowList().at(0)->setWindowIcon(QIcon(":/rec/images/autyper_icon.ico"));
  sub->setWindowIcon(QIcon(":/rec/images/autyper_icon.ico"));
  if (name_cnt++ != 0) {
    sub->setWindowTitle(QString::asprintf("%s%d.txt", UNTITLED_NAME, name_cnt++ ));
  }
  else {
    sub->setWindowTitle(QString::asprintf("%s.txt", UNTITLED_NAME ));
  }
  e->showMaximized();
  mdiList.append(e);
  activeText = e;

#ifdef OPEN_FILE_AT_STARTUP
  QString file("..\\..\\autyper\\voices\\invisibleman_Stereo_44100_32_256kbs.mp3");
  //QString file("..\\..\\autyper\\voices\\123.mp3");
#else
  QProcessEnvironment p;
  QString fp = p.systemEnvironment().value(QString("USERPROFILE"));
  QString file = QFileDialog::getOpenFileName(this,
                                               tr("Open Audio file"),
                                               fp,
                                               tr("Audio files (*.mp3 *.wav *.ogg *.flac *.aac)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);
#endif
  if (!file.isEmpty())
  {
    QString d ="Open file: " + file; // QDir::currentPath();
    LOG(d.toStdString().c_str());
    dlgProgress->update(0);
    dlgProgress->show();
    voice2Text->startConvertion(file);
  }
  else {
    LOG("Open audio file cancelled.");
  }
}
