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

#include "voice2text.h"
#include "log.h"
#include <stdio.h>

Voice2Text::Voice2Text(): decoder(NULL)
{

}



void Voice2Text::run (void)
{
  QString result_txt("Hello");
  /* ... here is the expensive or blocking operation ... */
  CResult * res = new CResult(FINAL_TEXT, QString("Hello guys") );
  emit resultReady(res);
  convertToRaw(filename);
}

Voice2Text::Voice2Text( QString filename, void * handler_func, void * handler_ctx)
{
//  connect(this, &Voice2Text::resultReady, (QObject *) handler_ctx, handler_func);
//  connect(this, &Voice2Text::finished, this, &QObject::deleteLater);
//  start();
}

Voice2Text::Voice2Text( QString filename)
{
  this->filename = filename;
  convertToRaw(filename);
}

void cppProtocolInit(void)
{
}

//----------- Convert to Raw temp file ---------
void Voice2Text::convReadBuffer(void)
{
  char log_txt[64];
  QAudioBuffer buf = decoder->read();
  if ( buf.byteCount() == 0) {
    LOG_E("convReadBuffer: buffer with no data");
    return;
  }
  sprintf(log_txt, "buf data size = %d", buf.byteCount());
  LOG(log_txt);
}

void Voice2Text::convFinished(void)
{
  LOG("convFinished");
}

void Voice2Text::convError(void)
{
  LOG("convError");
}

bool Voice2Text::convertToRaw(QString filename) {
  QAudioFormat desiredFormat;
  desiredFormat.setChannelCount(1);
  desiredFormat.setCodec("audio/x-raw");
  desiredFormat.setSampleType(QAudioFormat::SignedInt); // UnSignedInt);
  desiredFormat.setSampleRate(16000);
  desiredFormat.setSampleSize(16);

  decoder = new QAudioDecoder(this);
  decoder->setAudioFormat(desiredFormat);
  decoder->setSourceFilename(filename);

  connect(decoder, SIGNAL(bufferReady()), this, SLOT(convReadBuffer())); // finished error
  connect(decoder, SIGNAL(finished()), this, SLOT(convFinished())); // finished error
  connect(decoder, SIGNAL(Error()), this, SLOT(convError())); // finished error
  decoder->start();
}

