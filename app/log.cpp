
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

#include <QDebug>
#include "log.h"

void qDebugCpp(char * s) // format,...)
{
//  va_list args;
//  va_start(args, format);
//  qDebug(format, args);
//  va_end(args);
  qDebug(s);
}

extern "C" {
  void qDebugC(char * format,...)
  {
    char s[1024];
    va_list args;
    va_start(args, format);
    vsprintf (s, format, args );
    qDebugCpp(s); //format, args);
    va_end(args);
  }
}
