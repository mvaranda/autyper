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

#include <QFileInfo>

#include "feederfactory.h"
#include "feeder_mp3.h"
#include "log.h"

//FeederFactory::FeederFactory()
//{

//}

FeederBase * FeederFactory::create(QString input, uint32_t model_samplerate)
{
  FeederBase * ret = NULL;
  QFileInfo fn(input);
  QString s = fn.suffix().toLower();

  if (s == QString("mp3")) {
    LOG("create MP3 feeder");
    ret = (FeederBase *) new FeederMp3(input, model_samplerate);
  }
  else if (s == QString("wav")) {
    LOG("create Wave feeder");
    //ret = (FeederBase *) new FeederMp3(input);
  }

  return ret;
}

