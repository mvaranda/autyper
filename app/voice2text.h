#ifndef VOICE2TEXT_H
#define VOICE2TEXT_H

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

#include <QThread>
#include <QAudioDecoder>
#include "feederbase.h"

#define   AUDIO_BUFFER_NUM_SAMPLES  (16 * 1024) // about 1 second (buffer is short... therefore size in bytes is double (32K)

class Voice2Text: public QThread
{

private:
  Q_OBJECT
  void run(void) override;

public:
  typedef enum {
    PARTIAL_TEXT,
    FINAL_TEXT,
    ERROR_BAD_MODEL_FILE,
    ERROR_BAD_SCORER_FILE,
  } Result_t;

  class CResult {
  public:
    QString   text;
    Result_t  result_code;
    CResult(Result_t code, QString txt) { text = txt; result_code = code; }
  };

  static uint32_t getModelSampleRate (QString filanema);

  Voice2Text();
  Voice2Text( QString filename, void * handler_func, void * handler_ctx);
  Voice2Text( QString filename, QString model, QString scorer, FeederBase * _feeder);


private:

  // private variables
  QAudioDecoder   * decoder;
  QString           filename;
  QString           model_fn;
  QString           scorer_fn;
  FeederBase      * feeder;
  sample_t          aBuffer[AUDIO_BUFFER_NUM_SAMPLES];

  // private methods
  void thread(void);
  bool convertToRaw(QString filename);

private slots:


signals:
    void resultReady(CResult * res);

};

#endif // VOICE2TEXT_H
