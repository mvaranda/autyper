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

class Voice2Text: public QThread
{

private:
  Q_OBJECT
  void run(void) override;

public:
  typedef enum {
    PARTIAL_TEXT,
    FINAL_TEXT,
    ERROR_BAD_FILE,
  } Result_t;

  class CResult {
  public:
    QString   text;
    Result_t  result_code;
    CResult(Result_t code, QString txt) { text = txt; result_code = code; }
  };



  Voice2Text();
  Voice2Text( QString filename, void * handler_func, void * handler_ctx);
  Voice2Text( QString filename);

private:
  void thread(void);

signals:
    void resultReady(CResult * res);

};

#endif // VOICE2TEXT_H
