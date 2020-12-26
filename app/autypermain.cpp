
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

extern int audio2text(int argc, char **argv);

#if 1
static const char * args [7] = {
  "test",
  "--model",
  "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.pbmm",
  "--scorer",
  "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.scorer",
  "--audio",
  "..\\..\\autyper\\deepspeech\\models\\2830-3980-0043.wav" };
#else
static const char * args [7] = {
  "test",
  "--model",
  "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.pbmm",
  "--scorer",
  "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.scorer",
  "--audio",
  "c:\\Users\\mvaranda\\voices\\invisibleman_Mono_16000_16_64kbs.wav" };
#endif

AutyperMain::AutyperMain(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AutyperMain)
{
  ui->setupUi(this);
  startVoice2TextThread(QString("C:\\Users\\mvaranda\\voices\\invisibleman_Mono_22050_32_64kbs_short.wav"));
}

AutyperMain::~AutyperMain()
{
  delete ui;
}

void AutyperMain::startVoice2TextThread(QString filename)
{
    Voice2Text *workerThread = new Voice2Text(filename);
    connect(workerThread, &Voice2Text::resultReady, this, &AutyperMain::handle_voice2text);
    //connect(workerThread, &Voice2Text::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void AutyperMain::on_actionOpen_triggered()
{
#if 0
  LOG("Open...");
  QString d ="Current dir: "+  QDir::currentPath();
  LOG(d.toStdString().c_str());
  ::audio2text(7, (char **) args);
#else
  QProcessEnvironment p;
  QString fp = p.systemEnvironment().value(QString("USERPROFILE"));
  QFileInfo fi(fp);
  QString file = QFileDialog::getOpenFileName(this,
                                               tr("Open Audio file"),
                                               fp,
                                               tr("Audio files (*.mp3 *.wav *.ogg *.flac *.aac)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (!file.isEmpty())
  {
    QString d ="Open file: " + file; // QDir::currentPath();
    LOG(d.toStdString().c_str());
  }
  else {
    LOG("Open audio file cancelled.");
  }
#endif
}

void AutyperMain::handle_voice2text(Voice2Text::CResult * res)
{
  QString t("Text result: ");
  t = t + res->text + QString("\n");
  LOG(t.toStdString().c_str());
  delete res;
}
