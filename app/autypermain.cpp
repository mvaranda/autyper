
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
  ui->setupUi(this);
  setWindowTitle("AuTyper - Version " AuTyperVersion);
  modelSampleRate = Voice2Text::getModelSampleRate (QString (MODEL));
  LOG("Model samplerate = %d\n", modelSampleRate);

  // Debug only: go straight to convert a file
#ifdef OPEN_FILE_AT_STARTUP
  on_actionOpen_triggered();
#endif
}

AutyperMain::~AutyperMain()
{
  delete ui;
}

void AutyperMain::startVoice2TextThread(QString filename, FeederBase * feeder)
{
    Voice2Text *workerThread = new Voice2Text(filename, QString(MODEL), QString(SCORER), feeder);
    connect(workerThread, &Voice2Text::resultReady, this, &AutyperMain::handle_voice2text);
    //connect(workerThread, &Voice2Text::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void AutyperMain::on_actionOpen_triggered()
{
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
    FeederBase * f = NULL;
    try {
      f = FeederFactory::create(file, modelSampleRate);
    } catch (FeederBase::FeederException e) {
      QMessageBox msgBox(QMessageBox::Warning, "Voice Input fail", e.msg);
      msgBox.exec();
      delete f;
      f = NULL;
    }

    if (f == NULL) {
      LOG("Could not create a feeded");
      return;
    }

    startVoice2TextThread(file, f);
  }
  else {
    LOG("Open audio file cancelled.");
  }

}

void AutyperMain::handle_voice2text(Voice2Text::CResult * res)
{
  QString t("Text result: ");
  t = t + res->text + QString("\n");
  LOG(t.toStdString().c_str());
  LOG("progress = %d\n", res->progress);
  if ( (res->result_code == Voice2Text::PARTIAL_TEXT) ||
       (res->result_code == Voice2Text::FINAL_TEXT) ) {

  }
  else {
    QMessageBox msgBox(QMessageBox::Warning, "Voice Input fail", res->text);
    msgBox.exec();
  }

  delete res;
}
