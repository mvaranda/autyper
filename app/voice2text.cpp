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


  CResult * res = new CResult(FINAL_TEXT, QString("All done!") );
  emit resultReady(res);

}

Voice2Text::Voice2Text( QString filename, void * handler_func, void * handler_ctx)
{

}

Voice2Text::Voice2Text( QString filename, FeederBase * _feeder)
{
  this->filename = filename;
  feeder =_feeder;
}

void cppProtocolInit(void)
{
}

