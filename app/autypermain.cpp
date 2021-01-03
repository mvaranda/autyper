
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
#include <QProcessEnvironment>
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <QMdiSubWindow>
#include <QStandardPaths>
#include <QFileInfo>

#include "feederfactory.h"
#include "autypermain.h"
#include "ui_autypermain.h"
#include "log.h"
#include "version.h"
#include "prefs.h"
#include "dlgmodelref.h"
#include <QDesktopServices>

#define HELP_URL      "https://github.com/mvaranda/autyper/tree/master/help"
#define UNTITLED_NAME "Untitled"
#define FONT_SIZE     14

extern int audio2text(int argc, char **argv);


/******************************************
 *
 *              Constructor
 *
 ******************************************/

AutyperMain::AutyperMain(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AutyperMain)
{
  name_cnt=0;

  ui->setupUi(this);
  setWindowTitle("AuTyper - Version " AuTyperVersion);
  dlgProgress = new DlgProgress(this);


  appDataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QString("/");
  LOGS(appDataPath);

  // We must have model setup... otherwise, we set now:
  Prefs::load();
  if ( (QFile::exists(Prefs::active_model_file) == false) ||
       (QFile::exists(Prefs::active_scorer_file) == false) ) {
    on_actionChange_Model_triggered();
  }


  voice2Text = new Voice2Text( Prefs::active_model_file,Prefs::active_scorer_file );

  connect(dlgProgress, &DlgProgress::canceReqToMain, this, &AutyperMain::handleAbortRequest);
  connect(voice2Text, &Voice2Text::resultReady, this, &AutyperMain::handle_voice2text);

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

void AutyperMain::updateUserPath(QString filePath)
{
  QDir d = QFileInfo(filePath).absoluteDir();
  Prefs::user_path = d.absolutePath();
  Prefs::save();
}

void  AutyperMain::updateUserAudioPath(QString filePath)
{
  QDir d = QFileInfo(filePath).absoluteDir();
  Prefs::user_audio_path = d.absolutePath();
  Prefs::save();
}

/******************************************
 *
 *        VoiceToText Result Handler
 *
 ******************************************/

void AutyperMain::handle_voice2text(Voice2Text::CResult * res)
{
#if 0 // log res
  QString t("Text result: ");
  t = t + res->text + QString("\n");
  LOGS(t);
  LOG("progress = %d\n", res->progress);
#endif

  if ( (res->result_code == Voice2Text::PARTIAL_TEXT) ||
       (res->result_code == Voice2Text::FINAL_TEXT) ) {
    dlgProgress->update(res->progress);
    if (activeText) {
      activeText->moveCursor (QTextCursor::End);
      if (res->result_code == Voice2Text::FINAL_TEXT) {
        activeText->insertPlainText (res->text + QString("\n"));
      }
      else {
        activeText->insertPlainText (res->text + QString(" "));
      }
      activeText->moveCursor (QTextCursor::End);
    }
    else {
      LOG_E("no active text... dropping\n");
    }
    if (res->result_code == Voice2Text::FINAL_TEXT) {
      dlgProgress->hide();
      enableConvControls();
    }
  }
  else {
    dlgProgress->hide();
    QMessageBox msgBox(QMessageBox::Warning, "Voice Input fail", res->text);
    msgBox.exec();
    enableConvControls();
  }

  delete res;
}


void AutyperMain::on_actionOpen_triggered()
{
  QString qPath = QFileDialog::getOpenFileName(this,
                                               tr("Open text file"),
                                               Prefs::user_path,
                                               tr("Text files (*.txt *.*)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (qPath.isEmpty())
  {
    return;
  }

  updateUserPath(qPath);

  QFile file(qPath);

  file.open(QFile::ReadOnly | QFile::Text);

  QTextStream ReadFile(&file);
  QString  content = ReadFile.readAll();

  QPlainTextEdit * e = new QPlainTextEdit(this);

  QFont f1 = e->font();
  QFontMetrics fm(f1);
  f1.setPointSize(FONT_SIZE);
  e->setFont(f1);

  QMdiSubWindow * sub = ui->mdiArea->addSubWindow(e);
  sub->setWindowIcon(QIcon(":/rec/images/autyper_icon.ico"));

  sub->setWindowTitle(qPath);

  e->setPlainText(content);
  e->showMaximized();
  mdiList.append(e);
  activeText = e;
}

void AutyperMain::on_actionNew_triggered()
{

  QPlainTextEdit * e = new QPlainTextEdit(this);

  QFont f1 = e->font();
  QFontMetrics fm(f1);
  f1.setPointSize(FONT_SIZE);
  e->setFont(f1);

  QMdiSubWindow * sub = ui->mdiArea->addSubWindow(e);
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

  QString file = QFileDialog::getOpenFileName(this,
                                               tr("Open Audio file"),
                                               Prefs::user_audio_path,
                                               tr("Audio files (*.mp3), // to be added later:  *.wav *.ogg *.flac *.aac)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (!file.isEmpty())
  {
    updateUserAudioPath(file);
    QString d ="Open file: " + file; // QDir::currentPath();
    LOGS(d);
    dlgProgress->update(0);
    dlgProgress->show();
    disableConvControls();
    voice2Text->startConvertion(file);
  }
  else {
    LOG("Open audio file cancelled.");
  }
}

void AutyperMain::on_actionSave_triggered()
{
  QMdiSubWindow * sub = nullptr;
  if ((sub = ui->mdiArea->activeSubWindow()) == nullptr) {
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "No Text Window selected");
    msgBox.exec();
    return;
  }

  QPlainTextEdit * e = sub->findChild<QPlainTextEdit *>();
  if (e == nullptr) {
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "unexpected empty window");
    msgBox.exec();
    return;
  }

  LOGS(e->toPlainText());

  QProcessEnvironment p;
  QString fp = p.systemEnvironment().value(QString("USERPROFILE"));
  QString qPath = QFileDialog::getSaveFileName(this,
                                               tr("Text file-name to be saved"),
                                               Prefs::user_path,
                                               tr("Text files (*.txt *.*)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (qPath.isEmpty())
  {
    return;
  }

  updateUserPath(qPath);

  QFile qFile(qPath);
  if (qFile.open(QIODevice::WriteOnly)) {
    QTextStream out(&qFile); out << e->toPlainText();
    qFile.close();
  }
  else {
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "fail to open file to write");
    msgBox.exec();
  }

  sub->setWindowTitle(qPath);

}

void  AutyperMain::enableConvControls(void)
{
  ui->actionNew->setEnabled(true);
  ui->actionAppend_Voice->setEnabled(true);
}

void  AutyperMain::disableConvControls(void)
{
  ui->actionNew->setEnabled(false);
  ui->actionAppend_Voice->setEnabled(false);
}

void AutyperMain::on_actionChange_Model_triggered()
{
    DlgModelRef d(this);
    d.setModal(true);
    d.exec();

    if ( (QFile::exists(Prefs::active_model_file) == false) ||
         (QFile::exists(Prefs::active_scorer_file) == false) ) {
      disableConvControls();
    }
    else {
      enableConvControls();
      voice2Text->updateModel(Prefs::active_model_file, Prefs::active_scorer_file);
    }

}

void AutyperMain::on_actionAppend_Voice_triggered()
{
  QMdiSubWindow * sub = nullptr;
  if ((sub = ui->mdiArea->activeSubWindow()) == nullptr) {
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "No Text Window selected");
    msgBox.exec();
    return;
  }

  QPlainTextEdit * e = sub->findChild<QPlainTextEdit *>();
  if (e == nullptr) {
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "unexpected empty window");
    msgBox.exec();
    return;
  }
  activeText = e;

  QString file = QFileDialog::getOpenFileName(this,
                                               tr("Open Audio file"),
                                               Prefs::user_audio_path,
                                               tr("Audio files (*.mp3), // to be added later:  *.wav *.ogg *.flac *.aac)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (!file.isEmpty())
  {
    updateUserAudioPath(file);
    QString d ="Open file: " + file; // QDir::currentPath();
    LOGS(d);
    dlgProgress->update(0);
    dlgProgress->show();
    disableConvControls();
    voice2Text->startConvertion(file);
  }
  else {
    LOG("Open audio file cancelled.");
  }

}

void AutyperMain::on_actionHelp_triggered()
{
  QDesktopServices::openUrl ( QUrl(HELP_URL) );
}
