#ifndef FEEDERBASE_H
#define FEEDERBASE_H
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


#include <stdint.h>
#include <stdbool.h>
#include <QString>

extern "C" {
int resample( const char * filename, unsigned int samplerate_in,
              const char * file_out, unsigned int samplerate_out);
}

typedef enum {
  FEEDER_T__MICROPHONE,
  FEEDER_T__MP3,
  FEEDER_T__WAVE,
} feeder_t;

typedef enum {
  FEEDER_RES__OK,
  FEEDER_RES__ALL_DONE,
  FEEDER_RES__ERROR,
} feeder_res_t;

typedef short sample_t;

#define RESAMPLE_NUM_SAMPLES (1024 * 2)

class FeederBase
{
public:
  class FeederException {
  public:
    FeederException();
    FeederException(const char * m, int v) { msg = m; exception_code = v; }
    const char *  msg;
    int           exception_code;
  };
  //-------- public methods ------

  FeederBase(QString input_name);
  virtual ~FeederBase() {}
  feeder_t getType(void);
  QString getInputName(void);
  virtual feeder_res_t getSamples(sample_t * samples, uint32_t num_samples, int progress) = 0;

private:
  //-------- private methods ------
//  int resample(  char * filename, unsigned int samplerate_in,
//                       char * file_out, unsigned int samplerate_out);

  //-------- private vaiables ---------
  feeder_t      feeder_type;
  QString       input;
//  sample_t      bufin[RESAMPLE_NUM_SAMPLES]; // for resample

protected:
  FeederBase();
};

#endif // FEEDERBASE_H
