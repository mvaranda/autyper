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

#include <QProcessEnvironment>
#include <stdio.h>
#include "feeder_mp3.h"
#include "log.h"

FeederMp3::FeederMp3(QString input, uint32_t model_samplerate):FeederBase(input, model_samplerate)
{
  QProcessEnvironment p;
  QString fp = p.systemEnvironment().value(QString("TEMP"));
  samples_fh = convertMp3ToRaw(input.toStdString().c_str(), (const char *) fp.toStdString().c_str(), modelSamplerate);
  if (samples_fh == NULL) {
    throw FeederException("Fail to convert MP3 file", 0);
  }

  fseek(samples_fh, 0, SEEK_END);
  samples_file_size = ftell(samples_fh);
  fseek(samples_fh, 0, SEEK_SET);
}

